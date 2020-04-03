cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME LittleBigGame)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp src/Tilemap.hh
        src/Worm.cpp src/Worm.hh
        src/Animation.cpp src/Animation.hh
        src/AnimatedSprite.cpp src/AnimatedSprite.hh
        src/AbstractEntity.cpp src/AbstractEntity.hh
        src/Character.cpp src/Character.hh
        src/ISerializable.hh
        src/IObservable.hh src/IObserver.hh
        src/Collider.cpp src/Collider.hh
        src/Platform.cpp src/Platform.hh
        src/Game.cpp src/Game.hh
        src/Constant.hh src/Constant.cpp
        src/Direction.hh
        src/Bullet.cpp src/Bullet.hh
        src/Monster/MonsterFactory.hh src/Monster/MonsterFactory.cpp
        src/Monster/Monster.cpp
        src/Monster/Monster.hh
        src/Monster/GroundMonster.cpp
        src/Monster/GroundMonster.hh
        src/Monster/SkyMonster.cpp
        src/Monster/SkyMonster.hh
        src/Monster/Spawner.cpp
        src/Monster/Spawner.hh
        src/TimeManager.hh
        src/TimeManager.cpp
        src/Map.cpp src/Map.hh
        src/Loader/ResourceLoader.cpp src/Loader/ResourceLoader.hh
        src/TimeManager.cpp
        src/Boom.cpp src/Boom.hh
        src/InitBoomer.cpp src/InitBoomer.hh
        src/Scenes.cpp src/Scenes.hh
        src/Audio/AudioLoader.cpp src/Audio/AudioLoader.hh
        src/Audio/AudioManager.cpp src/Audio/AudioManager.hh
        src/Audio/SoundWrapper.cpp src/Audio/SoundWrapper.hh
        src/TextManager.cpp src/TextManager.hh
        src/PathFinding/Pathfinding.cpp src/PathFinding/Pathfinding.hh
        src/PathFinding/Node.cpp src/PathFinding/Node.hh
        src/observable/EventObservable.cpp src/observable/EventObservable.hh
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(SFML_ROOT C:/Lib/SFML-2.5.1)
set(SFML_STATIC_LIBRAIRIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED COMPONENTS system audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()