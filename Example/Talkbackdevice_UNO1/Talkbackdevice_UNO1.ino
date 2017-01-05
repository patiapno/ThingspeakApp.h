#include <moisture.h>
#include <SoftwareSerial.h>
SoftwareSerial serial(0,1);
Soil_moisture soil(5,A0);
#define pin 2

void setup() {
  Serial.begin(115200);
  serial.begin(115200);
  pinMode(pin,OUTPUT);
  digitalWrite(pin,HIGH);
  delay(100);
}

void loop() {
  float Soil=soil.getMoisture();
  if(serial.readString())
  {
    String recive=serial.readString();
    if(recive=="soil")
    {
      Serial.print(Soil);
    }
    
    else if(recive=="Open_pump")
    {
      digitalWrite(pin,LOW);
      Serial.print("Open pump");
    }
    else if(recive=="Close_pump")
    {
      digitalWrite(pin,HIGH);
      Serial.print("Close pump");
    }
    
  }
  delay(2000);
}
