cmake_minimum_required(VERSION 3.26)
project(TSP_solver_cpp)

set(CMAKE_CXX_STANDARD 20)

set(CPX_BASE "/opt/ibm/ILOG/CPLEX_Studio2211")
set(CPX_INCDIR "${CPX_BASE}/cplex/include")
set(CPX_LIBDIR "${CPX_BASE}/cplex/lib/x86-64_linux/static_pic/libcplex.a")

include_directories(${CPX_INCDIR})

add_executable(TSP_solver_cpp src/main.cpp
        src/graph/Graph.cpp
        src/graph/Graph.h
        src/graph/Path.cpp
        src/graph/Path.h
        src/solvers/TspSolver.h
        src/solvers/TwoOptSolver.cpp
        src/solvers/TwoOptSolver.h
        src/solvers/TabuSearchSolver.cpp
        src/solvers/TabuSearchSolver.h
        src/solvers/SimplexSolver.cpp
        src/solvers/SimplexSolver.h
        src/solvers/NeighbourhoodSolver.cpp
        src/solvers/NeighbourhoodSolver.h
        src/graph/Point.cpp
        src/graph/Point.h
        src/Timer.cpp
        src/Timer.h
        src/solvers/TspSolver.cpp)

target_link_libraries(TSP_solver_cpp ${CPX_LIBDIR})