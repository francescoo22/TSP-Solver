//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TWOOPTSOLVER_H
#define TSP_SOLVER_CPP_TWOOPTSOLVER_H


#include "TspSolver.h"

class TwoOptSolver : public TspSolver {
public:
    [[nodiscard]] Path solve(const Graph &graph, const Path &initial_path) override;

    [[nodiscard]] const vector<Path> &get_trace() const override;

    string evaluated_trace_as_string(const Graph &graph) const override;

private:
    vector<Path> trace;
};


#endif //TSP_SOLVER_CPP_TWOOPTSOLVER_H
