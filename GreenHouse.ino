#include <dht.h>
 
 
#define dht_apin A0 // dht pin
byte serialA;
 
 
// MOISTURE SENSOR SMOOTHING ALGORITHM
const int numReadings = 30;
 
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
 
const int sensor_pin = A3;


int val = 0;  // variable to store the value read
int moisturePercentage = 0;

 
 
 int relay1 = 2;
 int relay2 = 4;
 
 dht DHT;
 
void setup(){
 
  Serial.begin(9600);
 pinMode(relay1,OUTPUT);
 pinMode(relay2, OUTPUT);

 // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
 
 
}
 
void loop(){
 
 
    DHT.read11(dht_apin);
   

 float moisture_percentage;
  int sensor_analog;

  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = abs(( 100 - ( (sensor_analog/1023.00) * 100 ) ));
 
 
 
 
 
    Serial.print("Humidity= ");
    Serial.println(DHT.humidity);
 
    Serial.print("Temperature= ");
    Serial.println(DHT.temperature);
 
    Serial.print("SoilMoisture=  ");
    Serial.println(moisture_percentage - 47);
      delay(350);
       // debug value
   
 
 if (Serial.available() > 0) {serialA = Serial.read();Serial.println(serialA);}
 
 switch(serialA)
 {
 
  case '1':
  digitalWrite(relay1,HIGH);
  
  break;
 
  case '2':
  digitalWrite(relay1,LOW);

  break;



   case '3':
 
  digitalWrite(relay2,HIGH);
  break;



   case '4':

  digitalWrite(relay2,LOW);
  break;
 
 
   
  }
 
 
 
 
}
