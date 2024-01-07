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
    explicit Graph(const string &);

    void print() const;

    [[nodiscard]] int size() const;

    [[nodiscard]] double eval_path(const Path &path) const;

    [[nodiscard]] double neighbour_delta(const Path &path, int i, int j) const;

    [[nodiscard]] Path get_random_path() const;

private:
    int _size{};
    vector<vector<double>> adj;

};

#endif //TSP_SOLVER_CPP_GRAPH_H
