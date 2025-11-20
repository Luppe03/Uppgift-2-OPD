#pragma once
#include "sensor.h"
#include "storage.h"
#include "thresholds.h"
#include <vector>
#include <memory>
#include <string>

class SystemController {
public:
    SystemController();
    void addSensor(std::unique_ptr<Sensor> s);
    void sampleAllOnce();
    void showAllMeasurements() const;
    void showStatsFor(const std::string& sensorName) const;
    void configureThresholdInteractive();
    void showAlerts() const;
    void saveMeasurements(const std::string& path) const;
    void loadMeasurements(const std::string& path);
private:
    std::vector<std::unique_ptr<Sensor>> sensors_;
    Storage storage_;
    std::vector<Threshold> thresholds_;
    std::vector<Alert> alerts_;

    void checkThresholds(const Measurement& m);
};
