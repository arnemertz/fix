set(DOMAIN_SOURCES
    application_service.cpp
    title.cpp
    )

add_library(domain ${DOMAIN_SOURCES})
target_link_libraries(domain
    PRIVATE
    project_warnings
    project_options
    CONAN_PKG::range-v3
    )
target_include_directories(domain PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
