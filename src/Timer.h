//
// Created by francesco on 12/01/24.
//

#ifndef TSP_SOLVER_CPP_TIMER_H
#define TSP_SOLVER_CPP_TIMER_H

#include <chrono>

class Timer {
public:
    void start();

    unsigned get_time_milliseconds();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start_time;
};


#endif //TSP_SOLVER_CPP_TIMER_H
