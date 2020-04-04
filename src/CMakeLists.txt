add_library(gpio
        STATIC
        digital.cpp
        gpio.cpp
        pwm.cpp)

add_library(gpio_bridge::gpio ALIAS gpio)
target_link_libraries(gpio PRIVATE wiringPi)
target_include_directories(gpio
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

#set_target_properties(gpio PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/gpio/")

install(TARGETS gpio
        EXPORT gpioTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
        COMPONENT dev)

