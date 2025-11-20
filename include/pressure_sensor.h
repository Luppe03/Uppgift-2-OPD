#pragma once
#include "sensor.h"
#include <string>
#include <random>

class PressureSensor : public Sensor {
public:
    PressureSensor(std::string id, double minV, double maxV);
    double read() override;
    std::string name() const override;
    std::string unit() const override;
private:
    std::string id_;
    double minV_, maxV_;
    std::mt19937_64 rng_;
    std::uniform_real_distribution<double> dist_;
};
