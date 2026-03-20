# Build & Dependencies

For general build instructions (prerequisites, Conan install, CMake configure, Visual Studio integration), see [BUILD.md](../../BUILD.md).

This file covers agent-specific knowledge beyond the general build procedure.

## Conan Setup

- Conan **must be run manually** before CMake configure. CMake will fail with a clear error if the toolchain is missing.
- CWD for the `conan install` command: `<fix-root>` (repository root).
- Command: `conan install . --output-folder=. --build=missing -s build_type=<Debug|Release> -s compiler.cppstd=23`
- Generators output to `<fix-root>/build/generators/`; CMake binary dir is `<fix-root>/build/`.
- Re-run whenever `conanfile.txt` changes.

## Dependencies

| Library | Package              |
|---------|----------------------|
| Catch2  | `catch2/2.13.10`     |
| CLI11   | `cli11/2.3.2`        |

## Static Analysis & Sanitizers

- clang-tidy is configured in `.clang-tidy` (most checks enabled; fuchsia, google, zircon, abseil, llvm, altera checks excluded).
- Sanitizers (ASAN, UBSAN) and clang-tidy are **not yet run in CI** but should be. When setting up CI, enable them.
- Doxygen is scaffolded but **not actively used**; do not add Doxygen comment blocks.
