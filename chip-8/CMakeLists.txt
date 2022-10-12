cmake_minimum_required(VERSION 3.7)

project(chip-8)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

file(GLOB SRC "src/*.c")

add_executable(chip-8 ${SRC})
target_link_libraries(chip-8 ${SDL2_LIBRARIES})
