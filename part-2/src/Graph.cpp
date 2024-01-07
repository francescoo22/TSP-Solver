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

Graph::Graph(const vector<vector<double>> &adj) {
    _size = adj.size();
    for (const auto &v: adj)
        if (v.size() != _size) throw invalid_argument("Graph can only be initialized with a square matrix");

    for (int i = 0; i < _size; i++)
        for (int j = i + 1; j < _size; j++)
            if (adj[i][j] != adj[j][i]) throw invalid_argument("Graph should be non-directed");

    this->adj = adj;
}

Graph::operator std::string() const {
    string res;
    res += to_string(_size) + "\n";
    for (const auto &v: adj) {
        for (double x: v) res += to_string(x) + " ";
        res += "\n";
    }
    return res;
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

void Graph::generate_input(int size) {
    ofstream out("../inputs/tsp" + to_string(size) + ".dat");
    vector<vector<double>> adj(size, vector<double>(size, 0));

    uniform_real_distribution<double> distribution(0, 50);
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            adj[i][j] = adj[j][i] = distribution(rng);

    Graph res(adj);
    out << string(res);
}
