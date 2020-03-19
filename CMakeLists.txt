cmake_minimum_required(VERSION 3.9)
project(dz2 C)
enable_language(C CXX)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wpedantic -fPIC" )

include_directories("${PROJECT_SOURCE_DIR}/infoContainer")
include_directories("${PROJECT_SOURCE_DIR}/consistentSolution")
include_directories("${PROJECT_SOURCE_DIR}/parallelSolution")
include_directories("${PROJECT_SOURCE_DIR}/dz")


configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(tests)

file(GLOB dz
        "${PROJECT_SOURCE_DIR}/dz/*.c")

file(GLOB container
        "${PROJECT_SOURCE_DIR}/infoContainer/*.c"
        "${PROJECT_SOURCE_DIR}/infoContainer/*.h")

file(GLOB consistent
        "${PROJECT_SOURCE_DIR}/consistentSolution/*.c"
        "${PROJECT_SOURCE_DIR}/consistentSolution/*.h")

file(GLOB parallel
        "${PROJECT_SOURCE_DIR}/parallelSolution/*.c"
        "${PROJECT_SOURCE_DIR}/parallelSolution/*.h")

add_executable(dz2 ${dz} ${container} ${consistent} ${parallel} )

add_library(StaticLibDecision STATIC ${PROJECT_SOURCE_DIR}/consistentSolution/decisionConsistent.c)
add_library(SharedLibDecision SHARED ${PROJECT_SOURCE_DIR}/parallelSolution/decisionParallel.c)


if(UNIX AND NOT APPLE)
    set(CMAKE_REQUIRED_LIBRARIES m)
    target_link_libraries(${PROJECT_NAME} m)
    find_package(Threads REQUIRED)
    target_link_libraries(dz2 Threads::Threads StaticLibDecision SharedLibDecision)
endif()



