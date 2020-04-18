set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/thirdparty/modules)

find_package(Threads REQUIRED)
find_library(rt rt REQUIRED)
find_library(crypt crypt REQUIRED)

find_package(wiringPi REQUIRED)
add_library(wiringPi SHARED IMPORTED)
set_target_properties(wiringPi PROPERTIES IMPORTED_LOCATION ${WIRINGPI_LIBRARIES})

set_target_properties(wiringPi PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${WIRINGPI_INCLUDE_DIRS})

