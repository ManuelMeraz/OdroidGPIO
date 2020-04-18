list(APPEND tests
        test_digital_pin
        test_pwm_pin
        test_gpio_interface
        )

foreach(test IN LISTS tests)
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} PRIVATE odroidgpio gtest_main)
    add_test(NAME ${test} COMMAND ${test})
endforeach()
