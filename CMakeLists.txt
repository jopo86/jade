cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(jade VERSION 0.0.0)

# file(GLOB SRC_CPP_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
# file(GLOB SRC_C_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

# add_executable(a ${SRC_CPP_FILES} ${SRC_C_FILES})

# target_include_directories(a SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include)
# target_link_directories(a PUBLIC ${CMAKE_SOURCE_DIR}/lib)
# target_link_libraries(a PUBLIC #[[libs]])

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/freetype)

add_subdirectory(src)

add_subdirectory(test)