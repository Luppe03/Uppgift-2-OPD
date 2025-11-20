#include "system_controller.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <iomanip>
#include <chrono>

using namespace std::chrono;

SystemController::SystemController() = default;

void SystemController::addSensor(std::unique_ptr<Sensor> s) {
    sensors_.push_back(std::move(s));
}

void SystemController::sampleAllOnce() {
    for (const auto& s : sensors_) {
        double val = s->read();
        Measurement m;
        m.sensorName = s->name();
        m.value = val;
        m.timestamp = system_clock::now();
        storage_.add(m);
        checkThresholds(m);
        std::cout << "Mätt: " << m.sensorName << " = " << m.value << " " << s->unit() << "\n";
    }
}

void SystemController::checkThresholds(const Measurement& m) {
    for (const auto& t : thresholds_) {
        if (t.sensorName != m.sensorName) continue;
        bool triggered = t.over ? (m.value > t.limit) : (m.value < t.limit);
        if (triggered) {
            Alert a;
            a.sensorName = m.sensorName;
            a.value = m.value;
            a.rule = t;
            a.timestamp = m.timestamp;
            alerts_.push_back(a);
        }
    }
}

void SystemController::showAllMeasurements() const {
    const auto& all = storage_.all();
    if (all.empty()) {
        std::cout << "Inga mätvärden sparade.\n";
        return;
    }
    for (const auto& m : all) {
        std::time_t t = system_clock::to_time_t(m.timestamp);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        char buf[32];
        std::strftime(buf, sizeof(buf), "%F %T", &tm);
        std::cout << buf << " | " << m.sensorName << " = " << m.value << "\n";
    }
}

void SystemController::showStatsFor(const std::string& sensorName) const {
    std::vector<double> vals;
    for (const auto& m : storage_.all()) {
        if (m.sensorName == sensorName) vals.push_back(m.value);
    }
    if (vals.empty()) {
        std::cout << "Inga mätningar för sensor " << sensorName << "\n";
        return;
    }
    double sum = std::accumulate(vals.begin(), vals.end(), 0.0);
    double mean = sum / vals.size();
    auto [minIt, maxIt] = std::minmax_element(vals.begin(), vals.end());
    std::cout << "Statistik för " << sensorName << ":\n";
    std::cout << "  Antal: " << vals.size() << "\n";
    std::cout << "  Medel: " << mean << "\n";
    std::cout << "  Min: " << *minIt << "  Max: " << *maxIt << "\n";
}

void SystemController::configureThresholdInteractive() {
    std::cout << "Konfigurera ny tröskelregel.\n";
    std::cout << "Sensor (exakt namn, t.ex. Temp:room1): ";
    std::string sname;
    std::getline(std::cin, sname);
    if (sname.empty()) {
        std::getline(std::cin, sname);
    }
    std::cout << "Gräns (nummer): ";
    double limit;
    std::cin >> limit;
    std::cout << "Riktning - skriv 'over' för larma om > limit, annars 'under': ";
    std::string dir;
    std::cin >> dir;
    bool over = (dir == "over" || dir == "Over" || dir == "o");
    Threshold t{ sname, limit, over };
    thresholds_.push_back(t);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Tröskel sparad.\n";
}

void SystemController::showAlerts() const {
    if (alerts_.empty()) {
        std::cout << "Inga larm registrerade.\n";
        return;
    }
    for (const auto& a : alerts_) {
        std::time_t t = system_clock::to_time_t(a.timestamp);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        char buf[32];
        std::strftime(buf, sizeof(buf), "%F %T", &tm);
        std::cout << buf << " | " << a.sensorName << " = " << a.value
                  << " | Regel: " << (a.rule.over ? "over" : "under") << " " << a.rule.limit << "\n";
    }
}

void SystemController::saveMeasurements(const std::string& path) const {
    if (storage_.saveCsv(path)) {
        std::cout << "Sparat mätdata till " << path << "\n";
    } else {
        std::cout << "Misslyckades med att spara till " << path << "\n";
    }
}

void SystemController::loadMeasurements(const std::string& path) {
    if (storage_.loadCsv(path)) {
        std::cout << "Laddade mätdata från " << path << "\n";
    } else {
        std::cout << "Misslyckades med att läsa från " << path << "\n";
    }
}
