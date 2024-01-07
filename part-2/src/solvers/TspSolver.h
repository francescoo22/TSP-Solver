//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TSPSOLVER_H
#define TSP_SOLVER_CPP_TSPSOLVER_H


#include "../Path.h"
#include "../Graph.h"

class TspSolver {
public:
    [[nodiscard]] virtual Path solve(const Graph &graph, const Path &initial_path) = 0;

    [[nodiscard]] virtual std::string evaluated_trace_as_string(const Graph &graph) const;

protected:
    std::vector<Path> trace;
};


#endif //TSP_SOLVER_CPP_TSPSOLVER_H
