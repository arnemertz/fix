cmake_minimum_required(VERSION 2.8.12)
project( fix )

# execute_process(COMMAND conan install .. -s build_type=${CMAKE_BUILD_TYPE} --build missing
#         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#         OUTPUT_VARIABLE conan_ver)
# message(STATUS "Conan: \n${conan_ver}")
# message(STATUS "End Conan")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(src/cpp/)

set( PROJ_MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/fix.cpp )
file( GLOB_RECURSE PROJ_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/*.cpp )
list( REMOVE_ITEM PROJ_SOURCES ${PROJ_MAIN_SRC} )

set( PROJ_NAME fix )
add_executable( ${PROJ_NAME} ${PROJ_SOURCES} ${PROJ_MAIN_SRC} )
target_link_libraries( ${PROJ_NAME} ${CONAN_LIBS} )
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)


set( TEST_PROJ_NAME unit_tests )
file( GLOB_RECURSE TEST_PROJ_SOURCES test/*.cpp )
add_executable( ${TEST_PROJ_NAME} ${TEST_PROJ_SOURCES} ${PROJ_SOURCES} )
target_link_libraries( ${TEST_PROJ_NAME} ${CONAN_LIBS} )
set_property(TARGET ${TEST_PROJ_NAME} PROPERTY CXX_STANDARD 14)
enable_testing()
ADD_TEST( ${TEST_PROJ_NAME} ${TEST_PROJ_NAME} )

