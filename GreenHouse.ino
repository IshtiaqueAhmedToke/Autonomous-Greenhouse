#include <DHT.h>

// Soil moisture sensors
const int soilMoisturePin1 = A0;
const int soilMoisturePin2 = A1;
const int soilMoisturePin3 = A2;

// CO sensor
const int coSensorPin = A3;

// pH sensor
const int phSensorPin = A4;

// DHT11 sensor
const int dht11Pin = 2;
#define DHTTYPE DHT11
DHT dht(dht11Pin, DHTTYPE);

// Control Pins
const int nutrientPumpPin = 3;
const int waterPumpPin = 4;
const int exhaustFanPin = 5;

// pH sensor simulation
float pH;
//actual ph
float phValue;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Set control pins as OUTPUT
  pinMode(nutrientPumpPin, OUTPUT);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(exhaustFanPin, OUTPUT);
}

void loop() {
  // Read soil moisture sensors
  int soilMoisture1 = analogRead(soilMoisturePin1);
  int soilMoisture2 = analogRead(soilMoisturePin2);
  int soilMoisture3 = analogRead(soilMoisturePin3);

  // Read CO sensor
  int coRaw = analogRead(coSensorPin);
  float co_ppm = calculateCOppm(coRaw);

  // Read DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read actual pH sensor
  phValue = readPhSensor();

  // Simulate pH sensor
  pH = simulatePhSensor(soilMoisture1, soilMoisture2, soilMoisture3, co_ppm, temperature, humidity);

  // Control nutrient pump, water pump, and exhaust fan
  controlSystem(temperature, soilMoisture1, soilMoisture2, soilMoisture3, phValue);

  // Manual control of nutrient pump, water pump, and exhaust fan
  if (Serial.available() > 0) {
    char serialA = Serial.read();
    Serial.println(serialA);

    switch(serialA) {
      case '1':
        digitalWrite(nutrientPumpPin, HIGH); // Turn on nutrient pump
        break;
      
      case '2':
        digitalWrite(nutrientPumpPin, LOW); // Turn off nutrient pump
        break;
        
      case '3':
        digitalWrite(waterPumpPin, HIGH); // Turn on water pump
        break;

      case '4':
        digitalWrite(waterPumpPin, LOW); // Turn off water pump
        break;

      case '5':
        digitalWrite(exhaustFanPin, HIGH); // Turn on exhaust fan
        break;

      case '6':
        digitalWrite(exhaustFanPin, LOW); // Turn off exhaust fan
        break;

      default:
        Serial.println("Invalid command");
    }
  }

  // Print readings
  Serial.print("Soil Moisture 1 (%): "); Serial.println(soilMoisture1);
  Serial.print("Soil Moisture 2 (%): "); Serial.println(soilMoisture2);
  Serial.print("Soil Moisture 3 (%): "); Serial.println(soilMoisture3);
  Serial.print("CO (ppm): "); Serial.println(co_ppm);
  Serial.print("Temperature (C): "); Serial.println(temperature);
  Serial.print("Humidity (%): "); Serial.println(humidity);
  Serial.print("Simulated pH: "); Serial.println(pH);
  Serial.print("Actual pH: "); Serial.println(phValue);

  delay(2000);
}

void controlSystem(float temperature, int soilMoisture1, int soilMoisture2, int soilMoisture3, float phValue) {
  // Control logic based on temperature, soil moisture and pH value
  // Activate nutrient pump if pH value is not within optimal range (5.5 to 7.0)
  if (phValue < 5.5 || phValue > 7.0) {
    digitalWrite(nutrientPumpPin, HIGH);
  } else {
    digitalWrite(nutrientPumpPin, LOW);
  }

  // Activate water pump if all of the soil moisture readings are below 40%
  if (soilMoisture1 < 40 && soilMoisture2 < 40 && soilMoisture3 < 40) {
    digitalWrite(waterPumpPin, HIGH);
  } else {
    digitalWrite(waterPumpPin, LOW);
  }

  // Activate exhaust fan if temperature is above 30 degrees Celsius
  if (temperature > 30) {
    digitalWrite(exhaustFanPin, HIGH);
  } else {
    digitalWrite(exhaustFanPin, LOW);
  }
}

float calculateCOppm(int coRaw) {
  float sensorVoltage = (float)coRaw / 1024 * 5.0;
  float sensorResistance = (5.0 - sensorVoltage) * 10 / sensorVoltage;
  float ro = 10; // Reference resistance in clean air (in kOhms)
  float sensitivity = 0.6; // Sensitivity factor (varies depending on the sensor)
  float rs_ro_ratio = sensorResistance / ro;
  float co_ppm = pow((rs_ro_ratio / sensitivity), (1 / -1.179));
  return co_ppm;
}

float simulatePhSensor(int soilMoisture1, int soilMoisture2, int soilMoisture3, float co_ppm, float temperature, float humidity) {
  float avgSoilMoisture = (soilMoisture1 + soilMoisture2 + soilMoisture3) / 3.0;
  float pH = 6.0 + ((avgSoilMoisture / 100.0) * 1.5) - (co_ppm / 1000.0) + (temperature / 100.0) - (humidity / 100.0);
  return constrain(pH, 0, 14);
}

float readPhSensor() {
  int phRaw = analogRead(phSensorPin);
  // Convert the raw analog value to pH using calibration parameters.
  float phValue = (float)phRaw / 1024 * 5.0 * 3.5; 
  return phValue;
}
