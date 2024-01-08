//
// Created by francesco on 08/01/24.
//

#ifndef TSP_SOLVER_CPP_SIMPLEXSOLVER_H
#define TSP_SOLVER_CPP_SIMPLEXSOLVER_H


#include "TspSolver.h"
#include <ilcplex/cplex.h>
#include <map>

class SimplexSolver : public TspSolver {
public:
    Path solve(const Graph &graph, const Path &initial_path) override;

    [[nodiscard]] std::string evaluated_trace_as_string(const Graph &graph) const override;

private:
    std::map<std::tuple<char, int, int>, int> var_index;

    static char **from_string(const std::string &s);

    void setupLP(CPXENVptr env, CPXLPptr lp, int size, const Graph &graph);
};


#endif //TSP_SOLVER_CPP_SIMPLEXSOLVER_H
