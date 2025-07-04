set(EXAMPLES bare_minimum config drawing colors input raindrop_catch)

foreach(example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    target_include_directories(${example} PUBLIC ${CMAKE_SOURCE_DIR}/include/)
    target_link_libraries(${example} PRIVATE jade)
endforeach()
