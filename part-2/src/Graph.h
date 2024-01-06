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

    void print() const;

    [[nodiscard]] double eval_path(const Path &path) const;

    [[nodiscard]] Path get_random_path() const;

    [[nodiscard]] pair<int, int> best_neighbour(const Path &path) const;

private:
    vector<vector<double>> adj;

};

#endif //TSP_SOLVER_CPP_GRAPH_H
