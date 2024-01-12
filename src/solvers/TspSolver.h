//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TSPSOLVER_H
#define TSP_SOLVER_CPP_TSPSOLVER_H


#include "../Path.h"
#include "../Graph.h"
#include "../Timer.h"

class TspSolver {
public:
    const Path &solve(const Graph &graph, const Path &initial_path);

    [[nodiscard]] virtual std::string evaluated_trace_as_string(const Graph &graph) const = 0;

protected:
    Path solution;
    unsigned execution_time_milliseconds{};

    [[nodiscard]] virtual Path _solve(const Graph &graph, const Path &initial_path) = 0;

    virtual void _reset() = 0;
};


#endif //TSP_SOLVER_CPP_TSPSOLVER_H
