//
// Created by francesco on 08/01/24.
//

#include "NeighbourhoodSolver.h"
#include <sstream>

std::string NeighbourhoodSolver::evaluated_trace_as_string(const Graph &graph) const {
    std::stringstream ss;
    for (const Path &path: trace) {
        ss << graph.eval_path(path) << " --> " << path.as_string() << "\n";
    }
    return ss.str();
}
