#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class Thingspeaktalkback// ThigSpeaktalkbackcommands,use in updateThingspeakdata
{                      // to garph  
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
		
    public:
    	void  Thingspeak_pub(float data,int field);
    	void  Thingspeak_mutiplepub(float data[8],int count_field);
    	String Thingspeak_read(int ch_num,int field);
   
    private:
   	int HR_ON;
   	int MIN_ON;
   	int HR_OFF;
   	int MIN_OFF;
   	float HIGH_DATA;
   	float LOW_DATA;
   public:
   	String Getcommand_time;
   	String Getcommands_data;
   	int State;
   public:
   	    void SetDeviceCensor(float hight,float low);
   	    void SetDevicetime(int hr_on,int min_on,int hr_off,int min_off);
   	    void DeviceaboutTime(int time_hr,int time_min,const char* command_on,
		   const char* command_off);
		void DeviceaboutCensor(float data_censor,bool logic,
		const char* cdm_on,const char* cdm_off); 
		//true=send hightopen flase=send lowopen	 
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