#include "measurement.h"
#include <iostream>

void Measurement::print() const {
    std::cout << "Measurement("
        << "Sensor name = " << sensorName
        << ", value = " << value
        << ", unit = " << unit
        << ", timestamp = " << timestamp
        << ")\n";
}