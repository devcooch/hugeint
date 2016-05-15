project(hugeint)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePackageConfigHelpers)
set(PACKAGE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_package_config_file(
    HugeIntConfig.cmake.in ${CMAKE_BINARY_DIR}/HugeIntConfig.cmake
    INSTALL_DESTINATION lib/hugeint/cmake
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/HugeIntConfig.cmake DESTINATION lib/hugeint/cmake)

add_subdirectory(example)
add_subdirectory(test)
