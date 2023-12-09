#include <iostream>
#include <fstream>
#include <vector>
#include "cpxmacro.h"

using namespace std;

// error status and messagge buffer
int status;
char errmsg[BUF_SIZE];

int main() {
    ifstream in("../inputs/tsp12.dat");
    int size;
    in >> size;
    vector<vector<double>> c(size, vector<double>(size));
    for (auto &v: c)
        for (auto &d: v) in >> d;

    cout << "INPUT TEST 9.3 = " << c[size - 1][size - 2];

    try {
        DECL_ENV(env)
        DECL_PROB(env, lp)

        ///////////////////////// create variables with newcols
        //
        // status =      CPXnewcols (env, lp, ccnt, obj, lb, ub, xctype, colname);
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
                int x_index = y_index + size;
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

    } catch (std::exception &e) {
        std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
    }


    return 0;
}
