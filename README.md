# OdroidGPIO
Modern C++ wrapper around WiringPi for Odroid (Tested on Linux)

Installation instructions for WiringPi on the odroid
https://wiki.odroid.com/odroid-xu4/application_note/gpio/wiringpi

Take a look at the examples and tests.

Installation instructions
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON ..
make -j6
sudo ctest 
sudo make install
```

In your project you can link to the library using cmake. No need to create your own cmake find package module.
```
find_package(Threads REQUIRED)
find_package(OdroidGPIO REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE OdroidGPIO Threads::Threads)
```
