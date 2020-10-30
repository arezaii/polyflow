cmake_minimum_required(VERSION 3.17)
project(polyflow)

set(CMAKE_CXX_STANDARD 11)

add_library(pfutil STATIC pfutil.cpp pfutil.hpp)

add_executable(polyflow main.cpp polyflow.hpp)

target_link_libraries(polyflow pfutil)