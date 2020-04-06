add_library(odroidgpio
        SHARED
        PinDatabase.cpp
        BasePin.cpp
        gpio.cpp
        digital/digital.cpp
        digital/DigitalPin.cpp
        pwm/pwm.cpp
        pwm/PWMPin.cpp
        serial/SerialPort.cpp
        serial/serial.cpp)

target_link_libraries(odroidgpio
        PUBLIC wiringPi
        PRIVATE Threads::Threads rt crypt)

target_include_directories(odroidgpio
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/OdroidGPIO>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS odroidgpio
        EXPORT OdroidGPIOTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
        COMPONENT dev)

