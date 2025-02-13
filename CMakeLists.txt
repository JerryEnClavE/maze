cmake_minimum_required(VERSION 3.10)
project(ProyectMaze)

set(CMAKE_C_STANDARD 17)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ProyectMaze main.c)

# Link SDL2
target_link_libraries(ProyectMaze ${SDL2_LIBRARIES})