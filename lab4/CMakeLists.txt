cmake_minimum_required(VERSION 3.23)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES startup.cpp
        Classes/GUI/Game.cpp
        Classes/GUI/Game.h
        Classes/GUI/GameMenu.cpp
        Classes/GUI/GameMenu.h
        Classes/GUI/LevelMenu.cpp
        Classes/GUI/LevelMenu.h
        Classes/GUI/MainMenu.cpp
        Classes/GUI/MainMenu.h
        Classes/GUI/MenuOption.cpp
        Classes/GUI/MenuOption.h
        Classes/GUI/SceneManager.cpp
        Classes/GUI/SceneManager.h
        Classes/GUI/EventManager.cpp
        Classes/GUI/EventManager.h
        Classes/GUI/EventStorage.cpp
        Classes/GUI/EventStorage.h
        Classes/GUI/GUI_Manager.cpp
        Classes/GUI/GUI_Manager.h
        Classes/GUI/Scene.cpp
        Classes/GUI/Scene.h
        Classes/GUI/GUI_Element.cpp
        Classes/GUI/GUI_Element.h
        Classes/GUI/ShopElement.cpp
        Classes/GUI/ShopElement.h
        Classes/GUI/Level.h
        Classes/GUI/Level.cpp
        tinyxml/tinyxml2.cpp
        tinyxml/tinyxml2.h
        Classes/GameLogic/TileType.h
        Classes/GUI/WeaponGUI.cpp
        Classes/GUI/WeaponGUI.h
        Classes/Vector/Vector.h
        Classes/GameLogic/Weapon.cpp
        Classes/GameLogic/Weapon.h
        Classes/GameLogic/Trap.cpp
        Classes/GameLogic/Trap.h
        Classes/GameLogic/MainGame.cpp
        Classes/GameLogic/MainGame.h
        Classes/GameLogic/EnemyManager.cpp
        Classes/GameLogic/EnemyManager.h
        Classes/GameLogic/Enemy.cpp
        Classes/GameLogic/Graph.h
        Classes/GameLogic/Weapon.cpp
        Classes/GameLogic/Weapon.h
        Classes/GameLogic/WeaponManager.cpp
        Classes/GameLogic/WeaponManager.h
        Classes/GameLogic/Wave.cpp
        Classes/GameLogic/Wave.h
        Classes/GameLogic/WaveManager.cpp
        Classes/GameLogic/WaveManager.h
        Classes/GUI/TileGUI.cpp
        Classes/GUI/TileGUI.h
        Classes/GameLogic/Path.cpp
        Classes/GameLogic/Path.h
        Classes/GameLogic/Tile.cpp
        Classes/GameLogic/Tile.h
        Classes/GameLogic/Castle.cpp
        Classes/GameLogic/Castle.h
        Classes/GameLogic/Lain.cpp
        Classes/GameLogic/Lain.h
        Classes/GUI/MapObject.cpp
        Classes/GUI/MapObject.h
        Classes/GameLogic/Tower.h
        Classes/GameLogic/Tower.cpp Classes/GameLogic/GameObject.cpp Classes/GameLogic/GameObject.h Classes/GameLogic/Direction.h)


#сделать проверку на добавление нужной библиотеки
set(SFML_DIR C:/SFML)
set(SFML_ROOT ${SFML_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIR} Storage)
add_executable(lab4 ${SOURCE_FILES})
target_link_libraries(lab4 ${SFML_LIBRARIES})

add_subdirectory(GTESTS)

#перед запуском проекта надо скопировать все .dll файлы из c:/SFML/bin в cmake-build-debug
#сделать это в cmake

#создать папку cmake-modules, куда кинуть скрипт FindSFML.cmake