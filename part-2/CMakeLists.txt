cmake_minimum_required(VERSION 3.26)
project(TSP_solver_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(TSP_solver_cpp main.cpp
        Graph.cpp
        Graph.h)
