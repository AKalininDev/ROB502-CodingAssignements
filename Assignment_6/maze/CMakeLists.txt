cmake_minimum_required(VERSION 3.0.0)
project(maze VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/output.txt ${CMAKE_BINARY_DIR}/output.txt COPYONLY)

add_library(maze maze.h maze_impl.cpp maze_impl_student.cpp)
target_include_directories(maze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(bfs INTERFACE)
target_sources(bfs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/bfs.h)
target_include_directories(bfs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(dfs INTERFACE)
target_sources(dfs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/dfs.h)
target_include_directories(dfs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(maze_main maze_main.cpp)
target_link_libraries(maze_main PUBLIC maze bfs dfs)