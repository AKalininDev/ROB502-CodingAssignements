cmake_minimum_required(VERSION 3.10)
project(climber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure input and output files 
configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/output.txt ${CMAKE_BINARY_DIR}/output.txt COPYONLY)

add_library(climber climber.h climber.cpp)
target_include_directories(climber PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(print_map print_map.cpp)
target_link_libraries(print_map PUBLIC climber)

add_executable(run_climber run_climber.cpp)
target_link_libraries(run_climber PUBLIC climber)
