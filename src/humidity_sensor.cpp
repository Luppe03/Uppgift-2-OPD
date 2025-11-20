#include "humidity_sensor.h"
#include <chrono>

HumiditySensor::HumiditySensor(std::string id, double minV, double maxV)
    : id_(std::move(id)), minV_(minV), maxV_(maxV),
      rng_(static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())),
      dist_(minV_, maxV_)
{}

double HumiditySensor::read() {
    return dist_(rng_);
}

std::string HumiditySensor::name() const { return "Hum:" + id_; }
std::string HumiditySensor::unit() const { return "%"; }
