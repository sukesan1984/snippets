import json
from typing import Annotated

from langchain.chat_models import init_chat_model
from langchain.chat_models.base import BaseChatModel
from langchain_core.messages import ToolMessage
from langchain_core.runnables import Runnable
from langchain_tavily import TavilySearch
from langgraph.graph import START, StateGraph
from langgraph.graph.message import add_messages
from langgraph.graph.state import CompiledStateGraph
from typing_extensions import TypedDict


class BasicToolNode:
    """A node that runs the tools requeste in the last AIMessage."""

    def __init__(self, tools: list) -> None:
        self.tools_by_name = {tool.name: tool for tool in tools}

    def __call__(self, inputs: dict):
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


def chatbot(state: State):
    llm = state.get("llm")
    return {"messages": [llm.invoke(state["messages"])]}


def stream_graph_updates(graph: CompiledStateGraph, llm: Runnable, user_input: str):
    for event in graph.stream(
        {"llm": llm, "messages": [{"role": "user", "content": user_input}]}
    ):
        for value in event.values():
            print("Assistant:", value["messages"][-1].content)


def main():
    tool = TavilySearch(max_results=2)
    tools = [tool]
    tool.invoke("What's a 'node' in LangGraph?")
    tool_node = BasicToolNode(tools=[tool])
    graph_builder = StateGraph(State)
    graph_builder.add_node("tools", tool_node)
    graph_builder.add_node("chatbot", chatbot)
    graph_builder.add_edge(START, "chatbot")
    graph = graph_builder.compile()
    llm = init_chat_model("openai:gpt-4.1")
    llm_with_tools = llm.bind_tools(tools)
    while True:
        try:
            user_input = input("User: ")
            if user_input.lower() in ["quit", "exit", "q"]:
                print("Goodbye!")
                break
            stream_graph_updates(graph, llm_with_tools, user_input)
        except:
            user_input = "LangGraphの何が知りたいですか"
            print("User: " + user_input)
            stream_graph_updates(graph, llm_with_tools, user_input)
            break


if __name__ == "__main__":
    main()
