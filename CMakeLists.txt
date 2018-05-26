cmake_minimum_required(VERSION 3.11)
project(sven)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories("${CMAKE_BINARY_DIR}")
configure_file(src/config.h.in "${CMAKE_BINARY_DIR}/config.h" @ONLY)

add_executable(sven main.cpp src/Word.cpp src/Word.h src/Example.cpp src/Example.h src/Dictionary.cpp src/Dictionary.h src/UString.cpp src/UString.h src/config.h.in)

target_link_libraries(sven tinyxml)

install(TARGETS sven RUNTIME DESTINATION bin)
install(FILES dict.xml DESTINATION share/sven)