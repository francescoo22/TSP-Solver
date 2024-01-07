//
// Created by francesco on 06/12/23.
//

#ifndef TSP_SOLVER_CPP_GRAPH_H
#define TSP_SOLVER_CPP_GRAPH_H

#include <vector>
#include <string>
#include "Path.h"

class Graph {
public:
    explicit Graph(const std::string &file);

    explicit Graph(const std::vector<std::vector<double>> &adj);

    explicit operator std::string() const;

    [[nodiscard]] int size() const;

    [[nodiscard]] double eval_path(const Path &path) const;

    [[nodiscard]] double neighbour_delta(const Path &path, int i, int j) const;

    [[nodiscard]] Path get_random_path() const;

    static void generate_input(int size);

private:
    int _size{};
    std::vector<std::vector<double>> adj;

};

#endif //TSP_SOLVER_CPP_GRAPH_H
