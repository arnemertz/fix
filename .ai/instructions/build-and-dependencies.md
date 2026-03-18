# Build & Dependencies

## Build System

- CMake ≥ 3.15 with Ninja generator.
- C++23 language standard.

## Package Manager

- Conan 2 (`conanfile.txt`).
- Conan is invoked automatically during CMake configure if dependencies are not yet installed.
- Conan output folder: `<build_dir>/build/generators/`.

## Dependencies

| Library | Package              |
|---------|----------------------|
| Catch2  | `catch2/2.13.10`     |
| CLI11   | `cli11/2.3.2`        |

## Building

```powershell
cmake -S . -B out/build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build out/build
```

## Running Tests

```powershell
ctest --test-dir out/build --output-on-failure
```

## Static Analysis & Sanitizers

- clang-tidy is configured in `.clang-tidy` (most checks enabled; fuchsia, google, zircon, abseil, llvm, altera checks excluded).
- Sanitizers (ASAN, UBSAN) and clang-tidy are **not yet run in CI** but should be. When setting up CI, enable them.
- Doxygen is scaffolded but **not actively used**; do not add Doxygen comment blocks.
