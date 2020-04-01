cmake_minimum_required(VERSION 3.8)
project(lazcorn)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp machine.cpp machine.h game.cpp game.h pauseMenu.cpp pauseMenu.h states/menu.cpp states/menu.h state.h states/stateExit.cpp states/stateExit.h states/stateInit.cpp states/stateInit.h gameMenu.cpp gameMenu.h gameConfig.h states/level_1.cpp states/level_1.h states/level_base.cpp states/level_base.h Object.cpp Object.h GameInterface.cpp GameInterface.h player.cpp player.h enemyShips.cpp enemyShips.h pathPoints.cpp pathPoints.h gameConfig.cpp equipment.cpp equipment.h BossClass.cpp BossClass.h MessageBox.cpp MessageBox.h states/shop.cpp states/shop.h asteroid.cpp asteroid.h)
add_executable(lazcorn ${SOURCE_FILES})

target_link_libraries (lazcorn sfml-graphics sfml-window sfml-audio sfml-system)