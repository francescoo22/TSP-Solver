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
    explicit SimplexSolver(unsigned int time_limit = 0);

    [[nodiscard]] std::string evaluated_trace_as_string(const Graph &graph) const override;

private:
    int status;
    cpxenv *env;
    cpxlp *lp;
    std::map<std::tuple<char, int, int>, int> tuple_to_index;
    std::vector<std::tuple<char, int, int>> index_to_tuple;

    Path _solve(const Graph &graph, const Path &initial_path) override;

    void _reset() override;

    static char **from_string(const std::string &s);

    static bool equal(double a, double b);

    Path solution_path();

    void setupLP(int size, const Graph &graph);
};


#endif //TSP_SOLVER_CPP_SIMPLEXSOLVER_H
