cmake_minimum_required(VERSION 3.19)
project(Taller_Prog_I_2021_1C_KIWI)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES main.cpp
        src/controller/handlers/flechaArriba.cpp
        src/model/Game.cpp
        src/model/Game.h
        src/view/TextureManager.cpp
        src/view/TextureManager.h
        src/model/Level.h
        src/model/Level.cpp
        src/model/Platform.cpp
        src/model/Platform.h)

# change to personal project name (as above)
add_executable(Taller_Prog_I_2021_1C_KIWI ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Taller_Prog_I_2021_1C_KIWI ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})