cmake_minimum_required(VERSION 3.26)
project(TSP_solver_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(TSP_solver_cpp src/main.cpp
        src/Graph.cpp
        src/Graph.h
        src/Path.cpp
        src/Path.h
        src/solvers/TspSolver.h
        src/solvers/TwoOptSolver.cpp
        src/solvers/TwoOptSolver.h)
