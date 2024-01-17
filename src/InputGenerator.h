//
// Created by francesco on 14/01/24.
//

#ifndef TSP_SOLVER_CPP_INPUTGENERATOR_H
#define TSP_SOLVER_CPP_INPUTGENERATOR_H


#include "graph/Graph.h"
#include "graph/Point.h"
#include <random>

enum class Shape {
    POINTS,
    LINE,
    RECTANGLE,
    CIRCLE,
};

class InputGenerator {
public:
    InputGenerator(double width, double height);

    void generate_input(const std::string &filename, int size);

    void generate_shaped_input(const std::string &filename, int number_of_shapes, int max_points = -1);

    std::vector<Point> generate_random_shape();

private:
    std::random_device rd;
    std::mt19937 rng;
    double _width, _height;

    Shape get_random_shape();

    Point generate_random_point();

    std::vector<Point> generate_random_points();

    std::vector<Point> generate_random_line();

    std::vector<Point> generate_random_rectangle();

    std::vector<Point> generate_random_circle();

    double rand_double(double from, double to);

    static double round_to_two_decimals(double value);

    int rand_int(int from, int to);

    [[nodiscard]] bool is_inside(Point p) const;
};


#endif //TSP_SOLVER_CPP_INPUTGENERATOR_H
