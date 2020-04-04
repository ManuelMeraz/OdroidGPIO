cmake_minimum_required(VERSION 3.10)
project(odroid_gpio
        VERSION 0.0.1
        DESCRIPTION "A C++ wrapper around WiringPi for Odroid"
        LANGUAGES CXX C)

include(cmake/Setup.cmake)

# Create gpio target and library
add_subdirectory(src)

# only test if building as main project
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(CTest)
    #    add_subdirectory(tests)
endif ()

# Add all targets to the build-tree export set
export(TARGETS gpio FILE "${PROJECT_BINARY_DIR}/gpioTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE gpio)

# Create the gpioConfig.cmake and gpioConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(cmake/gpioConfig.cmake.in "${PROJECT_BINARY_DIR}/gpioConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${GPIO_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(cmake/gpioConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/gpioConfig.cmake" @ONLY)
# ... for both
configure_file(cmake/gpioConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/gpioConfigVersion.cmake" @ONLY)

# Install the gpioConfig.cmake and gpioConfigVersion.cmake
install(FILES
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/gpioConfig.cmake"
        "${PROJECT_BINARY_DIR}/gpioConfigVersion.cmake"
        DESTINATION
        "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(DIRECTORY include/ DESTINATION ${INSTALL_INCLUDE_DIR})

# Install the export set for use with the install-tree
install(EXPORT gpioTargets
        DESTINATION "${INSTALL_CMAKE_DIR}"
        COMPONENT dev)
