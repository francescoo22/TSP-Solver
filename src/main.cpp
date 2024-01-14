#include <fstream>
#include <cassert>
#include <iostream>
#include "graph/Graph.h"
#include "solvers/TwoOptSolver.h"
#include "solvers/TabuSearchSolver.h"
#include "solvers/SimplexSolver.h"
#include "graph/Point.h"
#include "InputGenerator.h"

int main() {
    std::string file = "../inputs/tsp1000.dat";
    std::ofstream simplex_out("../outputs/simplex.txt");
    std::ofstream opt_out("../outputs/2-opt_trace.txt");
    std::ofstream ts_out("../outputs/ts_trace.txt");
    int time_limit = 2;

//    Graph graph(file);
    Graph graph = Graph::from_file(file);
    Path path(graph.size());

//    std::cout << graph.as_string();

    // ************ SIMPLEX SOLUTION ************
//    SimplexSolver simplex_solver(time_limit);
//    simplex_solver.solve(graph, path);
//    simplex_out << simplex_solver.evaluated_trace_as_string(graph);

    // ************ 2-OPT SOLUTION ************
    TwoOptSolver two_opt_solver(time_limit);
    Path two_opt_sol = two_opt_solver.solve(graph, path);
    opt_out << two_opt_solver.evaluated_trace_as_string(graph);

    // ************ TABU-SEARCH SOLUTION ************
    TabuSearchSolver tabu_search_solver(100, TabuSearchSolver::NO_LIMIT, 300, time_limit);
    tabu_search_solver.solve(graph, path);
    ts_out << tabu_search_solver.evaluated_trace_as_string(graph);

//    Graph::generate_input("tsp500", 500);
//    InputGenerator input_generator(100, 50);
//    input_generator.generate_shaped_input("test", 50);
}
