cmake_minimum_required(VERSION 3.5.0)
project(testing VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_executable(testing main.cpp
                    Cpp/Heads.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
