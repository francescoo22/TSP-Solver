//
// Created by francesco on 10/01/24.
//

#include <complex>
#include <sstream>
#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::distance(const Point &p) const {
    return std::sqrt(
            (x - p.x) * (x - p.x) +
            (y - p.y) * (y - p.y)
    );
}

std::string Point::as_string() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}
