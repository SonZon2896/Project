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

target_link_options(${PROJECT_NAME} PUBLIC -lfltk_images -lfltk)
target_compile_options(${PROJECT_NAME} PUBLIC -lfltk_images -lfltk)
add_compile_options(${PROJECT_NAME} -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 )
target_link_libraries(${PROJECT_NAME} -lfltk_images -lfltk -lX11) 

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})