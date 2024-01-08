#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include "cpxmacro.h"

//using namespace std;

// error status and messagge buffer
int status;
char errmsg[BUF_SIZE];

std::map<std::tuple<char, int, int>, int> var_index;

char **from_string(const std::string &s) {
    char **stringArray = new char *[1];
    stringArray[0] = new char[s.length() + 1];
    strcpy(stringArray[0], s.c_str());
    return stringArray;
}

void setupLP(CEnv env, Prob lp, int size, const std::vector <std::vector<double>> &c) {
    int cur_index = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char xtype = 'B';
            double lb = 0;
            double ub = 1;
            double cost = c[i][j]; // non proprio uguale
            std::string var_name = "y_" + std::to_string(i) + "_" + std::to_string(j);
            var_index[{'y', i, j}] = cur_index++;
//            CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &cost, &lb, &ub, &xtype, from_string(var_name));
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
//            CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &cost, &lb, &ub, &xtype, from_string(var_name));
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
//        CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
//                         nullptr);
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
//        CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
//                         nullptr);
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
//        CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
//                         nullptr);
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
//            CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0],
//                             nullptr,
//                             nullptr);
            CPXaddrows(env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr,
                       nullptr);
        }
    }
}

int main() {
    std::ifstream in("../inputs/tsp12.dat");
    int size;
    in >> size;
    std::vector<std::vector<double>> c(size, std::vector<double>(size));
    for (auto &v: c)
        for (auto &d: v) in >> d;

    std::cout << "INPUT TEST 9.3 = " << c[size - 1][size - 2] << std::endl;

    try {
//        DECL_ENV(env)
        Env env = CPXopenCPLEX(&status);
//        DECL_PROB(env, lp)
        Prob lp = CPXcreateprob(env, &status, "");

        setupLP(env, lp, size, c);

        // write the model
//        CHECKED_CPX_CALL(CPXwriteprob, env, lp, "first.lp", nullptr);
        CPXwriteprob(env, lp, "first.lp", nullptr);

        // solve
//        CHECKED_CPX_CALL(CPXmipopt, env, lp);
        CPXmipopt(env, lp);

        // get obj_val
        double obj_val;
//        CHECKED_CPX_CALL(CPXgetobjval, env, lp, &obj_val);
        CPXgetobjval(env, lp, &obj_val);
        // get the objective function value into objval
        std::cout << "Objval: " << obj_val << std::endl;
        assert(std::abs(obj_val - 66.4) < 0.1);

        CPXfreeprob(env, &lp);
        CPXcloseCPLEX(&env);

    } catch (std::exception &e) {
        std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
    }


    return 0;
}

///////////////////////// create constraints
//
// status = CPXaddrows (env, lp, colcnt, rowcnt, nzcnt, rhs, sense, rmatbeg, rmatind, rmatval , newcolname, newrowname);
// colcnt = 0
// rowcnt = number of constraints
// nzcnt = non-zero count
// rhs = vector of right sides of inequalities (e.g. x + y + z < rhs)
// sense = G (greater or equal) | L (less or equal) | E (equal) for each constraint
// rmatbeg = indexes where each row starts
// rmatind = name of the variable (index provided in obj func) referred to the value
// rmatval = values of the vars defined above