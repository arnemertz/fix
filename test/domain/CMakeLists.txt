set(DOMAIN_TEST_SOURCES
    application_service_test.cpp
    description_test.cpp
    domain_error_test.cpp
    issue_id_test.cpp
    title_test.cpp
    )

add_executable(domain_tests ${DOMAIN_TEST_SOURCES})
target_link_libraries(domain_tests
    PRIVATE project_warnings project_options catch_main domain)

catch_discover_tests(domain_tests TEST_PREFIX "DOMAIN: ")
