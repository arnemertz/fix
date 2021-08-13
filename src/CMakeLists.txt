# Generic test that uses conan libs

add_subdirectory(fix_cli)
add_subdirectory(domain)

add_executable(fix main.cpp)
target_link_libraries(
    fix
    PRIVATE
    project_options
    project_warnings
    fix_cli
)
