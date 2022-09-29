#include <dht.h>


#define dht_apin A0 // dht pin
byte serialA;

int analogPin = A3; //moisture sensor
int val = 0;  // variable to store the value read
int moisturePercentage = 0;
const int  dry = 599;
const int wet = 216;


 int relay1 = 2; 
 int relay2 = 3;
 
 dht DHT;
 
void setup(){
 
  Serial.begin(9600);
 pinMode(relay1,OUTPUT);
 pinMode(relay2, OUTPUT);
 
 
 
}
 
void loop(){
  
 
    DHT.read11(dht_apin);
    val = analogRead(analogPin);  
    moisturePercentage = map(val,wet,dry,100,0);
    



    Serial.print("Humidity= ");
    Serial.println(DHT.humidity);
  
    Serial.print("Temperature= ");
    Serial.println(DHT.temperature); 

    Serial.print("SoilMoisture=  ");
    Serial.println(  moisturePercentage);      
      delay(400);
       // debug value
    

 if (Serial.available() > 0) {serialA = Serial.read();Serial.println(serialA);} 

 switch(serialA)
 {
  
  case '1':
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  break;

  case '2':
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  break;


   
  }



 
}
