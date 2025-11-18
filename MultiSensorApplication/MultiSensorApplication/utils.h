#pragma once 
#include <string>
#include <vector>
namespace utils
{
    std::string getCurrentTimestamp();
    // Statistic calculations
    double calculateAverage(const std::vector<double>& values);
    double calculateMin(const std::vector<double>& values);
    double calculateMax(const std::vector<double>& values);
    double calculateStdDev(const std::vector<double>& values);
}
