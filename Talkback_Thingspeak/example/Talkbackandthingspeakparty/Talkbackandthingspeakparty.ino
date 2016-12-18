#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingspeakApp.h"

#define ssid "========="
#define pass "========="

#define Talkback_id "========="
#define Talkback_key "========="
#define Thing_write "========="

#define LIGHT_ON "========="
#define LIGHT_OFF "========="
#define PUMP_ON "========="
#define PUMP_OFF "========="
#define AIR_ON "========="
#define AIR_OFF "========="

Thingspeaktalkback Thing_Talk(Talkback_id,Talkback_key,Thing_write);
void setup() {
  Serial.begin(115200);
  Serial.println("\nConnecting to network");
  Thing_Talk.begin(ssid,pass);
  delay(500);
}
float i=20;
float z=50;
float y=70;
void loop() {
  i+=0.1;
  z/=2;
  y*=2.34;
  float data[3]={i,z,y};
  int num_field=3;
  //set time set pump set air =======================
  int set_timeon=Thing_Talk.Convert_toInt("8");
  float set_pumpon=Thing_Talk.Convert_toFloat("1024");
  float set_airon=Thing_Talk.Convert_toFloat("55");
  //================================================
  Serial.println("\n\n===Test commands===");
  String light=Thing_Talk.Timemer(set_timeon,LIGHT_ON,LIGHT_OFF);
  String pump=Thing_Talk.Pump(set_pumpon,PUMP_ON,PUMP_OFF);
  String air=Thing_Talk.Air(set_airon,AIR_ON,AIR_OFF);
  Serial.println(light);
  Serial.println(pump);
  Serial.println(air);
  Serial.println("===================\n\n");
  Serial.println("====WRITE THINGSPEAK====");
  Thing_Talk.Thingspeak_mutiplepub(data,num_field);
  Serial.println("========================\n\n");
  Serial.println("====READ THINGSPEAK====");
  String read_data1=Thing_Talk.Thingspeak_read(203958,1);
  String read_data2=Thing_Talk.Thingspeak_read(203958,2);
  String read_data3=Thing_Talk.Thingspeak_read(203958,3);
  Serial.println("Data in from: "+ read_data1);
  Serial.println("Data in from: "+ read_data2);
  Serial.println("Data in from: "+ read_data3);
  Serial.println("========================\n\n");
  delay(20*1000);
}
