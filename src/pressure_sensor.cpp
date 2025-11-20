#include "pressure_sensor.h"
#include <chrono>

PressureSensor::PressureSensor(std::string id, double minV, double maxV)
    : id_(std::move(id)), minV_(minV), maxV_(maxV),
      rng_(static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())),
      dist_(minV_, maxV_)
{}

double PressureSensor::read() {
    return dist_(rng_);
}

std::string PressureSensor::name() const { return "Pres:" + id_; }
std::string PressureSensor::unit() const { return "hPa"; }
