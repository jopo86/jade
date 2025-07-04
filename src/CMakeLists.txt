file(GLOB SRC_FILES *.cpp)
add_library(jade STATIC ${SRC_FILES})

target_include_directories(jade PUBLIC 
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/external/freetype/include/
    ${CMAKE_SOURCE_DIR}/external/glfw/include/
    ${CMAKE_SOURCE_DIR}/external/glad/include/
    ${CMAKE_SOURCE_DIR}/external/glm/
    ${CMAKE_SOURCE_DIR}/external/stb/
)

target_link_libraries(jade 
    PUBLIC opengl32 glad glfw freetype z bz2
)

target_compile_features(jade PUBLIC cxx_std_20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(jade PRIVATE -Wno-delete-incomplete)
endif()
