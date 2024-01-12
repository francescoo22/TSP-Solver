//
// Created by francesco on 12/01/24.
//

#include "Timer.h"
#include <chrono>

void Timer::start() {
    _start_time = std::chrono::high_resolution_clock::now();
}

unsigned Timer::get_time_milliseconds() {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto ms_int = duration_cast<std::chrono::milliseconds>(current_time - _start_time);
    return ms_int.count();
}
