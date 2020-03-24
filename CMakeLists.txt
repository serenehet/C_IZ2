cmake_minimum_required(VERSION 3.9)
project(dz2 C)
enable_language(C CXX)

set(CMAKE_C_STANDARD 11)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(unitTests)


set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wpedantic -fPIC" )

include_directories("${PROJECT_SOURCE_DIR}/dz")

add_library(static_lib STATIC
        ${PROJECT_SOURCE_DIR}/consistentSolution/decisionConsistent.c
        ${PROJECT_SOURCE_DIR}/infoContainer/infoContainer.c)
add_library(shared_lib SHARED
        ${PROJECT_SOURCE_DIR}/parallelSolution/decisionParallel.c
        ${PROJECT_SOURCE_DIR}/infoContainer/infoContainer.c)

file(GLOB dz
        "${PROJECT_SOURCE_DIR}/dz/*.c")

add_executable(dz2 ${dz})

if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()

target_link_libraries(${PROJECT_NAME} static_lib shared_lib)