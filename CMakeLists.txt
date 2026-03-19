cmake_minimum_required(VERSION 3.15)

project(fix CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# enable cache system
include(cmake/Cache.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()


# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)


# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if (ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif ()
endif ()

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

# Conan 2 integration - automatically install dependencies
# Only run if conan hasn't been run yet (to avoid infinite configure loop)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/build/generators/conan_toolchain.cmake")
  message(STATUS "Detecting Conan profile...")
  execute_process(
    COMMAND conan profile detect --force
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_QUIET
    ERROR_QUIET
  )

  message(STATUS "Running Conan install...")
  execute_process(
    COMMAND conan install ${CMAKE_SOURCE_DIR} 
            --output-folder=${CMAKE_BINARY_DIR} 
            --build=missing 
            -s build_type=${CMAKE_BUILD_TYPE}
            -s compiler.cppstd=23
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE CONAN_RESULT
  )

  if(NOT CONAN_RESULT EQUAL 0)
    message(FATAL_ERROR "Conan install failed with exit code: ${CONAN_RESULT}")
  endif()
else()
  message(STATUS "Conan already configured, skipping conan install")
endif()

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/build/generators")
find_package(CLI11 REQUIRED)
find_package(tomlplusplus REQUIRED)
if (ENABLE_TESTING)
  find_package(Catch2 REQUIRED)
endif()

add_subdirectory(src)

if (ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
  add_subdirectory(behave)
endif ()
