#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "sensor.h"
#include "storage.h"
#include "threshold.h"

class Application
{
private:
    Storage storage;
    std::vector<std::unique_ptr<Sensor>> sensors;  // Polymorphic storage!
    std::map<std::string, Threshold> thresholds;   // Sensor name -> Threshold
    std::vector<Alarm> alarms;                     // List of triggered alarms
    bool running;

    void showMenu();
    void handleReadMeasurements();
    void handleShowStatistics();
    void handleShowAll();
    void handleSaveToFile();
    void handleLoadFromFile();
    void handleConfigureThreshold();  // NEW
    void handleShowAlarms();          // NEW
    void clearWindow();

    void checkThreshold(const std::string& sensorName, double value, const std::string& timestamp);

public:
    Application();
    void run();
};

