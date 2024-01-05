#include <iostream>
#include <cassert>
#include "Graph.h"

using namespace std;

int main() {
    string file = "../inputs/tsp60.dat";
    Graph graph(file);

//    Path path = graph.get_random_path();
    Path path(graph.size);
    graph.print_path_evaluation(path);
    Path TSP_sol = graph.solve_TSP(path);
    assert(abs(graph.eval_path(TSP_sol) - 669.3) < 0.1);
}
