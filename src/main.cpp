#include <fstream>
#include <iostream>
#include "graph/Graph.h"
#include "solvers/TwoOptSolver.h"
#include "solvers/TabuSearchSolver.h"
#include "solvers/CplexSolver.h"
#include "graph/Point.h"

int main() {
    std::ofstream simplex_out("../outputs/simplex.txt");
    std::ofstream opt_out("../outputs/2-opt_trace.txt");
    std::ofstream ts_out("../outputs/ts_trace.txt");

    std::string file;
    std::cout << "Select instance size (25, 50 or 75)" << std::endl;
    std::cin >> file;
    if (file != "25" && file != "50" && file != "75") return 0;
    file = "../inputs/tsp" + file + ".dat";

    int time_limit;
    std::cout << "Select time limit for cplex solver (seconds)" << std::endl;
    std::cin >> time_limit;
    if (time_limit <= 0) return 0;

    Graph graph = Graph::from_file(file);
    Path path(graph.size());
    unsigned tabu_list_length = graph.size() * graph.size();
    unsigned max_iterations = 50 * graph.size();

    // ************ CPLEX SOLUTION ************
    CplexSolver simplex_solver(time_limit);
    simplex_solver.solve(graph, path);
    simplex_out << simplex_solver.evaluated_trace_as_string(graph, false);

    // ************ 2-OPT SOLUTION ************
    std::cout << "Solving with 2-opt..." << std::endl;
    TwoOptSolver two_opt_solver(time_limit);
    Path two_opt_sol = two_opt_solver.solve(graph, path);
    opt_out << two_opt_solver.evaluated_trace_as_string(graph, true);

    // ************ TABU-SEARCH SOLUTION ************
    std::cout << "Solving with tabu-search..." << std::endl;
    TabuSearchSolver tabu_search_solver(tabu_list_length,
                                        max_iterations,
                                        TabuSearchSolver::NO_LIMIT,
                                        TabuSearchSolver::NO_LIMIT);
    tabu_search_solver.solve(graph, path);
    ts_out << tabu_search_solver.evaluated_trace_as_string(graph, true);

    std::cout << "Results have been written in \"outputs\" directory" << std::endl;
}
