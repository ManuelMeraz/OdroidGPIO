# OdroidGPIO
Modern C++ wrapper around WiringPi for Odroid (Tested on Linux)

Installation instructions for WiringPi on the odroid
https://wiki.odroid.com/odroid-xu4/application_note/gpio/wiringpi

Take a look at the examples and tests.

Installation instructions
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING=ON ..
make -j6
sudo ctest 
sudo make install
```

In your project you can link to the library using cmake. No need to create your own cmake find package module.
```
find_package(Threads REQUIRED)
find_package(OdroidGPIO REQUIRED)
add_library(libodroidgpio INTERFACE)
target_link_libraries(libodroidgpio INTERFACE ${ODROIDGPIO_LIBRARIES})
target_include_directories(libodroidgpio INTERFACE ${ODROIDGPIO_INCLUDE_DIRS})

add_executable(main main.cpp)
target_link_libraries(main PRIVATE libodroidgpio Threads::Threads)
```
