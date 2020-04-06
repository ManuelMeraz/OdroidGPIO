list(APPEND examples
        serial_loopback)

foreach(example IN LISTS examples)
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} PRIVATE odroidgpio)
endforeach()
