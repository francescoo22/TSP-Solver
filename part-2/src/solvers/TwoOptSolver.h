//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TWOOPTSOLVER_H
#define TSP_SOLVER_CPP_TWOOPTSOLVER_H


#include "NeighbourhoodSolver.h"

class TwoOptSolver : public NeighbourhoodSolver {
public:
    [[nodiscard]] Path solve(const Graph &graph, const Path &initial_path) override;

    [[nodiscard]] std::string evaluated_trace_as_string(const Graph &graph) const override;

    [[nodiscard]] static std::pair<int, int> best_neighbour(const Graph &graph, const Path &path);

private:
    Path solution;
};


#endif //TSP_SOLVER_CPP_TWOOPTSOLVER_H
