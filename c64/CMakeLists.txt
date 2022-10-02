cmake_minimum_required(VERSION 3.7)

project(C64)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GTK REQUIRED)
include_directories(${GTK_INCLUDE_DIRS})

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

add_executable(C64 
   src/CIA/CIA.c
   src/CIA/IntervalTimer.c
   src/Memory/Memory.c
   src/VIC/vic.c
   src/VIC/vic_border.c
   src/VIC/vic_graphics.c
   src/VIC/vic_sprite.c
   src/CPU/cpu.c
   src/CPU/addr_modes.c
   src/CPU/instructions.c
   src/CPU/instruction_table.c
   src/Keyboard/Keyboard.c
   src/joystick/joystick.c
   src/Display/Display.c
   src/c64bus.c
   src/C64.c
   src/main.c)

target_link_libraries(C64 ${SDL2_LIBRARIES})
target_link_libraries(C64 ${GTK_LIBRARIES})