#include "application.h"
#include "utils.h"
#include "temperature_sensor.h"
#include "humidity_sensor.h"
#include "pressure_sensor.h"
#include <iostream>
#include <limits> 
#include <iomanip>

Application::Application() : running(true) {
    // Create sensors polymorphically using smart pointers
    sensors.push_back(std::make_unique<TemperatureSensor>("Temperature", 10.0, 35.0));
    sensors.push_back(std::make_unique<HumiditySensor>("Humidity", 0.0, 100.0));
    sensors.push_back(std::make_unique<PressureSensor>("Pressure", 980.0, 1030.0));
}

void Application::run() {
    while (running) {
        showMenu();
        int choice;
        std::cin >> choice;
        // Input validation
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }
        // Clear leftover newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        clearWindow();
        switch (choice) {
        case 1:
            handleReadMeasurements();
            break;
        case 2:
            handleShowStatistics();
            break;
        case 3:
            handleShowAll();
            break;
        case 4:
            handleSaveToFile();
            break;
        case 5:
            handleLoadFromFile();
            break;
        case 6:
            handleConfigureThreshold();
            break;
        case 7:
            handleShowAlarms();
            break;
        case 8:
            std::cout << "Exiting program.\n";
            running = false;
            break;
        default:
            std::cout << "Invalid option. Try again.\n";
            break;
        }
    }
}

void Application::showMenu() {
    std::cout << "\n=====  SENSOR MENU  =====\n";
    std::cout << "[1] Read new measurements\n";
    std::cout << "[2] Show statistics\n";
    std::cout << "[3] Show all measurements\n";
    std::cout << "[4] Save measurements to file\n";
    std::cout << "[5] Load measurements from file\n";
    std::cout << "[6] Configure threshold\n";
    std::cout << "[7] Show alarms\n";
    std::cout << "[8] Exit\n";
    std::cout << "Select option: ";
}

void Application::handleReadMeasurements() {
    std::cout << "\nReading new measurements...\n";

    for (const auto& sensor : sensors) {
        Measurement m;
        m.sensorName = sensor->getName();    
        m.unit = sensor->getUnit();          
        m.value = sensor->read();         
        m.timestamp = utils::getCurrentTimestamp();

        storage.addMeasurement(m);
        m.print();
        // Check if threshold is breached
        checkThreshold(m.sensorName, m.value, m.timestamp);
    }
    std::cout << "Measurements added successfully.\n";
}

void Application::handleShowStatistics() {
    std::cout << "\n--- STATISTICS PER SENSOR ---\n";
    for (const auto& sensor : sensors) {
        storage.printSensorStatistics(sensor->getName());
    }
}

void Application::handleShowAll() {
    std::cout << "\n--- ALL MEASUREMENTS ---\n";
    std::cout << std::left << std::setw(20) << "Timestamp"
        << std::setw(15) << "Sensor"
        << std::right << std::setw(10) << "Value"
        << std::setw(8) << "Unit" << std::endl;
    std::cout << std::setfill('-') << std::setw(53) << "-" << std::setfill(' ') << std::endl;
    storage.printAll();
}

void Application::handleSaveToFile() {
    std::string filename;
    std::cout << "Enter filename to save (e.g. SensorMeasurements.csv): ";
    std::getline(std::cin, filename);
    storage.saveToFile(filename);
    std::cout << "Data saved to " << filename << "\n";
}

void Application::handleLoadFromFile() {
    std::string filename;
    std::cout << "Enter filename to load: ";
    std::getline(std::cin, filename);
    storage.loadFromFile(filename);
    std::cout << "Data loaded from " << filename << "\n";
}

void Application::handleConfigureThreshold() {
    std::cout << "\n--- CONFIGURE THRESHOLD ---\n";
    std::cout << "Available sensors:\n";

    for (int i = 0; i < sensors.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " << sensors[i]->getName() << "\n";
    }

    std::cout << "Select sensor (1-" << sensors.size() << "): ";
    int choice;
    std::cin >> choice;
    if (choice < 1 || choice > static_cast<int>(sensors.size())) {
        std::cout << "Invalid choice.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::string sensorName = sensors[choice - 1]->getName();

    double limit;
    std::cout << "Enter threshold limit: ";
    std::cin >> limit;

    int direction;
    std::cout << "Alarm when:\n";
    std::cout << "[1] Value goes OVER limit\n";
    std::cout << "[2] Value goes UNDER limit\n";
    std::cout << "Choice: ";
    std::cin >> direction;
    if (direction != 1 && direction != 2) {
        std::cout << "Invalid choice.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    Threshold t;
    t.sensorName = sensorName;
    t.limit = limit;
    t.over = (direction == 1);
    thresholds[sensorName] = t;

    std::cout << "Threshold configured for " << sensorName << ": "
        << (t.over ? ">" : "<") << " " << limit << "\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Application::handleShowAlarms() {
    std::cout << "\n--- ALARMS ---\n";
    if (alarms.empty()) {
        std::cout << "No alarms triggered.\n";
        return;
    }

    for (const auto& alarm : alarms) {
        alarm.print();
    }
    std::cout << "\nTotal alarms: " << alarms.size() << "\n";
}

void Application::checkThreshold(const std::string& sensorName, double value, const std::string& timestamp) {
    auto it = thresholds.find(sensorName);
    if (it == thresholds.end()) {
        return;  // No threshold configured for this sensor
    }

    const Threshold& threshold = it->second;
    bool breach = false;

    if (threshold.over && value > threshold.limit) {
        breach = true;
    }
    else if (!threshold.over && value < threshold.limit) {
        breach = true;
    }
    if (breach) {
        Alarm alarm;
        alarm.timestamp = timestamp;
        alarm.sensorName = sensorName;
        alarm.value = value;
        alarm.limit = threshold.limit;
        alarm.wasOver = threshold.over;

        alarms.push_back(alarm);

        std::cout << " ALARM TRIGGERED! ";
        alarm.print();
    }
}

void Application::clearWindow() {
    std::cout << "\x1B[2J\x1B[H";
}