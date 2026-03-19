# Architecture

## Design Approach

This project follows Domain-Driven Design (DDD) principles with a clear separation between the domain model and application/infrastructure layers.

## Layer Structure

```
src/
├── main.cpp              # Entry point — wires layers together
├── domain/               # Domain model (namespace fix::domain)
│   └── ...               # Value objects, entities, domain services, application service
└── fix_cli/              # CLI layer (namespace fix::cli)
    └── ...               # CLI parsing, user interaction, delegates to domain
```

## Layer Rules

- **Domain layer** (`fix::domain`): Contains the core business logic — value objects, entities, domain services, and the application service. Must have **no dependencies** on UI, persistence, or framework code.
- **CLI layer** (`fix::cli`): Handles command-line parsing (via CLI11) and user interaction. Depends on the domain layer. Translates between CLI input/output and domain operations.
- **Entry point** (`main.cpp`): Wires the layers together. Minimal logic.

## Key Patterns

- **Value objects** with validation use the `create()` factory pattern (private constructor + `static expected<T> create(...)`). See [cpp-code-style.md](cpp-code-style.md) for details.
- **Error handling** uses `std::expected<T, std::error_code>` throughout the domain layer.
- **Repository pattern** (hexagonal architecture): Domain defines repository interfaces (ports); infrastructure provides concrete implementations (adapters).
- **Dependency injection**: Application service takes repository interfaces via constructor; CLI layer constructs and injects concrete implementations.
- New layers (e.g., alternative UIs) should be added as separate directories/namespaces alongside existing layers, never inside the domain layer.

## Persistence

### Storage Format

**TOML** is used for human-readable, diff-friendly storage of Fix data. Issues are stored one-per-file in `.fix/issues/<issue-id>.toml`.

**Rationale**: JSON was considered but TOML provides better readability and Git-diff clarity. The `toml++` library is header-only, well-maintained, and integrates easily.

**Schema** (current):
```toml
title = "Issue title here"
description = """
Multi-line description
"""
# Future: status field will be added here
```

### Repository Implementation

The `issue_repository` interface (port) lives in the domain layer. The `toml_issue_repository` concrete implementation lives in the infrastructure layer and handles all file I/O and TOML serialization/deserialization.

## Architecture Decisions

When proposing changes that affect layer boundaries, introduce new dependencies, or add new layers, always present the design to the user for approval before implementation.
