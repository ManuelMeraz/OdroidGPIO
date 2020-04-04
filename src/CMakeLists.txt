add_library(odroid-gpio
        STATIC
        digital.cpp
        gpio.cpp
        pwm.cpp)

target_link_libraries(odroid-gpio PRIVATE wiringPi)
target_include_directories(odroid-gpio
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS odroid-gpio
        EXPORT odroid-gpio-targets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
        COMPONENT dev)

