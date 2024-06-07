cmake_minimum_required(VERSION 3.25)
project(PP_SPACE_INVASION)

set(CMAKE_CXX_STANDARD 17)

add_executable(PP_SPACE_INVASION Source/main.cpp Source/Headers/Player.hpp Source/Player.cpp Source/Headers/Entity.hpp Source/Entity.cpp Source/Headers/Bullet.hpp Source/Bullet.cpp Source/Headers/Enemy.hpp Source/Enemy.cpp Source/Headers/AnimationManager.hpp Source/AnimationManager.cpp Source/EnemyManager.cpp Source/Headers/EnemyManager.hpp Source/Headers/InterfaceManager.hpp Source/InterfaceManager.cpp Source/Headers/Powerup.hpp Source/Powerup.cpp Source/Headers/BonusEnemy.hpp Source/BonusEnemy.cpp Source/Headers/Score.hpp Source/Score.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)

target_link_libraries(PP_SPACE_INVASION sfml-system sfml-window sfml-graphics sfml-audio)