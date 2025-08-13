#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Pin configuration
#define DHTPIN 7          // DHT sensor connected to pin 3
#define FAN_PIN 6        // Fan control pin
#define DHTTYPE DHT11     // Change to DHT11 if using DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address 0x27

DHT dht(DHTPIN, DHTTYPE);

// Function declaration
void writeInLcd(int col, int row, String message);

// Thresholds
const float TEMP_LOW = 35.0;    // Lower threshold in °C
const float TEMP_HIGH = 45.0;   // Upper threshold in °C
bool fanState = false;          // Track fan status

void setup() {
  dht.begin();
  
  lcd.init();
  lcd.backlight();
  writeInLcd(0, 0, "Starting....");
  delay(1000);

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

void loop() {
  lcd.clear();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    writeInLcd(0, 0, "Sensor Error!");
    delay(1500);
    return;
  }

  // Display temperature and humidity
  lcd.clear();
  String tempStr = "T:" + String(temperature, 1) + (char)223 + "C H:" + String(humidity, 0) + "%";
  writeInLcd(0, 0, tempStr);

  // Fan control logic
  if ((temperature > TEMP_HIGH) && !fanState) {
    digitalWrite(FAN_PIN, HIGH);
    fanState = true;
  } else if ((temperature < TEMP_LOW) && fanState) {
    digitalWrite(FAN_PIN, LOW);
    fanState = false;
  }

  // Display fan status
  String fanStatus = fanState ? "Fan: ON " : "Fan: OFF";
  writeInLcd(0, 1, fanStatus);

  delay(1500);
}

// Function to write to LCD
void writeInLcd(int col, int row, String message) {
  lcd.setCursor(col, row);
  lcd.print(message);
  delay(1000);
}
