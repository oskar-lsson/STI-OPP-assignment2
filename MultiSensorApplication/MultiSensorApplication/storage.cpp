#include "storage.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>  
#include <iomanip>   


void Storage::addMeasurement(const Measurement& m) {
    measurements.push_back(m);
}
void Storage::printAll() const {
    if (measurements.empty()) {
        std::cerr << "PRINT FAILED: No values" << std::endl;

    }
    else {
        for (auto& m : measurements) {
            std::cout << std::left << std::setw(20) << m.timestamp
                << std::setw(15) << m.sensorName
                << std::right << std::setw(10) << std::fixed << std::setprecision(2) << m.value
                << std::setw(8) << m.unit << std::endl;
        }
    }
}

std::vector<Measurement> Storage::getSensor(const std::string& sensorName) const {
    std::vector<Measurement> selectedSensor;   // empty list to save all measurement of selected sensor
    for (const auto& m : measurements) {
        if (m.sensorName == sensorName) {
            selectedSensor.push_back(m);
        }
    }
    return selectedSensor;
}

std::vector<double> Storage::getSensorValues(const std::string& sensorName) const {
    std::vector<double> sensorValues;   // empty list to save all measurement of selected sensor
    for (const auto& m : measurements) {
        if (m.sensorName == sensorName) {
            sensorValues.push_back(m.value);
        }
    }
    return sensorValues;
}

// statistics calculations
int Storage::count(const std::string& sensorName) const {
    auto val = getSensorValues(sensorName);
    return val.size();
}
float Storage::average(const std::string& sensorName) const {
    auto val = getSensorValues(sensorName);
    return utils::calculateAverage(val);
}
float Storage::minimum(const std::string& sensorName) const {
    auto val = getSensorValues(sensorName);
    return utils::calculateMin(val);

}
float Storage::maximum(const std::string& sensorName) const {
    auto val = getSensorValues(sensorName);
    return utils::calculateMax(val);
}
float Storage::stdDeviation(const std::string& sensorName) const {
    auto val = getSensorValues(sensorName);
    return utils::calculateStdDev(val);
}
//Prints the the sensorsstatistic
void Storage::printSensorStatistics(const std::string& sensorName) {
    if (measurements.empty()) {
        std::cerr << "PRINT FAILED: No values" << std::endl;
        return;
    }
    std::cout << "--- " << sensorName << " ---\n";

    for (const auto& m : getSensor(sensorName)) {
        std::cout << m.timestamp << ", " << std::right << std::setw(4) << std::fixed << std::setprecision(2) << m.value << " " << m.unit << std::endl;
    }
    std::cout << "\n";
    // Printing statistics
    std::cout << "Count: " << count(sensorName) << '\n';
    std::cout << "Average: " << std::fixed << std::setprecision(2) << average(sensorName) << '\n';
    std::cout << "Minimum value: " << minimum(sensorName) << '\n';
    std::cout << "Maximum value: " << maximum(sensorName) << '\n';
    std::cout << "Standard Deviation: " << stdDeviation(sensorName) << "\n\n";
}

void Storage::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open file\n";
        return;
    }

    file << "timestamp,sensor,value,unit\n";
    for (const auto& m : measurements) {
        file << m.timestamp << ","
            << m.sensorName << ","
            << std::fixed << std::setprecision(2) << m.value << ","
            << m.unit << "\n";
    }
    file.close();
    std::cout << "Measurements successfully saved to file.\n";
}

void Storage::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open file for reading.\n";
        return;
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        // skip the header if present
        if (firstLine && line.find("timestamp") != std::string::npos) {
            firstLine = false;
            continue;
        }
        firstLine = false;

        std::stringstream ss(line);
        std::string timestamp, sensorName, unit, valueStr;
        float value = 0.0f;

        std::getline(ss, timestamp, ',');
        std::getline(ss, sensorName, ',');
        std::getline(ss, valueStr, ',');
        std::getline(ss, unit, ',');

        if (timestamp.empty() || sensorName.empty() || valueStr.empty() || unit.empty()) {
            continue; // skip invalid lines
        }

        try {
            value = std::stof(valueStr);
        }
        catch (...) {
            continue; // skip invalid number format
        }

        Measurement m;
        m.timestamp = timestamp;
        m.sensorName = sensorName;
        m.value = value;
        m.unit = unit;
        measurements.push_back(m);
    }
    file.close();
    std::cout << "Measurements successfully loaded from file.\n";
}
