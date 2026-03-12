# Build Instructions with Conan 2

This project now uses Conan 2.x for dependency management.

## Prerequisites
- CMake 3.15 or higher
- Python 3.x
- Conan 2.x (`python -m pip install conan`)
- C++20 compatible compiler

## Building the Project

### Step 1: Install Dependencies with Conan
From the project root directory, run:

```bash
python -m conan install . --output-folder=out/build/x64-Debug --build=missing --settings=build_type=Debug
```

For Release build:
```bash
python -m conan install . --output-folder=out/build/x64-Release --build=missing --settings=build_type=Release
```

### Step 2: Configure CMake
The Conan toolchain will be automatically picked up by CMake when you configure.

In Visual Studio, the CMake cache should automatically regenerate after the Conan install step.

Alternatively, from command line:
```bash
cmake -B out/build/x64-Debug -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=out/build/x64-Debug/conan_toolchain.cmake
```

### Step 3: Build
```bash
cmake --build out/build/x64-Debug
```

## Visual Studio Integration
If using Visual Studio's CMake integration:
1. Run the Conan install command from a terminal in the project root
2. Reload the CMake cache in Visual Studio
3. Build as normal
