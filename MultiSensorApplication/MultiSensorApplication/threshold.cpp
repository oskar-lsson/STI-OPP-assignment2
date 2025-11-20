#include "threshold.h"
#include <iostream>
#include <iomanip>

void Alarm::print() const {
    std::cout << "[" << timestamp << "] "
        << sensorName << ": "
        << std::fixed << std::setprecision(2) << value
        << (wasOver ? " > " : " < ")
        << limit
        << " (THRESHOLD BREACH)\n";
}