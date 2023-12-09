//
// Created by francesco on 06/12/23.
//

#ifndef TSP_SOLVER_CPP_GRAPH_H
#define TSP_SOLVER_CPP_GRAPH_H

#include <vector>
#include <string>
using namespace std;

class Graph {
public:
    explicit Graph(const string&);
    void print();
    double eval_path(const vector<int> &path);
    [[nodiscard]] vector<int> get_starting_path() const;
    pair<int, int> best_neighbour(const vector<int> &path);
    void print_path_evaluation(const vector<int> &path);
    static vector<int> reverse_path(int from, int to, const vector<int> &path);
    vector<int> solve_TSP(vector<int> initial_path);

private:
    int size{};
    vector<vector<double>> adj;

};

#endif //TSP_SOLVER_CPP_GRAPH_H
