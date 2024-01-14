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

void InputGenerator::generate_shaped_input(const std::string &filename, int number_of_shapes) {
    std::ofstream out("../inputs/" + filename + ".dat");
    std::vector<Point> points;
    for (int i = 0; i < number_of_shapes; i++) {
        std::vector<Point> shape = generate_random_shape();

        for (auto p: shape) {
            std::cout << p.as_string() << "\n";
        }
        std::cout << "\n";

        points.insert(points.end(), shape.begin(), shape.end());
    }
    out << points.size() << "\n";
    for (Point point: points) {
        if (is_inside(point)) {
            out << point.x << " " << point.y << "\n";
        }
    }
}

std::vector<Point> InputGenerator::generate_random_shape() {
    Shape shape = get_random_shape();
    std::vector<Point> res;
    switch (shape) {
        case Shape::POINT:
            res.push_back(generate_random_point());
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
    int randomValue = rand_int(static_cast<int>(Shape::POINT), static_cast<int>(Shape::CIRCLE));
    return static_cast<Shape>(randomValue);
}

Point InputGenerator::generate_random_point() {
    return {rand_double(0, _width), rand_double(0, _height)};
}

std::vector<Point> InputGenerator::generate_random_line() {
    std::cout << "Line\n";
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
    std::cout << "Rectangle\n";
    std::vector<Point> res;
    Point origin = generate_random_point();
    double width = rand_double(2, 10);
    double height = rand_double(2, 10);
    int points_on_side = rand_int(3, 5);

    for (int i = 0; i < points_on_side; i++) {
        double dx = i * (width / points_on_side);
        res.emplace_back(origin.x + dx, origin.y);
        res.emplace_back(origin.x + dx + (width / points_on_side), origin.y + height);
    }

    for (int i = 0; i < points_on_side; i++) {
        double dy = i * (height / points_on_side);
        res.emplace_back(origin.x, origin.y + dy + (height / points_on_side));
        res.emplace_back(origin.x + width, origin.y + dy);
    }

    return res;
}

std::vector<Point> InputGenerator::generate_random_circle() {
    std::cout << "Circle\n";
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
