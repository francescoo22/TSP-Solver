//
// Created by francesco on 06/01/24.
//

#include "TwoOptSolver.h"
#include <sstream>

Path TwoOptSolver::solve(const Graph &graph, const Path &initial_path) {
//    TODO: make non-recursive and clear trace at the beginning

    auto [i, j] = best_neighbour(graph, initial_path);
    Path best_neighbour_path = initial_path.reverse_sub_path(i, j);
    double initial_cost = graph.eval_path(initial_path);
    double best_neighbour_cost = graph.eval_path(best_neighbour_path);
    trace.push_back(initial_path);
    if (best_neighbour_cost >= initial_cost) {
        return initial_path;
    } else {
        return solution = solve(graph, best_neighbour_path);
    }
}

string TwoOptSolver::evaluated_trace_as_string(const Graph &graph) const {
    stringstream ss;
    ss << "******************* 2-OPT SOLUTION = "
       << graph.eval_path(solution)
       << " *******************\n"
       << TspSolver::evaluated_trace_as_string(graph);
    return ss.str();
}

pair<int, int> TwoOptSolver::best_neighbour(const Graph &graph, const Path &path) {
    double initial_cost = graph.eval_path(path);
    double cur_best = 1e20;
    int size = graph.size();
    pair<int, int> best_neighbour = {0, 0};
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (i == 0 && j == size - 1) continue;

            double cost = initial_cost + graph.neighbour_delta(path, i, j);
            if (cost < cur_best) {
                cur_best = cost;
                best_neighbour = {i, j};
            }
        }
    }
    return best_neighbour;
}
