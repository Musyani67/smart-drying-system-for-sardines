#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <HX711.h>

// Pin configuration
#define DHTPIN 7          // DHT sensor connected to pin 7
#define FAN_PIN 6        // Fan control pin
#define DHTTYPE DHT11     // Change to DHT11 if using DHT11
#define HEATER_PIN 11
#define LD_Cell_DO_PIN  13
#define LD_Cell_CK_PIN 12

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address 0x27

DHT dht(DHTPIN, DHTTYPE);

// Function declaration
void writeInLcd(int col, int row, String message);

// Thresholds
const float TEMP_LOW = 35.0;    // Lower threshold in °C
const float TEMP_HIGH = 45.0;   // Upper threshold in °C
bool fanState = false;          // Track fan status

//Load cell
HX711 scale;  
const float Calib_factor = 0.0001;
float initialWeight = 0.0;
bool initialWeightTaken = false;

void setup() {
  dht.begin();
  
  lcd.init();
  lcd.backlight();
  writeInLcd(0, 0, "Starting....");
  delay(1000);

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW); // Fan OFF initially

  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW); // Heater OFF initially

  //Load Cell
  scale.set_scale(Calib_factor);
  scale.tare();
  Serial.println("Place the sardines on the scale to record the initial Weight");
   writeInLcd(0, 0, "Place sardines to record initial Weight");
}

void loop() {
  lcd.clear();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  //Load cell
  float currentWeight = scale.get_units(10);

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
  lcd.clear();

  String heaterStatus;
  // Heater control logic
    if (temperature <=TEMP_LOW) {
    digitalWrite(HEATER_PIN, HIGH); // Heater ON
    heaterStatus = "Heater ON";
  } 
  else if (temperature >= TEMP_HIGH) {
    digitalWrite(HEATER_PIN, LOW); // Heater OFF
    heaterStatus = "Heater OFF";
  }
  writeInLcd(0, 0, heaterStatus);

  delay(1500);

  // Load Cell 
  if (!initialWeightTaken){
  if (currentWeight > 1.0){
    initialWeight = currentWeight;
    initialWeightTaken = true;
    Serial.print("Initial Weight recorded: ");
    Serial.print(initialWeight, 13);
    Serial.print(" g");
    }
    } else{
      float WeightLossPercentage = ((initialWeight - currentWeight) / initialWeight) * 100;
    lcd.clear();
    String per_weight = "Weight Loss :" + String(WeightLossPercentage, 2) + "%" + " Current Weight: " + String(currentWeight, 2) + "g";
    writeInLcd(0, 1, per_weight);

      Serial.print(millis()/ 1000);
      Serial.print( " s");
      Serial.println(currentWeight, 2);
      Serial.print(" g");
      Serial.println(WeightLossPercentage,2);
      Serial.print(" %");

    }
}



// Function to write to LCD
void writeInLcd(int col, int row, String message) {
  lcd.setCursor(col, row);
  lcd.print(message);
  delay(1000);
}