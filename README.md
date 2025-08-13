# Smart Drying System for Sardines

This project uses an ATMEGA328P microcontroller to automate the drying process for sardines. The system monitors temperature and humidity using a DHT sensor, displays readings on an LCD, and controls a fan based on temperature thresholds.

## Main Features

- DHT sensor for temperature and humidity
- LCD display (I2C, PC8574 chip)
- Automatic fan control
- Simple LCD message function

## Simulation

Proteus simulation files are in the `proteus_circuit` folder. These show the full circuit setup: microcontroller, fan, heater (relay), and LCD display.

## Code Usage

- Temperature and humidity are displayed on the LCD
- Fan turns ON above 50°C, OFF below 40°C
- Use `writeInLcd(col, row, "Your Message")` to display custom messages

## Getting Started

1. Upload `Main.ino` to your ATMEGA328P board
2. Use Proteus files to simulate the circuit before hardware implementation
3. Connect DHT sensor, fan, and LCD as shown in simulation

---
For further development, add more sensors or actuators as needed for drying control.
