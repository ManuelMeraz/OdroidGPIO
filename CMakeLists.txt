cmake_minimum_required(VERSION 3.10)
project(odroid_gpio)

include(cmake/Setup.cmake)
add_subdirectory(src)

if (BUILD_TESTING)
    enable_testing()
#    add_subdirectory(tests)
endif ()
