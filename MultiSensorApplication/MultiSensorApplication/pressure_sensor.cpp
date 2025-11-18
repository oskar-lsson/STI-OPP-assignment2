#include "pressure_sensor.h"
#include <random>

PressureSensor::PressureSensor(const std::string& sensorName, double minValue, double maxValue)
    : sensorName_(sensorName), minValue_(minValue), maxValue_(maxValue) {
}

double PressureSensor::read() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minValue_, maxValue_);
    return dist(gen);
}

std::string PressureSensor::getName() const {
    return sensorName_;
}

std::string PressureSensor::getUnit() const {
    return "hPa";
}