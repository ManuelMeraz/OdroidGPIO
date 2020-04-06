list(APPEND tests
        test_digital_pin
        test_pwm_pin
        test_serial_port)

foreach(test IN LISTS tests)
    add_executable(${test} ${test}.cpp ../include/odroid/serial/SerialPort.hpp)
    add_test(NAME ${test} COMMAND ${test})
    target_link_libraries(${test} PRIVATE odroidgpio)
endforeach()
