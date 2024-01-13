//
// Created by francesco on 05/01/24.
//

#ifndef TSP_SOLVER_CPP_PATH_H
#define TSP_SOLVER_CPP_PATH_H

#include <vector>
#include <string>

class Path {
public:
    Path() = default;

    explicit Path(int size);

    explicit Path(const std::vector<int> &v);

    [[nodiscard]] unsigned long size() const;

    int operator[](int index) const;

    bool operator<(const Path &p) const;

    [[nodiscard]] const std::vector<int> &as_vector() const;

    [[nodiscard]] Path reverse_sub_path(int from, int to) const;

    [[nodiscard]] std::string as_string() const;

private:
    std::vector<int> nodes;
};


#endif //TSP_SOLVER_CPP_PATH_H
