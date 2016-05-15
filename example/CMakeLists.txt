add_executable(example_hugeint main.cpp)
find_package(HugeInt)
target_include_directories(example_hugeint PRIVATE ${HUGEINT_INCLUDE_DIRS})
