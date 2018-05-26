cmake_minimum_required(VERSION 3.11)
project(sven)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(sven main.cpp src/Word.cpp src/Word.h src/Example.cpp src/Example.h src/Dictionary.cpp src/Dictionary.h src/Utils.h)

target_link_libraries(sven tinyxml)