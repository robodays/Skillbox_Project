cmake_minimum_required(VERSION 3.21)
project(search_engine VERSION 1.0.0)

configure_file(include/config.h.in ${PROJECT_BINARY_DIR}/include/config.h)
include_directories(${PROJECT_BINARY_DIR}/include)

set(CMAKE_CXX_STANDARD 17)


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



#JSON
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)


#googletest
add_subdirectory(GTests)