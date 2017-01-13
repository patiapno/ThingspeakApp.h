#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingspeakApp.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(D5,D6);

#define ssid "TP-LINK_D3B838"
#define pass "034996393"

#define Talk_id "12266"
#define Talk_key "FD108CTVY6DF8XQU"
#define Thing_key "0UTN3TESA594F39V"

#define command_time1 "3476690"
#define command_time2 "3476691"
#define command_censor1On "3504217"
#define command_censor1Off "3504218"
#define command_censor2On "3560900"
#define command_censor2Off "3560903"
#define command_temp1on "3504219"
#define command_temp1off "3504220"

Thingspeaktalkback Talk(Talk_id,Talk_key,Thing_key);
Thingspeaktalkback Talking(Talk_id,Talk_key,Thing_key);
void setup() {
  Serial.begin(115200);
  serial.begin(115200);
  Talk.begin(ssid,pass);
  Talk.SetDeviceCensor(70.23,40.03);
  Talk.SetDevicetime(8,20,13,30);
  Talking.SetDeviceCensor(31.3,20.7);
  delay(500);
}

void loop() {
  String hour1="";
  String min1="";
  String soil1="";
  String soil2="";
  String temp1="";
  while(hour1=="")
  {
    Serial.println("GET1");
    serial.print("hour");
    hour1=serial.readString();
    delay(500);
  }
  while(min1=="")
  {
    Serial.println("GET2");
    serial.print("minute");
    min1=serial.readString();
    delay(500);
  }
  while(soil1=="")
  {
    Serial.println("GET3");
    serial.print("soil1");
    soil1=serial.readString();
    delay(500);
  }
  while(soil2=="")
  {
    Serial.println("GET4");
    serial.print("soil2");
    soil2=serial.readString();
    delay(500);
  }
  while(temp1=="")
  {
    Serial.println("GET5");
    serial.print("temp1");
    temp1=serial.readString();
    delay(500);
  }

  int Hour1=Talk.Convert_toInt(hour1);
  int Min1=Talk.Convert_toInt(min1);
  float Soil1=Talk.Convert_toFloat(soil1);
  float Soil2=Talk.Convert_toFloat(soil2);
  float Temp1=Talk.Convert_toFloat(temp1);
  Serial.println(Hour1);
  Serial.println(Min1);
  Serial.println(Soil1);
  Serial.println(Soil2);
  Serial.println(Temp1);
  float data[3]={Soil1,Soil2,Temp1};
  Serial.println("\nWrite to thing speak");
  Talk.Thingspeak_mutiplepub(data,3);
  String rest1="",rest2="",rest3="",rest4="";
  while(rest1=="")
  {
    Serial.println("GET6");
    //Time
    Talk.DeviceaboutTime(Hour1,Min1,command_time1,command_time2);
    String Time=Talk.Getcommand_time;
    serial.print(Time);
    Serial.print(Time);
    rest1=serial.readString();
    delay(500);
  }
  while(rest2=="")
  {
    Serial.println("GET7");
    //Censor1
    Talk.DeviceaboutCensor(Soil1,false,command_censor1On,command_censor1Off);
    String Censor1=Talk.Getcommands_data;
    serial.print(Censor1);
    rest2=serial.readString();
    delay(500);
    
  }
  while(rest3=="")
  {
    Serial.println("GET8");
    //Censor2
    Talk.DeviceaboutCensor(Soil2,false,command_censor2On,command_censor2Off);
    String Censor2=Talk.Getcommands_data;
    serial.print(Censor2);
    rest3=serial.readString();
    delay(500);
  }
  while(rest4=="")
  {
    Serial.println("GET9");
    //Temp1
    Talking.DeviceaboutCensor(Temp1,true,command_temp1on,command_temp1off);
    String Temp_1=Talking.Getcommands_data;
    serial.print(Temp_1);
    rest4=serial.readString();
    delay(500); 
  }
  Serial.println(rest1);
  Serial.println(rest2);
  Serial.println(rest3);
  Serial.println(rest4);
  delay(17*1000);
}
