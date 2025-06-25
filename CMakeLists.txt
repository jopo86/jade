cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(jade VERSION 0.0.0)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/freetype)

add_subdirectory(src)

add_subdirectory(test)
