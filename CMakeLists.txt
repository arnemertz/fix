cmake_minimum_required(VERSION 2.8.12)

project( fix )
include(build/conanbuildinfo.cmake)
conan_basic_setup()


set( PROJ_NAME main )
file( GLOB_RECURSE PROJ_SOURCES src/*.cpp )
add_executable( ${PROJ_NAME} ${PROJ_SOURCES} )
target_link_libraries( ${PROJ_NAME} ${CONAN_LIBS} )


set( TEST_PROJ_NAME unit_tests )
file( GLOB_RECURSE TEST_PROJ_SOURCES test/*.cpp )
add_executable( ${TEST_PROJ_NAME} ${TEST_PROJ_SOURCES} )
target_link_libraries( ${TEST_PROJ_NAME} ${CONAN_LIBS} )
enable_testing()
ADD_TEST( ${TEST_PROJ_NAME} ${TEST_PROJ_NAME} )


