set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/thirdparty/modules)

find_package(Threads REQUIRED)
find_library(rt rt REQUIRED)
find_library(crypt crypt REQUIRED)

find_package(wiringPi REQUIRED)
add_library(wiringPi SHARED IMPORTED)
set_property(TARGET wiringPi PROPERTY IMPORTED_LOCATION ${WIRINGPI_LIBRARIES})
target_include_directories(wiringPi INTERFACE ${WIRINGPI_INCLUDE_DIRS})
target_link_libraries(wiringPi INTERFACE Threads::Threads rt crypt)
