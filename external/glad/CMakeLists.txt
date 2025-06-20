add_library(glad STATIC src/glad.c)

target_include_directories(glad SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

if (MSVC)
    target_compile_options(glad PRIVATE /W0)
else()
    target_compile_options(glad PRIVATE -w)
endif()
