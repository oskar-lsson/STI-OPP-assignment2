#pragma once
#include "sensor.h"

class TempertureSensor : public Sensor {
private:
    std::string sensorName_;
    double minValue_;
    double maxValue_;
public:
    TempertureSensor(const std::string& sensorName_, double minValue_, double maxValue_);

    double read() override;
    std::string getName() override;
    std::string getUnit() override;
};
