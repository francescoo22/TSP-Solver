CC = g++
CPPFLAGS = -g -Wall -O2
LDFLAGS =

CPX_BASE    = /opt/ibm/ILOG/CPLEX_Studio2211
CPX_INCDIR  = $(CPX_BASE)/cplex/include
CPX_LIBDIR  = $(CPX_BASE)/cplex/lib/x86-64_linux/static_pic
CPX_LDFLAGS = -lcplex -lm -pthread -ldl

SRC_DIR = ../src

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/graph/Graph.cpp \
       $(SRC_DIR)/graph/Path.cpp \
       $(SRC_DIR)/graph/Point.cpp \
       $(SRC_DIR)/solvers/TwoOptSolver.cpp \
       $(SRC_DIR)/solvers/TabuSearchSolver.cpp \
       $(SRC_DIR)/solvers/CplexSolver.cpp \
       $(SRC_DIR)/solvers/NeighbourhoodSolver.cpp \
       $(SRC_DIR)/Timer.cpp \
       $(SRC_DIR)/InputGenerator.cpp \
       $(SRC_DIR)/solvers/TspSolver.cpp

OBJ = $(SRCS:.cpp=.o)

%.o: %.cpp
		$(CC) $(CPPFLAGS) -I$(CPX_INCDIR) -c $^ -o $@

main: $(OBJ)
		$(CC) $(CPPFLAGS) $(OBJ) -o main -L$(CPX_LIBDIR) $(CPX_LDFLAGS)

clean:
		rm -rf $(OBJ) main

.PHONY: clean

