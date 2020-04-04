if (NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 99)
endif ()

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# creates compile_commands.json database for linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# will avoid extensions being added without it you'd get things like -std=g++11
# replacing -std=c++11
set(CMAKE_CXX_EXTENSIONS OFF)

# All static libs will be placed here
link_directories(${PROJECT_BINARY_DIR}/lib)

# Set up third party
include(cmake/thirdparty/SetupThirdParty.cmake)
