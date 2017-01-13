#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingspeakApp.h"
#define Thing_key "YOU KEY"
#define ssid "YOU SSID"
#define pass "YOU PASS"
float data=14.55;
Thingspeakgarph2 g(Thing_key);
Thingspeaktalkback T;
void setup() {
  Serial.begin(115200);
  T.begin(ssid,pass);
  delay(100);
}

void loop() {
  g.ThingSpeakWrite(data,2,1);
  delay(20*1000);
}
