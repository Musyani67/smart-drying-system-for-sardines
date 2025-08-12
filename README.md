# Smart Drying System for Sardines

This project uses an ATMEGA328P microcontroller to automate the drying process for sardines. It includes:

- LCD display (with PC8574 chip)
- Fan circuit
- Heater circuit (controlled by relay)
- Microcontroller logic

## Simulation

Proteus simulation files are in the `proteus_circuit` folder. These files show the full circuit setup, including microcontroller, fan, heater, relay, and LCD display.

## Code Usage

- LCD initialization and message display via `writeInLcd(col, row, "Your Message")`
- Example: `writeInLcd(0, 0, "Hello World")`

## Getting Started

1. Upload `Main.ino` to your ATMEGA328P board.
2. Use the Proteus files to simulate the circuit before hardware implementation.
3. Connect components as shown in the simulation.

---
For further development, add sensor and actuator code for temperature and humidity control.
