#pragma once
#include <string>

struct Measurement {
    std::string sensorName;
    std::string unit;
    double value;  // Changed from float to double for consistency
    std::string timestamp;

    void print() const;
};