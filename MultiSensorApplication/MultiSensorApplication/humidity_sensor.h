#pragma once
#include "sensor.h"
class HumiditySensor {
private:
    std::string sensorName_;
    double minValue_;
    double maxValue_;
public:
    HumiditySensor(const std::string& sensorName_, double minValue_, double maxValue_);

    double read() override;
    std::string getName() override;
    std::string getUnit() override;
};

