#include <fstream>
#include <cassert>
#include "Graph.h"
#include "solvers/TwoOptSolver.h"
#include "solvers/TabuSearchSolver.h"
#include "solvers/SimplexSolver.h"

int main() {
    std::string file = "../inputs/tsp12.dat";
    std::ofstream opt_out("../outputs/2-opt_trace.txt");
    std::ofstream ts_out("../outputs/ts_trace.txt");

    Graph graph(file);
    Path path(graph.size());

    // ************ SIMPLEX SOLUTION ************
    SimplexSolver simplex_solver;
    simplex_solver.solve(graph, path);

    // ************ 2-OPT SOLUTION ************
    TwoOptSolver two_opt_solver;
    Path two_opt_sol = two_opt_solver.solve(graph, path);
    opt_out << two_opt_solver.evaluated_trace_as_string(graph);
    if (file == "../inputs/tsp60.dat") assert(std::abs(graph.eval_path(two_opt_sol) - 669.3) < 0.1);

    // ************ TABU-SEARCH SOLUTION ************
    TabuSearchSolver tabu_search_solver(50, 1000);
    Path tabu_sol = tabu_search_solver.solve(graph, path);
    ts_out << tabu_search_solver.evaluated_trace_as_string(graph);

    //    Graph::generate_input(200);
}
