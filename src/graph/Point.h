//
// Created by francesco on 10/01/24.
//

#ifndef TSP_SOLVER_CPP_POINT_H
#define TSP_SOLVER_CPP_POINT_H


#include <string>

class Point {
public:
    Point(double x, double y);

    [[nodiscard]] double distance(const Point &p) const;

    [[nodiscard]] std::string as_string() const;

private:
    double x, y;
};


#endif //TSP_SOLVER_CPP_POINT_H
