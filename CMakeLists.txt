cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME LittleBigGame)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp src/Tilemap.hh src/Worm.cpp src/Worm.hh src/Animation.cpp src/Animation.hh src/AnimatedSprite.cpp src/AnimatedSprite.hh)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(SFML_ROOT C:/Lib/SFML-2.5.1)
set(SFML_STATIC_LIBRAIRIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED COMPONENTS system audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()