//
// Created by francesco on 06/12/23.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include "Graph.h"
#include "Path.h"

Graph::Graph(const string &file) {
    ifstream in(file);
    in >> _size;
    adj = vector<vector<double>>(_size, vector<double>(_size));
    for (auto &v: adj)
        for (double &x: v) in >> x;
    in.close();
}

void Graph::print() const {
    cout << _size << endl;
    for (const auto &v: adj) {
        for (double x: v) cout << x << " ";
        cout << endl;
    }
}

double Graph::eval_path(const Path &path) const {
    double res = 0;
    for (int i = 0; i < _size; i++) {
        res += adj[path[i]][path[i + 1]];
    }
    return res;
}

Path Graph::get_random_path() const {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    auto res = vector<int>(_size);
    for (int i = 0; i < _size; i++) res[i] = i;
    std::shuffle(std::begin(res), std::end(res), rng);
    return Path(res);
}

double Graph::neighbour_delta(const Path &path, int i, int j) const {
    int from = path[i], prev_from = path[i - 1], to = path[j], next_to = path[j + 1];
    return -adj[from][prev_from] - adj[to][next_to] + adj[from][next_to] + adj[to][prev_from];
}

int Graph::size() const {
    return _size;
}
