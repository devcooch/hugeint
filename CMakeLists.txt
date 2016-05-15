cmake_minimum_required(VERSION 3.2)
project(hugeint)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePackageConfigHelpers)
set(PACKAGE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_package_config_file(
    "HugeIntConfig.cmake.in" "${CMAKE_BINARY_DIR}/cmake/HugeIntConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_BINARY_DIR}/cmake
)

add_subdirectory(example)
