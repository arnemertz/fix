# Automatically enable catch2 to generate ctest targets
include(Catch)

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2)
target_link_libraries(catch_main PRIVATE project_options)

add_subdirectory(fix_cli)
add_subdirectory(domain)
