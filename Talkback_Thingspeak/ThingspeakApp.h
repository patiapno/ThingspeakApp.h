#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class Thingspeaktalkback  // ThigSpeaktalkbackcommands,use in updateThingspeakdata
{                         // to garph  
	public:HTTPClient http;
	public:
		void begin(const char* ssid,const char* pass); // connect wifi
		void begin(const char* ssid, const char* pass,int ip[4],int getwat[4],
		int subnet[4]); //to connect and config you wofo ip address
	
	public:
		Thingspeaktalkback(const char* Talkback_id,const char* Talkback_key,
		const char* Thing_write);  //not use thingspeak readkey because
		                           //you must make you channel to public
		Thingspeaktalkback(const char* Talkback_id,const char* Talkback_key);
		//for when you want to use only thingspeakcommands 
	
		Thingspeaktalkback(const char* Talkbacl_id1,const char* Talkback_key1,
		const char* Talkback_id2,const char* Talkback_key2);
		//use when you want to connect whit two Talkbackcommands 
		//(whith out thingspeak)
	
		Thingspeaktalkback(const char* Talkbacl_id1,const char* Talkback_key1,
		const char* Talkback_id2,const char* Talkback_key2,const char* 
		Thing_write);
	    //use when you want to connect whit two Talkbackcommands 
		//(whith  thingspeak)
		
		float Convert_toFloat(String data); //convertdata to float type
		int Convert_toInt(String data); //convertdata to int type
		
		String Timemer(int time_on,const char* cdm_on,
		const char* cdm_off); //set time to on off device
		
		String Pump(float hight_off,const char* cdm_on,
		const char* cdm_off); //set soil hum to on/off pump
		
		String Air(float hum_on,const char* cdm_on,
		const char* cdm_off); //set hun to on/off air
   
    public:
    	void  Thingspeak_pub(float data,int field);
    	void  Thingspeak_mutiplepub(float data[8],int count_field);
    	String Thingspeak_read(int ch_num,int field);
 	
	 /*public:
 		const char* talk_id1;
        const char* talk_key1;
        const char* talk_id2;
        const char* talk_key2;
        const char* thing_write;*/
		 
};                                

class Thingspeakgarph
{
	public: HTTPClient http;
	public:
		Thingspeakgarph(); // set thingspeak
		
		void ThingSpeakWrite(float data,int field);
		void ThingSpeakMutipleWrite(float data[8],int cout_field);
		String ThingSpeakRead(int ch_num,int field); //public only
};