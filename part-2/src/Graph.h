//
// Created by francesco on 06/12/23.
//

#ifndef TSP_SOLVER_CPP_GRAPH_H
#define TSP_SOLVER_CPP_GRAPH_H

#include <vector>
#include <string>
#include "Path.h"

using namespace std;

class Graph {
public:
    int size{};

    explicit Graph(const string &);

    void print();

    double eval_path(const Path &path);

    [[nodiscard]] Path get_random_path() const;

    pair<int, int> best_neighbour(const Path &path);

    void print_path_evaluation(const Path &path);

    Path solve_TSP(Path initial_path);

private:
    vector<vector<double>> adj;

};

#endif //TSP_SOLVER_CPP_GRAPH_H
