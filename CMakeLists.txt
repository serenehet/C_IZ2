cmake_minimum_required(VERSION 3.9)
project(dz2 C)
enable_language(C CXX)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wpedantic -fPIC" )

include_directories("${PROJECT_SOURCE_DIR}/dz")

add_library(static_lib STATIC ${PROJECT_SOURCE_DIR}/consistentSolution/decisionConsistent.c ${PROJECT_SOURCE_DIR}/infoContainer/infoContainer.c)
add_library(shared_lib SHARED ${PROJECT_SOURCE_DIR}/parallelSolution/decisionParallel.c ${PROJECT_SOURCE_DIR}/infoContainer/infoContainer.c)

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/dz/*.c")

add_executable(${PROJECT_NAME} ${sources})

if(UNIX AND NOT APPLE)
    set(CMAKE_REQUIRED_LIBRARIES m)
    target_link_libraries(${PROJECT_NAME} m)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()

target_link_libraries(${PROJECT_NAME} static_lib shared_lib)