#https://www.jetbrains.com/help/clion/unit-testing-tutorial.html#adding-framework

project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run2
        test.cpp
        ../ConverterJSON.cpp
        ../ConverterJSON.h
        ../InvertedIndex.cpp
        ../InvertedIndex.h
        ../SearchServer.cpp
        ../SearchServer.h)

# linking Google_Tests_run with DateConverter_lib which will be tested
#target_link_libraries(Google_Tests_run2 DateConverter_lib)

target_link_libraries(Google_Tests_run2 gtest gtest_main)
