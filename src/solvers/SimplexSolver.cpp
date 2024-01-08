//
// Created by francesco on 08/01/24.
//

#include "SimplexSolver.h"
#include <cstring>
#include <iostream>
#include <cassert>

std::string SimplexSolver::evaluated_trace_as_string(const Graph &graph) const {
    return {};
}

Path SimplexSolver::solve(const Graph &graph, const Path &initial_path) {
    int status;
    auto env = CPXopenCPLEX(&status);
    auto lp = CPXcreateprob(env, &status, "");

    setupLP(env, lp, graph.size(), graph);

    // write the model
    CPXwriteprob(env, lp, "../outputs/simplex_model.lp", nullptr);

    // solve
    CPXmipopt(env, lp);

    // get obj_val
    double obj_val;
    CPXgetobjval(env, lp, &obj_val);
    std::cout << "Objval: " << obj_val << std::endl;
    assert(std::abs(obj_val - 66.4) < 0.1);

    CPXfreeprob(env, &lp);
    CPXcloseCPLEX(&env);
    return {};
}

char **SimplexSolver::from_string(const std::string &s) {
    char **stringArray = new char *[1];
    stringArray[0] = new char[s.length() + 1];
    strcpy(stringArray[0], s.c_str());
    return stringArray;
}

void SimplexSolver::setupLP(CPXENVptr env, CPXLPptr lp, int size, const Graph &graph) {
    int cur_index = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char xtype = 'B';
            double lb = 0;
            double ub = 1;
            double cost = graph.get_edge(i, j);
            std::string var_name = "y_" + std::to_string(i) + "_" + std::to_string(j);
            var_index[{'y', i, j}] = cur_index++;
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
            var_index[{'x', i, j}] = cur_index++;
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
            coef.push_back(1);
            idx.push_back(var_index[{'x', i, k}]);
        }
        for (int j = 1; j < size; j++) {
            coef.push_back(-1);
            idx.push_back(var_index[{'x', k, j}]);
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
            idx.push_back(var_index[{'y', i, j}]);
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
            idx.push_back(var_index[{'y', i, j}]);
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
            idx.push_back(var_index[{'y', i, j}]);

            // x_ij
            coef.push_back(1);
            idx.push_back(var_index[{'x', i, j}]);
            CPXaddrows(env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
                       nullptr);
        }
    }
}