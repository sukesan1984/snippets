from langgraph.prebuilt import create_react_agent

def get_weather(city: str) -> str:
    """Get weather for a given city."""
    return f"It's always sunny in {city}!"

def main():
    agent = create_react_agent(
            model="anthropic:claude-3-7-sonnet-latest",
            tools=[get_weather],
            prompt="You are a helpful assistant"
    )
    result = agent.invoke(
        {"messages": [
                {
                    "role": "user",
                    "content": "what is the weather in sf"
                }
            ]
         }
    )
    print(result)



if __name__ == "__main__":
    main()
