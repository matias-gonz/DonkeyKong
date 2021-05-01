cmake_minimum_required(VERSION 3.19)
project(Taller_Prog_I_2021_1C_KIWI)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES main.cpp
        src/controller/handlers/flechaArriba.cpp
        src/model/mario.cpp
        src/model/mario.h
        src/model/Position.cpp
        src/model/Position.h
        src/view/background.cpp)

# change to personal project name (as above)
add_executable(Taller_Prog_I_2021_1C_KIWI ${SOURCE_FILES})
target_link_libraries(Taller_Prog_I_2021_1C_KIWI PRIVATE SDL2)