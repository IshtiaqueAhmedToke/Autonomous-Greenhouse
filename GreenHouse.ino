
#include<DHT.h>


byte serialA;

const int led1 = 8;

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
const byte MQ4_Pin = A0;
const int R_0 = 945;
 
//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value




void setup() {
Serial.begin(9600);
pinMode(led1,OUTPUT);
 dht.begin();




}

void loop() {
 if (Serial.available() > 0) {serialA = Serial.read();Serial.println(serialA);} 

 switch(serialA)
 {
  
  case '1':
  digitalWrite(led1,HIGH);
  break;

  case '2':
  digitalWrite(led1,LOW);
  break;

   
  }



dhtRead();
 

 
 
}



float dhtRead()
{
  
  //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
//    Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(1000); //Delay 2 sec.
  
  
  }
