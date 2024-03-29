//
// Created by francesco on 14/01/24.
//

#include <fstream>
#include <iostream>
#include <cmath>
#include "InputGenerator.h"

InputGenerator::InputGenerator(double width, double height) : _width(width), _height(height), rd(), rng(rd()) {}

void InputGenerator::generate_input(const std::string &filename, int size) {
    std::ofstream out("../inputs/" + filename + ".dat");
    out << size << "\n";
    for (int i = 0; i < size; i++) {
        Point p = generate_random_point();
        out << p.x << " " << p.y << "\n";
    }
}

void InputGenerator::generate_shaped_input(const std::string &filename, int number_of_shapes, int max_points) {
    std::ofstream out("../inputs/" + filename + ".dat");
    std::vector<Point> points;
    for (int i = 0; i < number_of_shapes; i++) {
        std::vector<Point> shape = generate_random_shape();
        std::vector<Point> inside_shape;

        for (auto p: shape) {
            if (is_inside(p)) inside_shape.push_back(p);
        }

        points.insert(points.end(), inside_shape.begin(), inside_shape.end());
    }
    if (max_points > 0 && points.size() > max_points) {
        points = std::vector<Point>(points.begin(), points.begin() + max_points);
    }

    for (Point &p: points) {
        p.x = round_to_two_decimals(p.x);
        p.y = round_to_two_decimals(p.y);
    }

    out << points.size() << "\n";
    for (Point point: points) {
        out << point.x << " " << point.y << "\n";
    }
    out.close();
}

std::vector<Point> InputGenerator::generate_random_shape() {
    Shape shape = get_random_shape();
    std::vector<Point> res;
    switch (shape) {
        case Shape::POINTS:
            res = generate_random_points();
            break;
        case Shape::LINE:
            res = generate_random_line();
            break;
        case Shape::RECTANGLE:
            res = generate_random_rectangle();
            break;
        case Shape::CIRCLE:
            res = generate_random_circle();
            break;
    }
    return res;
}

Shape InputGenerator::get_random_shape() {
    int randomValue = rand_int(static_cast<int>(Shape::POINTS), static_cast<int>(Shape::CIRCLE));
    return static_cast<Shape>(randomValue);
}

Point InputGenerator::generate_random_point() {
    return {rand_double(0, _width), rand_double(0, _height)};
}

std::vector<Point> InputGenerator::generate_random_points() {
    int number_of_points = rand_int(3, 7);
    std::vector<Point> res;
    for (int i = 0; i < number_of_points; i++) {
        res.push_back(generate_random_point());
    }
    return res;
}

std::vector<Point> InputGenerator::generate_random_line() {
    std::vector<Point> res;
    int number_of_points = rand_int(3, 7);
    double dx = rand_double(-3, 3), dy = rand_double(-3, 3);
    res.push_back(generate_random_point());
    while (res.size() < number_of_points) {
        Point p(res.back().x + dx, res.back().y + dy);
        res.push_back(p);
    }
    return res;
}

std::vector<Point> InputGenerator::generate_random_rectangle() {
    std::vector<Point> res;
    Point origin = generate_random_point();
    double width = rand_double(2, 10);
    double height = rand_double(2, 10);
    int points_on_side = rand_int(3, 5);

    for (int i = 0; i < points_on_side; i++) {
        double dx = i * (width / points_on_side);
        res.emplace_back(origin.x + dx, origin.y);
    }

    for (int i = 0; i < points_on_side; i++) {
        double dy = i * (height / points_on_side);
        res.emplace_back(origin.x + width, origin.y + dy);
    }

    for (int i = 0; i < points_on_side; i++) {
        double dx = i * (width / points_on_side);
        res.emplace_back(origin.x + width - dx, origin.y + height);
    }

    for (int i = 0; i < points_on_side; i++) {
        double dy = i * (height / points_on_side);
        res.emplace_back(origin.x, origin.y + height - dy);
    }

    return res;
}

std::vector<Point> InputGenerator::generate_random_circle() {
    std::vector<Point> res;

    Point center = generate_random_point();
    double radius = rand_double(2, 6);
    int number_of_points = rand_int(10, 15);

    for (int i = 0; i < number_of_points; ++i) {
        double angle = 2 * M_PI * static_cast<double>(i) / static_cast<double>(number_of_points);
        double x = center.x + radius * cos(angle);
        double y = center.y + radius * sin(angle);
        res.emplace_back(x, y);
    }

    return res;
}

double InputGenerator::rand_double(double from, double to) {
    std::uniform_real_distribution<double> dist(from, to);
    return std::round(100. * dist(rng)) / 100.;
}

int InputGenerator::rand_int(int from, int to) {
    std::uniform_int_distribution<int> dist(from, to);
    return dist(rng);
}

bool InputGenerator::is_inside(Point p) const {
    return p.x >= 0 && p.y >= 0 && p.x <= _width && p.y <= _height;
}

double InputGenerator::round_to_two_decimals(double value) {
    double shifted_value = value * 100.0;
    double rounded_value = std::round(shifted_value);
    return rounded_value / 100.0;
}
