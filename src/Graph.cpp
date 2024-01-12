//
// Created by francesco on 06/12/23.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include "Graph.h"
#include "Path.h"

Graph::Graph(const std::vector<Point> &points) {
    _size = points.size();
    _adj = std::vector<std::vector<double>>(_size, std::vector<double>(_size));
    _points = points;
    for (int i = 0; i < _size; i++)
        for (int j = i; j < _size; j++)
            _adj[i][j] = _adj[j][i] = points[i].distance(points[j]);
}

std::string Graph::as_string() const {
    std::stringstream ss;
    ss << _size << "\n";
    for (const auto &v: _adj) {
        for (double x: v) ss << x << " ";
        ss << "\n";
    }
    return ss.str();
}

double Graph::eval_path(const Path &path) const {
    double res = 0;
    for (int i = 0; i < _size; i++) {
        res += _adj[path[i]][path[i + 1]];
    }
    return res;
}

Path Graph::get_random_path() const {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    auto res = std::vector<int>(_size);
    for (int i = 0; i < _size; i++) res[i] = i;
    std::shuffle(std::begin(res), std::end(res), rng);
    return Path(res);
}

double Graph::neighbour_delta(const Path &path, int i, int j) const {
    int from = path[i], prev_from = path[i - 1], to = path[j], next_to = path[j + 1];
    return -_adj[from][prev_from] - _adj[to][next_to] + _adj[from][next_to] + _adj[to][prev_from];
}

int Graph::size() const {
    return _size;
}

void Graph::generate_input(int size) {
    std::ofstream out("../inputs/tsp" + std::to_string(size) + ".dat");
    std::uniform_real_distribution<double> distribution(0, 100);
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    out << size << "\n";

    for (int i = 0; i < size; i++) {
        double x = std::round(100. * distribution(rng)) / 100.;
        double y = std::round(100. * distribution(rng)) / 100.;
        out << x << " " << y << "\n";
    }
}

double Graph::get_edge(int i, int j) const {
    if (i >= _size || j >= _size) throw std::invalid_argument("Edge out of bounds");
    return _adj[i][j];
}

Graph Graph::from_file(const std::string &file) {
    std::ifstream in(file);
    int size;
    in >> size;
    std::vector<Point> points;
    for (int i = 0; i < size; i++) {
        double x, y;
        in >> x >> y;
        points.emplace_back(x, y);
    }
    in.close();
    return Graph(points);
}

const std::vector<Point> &Graph::points_of_path(const Path &path) const {
    auto *res = new std::vector<Point>;
    for (int i: path.as_vector()) {
        res->push_back(_points[i]);
    }
    return *res;
}
