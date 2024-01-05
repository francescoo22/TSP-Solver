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
    in >> size;
    adj = vector<vector<double>>(size, vector<double>(size));
    for (auto &v: adj)
        for (double &x: v) in >> x;
    in.close();
}

void Graph::print() {
    cout << size << endl;
    for (const auto &v: adj) {
        for (double x: v) cout << x << " ";
        cout << endl;
    }
}

double Graph::eval_path(const Path &path) {
    double res = 0;
    for (int i = 0; i < size; i++) {
        res += adj[path[i]][path[i + 1]];
    }
    return res;
}

Path Graph::get_random_path() const {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    auto res = vector<int>(size);
    for (int i = 0; i < size; i++) res[i] = i;
    std::shuffle(std::begin(res), std::end(res), rng);
    return Path(res);
}

pair<int, int> Graph::best_neighbour(const Path &path) {
    double initial_cost = eval_path(path);
    double cur_best = 1e20;
    pair<int, int> best_neighbour = {0, 0};
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (i == 0 && j == size - 1) continue;

            int from = path[i], prev_from = path[i - 1], to = path[j], next_to = path[j + 1];
            double cost = initial_cost - adj[from][prev_from] - adj[to][next_to] +
                          adj[from][next_to] + adj[to][prev_from];
            if (cost < cur_best) {
                cur_best = cost;
                best_neighbour = {i, j};
            }
        }
    }
    return best_neighbour;
}

void Graph::print_path_evaluation(const Path &path) {
    cout << "path: " + path.as_string();
    cout << " --> " << eval_path(path) << endl;
}

Path Graph::solve_TSP(Path initial_path) {
    auto [i, j] = best_neighbour(initial_path);
    Path best_neighbour_path = initial_path.reverse_sub_path(i, j);
    double initial_cost = eval_path(initial_path);
    double best_neighbour_cost = eval_path(best_neighbour_path);
    if (best_neighbour_cost >= initial_cost) {
        return initial_path;
    } else {
        print_path_evaluation(best_neighbour_path);
        return solve_TSP(best_neighbour_path);
    }
}
