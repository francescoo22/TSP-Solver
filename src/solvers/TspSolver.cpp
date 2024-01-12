//
// Created by francesco on 12/01/24.
//

#include "TspSolver.h"

const Path &TspSolver::solve(const Graph &graph, const Path &initial_path) {
    _reset();
    Timer timer;
    timer.start();
    solution = _solve(graph, initial_path);
    execution_time_milliseconds = timer.get_time_milliseconds();
    return solution;
}
