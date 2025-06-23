from langgraph.checkpoint.memory import InMemorySaver
from langchain.chat_models import init_chat_model
from langgraph.prebuilt import create_react_agent
from langchain_core.messages import AnyMessage
from langchain_core.runnables import RunnableConfig
from langgraph.prebuilt.chat_agent_executor import AgentState
from pydantic import BaseModel

class WeatherResponse(BaseModel):
    conditions: str

def get_weather(city: str) -> str:
    """Get weather for a given city."""
    return f"It's always sunny in {city}!"

def prompt(state: AgentState, config: RunnableConfig) -> list[AnyMessage]:
    user_name = config["configurable"].get("user_name")
    system_msg = f"You are a helpful assistant. Address the user as {user_name}."
    return [{"role": "system", "content": system_msg}] + state["messages"]

def main():
    model = init_chat_model(
        "anthropic:claude-3-7-sonnet-latest",
        temperature=0
    )

    checkpointer = InMemorySaver()

    agent = create_react_agent(
            model=model,
            tools=[get_weather],
            prompt="You are a helpful assistant",
            checkpointer=checkpointer,
            response_format=WeatherResponse
    )
    config = {"configurable": {
            "user_name": "John Smith",
            "thread_id": "1"
        }
    }
    sf_response = agent.invoke(
        {"messages": [
                {
                    "role": "user",
                    "content": "what is the weather in sf"
                }
            ]
         },
        config=config
    )

    ny_response = agent.invoke(
        {"messages": [
                {
                    "role": "user",
                    "content": "what about new yourk?"
                }
            ]
         },
        config=config
    )

    print(sf_response["structured_response"])
    print(ny_response["structured_response"])


if __name__ == "__main__":
    main()
