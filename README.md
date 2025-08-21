# Smart Drying System for Sardines

This project automates the drying process for sardines using an ATMEGA328P microcontroller. It monitors temperature, humidity, and weight, and controls a fan and heater to optimize drying. The system provides real-time feedback via an I2C LCD display and allows users to adjust temperature thresholds using physical buttons.

## Features

- **DHT11 Sensor**: Measures temperature and humidity.
- **HX711 Load Cell**: Monitors the weight of the sardines to track drying progress.
- **LCD Display (I2C, 16x2)**: Shows temperature, humidity, fan/heater status, weight, and percentage weight loss.
- **Fan & Heater Control**: Automatically switches fan and heater based on user-defined temperature thresholds.
- **User Settings**: Adjust max/min temperature thresholds using UP, DOWN, and SET buttons.
- **Drying Completion Detection**: System stops when weight loss exceeds 70%.
- **PCB Design**: The PCB design for this project is already completed and ready for printing.

## How It Works

- On startup, the system calibrates the load cell and prompts the user to place the sardines.
- During operation, temperature and humidity are read every second, and weight is checked every two seconds.
- The fan turns ON if temperature exceeds the max threshold; the heater turns ON if temperature falls below the min threshold.
- The LCD alternates between showing sensor readings, actuator status, and drying progress.
- Enter settings mode with the SET button to adjust temperature thresholds using UP/DOWN buttons

## Getting Started

1. Upload `Main.ino` to your ATMEGA328P board.
2. Connect all components as per the pin table above.
3. Use the Proteus simulation files in the `proteus_circuit` folder for circuit validation.
4. Power on the system and follow LCD prompts.

## Usage Tips

- Use the SET button to enter/exit settings mode.
- In settings mode, select which temperature to adjust (max or min) using UP/DOWN, then change values.
- The system will display "Dried product!" when drying is complete.

## PCB Design

The PCB design for this system is already completed and ready for printing. You can find the design files in the repository.

---

For further development, consider adding more sensors, remote monitoring, or advanced control algorithms.
