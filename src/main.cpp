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
    std::string file = "../inputs/tsp50/tsp50_1.dat";
    std::ofstream simplex_out("../outputs/simplex.txt");
    std::ofstream opt_out("../outputs/2-opt_trace.txt");
    std::ofstream ts_out("../outputs/ts_trace.txt");
    int time_limit = 45 * 60;
    bool create = false;
    bool solve = true;


    if (create) {
        for (int i = 1; i <= 10; i++) {
            InputGenerator input_generator(100, 50);
            input_generator.generate_shaped_input("tsp200_" + std::to_string(i), 100, 200);
        }
    }

    if (solve) {
        for (int i = 1; i <= 10; i++) {
            // ************ SIMPLEX SOLUTION ************
            std::string test_size = "100";
            std::string input_path = "../inputs/tsp200/tsp200_" + std::to_string(i) + ".dat";
            Graph graph = Graph::from_file(input_path);
            Path path(graph.size());

//            SimplexSolver simplex_solver(time_limit);
//            simplex_solver.solve(graph, path);
//            simplex_out << input_path << "\n"
//                        << simplex_solver.evaluated_trace_as_string(graph, false) << "\n";

            // ************ 2-OPT SOLUTION ************
            TwoOptSolver two_opt_solver(time_limit);
            Path two_opt_sol = two_opt_solver.solve(graph, path);
            opt_out << input_path << "\n"
                    << two_opt_solver.evaluated_trace_as_string(graph, false) << "\n";

            // ************ TABU-SEARCH SOLUTION ************
            TabuSearchSolver tabu_search_solver(700, TabuSearchSolver::NO_LIMIT, 1000, time_limit);
            tabu_search_solver.solve(graph, path);
            ts_out << input_path << "\n"
                   << tabu_search_solver.evaluated_trace_as_string(graph, false) << "\n";
        }
    }

}
