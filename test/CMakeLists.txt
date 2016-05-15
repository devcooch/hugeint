include(ExternalProject)
set(GTEST_VERSION "1.7.0")
set(GTEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest-${GTEST_VERSION}")
set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
ExternalProject_Add(googletest
    GIT_REPOSITORY git@github.com:google/googletest.git
    GIT_TAG release-${GTEST_VERSION}
    PREFIX ${GTEST_DIR}
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)
ExternalProject_Get_Property(googletest SOURCE_DIR BINARY_DIR)
enable_testing()
add_executable(test_hugeint main.cpp)
find_package(HugeInt CONFIG)
target_include_directories(test_hugeint
    PRIVATE
    ${HUGEINT_INCLUDE_DIRS}
    ${SOURCE_DIR}/include
)
add_dependencies(test_hugeint googletest)
target_link_libraries(test_hugeint
    ${BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
)
add_test(NAME test_hugeint COMMAND test_hugeint)
