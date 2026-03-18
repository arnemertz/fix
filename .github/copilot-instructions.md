# Copilot Instructions

See [AGENTS.md](../AGENTS.md) for project overview, tech stack, and pointers to detailed instructions.

Agent definitions live in [.ai/agents/](../.ai/agents/) and topic-specific rules in [.ai/instructions/](../.ai/instructions/).

## C++ Qualified Names in Chat

When mentioning C++ qualified names (namespaces, types) in chat, write them in a fenced code block to avoid the VS chat rendering issue where `::` inside inline backticks gets interpreted as search links.

Example: use

```
fix::domain::title
```

instead of `` `fix::domain::title` ``.
