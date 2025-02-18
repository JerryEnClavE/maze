cmake_minimum_required(VERSION 3.23)
project(Proyect-Maze)

set(CMAKE_C_STANDARD 17)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Pryect-Maze main.c)
target_link_libraries(Proyect-Maze ${SDL2_LIBRARIES})
