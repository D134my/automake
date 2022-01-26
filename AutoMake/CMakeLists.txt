cmake_minimum_required(VERSION 3.5)

project(AutoMake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AutoMake helperfunctions.hpp helperfunctions.cpp main.cpp catch_errors.hpp typeofcontents.hpp scan.cpp scan.hpp)
target_link_libraries(AutoMake stdc++fs)
