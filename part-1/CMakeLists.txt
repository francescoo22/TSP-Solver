cmake_minimum_required(VERSION 3.26)
project(part_1)

set(CMAKE_CXX_STANDARD 20)

set(CPX_BASE "/opt/ibm/ILOG/CPLEX_Studio2211")
set(CPX_INCDIR "${CPX_BASE}/cplex/include")
set(CPX_LIBDIR "${CPX_BASE}/cplex/lib/x86-64_linux/static_pic/libcplex.a")

include_directories(${CPX_INCDIR})

add_executable(part_1 src/main.cpp
        src/cpxmacro.h
)

target_link_libraries(part_1 ${CPX_LIBDIR})
