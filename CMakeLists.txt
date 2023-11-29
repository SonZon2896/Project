cmake_minimum_required(VERSION 3.5.0)
project(testing VERSION 0.1.0 LANGUAGES CXX)

set(SOURCES main.cpp
            Headers/Heads.cpp
            Graphic/FLTKgraphic.cpp
            events/events.cpp
            Main/Waves.cpp
            Main/GameManager.cpp
            Main/Logic.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})