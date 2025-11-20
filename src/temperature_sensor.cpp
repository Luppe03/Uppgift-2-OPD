#include "temperature_sensor.h"
#include <chrono>

TemperatureSensor::TemperatureSensor(std::string id, double minV, double maxV)
    : id_(std::move(id)), minV_(minV), maxV_(maxV),
      rng_(static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())),
      dist_(minV_, maxV_)
{}

double TemperatureSensor::read() {
    return dist_(rng_);
}

std::string TemperatureSensor::name() const { return "Temp:" + id_; }
std::string TemperatureSensor::unit() const { return "°C"; }
