#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include "cpxmacro.h"

using namespace std;

// error status and messagge buffer
int status;
char errmsg[BUF_SIZE];

map<tuple<char, int, int>, int> var_index;

char **from_string(const string &s) {
    char **stringArray = new char *[1];
    stringArray[0] = new char[s.length() + 1];
    strcpy(stringArray[0], s.c_str());
    return stringArray;
}

void setupLP(CEnv env, Prob lp, int size, const vector<vector<double>> &c) {
    int cur_index = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double *cost = new double(c[i][j]);
            double *lb = new double(0);
            double *ub = new double(1);
            char *xtype = new char('B');
            string var_name = "y_" + to_string(i) + "_" + to_string(j);
            var_index[{'y', i, j}] = cur_index++;
            CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, cost, lb, ub, xtype, from_string(var_name));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            double *cost = new double(0);
            double *lb = new double(0);
            double *ub = new double(CPX_INFBOUND);
            char *xtype = new char('C');
            string var_name = "x_" + to_string(i) + "_" + to_string(j);
            var_index[{'x', i, j}] = cur_index++;
            CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, cost, lb, ub, xtype, from_string(var_name));
        }
    }
}

int main() {
    ifstream in("../inputs/tsp6.dat");
    int size;
    in >> size;
    vector<vector<double>> c(size, vector<double>(size));
    for (auto &v: c)
        for (auto &d: v) in >> d;

    cout << "INPUT TEST 9.3 = " << c[size - 1][size - 2] << endl;

    try {
        DECL_ENV(env)
        DECL_PROB(env, lp)

//        CPXsetintparam(env, CPXPARAM_WorkMem, 1024000000);
//        CPXsetdblparam(env, CPX_PARAM_EPAGAP, 0.05);
        cout<< "AAAAA" << endl;

        setupLP(env, lp, size, c);

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

        vector<int> constraint_rows = {size - 1, size, size, (size * (size - 1))};
        vector<int> constraint_non_zeros = {2 * size - 1, size, size, 2}; // repetitions for the first should be ok

        int colcount = 0;

        int rowcount = accumulate(constraint_rows.begin(), constraint_rows.end(), 0);

        int nzcnt = 0;
        for (int i = 0; i < 4; i++) nzcnt += constraint_rows[i] * constraint_non_zeros[i];

//        double rhs[rowcount];
//        char sense[rowcount];
//        int rmatbeg[rowcount];
//        int rmatind[nzcnt];
//        double rmatval[nzcnt];
        auto rhs = new double[rowcount];
        auto sense = new char[rowcount];
        auto rmatbeg = new int[rowcount];
        auto rmatind = new int[nzcnt];
        auto rmatval = new double[nzcnt];

        char **newcolnames = NULL;
        char **rownames = NULL;

        // sum_i (x_ik) - sum_j (x_kj) = 1 forall 0 < k < size
        int cur_nz = 0;
        int cur_row = 0;
        for (int k = 1; k < size; k++, cur_row++) {
            rhs[cur_row] = 1;
            sense[cur_row] = 'E';
            rmatbeg[cur_row] = cur_nz;
            for (int i = 0; i < size; i++, cur_nz++) {
                rmatval[cur_nz] = 1;
                rmatind[cur_nz] = var_index[{'x', i, k}];
            }
            for (int j = 1; j < size; j++, cur_nz++) {
                rmatval[cur_nz] = -1;
                rmatind[cur_nz] = var_index[{'x', k, j}];
            }
        }

        // sum_j (y_ij) = 1 forall 0 <= i < size
        for (int i = 0; i < size; i++, cur_row++) {
            rhs[cur_row] = 1;
            sense[cur_row] = 'E';
            rmatbeg[cur_row] = cur_nz;
            for (int j = 0; j < size; j++, cur_nz++) {
                rmatval[cur_nz] = 1;
                rmatind[cur_nz] = var_index[{'y', i, j}];
            }
        }

        // sum_i (y_ij) = 1 forall 0 <= j < size
        for (int j = 0; j < size; j++, cur_row++) {
            rhs[cur_row] = 1;
            sense[cur_row] = 'E';
            rmatbeg[cur_row] = cur_nz;
            for (int i = 0; i < size; i++, cur_nz++) {
                rmatval[cur_nz] = 1;
                rmatind[cur_nz] = var_index[{'y', i, j}];
            }
        }

        // x_ij - (size - 1) * y_ij <= 0 forall (i,j) in (size * size)
        for (int i = 0; i < size; i++) {
            for (int j = 1; j < size; j++, cur_row++, cur_nz += 2) {
                rhs[cur_row] = 0;
                sense[cur_row] = 'L';
                rmatbeg[cur_row] = cur_nz;

                // -(size - 1) * y_ij
                rmatval[cur_nz] = 1 - size;
                rmatind[cur_nz] = var_index[{'y', i, j}];

                // x_ij
                rmatval[cur_nz + 1] = 1;
                rmatind[cur_nz + 1] = var_index[{'x', i, j}];
            }
        }

        CHECKED_CPX_CALL(CPXaddrows, env, lp, colcount, rowcount, nzcnt, &rhs[0], &sense[0], &rmatbeg[0], &rmatind[0],
                         &rmatval[0], newcolnames, rownames);

        // write the model
        CHECKED_CPX_CALL(CPXwriteprob, env, lp, "first.lp", NULL);

        cout << "row test: " << cur_row << " = " << rowcount << endl;
        cout << "non-zero test: " << cur_nz << " = " << nzcnt << endl;

        // solve
        CHECKED_CPX_CALL(CPXmipopt, env, lp);

        // get obj_val
        double obj_val;
        CHECKED_CPX_CALL(CPXgetobjval, env, lp, &obj_val);
        // get the objective function value into objval
        cout << "Objval: " << obj_val << endl;

        CPXfreeprob(env, &lp);
        CPXcloseCPLEX(&env);

    } catch (std::exception &e) {
        std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
    }


    return 0;
}
