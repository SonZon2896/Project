cmake_minimum_required(VERSION 3.5.0)
project(testing VERSION 0.1.0 LANGUAGES CXX)

set(SOURCES main.cpp
            Cpp/Heads.cpp
            Graphic/FLTKgraphic.cpp
            Main/Waves.cpp
            Main/GameManager.cpp
            Main/Logic.cpp
            Graph_lib/Graph.cpp
            Graph_lib/GUI.cpp
            Graph_lib/Window.cpp
            )

add_executable(${PROJECT_NAME} ${SOURCES})

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})