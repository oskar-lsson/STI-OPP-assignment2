#include "temperature_sensor.h"
#include <random>

TemperatureSensor::TemperatureSensor(const std::string& sensorName, double minValue, double maxValue)
    : sensorName_(sensorName), minValue_(minValue), maxValue_(maxValue) {
}

double TemperatureSensor::read() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minValue_, maxValue_);
    return dist(gen);
}

std::string TemperatureSensor::getName() const {
    return sensorName_;
}

std::string TemperatureSensor::getUnit() const {
    return "\370C";
}