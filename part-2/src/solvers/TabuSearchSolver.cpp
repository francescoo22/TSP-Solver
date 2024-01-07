//
// Created by francesco on 06/01/24.
//

#include "TabuSearchSolver.h"

TabuSearchSolver::TabuSearchSolver(int tabu_list_length, int max_iterations) : tabu_list_length(tabu_list_length),
                                                                               max_iterations(max_iterations) {}

Path TabuSearchSolver::solve(const Graph &graph, const Path &initial_path) {
    tabu_map.clear();
    tabu_list.clear();
    trace.clear();

    trace.push_back(initial_path);

    Path best_path = initial_path;
    Path cur_path = initial_path;
    for (int i = 0; i < max_iterations; i++) {
        cur_path = best_neighbour(graph, cur_path);
        trace.push_back(cur_path);
        // TODO: try to avoid evaluation
        if (graph.eval_path(best_path) > graph.eval_path(cur_path)) best_path = cur_path;
    }

    solution = best_path;
    return best_path;
}

string TabuSearchSolver::evaluated_trace_as_string(const Graph &graph) const {
    return "**************** TABU SEARCH SOLUTION ****************\n"
           "Solution: " + to_string(graph.eval_path(solution)) + "\n"
           + TspSolver::evaluated_trace_as_string(graph) + "\n";
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

    tabu_map[best_neighbour] = true;
    if (tabu_list.size() == tabu_list_length) {
        tabu_map[tabu_list.back()] = false;
        tabu_list.pop_back();
        tabu_list.push_front(best_neighbour);
    }
    return best_neighbour;
}
