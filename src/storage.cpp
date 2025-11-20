#include "storage.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>

using namespace std::chrono;

void Storage::add(const Measurement& m) {
    measurements_.push_back(m);
}

const std::vector<Measurement>& Storage::all() const {
    return measurements_;
}

void Storage::clear() {
    measurements_.clear();
}

static std::string timeToString(system_clock::time_point tp) {
    std::time_t t = system_clock::to_time_t(tp);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}


static system_clock::time_point stringToTime(const std::string& s) {
    std::tm tm{};
    std::istringstream ss(s);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return system_clock::from_time_t(std::mktime(&tm));
}

bool Storage::saveCsv(const std::string& path) const {
    std::ofstream ofs(path);
    if (!ofs) return false;
    ofs << "sensor,timestamp,value\n";
    for (const auto& m : measurements_) {
        ofs << m.sensorName << "," << timeToString(m.timestamp) << "," << m.value << "\n";
    }
    return true;
}

bool Storage::loadCsv(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) return false;
    std::string line;
    std::getline(ifs, line);
    std::vector<Measurement> tmp;
    while (std::getline(ifs, line)) {
        std::istringstream ss(line);
        std::string sensor, timestamp, valueStr;
        if (!std::getline(ss, sensor, ',')) continue;
        if (!std::getline(ss, timestamp, ',')) continue;
        if (!std::getline(ss, valueStr, ',')) continue;
        Measurement m;
        m.sensorName = sensor;
        m.timestamp = stringToTime(timestamp);
        m.value = std::stod(valueStr);
        tmp.push_back(m);
    }
    measurements_ = std::move(tmp);
    return true;
}
