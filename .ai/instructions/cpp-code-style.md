# C++ Code Style

## Baseline

Follow [Jason Turner's C++ best practices](https://github.com/lefticus/cppbestpractices) as a baseline. The project-specific rules below take precedence where they overlap or extend it.

## General Rules

- Header guards: `#ifndef FIX_<PATH>_<FILE>_HPP` / `#define` / `#endif` with comment.

## Naming Conventions

- **Files**: `snake_case.cpp` / `snake_case.hpp`.
- **Types / classes**: `snake_case` (e.g., `application_service`, `issue_id`).
- **Functions / methods**: `snake_case`.
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MIN_LENGTH`, `MAX_LENGTH`).
- **Member variables**: plain `snake_case`, no prefix or suffix.

## Namespaces

- `fix::domain` — domain model classes and application service.
- `fix::cli` — CLI application layer.

## Error Handling

- Use `std::expected<T, std::error_code>` (aliased as `fix::domain::expected<T>`) for fallible operations.
- Domain error codes are defined in `fix::domain::domain_error` (an `enum class` registered with `std::error_code`).

## Construction Patterns

- Direct construction is acceptable when no validation is required.
- Use a private constructor + `static expected<T> create(...)` factory only when construction can fail and inputs must be validated.
- `cppcheck-suppress functionStatic` is used where cppcheck false-positives on methods that will become non-static later.

## Formatting

- Formatting is handled by clang-format (`.clang-format`, LLVM base style).
- `// clang-format off` / `on` guards are acceptable for ranges pipelines and similar constructs.
