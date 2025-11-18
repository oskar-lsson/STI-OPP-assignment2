#pragma once
#include "sensor.h"
class PressureSensor {
private:
    std::string sensorName_;
    double minValue_;
    double maxValue_;
public:
    PressureSensor(const std::string& sensorName_, double minValue_, double maxValue_);

    double read() override;
    std::string getName() const override;
    std::string getUnit() const override;
};

