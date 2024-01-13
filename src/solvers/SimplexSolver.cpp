//
// Created by francesco on 08/01/24.
//

#include "SimplexSolver.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>

std::string SimplexSolver::evaluated_trace_as_string(const Graph &graph) const {
    std::stringstream ss;
    ss << "******************* SIMPLEX SOLUTION = "
       << graph.eval_path(solution)
       << " *******************\n"
       << "Execution time: " << execution_time_milliseconds << " ms\n"
       << solution.as_string()
       << "\n[";
    auto points = graph.points_of_path(solution);
    for (int i = 0; i < points.size(); i++) {
        ss << points[i].as_string();
        if (i != points.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

Path SimplexSolver::_solve(const Graph &graph, const Path &initial_path) {
    if (time_limit != 0) {
        CPXsetdblparam(env, CPX_PARAM_TILIM, time_limit);
    }
    setupLP(graph.size(), graph);
    CPXwriteprob(env, lp, "../outputs/simplex/simplex_model.lp", nullptr);
    CPXmipopt(env, lp);
    double obj_val;
    CPXgetobjval(env, lp, &obj_val);
    std::cout << "Objval: " << obj_val << std::endl;

    CPXsolwrite(env, lp, "../outputs/simplex/simplex_sol.sol");

    Path res = solution_path();

    CPXfreeprob(env, &lp);
    CPXcloseCPLEX(&env);
    return res;
}

char **SimplexSolver::from_string(const std::string &s) {
    char **stringArray = new char *[1];
    stringArray[0] = new char[s.length() + 1];
    strcpy(stringArray[0], s.c_str());
    return stringArray;
}

void SimplexSolver::setupLP(int size, const Graph &graph) {
    int cur_index = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char xtype = 'B';
            double lb = 0;
            double ub = 1;
            double cost = graph.get_edge(i, j);
            std::string var_name = "y_" + std::to_string(i) + "_" + std::to_string(j);
            index_to_tuple[cur_index] = {'y', i, j};
            tuple_to_index[{'y', i, j}] = cur_index++;
            CPXnewcols(env, lp, 1, &cost, &lb, &ub, &xtype, from_string(var_name));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            char xtype = 'C';
            double lb = 0;
            double ub = CPX_INFBOUND;
            double cost = 0;
            std::string var_name = "x_" + std::to_string(i) + "_" + std::to_string(j);
            index_to_tuple[cur_index] = {'x', i, j};
            tuple_to_index[{'x', i, j}] = cur_index++;
            CPXnewcols(env, lp, 1, &cost, &lb, &ub, &xtype, from_string(var_name));
        }
    }

    // ********************************** ROWS CREATION **********************************

    // sum_i (x_ik) - sum_j (x_kj) = 1 forall 0 < k < size
    for (int k = 1; k < size; k++) {
        std::vector<int> idx;
        std::vector<double> coef;
        char sense = 'E';
        const double rhs = 1;
        int matbeg = 0;

        for (int i = 0; i < size; i++) {
            if (i == k) continue;
            coef.push_back(1);
            idx.push_back(tuple_to_index[{'x', i, k}]);
        }
        for (int j = 1; j < size; j++) {
            if (j == k) continue;
            coef.push_back(-1);
            idx.push_back(tuple_to_index[{'x', k, j}]);
        }
        CPXaddrows(env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
                   nullptr);
    }



    // sum_j (y_ij) = 1 forall 0 <= i < size
    for (int i = 0; i < size; i++) {
        std::vector<int> idx;
        std::vector<double> coef;
        const double rhs = 1;
        char sense = 'E';
        int matbeg = 0;
        for (int j = 0; j < size; j++) {
            coef.push_back(1);
            idx.push_back(tuple_to_index[{'y', i, j}]);
        }
        CPXaddrows(env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
                   nullptr);
    }

    // sum_i (y_ij) = 1 forall 0 <= j < size
    for (int j = 0; j < size; j++) {
        std::vector<int> idx;
        std::vector<double> coef;
        const double rhs = 1;
        char sense = 'E';
        int matbeg = 0;
        for (int i = 0; i < size; i++) {
            coef.push_back(1);
            idx.push_back(tuple_to_index[{'y', i, j}]);
        }
        CPXaddrows(env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
                   nullptr);
    }

    // x_ij - (size - 1) * y_ij <= 0 forall (i,j) in (size * size)
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            std::vector<int> idx;
            std::vector<double> coef;
            const double rhs = 0;
            char sense = 'L';
            int matbeg = 0;

            // -(size - 1) * y_ij
            coef.push_back(1 - size);
            idx.push_back(tuple_to_index[{'y', i, j}]);

            // x_ij
            coef.push_back(1);
            idx.push_back(tuple_to_index[{'x', i, j}]);
            CPXaddrows(env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
                       nullptr);
        }
    }
}

Path SimplexSolver::solution_path() {
    std::vector<double> var_values(index_to_tuple.size());
    std::vector<std::pair<int, int>> arcs;
    CPXgetx(env, lp, &var_values[0], 0, var_values.size() - 1);
    for (int i = 0; i < var_values.size(); i++) {
        auto [c, a, b] = index_to_tuple[i];
        if (c == 'y' && equal(var_values[i], 1)) {
            arcs.emplace_back(a, b);
        }
    }
    std::sort(arcs.begin(), arcs.end());
    std::vector<int> ans;

    auto [cur, next] = arcs[0];
    do {
        ans.push_back(cur);
        cur = next;
        next = arcs[cur].second;
    } while (cur != 0);
    return Path(ans);
}

bool SimplexSolver::equal(double a, double b) {
    return std::abs(a - b) < 0.0001;
}

void SimplexSolver::_reset() {
    env = CPXopenCPLEX(&status);
    lp = CPXcreateprob(env, &status, "");
    tuple_to_index.clear();
    index_to_tuple.clear();
}

SimplexSolver::SimplexSolver(unsigned int time_limit) : TspSolver(time_limit), status(0), env(nullptr), lp(nullptr) {}
