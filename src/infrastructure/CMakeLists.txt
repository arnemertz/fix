set(INFRASTRUCTURE_SOURCES
    toml_issue_repository.cpp
    )

add_library(infrastructure ${INFRASTRUCTURE_SOURCES})
target_link_libraries(infrastructure
    PUBLIC
    domain
    tomlplusplus::tomlplusplus
    PRIVATE
    project_warnings
    project_options
    )
target_include_directories(infrastructure PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
