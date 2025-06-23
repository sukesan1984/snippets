from typing import Annotated
from typing_extensions import TypedDict
from langgraph.graph import StateGraph, START
from langgraph.graph.message import add_messages
from langgraph.graph.state import CompiledStateGraph
from langchain.chat_models import init_chat_model
from langchain.chat_models.base import BaseChatModel

class State(TypedDict):
    # Messages have the type "list". The `add_messages` function
    # in the annotation defines how this state key should be updated
    # (in this case, it appends messages to the list, rather than overwriting them)
    messages: Annotated[list, add_messages]
    llm: BaseChatModel

def chatbot(state: State):
    llm = state.get("llm")
    return {"messages": [llm.invoke(state["messages"])]}


def stream_graph_updates(graph: CompiledStateGraph, llm: BaseChatModel, user_input: str):
    for event in graph.stream({
            "llm": llm,
            "messages": [{"role": "user", "content": user_input}]
        }):
        for value in event.values():
            print("Assistant:", value["messages"][-1].content)

def main():
    graph_builder = StateGraph(State)
    graph_builder.add_node("chatbot", chatbot)
    graph_builder.add_edge(START, "chatbot")
    graph = graph_builder.compile()
    llm = init_chat_model("openai:gpt-4.1")
    while True:
        try:
            user_input = input("User: ")
            if user_input.lower() in ["quit", "exit", "q"]:
                print("Goodbye!")
                break
            stream_graph_updates(graph, llm, user_input)
        except:
            user_input = "LangGraphの何が知りたいですか"
            print("User: " + user_input)
            stream_graph_updates(graph, llm, user_input)
            break
    


    


if __name__ == "__main__":
    main()
