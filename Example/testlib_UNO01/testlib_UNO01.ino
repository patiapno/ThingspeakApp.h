#include <SoftwareSerial.h>
#include <moisture.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x3F,16,2);
Soil_moisture soil1(3.3,A0);
Soil_moisture soil2(3.3,A1);
SoftwareSerial serial(0,1);
#define DHTPIN 3
#define DHTTYPE DHT11 
#define pin1 4
#define pin2 5
#define pin3 6
#define pin4 7

DHT dht;
void setup() {
  Wire.begin();
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,HIGH);
  //SPI.begin();
  lcd.begin();
  Serial.begin(115200);
  serial.begin(115200);
  dht.setup(3);
  rtc.begin();
  delay(500);
  lcd.print("Welcome");
  delay(1000);
}

void loop() {
  lcd.clear();
  /*lcd.setCursor(0,0);
  lcd.print("Recive: ");
  lcd.setCursor(1,0);
  lcd.print("Send: ");*/
  lcd.print("Wellcome");
  delay(2000);
  lcd.clear();
  DateTime now=rtc.now();
  int Hour=now.hour();
  int Minute=now.minute();
  float temp=dht.getTemperature();
  float Soil1=soil1.getMoisture();
  float Soil2=soil2.getMoisture();
  if(serial.readString())
  {
    lcd.print(serial.readString());
    if(serial.readString()=="hour")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print(Hour);
      Serial.print(Hour);
    }
    else if(serial.readString()=="minute")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,1);
      lcd.print(Minute);
      Serial.print(Minute);
    }
    else if(serial.readString()=="soil1")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,1);
      lcd.print(Soil1);
      Serial.print(Soil1);
    }
    else if(serial.readString()=="soil2")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,1);
      lcd.print(Soil2);
      Serial.print(Soil2);
    }
    else if(serial.readString()=="temp1")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print(temp);
      Serial.print(temp);
    }
    else if(serial.readString()=="Open_light")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Open light");
      Serial.print("Open light");
      digitalWrite(pin1,LOW);
    }
    else if(serial.readString()=="Close_light")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Close light");
      Serial.print("Close light");
      digitalWrite(pin1,HIGH);
    }
    else if(serial.readString()=="Open_pump")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Open pump");
      Serial.print("Open pump");
      digitalWrite(pin2,LOW);
    }
    else if(serial.readString()=="Close_pump")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Close pump");
      Serial.print("Close pump");
      digitalWrite(pin2,HIGH);
    }
    else if(serial.readString()=="Open_air")
    {
      //lcd.setCursor(0,0);
      //lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Open air");
      Serial.print("Open air");
      digitalWrite(pin3,LOW);
    }
    else if(serial.readString()=="Close_air")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Close air");
      Serial.print("Close air");
      digitalWrite(pin3,HIGH);
    }
    else if(serial.readString()=="Open_pump2")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Open pump2");
      Serial.print("Open pump2");
      digitalWrite(pin4,LOW);
    }
    else if(serial.readString()=="Close_pump2")
    {
      //lcd.setCursor(0,0);
      lcd.print(serial.readString());
      //lcd.setCursor(1,0);
      lcd.print("Close pump2");
      Serial.print("Close pump2");
      digitalWrite(pin4,HIGH);
    }
  }
  delay(2*1000);
  lcd.clear();
}
