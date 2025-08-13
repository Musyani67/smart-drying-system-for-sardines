#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Pin configuration
#define DHTPIN 3          // DHT sensor connected to pin 3
#define FAN_PIN 12        // Fan control pin
#define DHTTYPE DHT22     // Change to DHT11 if using DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address 0x27

DHT dht(DHTPIN, DHTTYPE);

// Function declaration
void writeInLcd(int col, int row, String message);

// Thresholds
const float TEMP_LOW = 40.0;    // Lower threshold in °C
const float TEMP_HIGH = 50.0;   // Upper threshold in °C
bool fanState = false;          // Track fan status

void setup() {
  lcd.init();
  lcd.backlight();
  writeInLcd(0, 0, "Starting....");
  delay(2000);
  lcd.clear();

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    writeInLcd(0, 0, "Sensor Error!");
    delay(2000);
    return;
  }

  // Display temperature and humidity
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");

  // Fan control logic
  if (temperature > TEMP_HIGH && !fanState) {
    digitalWrite(FAN_PIN, HIGH);
    fanState = true;
  } else if (temperature < TEMP_LOW && fanState) {
    digitalWrite(FAN_PIN, LOW);
    fanState = false;
  }

  // Display fan status
  lcd.setCursor(0, 1);
  if (fanState) {
    lcd.print("Fan: ON ");
  } else {
    lcd.print("Fan: OFF");
  }

  delay(2000);
}

// Function to write to LCD
void writeInLcd(int col, int row, String message) {
  lcd.setCursor(col, row);
  lcd.print(message);
  delay(1000);
}
