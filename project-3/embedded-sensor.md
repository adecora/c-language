# Project 3: Embedded Sensor Management System

Design a C program for an embedded system that manages multiple sensor types in a samrt device (e.g. IoT environmental monitor). Use unions, structs, and enums to efficiently handle different sensor types (Temperature, Humidity, Pressure) with a type-specific configurations and data processing.

The program should run on a constrained embedded system with limited memory, emphasizing efficient use of unions for sensor data storage, and include functions to configure sensors, read data, and process readings based on sensor-specific logic.

## Requirements

1. Enum for Sensor Types: `TEMPERATURE, HUMIDITY, PRESSURE`.
2. Sensor Struct:
   - **id:** unsigned char (for memory efficiency)
   - **name:** char array (max 20 characters)
   - **type:** Sensor type (enum)
   - **data:** Union for type-specific configuration and data:
     - **Temperature:** min_range (short int), max_range (short int), reading (float)
     - **Humidity** calibration (float), reading (float)
     - **Pressure** altitude (short int), reading (float)
   - **status:** enum (`ACTIVE, INACTIVE, ERROR`)
3. Functions:
   - Initialize a sensor: Configure with type-specific settings (static array. max 10 sensors).
   - Read sensor data: Store latest reading.
   - Process sensor data:
     - **Temperature:** Flag ERROR if reading is outside min/max range.
     - **Humidity:** Apply calibration factor to reading.
     - **Pressure:** Adjust reading based on altitude compensation.
   - Display sensors: Show details and status.
4. Embedded System Optimization:
  - Use fixed-size arrays (no dynamic memory allocation).
  - Minimize memory usage with unions and appropriate data types.
  - Include basic error handling for invalid readings.
5. Simulation:
  - Simulate sensor readings with random values (no hardware I/O).


## Example Usage

- Initialize a Temperature sensor: `ID 1, "Temp1", range -10 to 50 ºC`
- Initialize a Humidity sensor: `ID 2, "Hum1", calibration factro 1.05`
- Initialize a Temperature sensor: `ID 1, "Pres1", altitude compesation 100m`
- Read and process data for all sensors.
- Display sensor details, latest readings, and status.


## Challenges

- Optimize memory usage with unions for sensor-specific data.
- Handle type-specific data processing in a constrained environment.
- Ensure robust error checking for sensor status.
- Simulate realistic sensor readings without hardware.