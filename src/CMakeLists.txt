file(GLOB SRC_FILES *.cpp)
add_library(jade ${SRC_FILES})

target_include_directories(jade PUBLIC 
    ${CMAKE_SOURCE_DIR}/external/freetype/include/
    ${CMAKE_SOURCE_DIR}/external/glfw/include/
    ${CMAKE_SOURCE_DIR}/external/glad/include/
    ${CMAKE_SOURCE_DIR}/external/glm/
    ${CMAKE_SOURCE_DIR}/external/stb/
)

target_link_libraries(jade 
    PRIVATE opengl32 glad glfw freetype
)

target_compile_options(jade PRIVATE -Wno-delete-incomplete)
