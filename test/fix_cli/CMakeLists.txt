set(FIX_CLI_TEST_SOURCES
    app_test.cpp
    )

add_executable(fix_cli_tests ${FIX_CLI_TEST_SOURCES})
target_link_libraries(fix_cli_tests
    PRIVATE project_warnings project_options catch_main CONAN_PKG::fmt CONAN_PKG::range-v3 fix_cli)

catch_discover_tests(fix_cli_tests TEST_PREFIX "CLI: ")
