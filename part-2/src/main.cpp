#include <iostream>
#include "Graph.h"

int main() {
    string file = "../inputs/tsp60.dat";
    Graph graph(file);

    auto path = graph.get_starting_path();
    graph.print_path_evaluation(path);
    auto TSP_sol = graph.solve_TSP(path);
}
