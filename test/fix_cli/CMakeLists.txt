set(FIX_CLI_TEST_SOURCES
    app_test.cpp
    )

add_executable(fix_cli_tests ${FIX_CLI_TEST_SOURCES})
target_link_libraries(fix_cli_tests
    PRIVATE project_warnings project_options catch_main CONAN_PKG::fmt fix_cli)
