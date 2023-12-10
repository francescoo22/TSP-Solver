#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include "cpxmacro.h"

using namespace std;

// error status and messagge buffer
int status;
char errmsg[BUF_SIZE];

int main() {
    ifstream in("../inputs/tsp60.dat");
    int size;
    in >> size;
    vector<vector<double>> c(size, vector<double>(size));
    for (auto &v: c)
        for (auto &d: v) in >> d;

    cout << "INPUT TEST 9.3 = " << c[size - 1][size - 2] << endl;

    try {
        DECL_ENV(env)
        DECL_PROB(env, lp)

        ///////////////////////// create variables with newcols
        //
        // status = CPXnewcols (env, lp, ccnt, obj, lb, ub, xctype, colname);
        // ccnt -> numero di variabili,
        // objCost -> costi nella funzione obiettivo
        // lb, ub -> bound delle variabili
        // xctype -> tipi delle variabli

        // order: y_ij, x_ij

        int ccnt = size * size * 2;
        double objCost[ccnt];
        double lb[ccnt];
        double ub[ccnt];
        char xtype[ccnt];
        char **xname = NULL;

        for (int i = 0, y_index = 0; i < size; i++) {
            for (int j = 0; j < size; j++, y_index++) {
                int x_index = y_index + size * size;
                objCost[y_index] = c[i][j];
                objCost[x_index] = 0;

                lb[y_index] = 0;
                lb[x_index] = 0;

                ub[y_index] = 1;
                ub[x_index] = CPX_INFBOUND;

                xtype[y_index] = 'B';
                xtype[x_index] = 'C';
            }
        }

        CHECKED_CPX_CALL(CPXnewcols, env, lp, ccnt, &objCost[0], &lb[0], &ub[0], &xtype[0], xname);

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

        double rhs[rowcount];
        char sense[rowcount];
        int rmatbeg[rowcount];
        int rmatind[nzcnt];
        double rmatval[nzcnt];
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
                rmatind[cur_nz] = (size * size) + (i * size) + k;
            }
            for (int j = 1; j < size; j++, cur_nz++) {
                rmatval[cur_nz] = -1;
                rmatind[cur_nz] = (size * size) + (k * size) + j;
            }
        }

        // sum_j (y_ij) = 1 forall 0 <= i < size
        for (int i = 0; i < size; i++, cur_row++) {
            rhs[cur_row] = 1;
            sense[cur_row] = 'E';
            rmatbeg[cur_row] = cur_nz;
            for (int j = 0; j < size; j++, cur_nz++) {
                rmatval[cur_nz] = 1;
                rmatind[cur_nz] = i * size + j;
            }
        }

        // sum_i (y_ij) = 1 forall 0 <= j < size
        for (int j = 0; j < size; j++, cur_row++) {
            rhs[cur_row] = 1;
            sense[cur_row] = 'E';
            rmatbeg[cur_row] = cur_nz;
            for (int i = 0; i < size; i++, cur_nz++) {
                rmatval[cur_nz] = 1;
                rmatind[cur_nz] = i * size + j;
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
                rmatind[cur_nz] = i * size + j;

                // x_ij
                rmatval[cur_nz + 1] = 1;
                rmatind[cur_nz + 1] = (size * size) + i * size + j;
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
