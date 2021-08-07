set(FIX_CLI_SOURCES
    app.cpp
    )


add_library(fix_cli ${FIX_CLI_SOURCES})
target_link_libraries(fix_cli
    PRIVATE
    project_warnings
    project_options
    CONAN_PKG::docopt.cpp
    CONAN_PKG::fmt)
target_include_directories(fix_cli PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
