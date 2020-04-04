add_library(gpio
        STATIC
        digital.cpp
        gpio.cpp
        pwm.cpp)

add_library(gpio_bridge::gpio ALIAS gpio)
target_link_libraries(gpio PRIVATE wiringPi)
target_include_directories(gpio
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
