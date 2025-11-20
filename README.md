#  Multi-Sensor Monitoring System with Threshold Alarms

## Overview
This project is a C++ application that models an **IoT-based sensor monitoring system** with alarm capabilities.  
The program can **simulate measurements**, **store data**, **perform statistical analysis**, **configure threshold alarms**, and **handle file input/output**.  
Users interact with the program through a **menu-based terminal interface**.

This system demonstrates **object-oriented design** using **inheritance** and **polymorphism** for sensor management.

---

## Purpose
The goal of this project is to practice:
- Building a **multi-class C++ system** with clear separation of responsibility  
- Implementing **polymorphic sensor classes** with a common interface  
- Modeling a **sensor-based system** with **real-time alarm monitoring**  
- Handling **structured data**, performing **analysis**, and **saving results**  
- Using **modern C++ features** such as smart pointers, inheritance, and containers  
- Writing clean, structured, and well-organized code  

---

## Program Features
The program can:
1. Manage **multiple sensors** of different types (Temperature, Humidity, Pressure)  
2. Simulate **measurement values** within defined intervals  
3. Store each measurement in a **structured format** with timestamps  
4. Perform **statistical analysis** per sensor (count, average, min, max, standard deviation)  
5. **Configure custom threshold alarms** for each sensor  
6. **Monitor and log alarm events** when thresholds are breached  
7. **Read from and write to CSV files**  
8. Provide a **menu-driven terminal interface**  

---

## Timestamps
Each measurement automatically gets a **timestamp** using the current system time (`std::chrono`).  
The timestamp is stored in the `Measurement` struct and displayed when data is printed or saved to a file.

Example format:
```
2025-11-20 14:30 | Temperature | 22.40 °C
```

---

## Project Structure
```
project/
├── main.cpp
├── sensor.h
├── temperature_sensor.h / temperature_sensor.cpp
├── humidity_sensor.h / humidity_sensor.cpp
├── pressure_sensor.h / pressure_sensor.cpp
├── measurement.h / measurement.cpp
├── storage.h / storage.cpp
├── threshold.h / threshold.cpp
├── utils.h / utils.cpp
├── application.h / application.cpp   
└── README.md
```

---

## Classes and Structures

### **Sensor (Base Class)**
Abstract base class for all sensor types.
- Pure virtual methods:
  - `double read()` — returns a simulated measurement value
  - `std::string getName() const` — returns sensor name
  - `std::string getUnit() const` — returns unit of measurement

### **TemperatureSensor : Sensor**
- Unit: `°C`
- Range: `10.0 - 35.0`

### **HumiditySensor : Sensor**
- Unit: `%`
- Range: `0.0 - 100.0`

### **PressureSensor : Sensor**
- Unit: `hPa`
- Range: `980.0 - 1030.0`

---

### **Measurement (struct)**
- `std::string sensorName`
- `std::string unit`
- `double value`
- `std::string timestamp`

Represents one individual sensor reading.

---

### **Threshold (struct)**
- `std::string sensorName`
- `double limit`
- `bool over` — `true`: alarm if value > limit, `false`: alarm if value < limit

Configuration for sensor alarms.

---

### **Alarm (struct)**
- `std::string timestamp`
- `std::string sensorName`
- `double value`
- `double limit`
- `bool wasOver` — indicates if alarm was triggered by exceeding or falling below threshold

Represents a logged alarm event.

---

### **Storage**
- Contains: `std::vector<Measurement> measurements`
- Methods:
  - `addMeasurement(const Measurement&)`
  - `printAll()`
  - `printSensorStatistics(sensorName)` — displays count, mean, min, max, and standard deviation
  - `saveToFile(filename)` — exports to CSV
  - `loadFromFile(filename)` — imports from CSV

---

### **Application**
Main application controller managing sensors, storage, thresholds, and alarms.
- Contains:
  - `std::vector<std::unique_ptr<Sensor>> sensors` — polymorphic sensor collection
  - `std::map<std::string, Threshold> thresholds` — threshold configurations
  - `std::vector<Alarm> alarms` — alarm history
- Handles all menu operations and user interactions

---

## Data Analysis
For each sensor, the system can calculate:
- Number of measurements  
- Average value  
- Minimum and maximum values  
- Standard deviation  

Formatted output is displayed using `std::setprecision` and `std::setw`.

---

## Threshold Alarm System
Users can configure custom thresholds for each sensor:
- Set a **limit value**
- Choose alarm direction: **over** or **under** the limit
- System automatically checks each new measurement
- Triggered alarms are **logged with timestamp** and displayed immediately
- View full alarm history via the menu

Example alarm output:
```
ALARM TRIGGERED!
[2025-11-20 14:35] Temperature: 36.20 > 35.00 (THRESHOLD BREACH)
```

---

## File Format
CSV format used for data persistence:
```
timestamp,sensor,value,unit
2025-11-20 14:30,Temperature,22.50,°C
2025-11-20 14:30,Humidity,45.80,%
2025-11-20 14:30,Pressure,1013.25,hPa
```

File handling uses:
- `std::ofstream` — save data to file  
- `std::ifstream` — load data from file  
- Invalid or malformed lines are skipped safely

---

## Menu Interface
User menu options:

| Option | Description |
|---------|-------------|
| 1 | Read new measurements from all sensors |
| 2 | Show statistics per sensor |
| 3 | Display all stored measurements |
| 4 | Save measurements to file |
| 5 | Load measurements from file |
| 6 | Configure threshold for a sensor |
| 7 | Show alarm history |
| 8 | Exit the program |

Invalid input is handled gracefully with clear error messages.

---

## Example Run
```
=====  SENSOR MENU  =====
[1] Read new measurements
[2] Show statistics
[3] Show all measurements
[4] Save measurements to file
[5] Load measurements from file
[6] Configure threshold
[7] Show alarms
[8] Exit
Select option: 1

Reading new measurements...
Measurement(Sensor name = Temperature, value = 22.45, unit = °C, timestamp = 2025-11-20 14:30)
Measurement(Sensor name = Humidity, value = 58.32, unit = %, timestamp = 2025-11-20 14:30)
Measurement(Sensor name = Pressure, value = 1015.67, unit = hPa, timestamp = 2025-11-20 14:30)
Measurements added successfully.
```

---

## Technical Requirements
- Language: **C++17** or later  
- Compiler: Visual Studio, g++, or clang++  
- Uses:
  - `std::vector`, `std::map`
  - `std::unique_ptr` (smart pointers)
  - `std::string`
  - `<iostream>`, `<fstream>`, `<iomanip>`
  - `<chrono>` (for timestamps)
  - `<random>` (for simulated sensor values)
  - **Inheritance and polymorphism**

---

## Architecture Highlights
- **Polymorphic Design**: Base `Sensor` class with specialized implementations
- **Smart Pointers**: Modern C++ memory management with `std::unique_ptr`
- **Separation of Concerns**: Distinct classes for sensors, storage, measurements, thresholds, and utilities
- **Extensible**: Easy to add new sensor types by inheriting from `Sensor`
- **Robust Input Handling**: Validates user input and handles errors gracefully
