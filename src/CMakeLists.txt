add_library(odroidgpio
        STATIC
        digital.cpp
        gpio.cpp
        pwm.cpp)

target_link_libraries(odroidgpio PRIVATE wiringPi)
target_include_directories(odroidgpio
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS odroidgpio
        EXPORT OdroidGPIOTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
        COMPONENT dev)

