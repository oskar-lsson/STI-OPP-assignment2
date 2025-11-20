#pragma once
#include <string>

// Threshold configuration for a sensor
struct Threshold {
    std::string sensorName;
    double limit;
    bool over;  // true: alarm if value > limit, false: alarm if value < limit
};

// Alarm event when a threshold is breached
struct Alarm {
    std::string timestamp;
    std::string sensorName;
    double value;
    double limit;
    bool wasOver;  // true if alarm triggered by going over limit

    void print() const;
};
