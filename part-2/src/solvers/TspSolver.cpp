//
// Created by francesco on 07/01/24.
//
#include "TspSolver.h"

string TspSolver::evaluated_trace_as_string(const Graph &graph) const {
    string res;
    for (const Path &path: trace) {
        res += to_string(graph.eval_path(path)) + " --> " + path.as_string() + "\n";
    }
    res.pop_back();
    return res;
}

