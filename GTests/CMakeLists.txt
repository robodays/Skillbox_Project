#https://www.jetbrains.com/help/clion/unit-testing-tutorial.html#adding-framework

project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})




# adding the Google_Tests_run target
add_executable(Google_Tests_run2
        test.cpp
#        ../src/ConverterJSON.cpp
#        ../include/ConverterJSON.h
        ../src/InvertedIndex.cpp
#       ../include/InvertedIndex.h
        ../src/SearchServer.cpp
#        ../include/SearchServer.h]]
        )

# linking Google_Tests_run with DateConverter_lib which will be tested
#target_link_libraries(Google_Tests_run2 DateConverter_lib)

target_include_directories(search_engine PUBLIC ../include)

target_link_libraries(Google_Tests_run2 gtest gtest_main)
