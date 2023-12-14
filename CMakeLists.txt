cmake_minimum_required(VERSION 3.5.0)
project(ROOM153 VERSION 0.1.0 LANGUAGES CXX)

file(GLOB FLTK_SOURCES "lib/fltk/*.cpp")

set(SOURCES main.cpp
            Headers/Heads.cpp
            Headers/MainMenu.cpp
            Graphic/FLTKgraphic.cpp
            events/events.cpp
            Weapons/weapons.cpp
            Main/Waves.cpp
            Main/GameManager.cpp
            Main/MainMenuManager.cpp
            Main/Logic.cpp
            ${FLTK_SOURCES}
            )

set(HEADERS Headers/heads.h
            Headers/MainMenu.h
            Headers/utils.h
            Graphic/FLTKgraphic.h
            Main/GameManager.h
            Main/MainMenuManager.h
            Main/Waves.h
            Weapons/weapons.h)

add_executable(${PROJECT_NAME} ${SOURCES})

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/PNG"
        "${CMAKE_CURRENT_BINARY_DIR}/PNG" SYMBOLIC)

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION Room153)
# install(FILES ${HEADERS} DESTINATION Room153/bin/headers)
install(DIRECTORY PNG DESTINATION Room153)