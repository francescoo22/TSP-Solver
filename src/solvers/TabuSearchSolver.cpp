//
// Created by francesco on 06/01/24.
//

#include <sstream>
#include "TabuSearchSolver.h"

TabuSearchSolver::TabuSearchSolver(int tabu_list_length, int max_non_increasing_iterations, unsigned int time_limit)
        : NeighbourhoodSolver(time_limit),
          tabu_list_length(tabu_list_length),
          max_non_increasing_iterations(max_non_increasing_iterations) {}

Path TabuSearchSolver::_solve(const Graph &graph, const Path &initial_path) {
    Timer timer;
    timer.start();
    trace.push_back(initial_path);

    Path best_path = initial_path;
    Path cur_path = initial_path;
    double best_sol = graph.eval_path(initial_path);
    int non_increasing_iterations = 0;
//    for (int i = 0; i < max_non_increasing_iterations; i++) {
    while (non_increasing_iterations < max_non_increasing_iterations &&
           timer.get_time_milliseconds() < time_limit * 1000) {
        cur_path = best_neighbour(graph, cur_path);
        double cur_sol = graph.eval_path(cur_path);
        trace.push_back(cur_path);
        if (best_sol > cur_sol) {
            best_path = cur_path;
            best_sol = cur_sol;
            non_increasing_iterations = 0;
        } else {
            non_increasing_iterations++;
        }
    }
    return best_path;
}

std::string TabuSearchSolver::evaluated_trace_as_string(const Graph &graph) const {
    std::stringstream ss;
    ss << "******************* TABU SEARCH SOLUTION = "
       << graph.eval_path(solution)
       << " *******************\n"
       << "Execution time: " << execution_time_milliseconds << " ms\n"
       << NeighbourhoodSolver::evaluated_trace_as_string(graph);
    return ss.str();
}

Path TabuSearchSolver::best_neighbour(const Graph &graph, const Path &path) {
    double initial_cost = graph.eval_path(path);
    double cur_best = 1e20;
    int size = graph.size();
    Path best_neighbour = path;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (j - i >= size - 2) continue;

            double cost = initial_cost + graph.neighbour_delta(path, i, j);
            if (cost < cur_best) {
                Path new_path = path.reverse_sub_path(i, j);
                if (!tabu_map[new_path]) {
                    cur_best = cost;
                    best_neighbour = new_path;
                }
            }
        }
    }

    if (tabu_list.size() == tabu_list_length) {
        tabu_map[tabu_list.back()] = false;
        tabu_list.pop_back();
    }
    tabu_map[best_neighbour] = true;
    tabu_list.push_front(best_neighbour);

    return best_neighbour;
}

void TabuSearchSolver::_reset() {
    NeighbourhoodSolver::_reset();
    tabu_map.clear();
    tabu_list.clear();
}
