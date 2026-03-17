# AGENTS.md — Project Guide for AI Agents

> **For AI agents:** This is the single source of truth for project guidelines, coding conventions, and workflow rules. Always extend *this file* when recording new preferences or instructions.

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
└── scripts/                  # Helper shell scripts
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

## Code Style

### General
- **East const**: `char const*`, `int const&` — not `const char*`, `const int&`.
- Pointer alignment: left (`int* p`, not `int *p`).
- Column limit: 120 characters.
- Header guards: `#ifndef FIX_<PATH>_<FILE>_HPP` / `#define` / `#endif` with comment.
- Apply `[[nodiscard]]` by default to all non-`void` functions.
- Mark functions `constexpr` wherever possible.

### Member variables
- Plain `snake_case`, no prefix or suffix.

### Namespaces
- `fix::domain` — domain model classes and application service.
- `fix::cli` — CLI application layer.

### Error handling
- Use `std::expected<T, std::error_code>` (aliased as `fix::domain::expected<T>`) for fallible operations.
- Domain error codes are defined in `fix::domain::domain_error` (an `enum class` registered with `std::error_code`).

### Construction pattern
- Direct construction is acceptable when no validation is required.
- Use a private constructor + `static expected<T> create(...)` factory only when construction can fail and inputs must be validated.
- `cppcheck-suppress functionStatic` is used where cppcheck false-positives on methods that will become non-static later.

### Formatting
- Formatting is handled by clang-format (`.clang-format`, LLVM base style).
- `// clang-format off` / `on` guards are acceptable for ranges pipelines and similar constructs.

---

## Naming Conventions

- **Files**: `snake_case.cpp` / `snake_case.hpp`.
- **Types / classes**: `snake_case` (e.g., `application_service`, `issue_id`).
- **Functions / methods**: `snake_case`.
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MIN_LENGTH`, `MAX_LENGTH`).
- **Test case names**: end with `"..."` if the test case contains sections.
- **Section names**: start with `"..."`.

---

## Testing

### Unit tests (Catch2)
- Located under `test/`.
- Test file naming convention: `<module>_test.cpp`. If there is no clear primary unit under test, ask for guidance.
- A shared `catch_main` static library provides the Catch2 runner.
- `test/.clang-tidy` relaxes `readability-function-cognitive-complexity` for test files.
- Run via CTest: `ctest --test-dir <build_dir> --output-on-failure`

### Integration tests (behave)
- Located under `behave/`; feature files use Gherkin, step implementations are in `behave/steps/`.
- Scenarios tagged `@wip` are work-in-progress; scenarios tagged `@skip` are skipped.
- Run **stable** tests (excludes `@wip` and `@skip`):
  ```powershell
  behave -t ~skip -t ~wip
  ```
- Run **WIP** tests only:
  ```powershell
  behave -t wip --no-capture --no-logcapture
  ```
- Both are registered as CTest targets (`behave_stable_tests`, `behave_wip_tests`) in `behave/CMakeLists.txt`.

### Pre-commit rule
**Before every commit, run the unit tests and `behave_stable_tests`. Only commit if all of them pass.**

---

## Git Workflow

- **Branching strategy**: trunk-based development. Commit directly to `main`.
- **Commit size**: atomic commits; do not exceed ~100 lines of change per commit.
- Commit messages must be concise and must not note what *didn't* change.
- Never amend commits or rewrite git history without an explicit request. Only use `git commit --amend` or `git rebase` when specifically asked.

---

## Static Analysis & Sanitizers

- clang-tidy is configured in `.clang-tidy` (most checks enabled; fuchsia, google, zircon, abseil, llvm, altera checks excluded).
- Sanitizers (ASAN, UBSAN) and clang-tidy are **not yet run in CI** but should be. When setting up CI, enable them.
- Doxygen is scaffolded but **not actively used**; do not add Doxygen comment blocks.

---

## Build & Dependencies

1. Conan 2 is invoked automatically during CMake configure if dependencies are not yet installed.
2. Conan output folder: `<build_dir>/build/generators/`.
3. To build manually:
   ```powershell
   cmake -S . -B out/build -G Ninja -DCMAKE_BUILD_TYPE=Debug
   cmake --build out/build
   ```
4. Testing:
   ```powershell
   ctest --test-dir out/build --output-on-failure
   ```

---

## C++ Qualified Names in Chat

When mentioning C++ qualified names (namespaces, types) in chat or documentation, write them in a fenced code block to avoid rendering issues where `::` inside inline backticks is misinterpreted as search links.

Example: use
```
fix::domain::title
```
instead of `` `fix::domain::title` ``.
