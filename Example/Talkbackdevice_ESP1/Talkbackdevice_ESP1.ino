#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingspeakApp.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(D5,D6);

#define ssid "TP-LINK_D3B838"
#define pass "034996393"

#define Talk_id "12540"
#define Talk_key "0AC5D8JY5MTZFD1H"
#define Thing_key "H1KZQV11WIV1MAMY"

#define cdm_id_on "3686455"
#define cdm_id_off "3686456"
Thingspeaktalkback Talk(Talk_id,Talk_key,Thing_key);

void setup() {
  Serial.begin(115200);
  serial.begin(115200);
  Talk.begin(ssid,pass);
  Talk.SetDeviceCensor(90.5,72.66);
  delay(500);
}

void loop() {
  String soil="";
  
  while(soil=="")
  {
    Serial.println("GET soil");
    serial.print("soil");
    soil=serial.readString();
    delay(500);
  }
  
  float Soil=Talk.Convert_toFloat(soil);
  Serial.println(soil);
  Talk.Thingspeak_pub(Soil,1);
  String rest="";
  
  while(rest=="")
  {
    Serial.println("GET rest");
    Talk.DeviceaboutCensor(Soil,false,cdm_id_on,cdm_id_off);
    String Censor=Talk.Getcommands_data;
    serial.print(Censor);
    rest=serial.readString();
    delay(500);
  }
  
  Serial.println(rest);
  delay(20*1000);
}
