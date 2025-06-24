import json
from typing import Annotated

from langchain.chat_models import init_chat_model
from langchain.chat_models.base import BaseChatModel
from langchain_core.messages import ToolMessage
from langchain_core.runnables import Runnable, RunnableConfig
from langchain_core.tools import tool
from langchain_tavily import TavilySearch
from langgraph.checkpoint.memory import MemorySaver
from langgraph.graph import END, START, StateGraph
from langgraph.graph.message import add_messages
from langgraph.graph.state import CompiledStateGraph
from langgraph.prebuilt import ToolNode, tools_condition
from langgraph.types import Command, interrupt
from typing_extensions import TypedDict


class BasicToolNode:
    """A node that runs the tools requeste in the last AIMessage."""

    def __init__(self, tools: list) -> None:
        self.tools_by_name = {tool.name: tool for tool in tools}

    def __call__(self, inputs: dict):
        print("BasicToolNode.__call__")
        if messages := inputs.get("messages", []):
            message = messages[-1]
        else:
            raise ValueError("No message found in input")
        outputs = []
        for tool_call in message.tool_calls:
            tool_result = self.tools_by_name[tool_call["name"]].invoke(
                tool_call["args"]
            )
            outputs.append(
                ToolMessage(
                    content=json.dumps(tool_result),
                    name=tool_call["name"],
                    tool_call_id=tool_call["id"],
                )
            )

        return {"messages": outputs}


class State(TypedDict):
    # Messages have the type "list". The `add_messages` function
    # in the annotation defines how this state key should be updated
    # (in this case, it appends messages to the list, rather than overwriting them)
    messages: Annotated[list, add_messages]
    llm: BaseChatModel


@tool
def human_assistance(query: str) -> str:
    """Request assistance from a human."""
    human_response = interrupt({"query": query})
    if human_response is None:
        return "人間からの応答を待っています..."
    if isinstance(human_response, dict) and "data" in human_response:
        return human_response["data"]
    elif isinstance(human_response, str):
        return human_response
    else:
        return str(human_response)


def route_tools(
    state: State,
):
    """
    Use in the conditional_edge to route to the ToolNode if the last message
    has tool calls. Otherwise, route to the end.
    """
    messages = state["messages"]
    last_message = messages[-1]
    # If the last message has tool calls, then we route to the "tools" node

    if last_message.tool_calls:
        return "tools"
    return END


def chatbot(state: State):
    llm = state.get("llm")
    message = llm.invoke(state["messages"])
    return {"messages": [message]}


def stream_graph_updates(
    graph: CompiledStateGraph, llm: Runnable, user_input: str, config: RunnableConfig
):
    for event in graph.stream(
        {"llm": llm, "messages": [{"role": "user", "content": user_input}]},
        config,
        # stream_mode="values",
    ):
        if "__interrupt__" in event:
            # Handle interrupt
            interrupt_data = event["__interrupt__"][0]
            print("Human assistance requested:", interrupt_data.value["query"])
            # Get human response
            human_response = input("Your response: ")
            # Resume with the response
            for resume_event in graph.stream(Command(resume={"data": human_response}), config):
                for value in resume_event.values():
                    if "messages" in value and value["messages"]:
                        print("Assistant:", value["messages"][-1].content)
        else:
            for value in event.values():
                if "messages" in value and value["messages"]:
                    print("Assistant:", value["messages"][-1].content)


def main():
    memory = MemorySaver()
    tool = TavilySearch(max_results=2)
    tools = [tool, human_assistance]
    tool.invoke("What's a 'node' in LangGraph?")
    tool_node = ToolNode(tools=tools)
    graph_builder = StateGraph(State)
    graph_builder.add_node("tools", tool_node)
    graph_builder.add_node("chatbot", chatbot)
    graph_builder.add_edge(START, "chatbot")
    graph_builder.add_edge("tools", "chatbot")
    graph_builder.add_conditional_edges(
        "chatbot",
        tools_condition,
        # route_tools,
        # {"tools": "tools", END: END},
    )
    graph = graph_builder.compile(checkpointer=memory)
    llm = init_chat_model("openai:gpt-4.1")
    llm_with_tools = llm.bind_tools(tools)
    config = RunnableConfig({"configurable": {"thread_id": "1"}})
    while True:
        try:
            user_input = input("User: ")
            if user_input.lower() in ["quit", "exit", "q"]:
                print("Goodbye!")
                break
            stream_graph_updates(graph, llm_with_tools, user_input, config)
        except:
            user_input = "LangGraphの何が知りたいですか"
            print("User: " + user_input)
            stream_graph_updates(graph, llm_with_tools, user_input, config)
            break


if __name__ == "__main__":
    main()
