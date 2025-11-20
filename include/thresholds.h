#pragma once
#include "measurement.h"
#include <string>
#include <vector>
#include <chrono>

struct Threshold {
    std::string sensorName;
    double limit;
    bool over;
};

struct Alert {
    std::string sensorName;
    double value;
    Threshold rule;
    std::chrono::system_clock::time_point timestamp;
};
