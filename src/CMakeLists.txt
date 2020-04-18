add_library(OdroidGPIO
        SHARED
        BasePin.cpp
        Database.cpp
        gpio.cpp

        digital/Pin.cpp
        digital/digital.cpp
        pwm/Pin.cpp
        pwm/pwm.cpp
        serial/Port.cpp
        serial/serial.cpp
        I2C/Device.cpp
        I2C/I2C.cpp)

target_link_libraries(OdroidGPIO
        PUBLIC wiringPi
        Threads::Threads rt crypt)

target_include_directories(OdroidGPIO
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/OdroidGPIO>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS OdroidGPIO
        EXPORT OdroidGPIOTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
        COMPONENT dev)

