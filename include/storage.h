#pragma once
#include "measurement.h"
#include <vector>
#include <string>

class Storage {
public:
    void add(const Measurement& m);
    const std::vector<Measurement>& all() const;
    void clear();

    
    bool saveCsv(const std::string& path) const;
    bool loadCsv(const std::string& path);
private:
    std::vector<Measurement> measurements_;
};
