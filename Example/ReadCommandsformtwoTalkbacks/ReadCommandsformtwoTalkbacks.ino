#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingspeakApp.h>

#define ssid "YOU ssid"
#define pass "YOU pass"

#define Talk_key1 "YOU key1" //plantduino_esp
#define Talk_key2 "YOU key2" //plantduino_esp8266
#define Talk_id1 "YOU id1"   //plantduino_esp
#define Talk_id2 "YOU id2"  //plantduino_esp8266

#define cdm_id1 "YOU command id from key1" //Palntduino_ESP
#define cdm_id2 "YOU command id from key2" //plantduino_esp8266
Thingspeaktalkback  Thing(Talk_id1,Talk_key1,Talk_id2,Talk_key2);  //input key befor put id
void setup() {
  Serial.begin(115200);
  Thing.begin(ssid,pass);
}

void loop() {
  Thing.getCommand(cdm_id1);
  Serial.println(Thing.Getcommands_data);
  Thing.getCommand2(cdm_id2);
  Serial.println(Thing.Getcommands_data);
  delay(8000);
}
