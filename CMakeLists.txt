cmake_minimum_required(VERSION 3.21)
project(search_engine VERSION 1.0.0)

configure_file(include/config.h.in ${PROJECT_BINARY_DIR}/include/config.h)
include_directories(${PROJECT_BINARY_DIR}/include)

set(CMAKE_CXX_STANDARD 17)

#googletest
#[[
include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
]]

#for MinGW googletest
#[[set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()]]




#JSON
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)


add_executable(search_engine
        main.cpp
        src/ConverterJSON.cpp
        include/ConverterJSON.h
        src/InvertedIndex.cpp
        include/InvertedIndex.h
        src/SearchServer.cpp
        include/SearchServer.h
        #${PROJECT_BINARY_BIN}/include/config.h
        )

#target_include_directories(search_engine PUBLIC include)

#JSON
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)


#googletest
#[[
target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)]]
add_subdirectory(GTests)