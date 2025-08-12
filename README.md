# Smart Drying System for Sardines

This project uses an ATMEGA328P microcontroller to control an LCD display for a sardine drying system. The code initializes a LiquidCrystal LCD and provides a helper function to display messages on the screen.

## Main Features

- LCD initialization and backlight control
- Simple function to print messages to the LCD at any position

## Usage

- To display a message, use: `writeInLcd(col, row, "Your Message")`
- Example: `writeInLcd(0, 0, "Hello World")`

## Getting Started

1. Upload `Main.ino` to your ATMEGA328P board.
2. Connect the LCD as specified in the code.
3. The LCD will show "Starting..." on boot.

---
For further development, add sensor and actuator code as needed for temperature and humidity control.
