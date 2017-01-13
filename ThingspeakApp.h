#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
/*
   Thingspeak Talkback library Creat by ESP8266HTTPClient.h 

   Update!!! 13/01/2017

   Crate by Mr Patipan Polvirat
   
   at: AT&T_LAB2017
   coppy right AT&T_LAB
       (2016-2017)
*/
class Thingspeaktalkback// ThigSpeaktalkbackcommands,use in updateThingspeakdata
{                      // to garph  
	public:HTTPClient http;
	public:
		void begin(const char* ssid,const char* pass); // connect wifi
		void begin(const char* ssid, const char* pass,int ip[4],int getwat[4],
		int subnet[4]); //to connect and config you wofo ip address
	
	public:
		Thingspeaktalkback();
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
   
  protected:
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

class Thingspeakgarph2:Thingspeakgarph
{
	public:
		String input;
		String output;
	public:
	   Thingspeakgarph2(const char* Thing_write);
	   Thingspeakgarph2(const char* Thing_write1,const char* Thing_write2);	;
	   void ThingSpeakWrite(float data,int filed,int type_key);
	   void ThingSpeakMutipleWrite(float data[8],int cout_field,
	   int type_key);
};

class Thingspeaktalkback2:Thingspeaktalkback
{
	protected:
		int hr_on;
		int min_on;
		int hr_off;
		int min_off;
		float high_data;
		float low_data;
	private:
		Thingspeaktalkback Talk;
	public:
		String Getcommand_data;
		String Getcommand_Time;
		Thingspeaktalkback2();
		Thingspeaktalkback2(const char* Talk_id,const char* Talk_key);
		Thingspeaktalkback2(const char* Talk_id1,const char* Talk_key1,
		const char* Talk_id2,const char* Talk_key2);
    public:
    	void Config(const char* ssid,const char* pass);
    	void Config(const char* ssid, const char* pass,int ip[4]
		,int gatway[4],int subnet[4]);
	public:
    	void getCommand(const char* cdm_id,int type_key);
    	void setDevice_time(int Hr1,int Min1,int Hr2,int Min2);
    	void setDevice_censor(float data_high,float data_low);
    	void writeCommand(String cdm,int type); //Esp8266WiFi
    	//Overwriting method
		void DeviceaboutCensor(float data,bool logic,const char* command_on,
		const char* command_off,int type); 
		void DeviceaboutTime(int time_hr,int time_min,const char* command_on,
		const char* command_off,int type);
};