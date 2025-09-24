cmake_minimum_required(VERSION 3.10)
project(mai_oop_cpp_task_1)

set(CMAKE_CXX_STANDARD 17)

# Dependencies
include(CTest)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)


include_directories(include)

add_library(time_converter src/time_converter.cpp)

add_executable(main main.cpp)
target_link_libraries(main time_converter)

add_executable(time_converter_tests test/test_time_converter.cpp)
target_link_libraries(time_converter_tests 
    gtest_main 
    time_converter
)

enable_testing()
add_test(NAME TimeConverterTests COMMAND time_converter_tests)
