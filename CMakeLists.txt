cmake_minimum_required(VERSION 3.14)
project(sudoku)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# Include debugging flag
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)
add_subdirectory(test)
