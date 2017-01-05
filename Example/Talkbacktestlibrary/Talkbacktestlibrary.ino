#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingspeakApp.h>

#define ssid "+++++++++"
#define pass "--------"

#define Talk_id "------"
#define Talk_key "================="

#define Time_on "========"
#define Time_off "======="

#define data_on "========"
#define data_off "========"
Thingspeaktalkback Talk_thing(Talk_id,Talk_key);
void setup() {
  Serial.begin(115200);
  Talk_thing.begin(ssid,pass);
  Talk_thing.SetDevicetime(8,10,15,20);
  Talk_thing.SetDeviceCensor(14.50,12.33);
  delay(500);
}

void loop() {
  Talk_thing.DeviceaboutCensor(13.30,false,data_on,data_off);
  //Talk_thing.DeviceaboutTime(13,10,Time_on,Time_off);
  //if youwant to open device at night you will run like this
  Talk_thing.DeviceaboutTime(13,10,Time_off,Time_on);
  Serial.println("Time commands: "+Talk_thing.Getcommand_time);
  Serial.println("Data commands: "+Talk_thing.Getcommands_data);
  delay(5*1000);
}
