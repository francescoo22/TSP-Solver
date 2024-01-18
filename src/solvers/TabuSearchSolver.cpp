//
// Created by francesco on 06/01/24.
//

#include <sstream>
#include "TabuSearchSolver.h"

TabuSearchSolver::TabuSearchSolver(unsigned int tabu_list_length, unsigned int max_iterations,
                                   unsigned int max_non_increasing_iterations,
                                   unsigned long long int time_limit)
        : NeighbourhoodSolver(time_limit),
          tabu_list_length(tabu_list_length),
          max_iterations(max_iterations),
          max_non_increasing_iterations(max_non_increasing_iterations),
          stopping_criteria(StoppingCriteria::UNKNOWN) {}

Path TabuSearchSolver::_solve(const Graph &graph, const Path &initial_path) {
    Timer timer;
    timer.start();
    trace.push_back(initial_path);

    Path best_path = initial_path;
    Path cur_path = initial_path;
    double best_sol = graph.eval_path(initial_path);
    int iterations = 0, non_increasing_iterations = 0;
    while (!stop(iterations, non_increasing_iterations, timer)) {
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
        iterations++;
    }
    return best_path;
}

std::string TabuSearchSolver::evaluated_trace_as_string(const Graph &graph, bool extended) const {
    std::stringstream ss;
    ss << "Execution time: " << execution_time_milliseconds << " ms\n"
       << "Solution value: " << graph.eval_path(solution) << "\n"
       << "Solution path: " << solution.as_string() << "\n"
       << "Stopping criteria: " << as_string(stopping_criteria) << "\n";
    if (extended) ss << NeighbourhoodSolver::evaluated_trace_as_string(graph, false);
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

bool TabuSearchSolver::stop(unsigned int iterations, unsigned int non_increasing_iterations, const Timer &timer) {
    if (iterations > max_iterations)
        stopping_criteria = StoppingCriteria::MAX_ITERATIONS;
    else if (non_increasing_iterations > max_non_increasing_iterations)
        stopping_criteria = StoppingCriteria::MAX_NON_INCREASING_ITERATIONS;
    else if (timer.get_time_milliseconds() > time_limit * 1000)
        stopping_criteria = StoppingCriteria::TIME_LIMIT;
    else return false;
    return true;
}

std::string TabuSearchSolver::as_string(StoppingCriteria criteria) {
    switch (criteria) {
        case StoppingCriteria::UNKNOWN:
            return "UNKNOWN";
        case StoppingCriteria::MAX_ITERATIONS:
            return "MAX_ITERATIONS";
        case StoppingCriteria::MAX_NON_INCREASING_ITERATIONS:
            return "MAX_NON_INCREASING_ITERATIONS";
        case StoppingCriteria::TIME_LIMIT:
            return "TIME_LIMIT";
        default:
            return "Invalid StoppingCriteria";
    }
}
