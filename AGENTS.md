# AGENTS.md — Project Guide for AI Agents

> **For AI agents:** This is the single source of truth for project overview, tech stack, and pointers to detailed instructions. Topic-specific rules live in `.ai/instructions/` and are referenced below.

## Project Overview

**Fix** is a lightweight issue tracker, built as a personal learning and practice project for modern C++ techniques, libraries, and tooling. The author blogs about development progress at <http://arne-mertz.de/category/fix/>.

---

## Repository Structure

```
fix/
├── src/
│   ├── main.cpp              # Entry point
│   ├── fix_cli/              # CLI layer (namespace fix::cli)
│   └── domain/               # Domain model (namespace fix::domain)
├── test/
│   ├── catch_main.cpp        # Catch2 main
│   ├── fix_cli/              # Unit tests for CLI layer
│   └── domain/               # Unit tests for domain layer
├── behave/                   # BDD integration tests (Python/behave)
│   ├── *.feature             # Gherkin feature files
│   └── steps/                # Step implementations
├── cmake/                    # CMake utility modules
├── docs/                     # Jekyll-based developer diary / blog
├── scripts/                  # Helper shell scripts
└── .ai/                      # AI agent and instruction files
    ├── agents/               # Agent role definitions
    └── instructions/         # Topic-specific project rules
```

---

## Tech Stack

| Concern            | Tool / Library                          |
|--------------------|-----------------------------------------|
| Language standard  | C++23                                   |
| Build system       | CMake ≥ 3.15, Ninja generator           |
| Package manager    | Conan 2 (`conanfile.txt`)               |
| Unit testing       | Catch2 v2 (`catch2/2.13.10`)            |
| Integration tests  | Python `behave` (BDD / Gherkin)         |
| CLI parsing        | CLI11 (`cli11/2.3.2`)                   |
| Static analysis    | clang-tidy (`.clang-tidy`)              |
| Formatting         | clang-format (`.clang-format`, LLVM based, 120-col limit) |
| Error handling     | `std::expected` (via `fix::domain::expected<T>` alias) |

---

## Agent Team

| Agent | File | Role |
|-------|------|------|
| Product Owner | [product-owner.md](.ai/agents/product-owner.md) | Requirements, task decomposition, orchestration |
| Architect | [architect.md](.ai/agents/architect.md) | Design proposals, DDD guidance, user collaboration |
| Coder | [coder.md](.ai/agents/coder.md) | C++ implementation |
| Tester | [tester.md](.ai/agents/tester.md) | Catch2 unit tests, behave BDD tests |
| Reviewer | [reviewer.md](.ai/agents/reviewer.md) | Code review, static analysis, convention checks |
| Toolsmith | [toolsmith.md](.ai/agents/toolsmith.md) | CMake, Conan, CI/CD, tooling |

---

## General Agent Rules

- **No out-of-repository side effects**: No agent may perform any action with effects outside the repository (e.g., modifying global git or shell configuration, installing system packages, changing environment variables, writing files outside the repo root) unless the user has **explicitly requested** it. When in doubt, ask first rather than act.

---

## Detailed Instructions

Topic-specific rules are maintained in `.ai/instructions/` to avoid duplication. All agents reference these as needed.

| Topic | File |
|-------|------|
| C++ Code Style | [cpp-code-style.md](.ai/instructions/cpp-code-style.md) |
| Architecture | [architecture.md](.ai/instructions/architecture.md) |
| Testing | [testing.md](.ai/instructions/testing.md) |
| Git Workflow | [git-workflow.md](.ai/instructions/git-workflow.md) |
| Build & Dependencies | [build-and-dependencies.md](.ai/instructions/build-and-dependencies.md) |
