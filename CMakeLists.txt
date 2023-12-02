cmake_minimum_required(VERSION 3.5.0)
project(cockroaches VERSION 0.1.0 LANGUAGES CXX)

install()

set(SOURCES main.cpp
            Headers/Heads.cpp
            Graphic/FLTKgraphic.cpp
            events/events.cpp
            Weapons/weapons.cpp
            Main/Waves.cpp
            Main/GameManager.cpp
            Main/Logic.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/PNG"
        "${CMAKE_CURRENT_BINARY_DIR}/PNG" SYMBOLIC)

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})