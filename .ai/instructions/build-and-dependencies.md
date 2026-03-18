# Build & Dependencies

For general build instructions (prerequisites, Conan install, CMake configure, Visual Studio integration), see [BUILD.md](../../BUILD.md).

This file covers agent-specific knowledge beyond the general build procedure.

## Conan Auto-invocation

- Conan is invoked automatically during CMake configure if dependencies are not yet installed. Agents do not need to run Conan manually.
- Conan output folder: `<build_dir>/build/generators/`.

## Dependencies

| Library | Package              |
|---------|----------------------|
| Catch2  | `catch2/2.13.10`     |
| CLI11   | `cli11/2.3.2`        |

## Static Analysis & Sanitizers

- clang-tidy is configured in `.clang-tidy` (most checks enabled; fuchsia, google, zircon, abseil, llvm, altera checks excluded).
- Sanitizers (ASAN, UBSAN) and clang-tidy are **not yet run in CI** but should be. When setting up CI, enable them.
- Doxygen is scaffolded but **not actively used**; do not add Doxygen comment blocks.
