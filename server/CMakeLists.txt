cmake_minimum_required(VERSION 3.27)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp SafeFile.cpp SafeFile.hpp)
