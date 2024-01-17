//
// Created by francesco on 08/01/24.
//

#include "NeighbourhoodSolver.h"
#include <sstream>

std::string NeighbourhoodSolver::evaluated_trace_as_string(const Graph &graph, bool extended) const {
    std::stringstream ss;
    ss << "Trace:\n";
    for (const Path &path: trace) {
        ss << graph.eval_path(path) << " --> " << path.as_string() << "\n";
    }
    return ss.str();
}

void NeighbourhoodSolver::_reset() {
    trace.clear();
}

NeighbourhoodSolver::NeighbourhoodSolver(unsigned int time_limit) : TspSolver(time_limit) {}
