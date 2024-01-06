#include <iostream>
#include <cassert>
#include "Graph.h"
#include "solvers/TwoOptSolver.h"

using namespace std;

int main() {
    string file = "../inputs/tsp60.dat";

    Graph graph(file);
    Path path(graph.size);
    TwoOptSolver solver;

    Path tsp_sol = solver.solve(graph, path);
    cout << solver.evaluated_trace_as_string(graph) << endl;
    assert(abs(graph.eval_path(tsp_sol) - 669.3) < 0.1);
}
