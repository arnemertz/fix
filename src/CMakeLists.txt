# Generic test that uses conan libs

add_executable(fix main.cpp)
target_link_libraries(
    fix
    PRIVATE
    project_options
    project_warnings
    CONAN_PKG::fmt
)
