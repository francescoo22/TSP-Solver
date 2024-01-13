#include <fstream>
#include <cassert>
#include "graph/Graph.h"
#include "solvers/TwoOptSolver.h"
#include "solvers/TabuSearchSolver.h"
#include "solvers/SimplexSolver.h"
#include "graph/Point.h"

int main() {
    std::string file = "../inputs/tsp30.dat";
    std::ofstream simplex_out("../outputs/simplex.txt");
    std::ofstream opt_out("../outputs/2-opt_trace.txt");
    std::ofstream ts_out("../outputs/ts_trace.txt");

//    Graph graph(file);
    Graph graph = Graph::from_file(file);
    Path path(graph.size());

//    std::cout << graph.as_string();

    // ************ SIMPLEX SOLUTION ************
    SimplexSolver simplex_solver;
    simplex_solver.solve(graph, path);
    simplex_out << simplex_solver.evaluated_trace_as_string(graph);

    // ************ 2-OPT SOLUTION ************
    TwoOptSolver two_opt_solver;
    Path two_opt_sol = two_opt_solver.solve(graph, path);
    opt_out << two_opt_solver.evaluated_trace_as_string(graph);

    // ************ TABU-SEARCH SOLUTION ************
    TabuSearchSolver tabu_search_solver(50, 2000);
    tabu_search_solver.solve(graph, path);
    ts_out << tabu_search_solver.evaluated_trace_as_string(graph);

//    Graph::generate_input("tsp150", 150);
}
