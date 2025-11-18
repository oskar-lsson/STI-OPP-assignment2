#pragma once
#include <string>

struct Measurement {
    std::string sensorName;
    std::string unit;
    double value;
    std::string timestamp;

    void print() const;
};