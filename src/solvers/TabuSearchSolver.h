//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TABUSEARCHSOLVER_H
#define TSP_SOLVER_CPP_TABUSEARCHSOLVER_H


#include <deque>
#include <map>
#include "NeighbourhoodSolver.h"

class TabuSearchSolver : public NeighbourhoodSolver {
public:
    explicit TabuSearchSolver(int tabu_list_length, int max_iterations);

    [[nodiscard]] std::string evaluated_trace_as_string(const Graph &graph) const override;

    [[nodiscard]] Path best_neighbour(const Graph &graph, const Path &path);

private:
    std::deque<Path> tabu_list;
    std::map<Path, bool> tabu_map;
    int tabu_list_length;
    int max_iterations;

    [[nodiscard]] Path _solve(const Graph &graph, const Path &initial_path) override;

    void _reset() override;

    // ********** STOPPING CRITERIA **********
    // TODO: refactor stopping criteria
//    int max_iterations, time_limit, max_not_improving_iterations;
    // TODO: Empty neighbourhood and no overruling
};


#endif //TSP_SOLVER_CPP_TABUSEARCHSOLVER_H
