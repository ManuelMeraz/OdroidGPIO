cmake_minimum_required(VERSION 3.10)
project(odroid-gpio
        VERSION 0.0.1
        DESCRIPTION "A C++ wrapper around WiringPi for Odroid"
        LANGUAGES CXX C)

include(cmake/Setup.cmake)

# Create odroid-gpio target and library
add_subdirectory(src)

# only test if building as main project
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(CTest)
    #    add_subdirectory(tests)
endif ()

# Add all targets to the build-tree export set
export(TARGETS odroid-gpio FILE "${PROJECT_BINARY_DIR}/odroid-gpio-targets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE odroid-gpio)

# Create the odroid-gpio-config.cmake and odroid-gpio-config-version files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(cmake/odroid-gpio-config.cmake.in "${PROJECT_BINARY_DIR}/odroid-gpio-config.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${GPIO_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(cmake/odroid-gpio-config.cmake.in "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/odroid-gpio-config.cmake" @ONLY)
# ... for both
configure_file(cmake/odroid-gpio-config-version.cmake.in "${PROJECT_BINARY_DIR}/odroid-gpio-config-version.cmake" @ONLY)

# Install the odroid-gpio-config.cmake and odroid-gpio-config-version.cmake
install(FILES
        "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/odroid-gpio-config.cmake"
        "${PROJECT_BINARY_DIR}/odroid-gpio-config-version.cmake"
        DESTINATION
        "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(DIRECTORY include/ DESTINATION ${INSTALL_INCLUDE_DIR})

# Install the export set for use with the install-tree
install(EXPORT odroid-gpio-targets
        DESTINATION "${INSTALL_CMAKE_DIR}"
        COMPONENT dev)
