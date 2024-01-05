//
// Created by francesco on 05/01/24.
//

#ifndef TSP_SOLVER_CPP_PATH_H
#define TSP_SOLVER_CPP_PATH_H

#include <vector>
#include <string>

using namespace std;

class Path {
public:
    explicit Path(int size);

    explicit Path(const vector<int> &v);

    [[nodiscard]] unsigned long size() const;

    int operator[](int index) const;

    [[nodiscard]] const vector<int> &as_vector() const;

    [[nodiscard]] Path reverse_sub_path(int from, int to) const;

    [[nodiscard]] string as_string() const;

private:
    vector<int> nodes;
};


#endif //TSP_SOLVER_CPP_PATH_H
