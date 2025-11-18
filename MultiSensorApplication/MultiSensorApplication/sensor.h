#pragma once
#include <string>

class Sensor {
public:
    virtual ~Sensor() = default;

    virtual double read() = 0;
    virtual std::string getName() const = 0;
    virtual std::string getUnit() const = 0;
};
