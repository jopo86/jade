set(EXAMPLES bare_minimum config drawing input)

foreach(example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} PRIVATE jade)
endforeach()
