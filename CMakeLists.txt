cmake_minimum_required(VERSION 3.10)

project(AutoMake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AutoMake catch_errors.hpp typeofcontents.h do_something.cpp do_something.hpp main.cpp)
target_link_libraries(AutoMake stdc++fs)
