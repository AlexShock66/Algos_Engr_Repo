cmake_minimum_required(VERSION 3.24)
project(Data_Structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(Data_Structures main.cpp src/Linked_List.h src/test.cpp)

add_executable(tests src/test.cpp src/catch.hpp src/catch_config.cpp src/Linked_List.h)