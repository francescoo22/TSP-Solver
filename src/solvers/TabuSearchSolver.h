//
// Created by francesco on 06/01/24.
//

#ifndef TSP_SOLVER_CPP_TABUSEARCHSOLVER_H
#define TSP_SOLVER_CPP_TABUSEARCHSOLVER_H


#include <deque>
#include <map>
#include "NeighbourhoodSolver.h"

enum class StoppingCriteria {
    UNKNOWN,
    MAX_ITERATIONS,
    MAX_NON_INCREASING_ITERATIONS,
    TIME_LIMIT
};

class TabuSearchSolver : public NeighbourhoodSolver {
public:
    explicit TabuSearchSolver(unsigned int tabu_list_length,
                              unsigned int max_iterations = NO_LIMIT,
                              unsigned int max_non_increasing_iterations = NO_LIMIT,
                              unsigned long long int time_limit = NO_LIMIT);

    [[nodiscard]] std::string evaluated_trace_as_string(const Graph &graph) const override;

    [[nodiscard]] Path best_neighbour(const Graph &graph, const Path &path);

    static const unsigned int NO_LIMIT = 1000000000;

    static std::string as_string(StoppingCriteria criteria);

private:
    std::deque<Path> tabu_list;
    std::map<Path, bool> tabu_map;
    unsigned int tabu_list_length;
    unsigned int max_iterations;
    unsigned int max_non_increasing_iterations;
    StoppingCriteria stopping_criteria;

    [[nodiscard]] Path _solve(const Graph &graph, const Path &initial_path) override;

    bool stop(unsigned iterations, unsigned non_increasing_iterations, const Timer &timer);

    void _reset() override;
};


#endif //TSP_SOLVER_CPP_TABUSEARCHSOLVER_H
