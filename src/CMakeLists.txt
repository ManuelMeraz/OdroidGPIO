add_library(odroidgpio
        STATIC
        digital.cpp
        gpio.cpp
        pwm.cpp include/detail/gpio.hpp include/detail/digital/digital.hpp include/detail/pwm/pwm.hpp ../include/odroid/digital/Pin.hpp ../include/odroid/pwm/Pin.hpp)

target_link_libraries(odroidgpio PRIVATE wiringPi)
target_include_directories(odroidgpio
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS odroidgpio
        EXPORT OdroidGPIOTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR}/static
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
        COMPONENT dev)

