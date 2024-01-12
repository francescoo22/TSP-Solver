//
// Created by francesco on 06/12/23.
//

#ifndef TSP_SOLVER_CPP_GRAPH_H
#define TSP_SOLVER_CPP_GRAPH_H

#include <vector>
#include <string>
#include "Path.h"
#include "Point.h"

class Graph {
public:
    explicit Graph(const std::vector<Point> &points);

    [[nodiscard]] std::string as_string() const;

    [[nodiscard]] int size() const;

    [[nodiscard]] double get_edge(int i, int j) const;

    [[nodiscard]] double eval_path(const Path &path) const;

    [[nodiscard]] double neighbour_delta(const Path &path, int i, int j) const;

    [[nodiscard]] Path get_random_path() const;

    [[nodiscard]] const std::vector<Point> &points_of_path(const Path &path) const;

    static void generate_input(int size);

    static Graph from_file(const std::string &file);

private:
    unsigned long _size;
    std::vector<Point> _points;
    std::vector<std::vector<double>> _adj;

};

#endif //TSP_SOLVER_CPP_GRAPH_H
