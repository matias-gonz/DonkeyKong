cmake_minimum_required(VERSION 3.19)
project(Taller_Prog_I_2021_1C_KIWI)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES main.cpp
        src/controller/handlers/flechaArriba.cpp
        src/model/Player.cpp
        src/model/Player.h
        src/model/Position.cpp
        src/model/Position.h
        src/model/Barrel.cpp
        src/model/Barrel.h
        src/view/ltexture.cpp
        src/view/ltexture.h
        src/view/ViewManager.cpp
        src/view/ViewManager.h
        src/model/Game.cpp
        src/model/Game.h
        src/view/TextureManager.cpp
        src/view/TextureManager.h
        src/model/Level.h
        src/model/Level.cpp
        src/model/Platform.cpp
        src/model/Platform.h
        src/model/Ladder.h
        src/model/Ladder.cpp
        src/model/PlatformMovement.cpp
        src/model/PlatformMovement.h
        src/model/Fire.cpp
        src/model/Fire.h
        src/controller/GameController.cpp
        src/controller/GameController.h
        src/controller/PlayerController.cpp
        src/controller/PlayerController.h
        src/view/LevelDrawer.cpp
        src/view/LevelDrawer.h
        src/controller/Configuration.cpp
        src/controller/Configuration.h
        src/view/Animator.cpp
        src/view/Animator.h
        src/model/EnemyFire.cpp
        src/model/EnemyFire.h
        src/model/Entity.cpp
        src/model/Entity.h
        src/model/Boss.cpp
        src/model/Boss.h
        src/model/LevelLoader.cpp
        src/model/LevelLoader.h
        src/model/Princess.cpp
        src/model/Princess.h
        src/model/LevelLoader.h
        src/model/Logger.cpp
        src/model/Logger.h
        src/model/BarrelMovement.cpp
        src/model/BarrelMovement.h
        src/Server/mainServer.cpp
        src/Server/mainServer.h
        src/Client/mainClient.cpp
        src/Client/mainClient.h
        src/Server/Server.cpp
        src/Server/Server.h
        src/Client/Client.cpp
        src/Client/Client.h
        src/Server/ServerSocket.cpp
        src/Server/ServerSocket.h
        src/Socket/Socket.cpp
        src/Socket/Socket.h
        src/Client/ClientSocket.cpp
        src/Client/ClientSocket.h
        src/model/BarrelMovement.h
        src/model/Collider.cpp
        src/model/Collider.h
        src/view/PlayerAnimator.cpp
        src/view/PlayerAnimator.h
        src/Constants.h src/view/LoginView.cpp src/view/LoginView.h)


# change to personal project name (as above)
add_executable(Taller_Prog_I_2021_1C_KIWI ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Taller_Prog_I_2021_1C_KIWI ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})