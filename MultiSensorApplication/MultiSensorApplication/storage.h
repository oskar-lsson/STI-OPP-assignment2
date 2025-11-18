#pragma once
#include <vector>
#include <string>
#include "measurement.h"

class Storage
{
private:
    std::vector<Measurement> measurements;
public:
    void addMeasurement(const Measurement& m);
    void printAll() const;

    std::vector<Measurement> getSensor(const std::string& sensorName) const;        //used for sorting the vector to one sensor, later used for showing statistics
    std::vector<float> getSensorValues(const std::string& sensorName) const;

    int count(const std::string& sensorName) const;
    float average(const std::string& sensorName) const;
    float minimum(const std::string& sensorName) const;
    float maximum(const std::string& sensorName) const;
    float stdDeviation(const std::string& sensorName) const;
    void printSensorStatistics(const std::string& sensorName);                      //Prints the statistics

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

