cmake_minimum_required(VERSION 2.8.12)

set( PROJ_NAME fix )
file( GLOB_RECURSE PROJ_SOURCES src/*.cpp )

project( ${PROJ_NAME} )

include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable( ${PROJ_NAME} ${PROJ_SOURCES} )
target_link_libraries(${PROJ_NAME} ${CONAN_LIBS})

set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)