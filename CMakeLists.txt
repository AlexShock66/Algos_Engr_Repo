cmake_minimum_required(VERSION 3.16.3)
project(Data_Structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph_generation src/graph_generation_runner.cpp src/GraphGenerator.h )

add_executable(graph_coloring src/graph_coloring.cpp src/GraphColorer.h)

add_executable(graph_stats src/graph_stats.cpp src/GraphGenerator.h)

add_executable(playground src/playground.cpp src/Data_Structures/Linked_List.h src/Data_Structures/Adj_List.h)
add_executable(tests src/Tests/DS_Tests.cpp src/Catch/catch.hpp src/Catch/catch_config.cpp src/Data_Structures/Linked_List.h src/Data_Structures/Adj_List.h)