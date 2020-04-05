cmake_minimum_required(VERSION 3.10)
project(OdroidGPIO
        VERSION 0.0.1
        DESCRIPTION "A C++ wrapper around WiringPi for Odroid"
        LANGUAGES CXX C)

include(cmake/Setup.cmake)

# Create odroidgpio target and library
add_subdirectory(src)

# only test if building as main project
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(CTest)
    #    add_subdirectory(tests)
endif ()

# Add all targets to the build-tree export set
export(TARGETS odroidgpio FILE "${PROJECT_BINARY_DIR}/OdroidGPIOTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE OdroidGPIO)

# Create the OdroidGPIOConfig.cmake and OdroidGPIOConfigVersion.cmake files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(cmake/OdroidGPIOConfig.cmake.in "${PROJECT_BINARY_DIR}/OdroidGPIOConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${ODROIDGPIO_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(cmake/OdroidGPIOConfig.cmake.in "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/OdroidGPIOConfig.cmake" @ONLY)
# ... for both
configure_file(cmake/OdroidGPIOConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/OdroidGPIOConfigVersion.cmake" @ONLY)

# Install the OdroidGPIOConfig.cmake and OdroidGPIOConfigVersion.cmake
install(FILES
        "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/OdroidGPIOConfig.cmake"
        "${PROJECT_BINARY_DIR}/OdroidGPIOConfigVersion.cmake"
        DESTINATION
        "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(DIRECTORY include/ DESTINATION ${INSTALL_INCLUDE_DIR})

# Install the export set for use with the install-tree
install(EXPORT OdroidGPIOTargets
        DESTINATION "${INSTALL_CMAKE_DIR}"
        COMPONENT dev)
