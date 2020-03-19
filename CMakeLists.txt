cmake_minimum_required(VERSION 3.9)
project(dz2 C)
enable_language(C CXX)
set(CMAKE_C_FLAGS  "-std=c99")

include_directories("${PROJECT_SOURCE_DIR}/consistentSolution")
include_directories("${PROJECT_SOURCE_DIR}/parallelSolution")
include_directories("${PROJECT_SOURCE_DIR}/dz")

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