#include <iostream>
#include <fstream>
#include <cassert>
#include "Graph.h"
#include "solvers/TwoOptSolver.h"
#include "solvers/TabuSearchSolver.h"

using namespace std;

int main() {
    string file = "../inputs/tsp60.dat";
    ofstream out("../outputs/trace.txt");

    Graph graph(file);
    Path path(graph.size());

    // ************ 2-OPT SOLUTION ************
    TwoOptSolver two_opt_solver;
    Path two_opt_sol = two_opt_solver.solve(graph, path);
    out << two_opt_solver.evaluated_trace_as_string(graph) << endl;
    if (file == "../inputs/tsp60.dat") assert(abs(graph.eval_path(two_opt_sol) - 669.3) < 0.1);

    // ************ TABU-SEARCH SOLUTION ************
    TabuSearchSolver tabu_search_solver(50, 2000);
    Path tabu_sol = tabu_search_solver.solve(graph, path);
    out << tabu_search_solver.evaluated_trace_as_string(graph);
}
