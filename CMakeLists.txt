project(fix)
cmake_minimum_required(VERSION 2.8.12)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(fix fix.cpp)
target_link_libraries(fix ${CONAN_LIBS})