//
// Created by francesco on 06/01/24.
//

#include "TwoOptSolver.h"

Path TwoOptSolver::solve(const Graph &graph, const Path &initial_path) {
    auto [i, j] = graph.best_neighbour(initial_path);
    Path best_neighbour_path = initial_path.reverse_sub_path(i, j);
    double initial_cost = graph.eval_path(initial_path);
    double best_neighbour_cost = graph.eval_path(best_neighbour_path);
    trace.push_back(initial_path);
    if (best_neighbour_cost >= initial_cost) {
        return initial_path;
    } else {
        return solve(graph, best_neighbour_path);
    }
}

const vector<Path> &TwoOptSolver::get_trace() const {
    return trace;
}

string TwoOptSolver::evaluated_trace_as_string(const Graph &graph) const {
    string res;
    for (const Path &path: trace) {
        res += path.as_string() + " --> " + to_string(graph.eval_path(path)) + "\n";
    }
    res.pop_back();
    return res;
}
