//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TSPSOLVER_H
#define TSP_SOLVER_CPP_TSPSOLVER_H


#include "../graph/Path.h"
#include "../graph/Graph.h"
#include "../Timer.h"

class TspSolver {
public:
    explicit TspSolver(unsigned int time_limit);

    const Path &solve(const Graph &graph, const Path &initial_path);

    [[nodiscard]] virtual std::string evaluated_trace_as_string(const Graph &graph, bool extended) const = 0;

protected:
    Path solution;
    unsigned execution_time_milliseconds;
    unsigned time_limit;

    [[nodiscard]] virtual Path _solve(const Graph &graph, const Path &initial_path) = 0;

    virtual void _reset() = 0;
};


#endif //TSP_SOLVER_CPP_TSPSOLVER_H
