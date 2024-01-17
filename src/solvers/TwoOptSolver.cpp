//
// Created by francesco on 06/01/24.
//

#include "TwoOptSolver.h"
#include <sstream>

Path TwoOptSolver::_solve(const Graph &graph, const Path &initial_path) {
    Timer timer;
    timer.start();
    double best_neighbour_cost, previous_cost;
    Path previous_path = initial_path;
    do {
        auto [i, j] = best_neighbour(graph, previous_path);
        Path best_neighbour_path = previous_path.reverse_sub_path(i, j);
        previous_cost = graph.eval_path(previous_path);
        best_neighbour_cost = graph.eval_path(best_neighbour_path);
        trace.push_back(previous_path);
        previous_path = best_neighbour_path;
    } while (best_neighbour_cost < previous_cost && timer.get_time_milliseconds() < time_limit * 1000);
    return trace.back();
}

std::string TwoOptSolver::evaluated_trace_as_string(const Graph &graph, bool extended) const {
    std::stringstream ss;
    ss << "Execution time: " << execution_time_milliseconds << " ms\n"
       << "Solution value: " << graph.eval_path(solution) << "\n"
       << "Solution path: " << solution.as_string() << "\n";
    if (extended) ss << NeighbourhoodSolver::evaluated_trace_as_string(graph, false);
    return ss.str();
}

std::pair<int, int> TwoOptSolver::best_neighbour(const Graph &graph, const Path &path) {
    double initial_cost = graph.eval_path(path);
    double cur_best = 1e20;
    int size = graph.size();
    std::pair<int, int> best_neighbour = {0, 0};
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

TwoOptSolver::TwoOptSolver(unsigned int time_limit) : NeighbourhoodSolver(time_limit) {}
