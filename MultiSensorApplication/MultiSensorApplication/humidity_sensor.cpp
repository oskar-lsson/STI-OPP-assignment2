#include "humidity_sensor.h"
#include <random>

HumiditySensor::HumiditySensor(const std::string& sensorName, double minValue, double maxValue)
    : sensorName_(sensorName), minValue_(minValue), maxValue_(maxValue) {
}

double HumiditySensor::read() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minValue_, maxValue_);
    return dist(gen);
}

std::string HumiditySensor::getName() const {
    return sensorName_;
}

std::string HumiditySensor::getUnit() const {
    return "%";
}