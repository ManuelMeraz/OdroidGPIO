list(APPEND tests test_digital_pin test_pwm_pin)

foreach(test IN LISTS tests)
    add_executable(${test} ${test}.cpp)
    add_test(NAME ${test} COMMAND ${test})
    target_link_libraries(${test} PRIVATE odroidgpio)
endforeach()
