#include "utils.h"
#include <chrono>   
#include <ctime>    
#include <cmath>    
#include <numeric>
#include <iomanip>
#include <sstream>

namespace utils {
    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();            //Takes the actual time from the system
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm;
        localtime_s(&local_tm, &now_time);
        std::ostringstream oss;
        oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M");
        return oss.str();
    }
    // Statistic calculations
    double calculateAverage(const std::vector<double>& values) {
        double sum = std::accumulate(values.begin(), values.end(), 0.0);
        return values.empty() ? 0.0 : sum / values.size();
    }

    double calculateMin(const std::vector<double>& values) {
        return *std::min_element(values.begin(), values.end());
    }

    double calculateMax(const std::vector<double>& values) {
        return *std::max_element(values.begin(), values.end());
    }

    double calculateStdDev(const std::vector<double>& values) {
        if (values.empty()) {
            return 0.0;
        }
        double mean = calculateAverage(values);
        double var = 0.0;
        for (double v : values) {
            var += std::pow(v - mean, 2);
        }
        return std::sqrt(var / values.size());
    }
}
