//
// Created by francesco on 08/01/24.
//

#ifndef TSP_SOLVER_CPP_NEIGHBOURHOODSOLVER_H
#define TSP_SOLVER_CPP_NEIGHBOURHOODSOLVER_H


#include "TspSolver.h"

class NeighbourhoodSolver : public TspSolver {
public:
    explicit NeighbourhoodSolver(unsigned int time_limit);

    [[nodiscard]] std::string evaluated_trace_as_string(const Graph &graph) const override;

protected:
    std::vector<Path> trace;

    void _reset() override;
};


#endif //TSP_SOLVER_CPP_NEIGHBOURHOODSOLVER_H
