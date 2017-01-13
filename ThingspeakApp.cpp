#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingspeakApp.h"
#define  host "api.thingspeak.com"
#define libversion "0.1.1Gamma"
const char* talk_id1;
const char* talk_key1;
const char* talk_id2;
const char* talk_key2;

//ues witch Thingsepakgrap2
const char* thing_write;
const char* thing_write2;
/*
   Thingspeak Talkback library Creat by ESP8266HTTPClient.h 

   Update!!! 13/01/2017

   Crate by Mr Patipan Polvirat
   
   at: AT&T_LAB2017
   coppy right AT&T_LAB
       (2016-2017)
*/
Thingspeaktalkback::Thingspeaktalkback()
{
	
}
Thingspeaktalkback::Thingspeaktalkback(const char* Talkback_id,
const char* Talkback_key,
const char* Thing_write)
{
	//not use thingspeak readkey because
    //you must make you channel to public
    talk_id1=Talkback_id;
    talk_key1=Talkback_key;
    thing_write=Thing_write;
}
Thingspeaktalkback::Thingspeaktalkback(const char* Talkback_id,
const char* Talkback_key)
{
	//for when you want to use only thingspeakcommands
	talk_id1=Talkback_id;
	talk_key1=Talkback_key;
}

Thingspeaktalkback::Thingspeaktalkback(const char* Talkback_id1,
const char* Talkback_key1,
const char* Talkback_id2,const char* Talkback_key2)
{
	//use when you want to connect whit two Talkbackcommands 
   //(whith out thingspeak)
   talk_id1=Talkback_id1;
   talk_key1=Talkback_key1;
   
   talk_id2=Talkback_id2;
   talk_key2=Talkback_key2;
   
}

Thingspeaktalkback::Thingspeaktalkback(const char* Talkback_id1,
const char* Talkback_key1,
const char* Talkback_id2,const char* Talkback_key2,const char* Thing_write)
{
	//use when you want to connect whit two Talkbackcommands 
   //(whith  thingspeak)
   talk_id1=Talkback_id1;
   talk_key1=Talkback_key1;
   
   talk_id2=Talkback_id2;
   talk_key2=Talkback_key2;
   
   thing_write=Thing_write;
}

void Thingspeaktalkback::begin(const char* ssid,const char* pass)
{
	//to connect wifi
	WiFi.begin(ssid,pass);
	Serial.print("\n\nConnecting to network.");
	while(WiFi.status()!=WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.print("\nConnect at: ");
	Serial.println(WiFi.localIP());
	Serial.print("\nlibrary version: ");
	Serial.println(libversion);
}
void Thingspeaktalkback::begin(const char* ssid,const char* pass,
int ip[4],int getway[4],int subnet[4])
{
	//to connect and config you wofo ip address
	WiFi.begin(ssid,pass);
	Serial.print("\n\nConnecting to network.");
	while(WiFi.status()!=WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.print("\nConnect at: ");
	IPAddress Ip={ip[0],ip[1],ip[2],ip[3]};
	IPAddress Getway={getway[0],getway[1],getway[2],getway[3]};
	IPAddress Subnet={subnet[0],subnet[1],subnet[2],subnet[3]};
	WiFi.config(Ip,Getway,Subnet);
	Serial.println(WiFi.localIP());
	Serial.print("\nlibrary version: ");
	Serial.println(libversion);
}
void Thingspeaktalkback::SetDevicetime(int hr_on,int min_on,
int hr_off,int min_off)
{
	HR_ON=hr_on;
	MIN_ON=min_on;
	HR_OFF=hr_off;
	MIN_OFF=min_off;
}
void Thingspeaktalkback::SetDeviceCensor(float hight,float low)
{
	HIGH_DATA=hight;
	LOW_DATA=low;
}
void Thingspeaktalkback::DeviceaboutTime(int time_hr,int time_min,
const char * command_on,const char* command_off)
{
	String url = "http://";
	url+=host;
	url+="/talkbacks/";
	url+=talk_id1;
	if(time_hr>=HR_OFF||time_hr<=HR_ON)
	{
		if((time_min>=MIN_OFF)&&(time_hr==HR_OFF))
		{
			url+="/commands/";
			url+=command_off;
			url+="?api_key=";
		}
		else
		{
			url+="/commands/";
			url+=command_off;
			url+="?api_key=";
		}
	}
	else if(time_hr>=HR_ON)
	{
		if((time_min>=MIN_ON)&&(time_hr==HR_ON))
		{
			url+="/commands/";
			url+=command_on;
			url+="?api_key=";
		}
		else
		{
			url+="/commands/";
			url+=command_on;
			url+="?api_key=";
		}
	}
	url+=talk_key1;
	http.begin(url);
	State=http.GET();
	if(State>0)
	{
		if(State==HTTP_CODE_OK)
		{
			Getcommand_time=http.getString();
			//Serial.println("OK: "+url);
		}
	}
	else
	{
		Getcommand_time="Error";
		Serial.println("Erroro: "+url);
	}
	http.end();
}
void Thingspeaktalkback::DeviceaboutCensor(float data_censor,bool logic,
const char* cdm_on,const char* cdm_off)
{
	if(logic==true)
	{
		String url="http://";
		url+=host;
		url+="/talkbacks/";
		url+=talk_id1;
		if(data_censor>=HIGH_DATA||data_censor>=LOW_DATA)
		{
			url+="/commands/";
			url+=cdm_on;
			url+="?api_key=";
		}
		else if(data_censor<=LOW_DATA)
		{
			url+="/commands/";
			url+=cdm_off;
			url+="?api_key=";
		}
		url+=talk_key1;
		http.begin(url);
		
		State=http.GET();
		if(State>0)
		{
			if(State==HTTP_CODE_OK)
			{
				Getcommands_data=http.getString();
				//Serial.println("URL OK: "+url);
				//Serial.println(Getcommands_data);
			}
		}
		else
		{
			Serial.println("Error: "+url);
		}
		http.end();
	}
	else
	{
		String url="http://";
		url+=host;
		url+="/talkbacks/";
		url+=talk_id1;
		if(data_censor>=HIGH_DATA||data_censor>=LOW_DATA)
		{
			url+="/commands/";
			url+=cdm_off;
			url+="?api_key=";
		}
		else if(data_censor<=LOW_DATA)
		{
			url+="/commands/";
			url+=cdm_on;
			url+="?api_key=";
		}
		url+=talk_key1;
		http.begin(url);
		
		State=http.GET();
		if(State>0)
		{
			if(State==HTTP_CODE_OK)
			{
				Getcommands_data=http.getString();
				//Serial.println("URL OK: "+url);
			}
		}
		else
		{
			Serial.println("Error: "+url);
		}
		http.end();
	}
}
float Thingspeaktalkback::Convert_toFloat(String data)
{
	return data.toFloat();
}
int Thingspeaktalkback::Convert_toInt(String data)
{
	return data.toInt();
}
void Thingspeaktalkback::Thingspeak_pub(float data,int field)
{
	Thingspeakgarph garp;
	garp.ThingSpeakWrite(data,field);
}
void Thingspeaktalkback::Thingspeak_mutiplepub(float data[8],int count_field)
{
	Thingspeakgarph garp;
	garp.ThingSpeakMutipleWrite(data,count_field);
}
String Thingspeaktalkback::Thingspeak_read(int ch_num,int field)
{
	Thingspeakgarph garp;
	return garp.ThingSpeakRead(ch_num,field);
}
/*
   Thingspeak Talkback library Creat by ESP8266HTTPClient.h 

   Update!!! 13/01/2017

   Crate by Mr Patipan Polvirat
   
   at: AT&T_LAB2017
   coppy right AT&T_LAB
       (2016-2017)
*/
Thingspeakgarph::Thingspeakgarph( )
{
	
}

void Thingspeakgarph::ThingSpeakWrite(float data,int field)
{
	String url="http://";
	url+=host;
	url+="/update?api_key=";
	url+=thing_write;
	url+="&field";
	url+=field;
	url+="=";
	url+=data;
	
	http.begin(url);
	int state=http.GET();
	if(state>0)
	{
		if(state==HTTP_CODE_OK)
		{
			String count=http.getString();
			Serial.println("State: "+String(state));
			Serial.println("Count of data: "+count);
		}
	}
	else
	{
		Serial.println("Error 404");
	}
}
void Thingspeakgarph::ThingSpeakMutipleWrite(float data[8],int count_field)
{
	int i=0;
	String url="http://";
	url+=host;
	url+="/update";
	url+="?api_key=";
	url+=thing_write;
	for(i=1;i<=count_field;i++)
	{
		url+="&field";
		url+=i;
		url+="=";
		url+=data[i-1];
	}
	
	http.begin(url);
	int state=http.GET();
	if(state>0)
	{
		if(state==HTTP_CODE_OK)
		{
			String count=http.getString();
		    Serial.println("State: "+String(state));
		    Serial.println("Count of data: "+count);
		    Serial.println(url);
		}
		
	}
	else
	{
		Serial.println("Error");
	}
}
String Thingspeakgarph::ThingSpeakRead(int ch_num,int field)
{
	String url="http://";
	url+=host;
	url+="/channels/";
	url+=ch_num;
	url+="/field/";
	url+=field;
	url+="/last.txt";
	
	http.begin(url);
	int state=http.GET();
	if(state>0)
	{
		if(state==HTTP_CODE_OK)
		{
			String response=http.getString();
			Serial.println("State: "+String(state));
			Serial.println("Data:  "+response);
			return response;
		}
	}
	else
	{
		Serial.println("Error");
		return "Error 404 read";
	}
}

Thingspeakgarph2::Thingspeakgarph2(const char* Thing_write)
{
	thing_write=Thing_write;
}
Thingspeakgarph2::Thingspeakgarph2(const char* Thing_write1,
const char* Thing_write2)
{
	thing_write=Thing_write1;
	thing_write2=Thing_write2;	
}
void Thingspeakgarph2::ThingSpeakWrite(float data,int field,int type_key)
{
	if(type_key==1)
	{
		Thingspeakgarph g;
        g.ThingSpeakWrite(data,field);
	}
	else
	{
        String url="http://";
	    url+=host;
	    url+="/update?api_key=";
	    url+=thing_write2;
	    url+="&field";
	    url+=field;
	    url+="=";
	    url+=data;
	
	    http.begin(url);
	    int state=http.GET();
	    if(state>0)
        {
		  if(state==HTTP_CODE_OK)
		  {
			  String count=http.getString();
			  Serial.println("State: "+String(state));
			  Serial.println("Count of data: "+count);
          }
	    }
	   else
	   {
		  Serial.println("Error 404");
       }
	}
}

/*
   Thingspeak Talkback library Creat by ESP8266HTTPClient.h 

   Update!!! 13/01/2017

   Crate by Mr Patipan Polvirat
   
   at: AT&T_LAB2017
   coppy right AT&T_LAB
       (2016-2017)
*/
Thingspeaktalkback2::Thingspeaktalkback2()
{
	
}
Thingspeaktalkback2::Thingspeaktalkback2(const char* Talk_id,
const char* Talk_key):Thingspeaktalkback(Talk_id,Talk_key){
}

Thingspeaktalkback2::Thingspeaktalkback2(const char* Talk_id1,
const char* Talk_key1,const char* Talk_id2,const char* Talk_key2):
Thingspeaktalkback(Talk_id1,Talk_key1,Talk_id2,Talk_key2){
}


void Thingspeaktalkback2::Config(const char* ssid,const char* pass)
{
	Thingspeaktalkback::begin(ssid,pass);
}
void Thingspeaktalkback2::Config(const char* ssid, const char* pass,int ip[4]
,int gatway[4],int subnet[4])
{
	Thingspeaktalkback::begin(ssid,pass,ip,gatway,subnet);
}

void Thingspeaktalkback2::DeviceaboutCensor(float data,bool logic
,const char* command_on,
const char* command_off,int type)
{
	if(type==1)
	{
		Talk.DeviceaboutCensor(data,logic,command_on,command_off);
		Getcommand_data=Talk.Getcommands_data;
	}	
	else
	{
		if(logic==true)
		{
			String url="http://";
			url+=host;
			url+="/talkbacks/";
			url+=talk_id2;
			if(data>=HIGH_DATA||data>=LOW_DATA)
			{
				url+="/commands/";
				url+=command_on;
				url+="?api_key=";
			}
			else if(data<=LOW_DATA)
			{
				url+="/commands/";
				url+=command_on;
				url+="?api_key=";
			}
			url+=talk_key2;
			http.begin(url);
			State=http.GET();
			if(State>0)
			{
				if(State==HTTP_CODE_OK)
				{
					Getcommand_data=http.getString();
				}
			}
			else
			{
				Getcommand_data="Error";
			}
		}
		else
		{
			String url="http://";
			url+=host;
			url+="/talkbacks/";
			url+=talk_id2;
			if(data>=HIGH_DATA||data>=LOW_DATA)
			{
				url+="/commands/";
				url+=command_off;
				url+="?api_key=";
			}
			else if(data<=LOW_DATA)
			{
				url+="/commands/";
				url+=command_on;
				url+="?api_key=";
			}
			url+=talk_key2;
			http.begin(url);
			State=http.GET();
			if(State>0)
			{
				if(State==HTTP_CODE_OK)
				{
					Getcommand_data=http.getString();
				}
			}
			else
			{
				Getcommand_data=http.getString();
			}
		}
		http.end();
	}
}
void Thingspeaktalkback2::DeviceaboutTime(int time_hr,int time_min,
const char* command_on,const char* command_off,int type)
{
	if(type==1)
	{
		Talk.DeviceaboutTime(time_hr,time_min,command_on,command_off);
		Getcommand_Time=Talk.Getcommand_time;
	}
	else
	{
		String url="http://";
		url+=host;
		url+="/talkbacks/";
		url+=talk_id2;
		if(time_hr>=HR_OFF||time_hr<=HR_ON)
		{
			if((time_min>=MIN_OFF)&&(time_hr==HR_OFF))
			{
				url+="/commands/";
				url+=command_off;
				url+="?api_key=";
			}
			else 
			{
				url+="/commands/";
				url+=command_off;
				url+="?api_key=";
			}
		}
		else if(time_hr>=HR_ON)
		{
			if((time_min>=MIN_ON)&&(time_hr==HR_ON))
			{
				url+="/commands/";
				url+=command_on;
				url+="?api_key=";
			}
			else 
			{
				url+="/commands/";
				url+=command_on;
				url+="?api_key=";
			}
		}
		url+=talk_key2;
		http.begin(url);
		State=http.GET();
		if(State>0)
		{
			if(State==HTTP_CODE_OK)
			{
				Getcommand_Time=http.getString();
			}
		}
		else
		{
			Getcommand_Time="Error";
		}
	}
}

void Thingspeaktalkback2::getCommand(const char* cdm_id,int type_key)
{
	String key,id;
	if(type_key==1)
	{
	    id=talk_id1;
		key=talk_key1;
	}
	else
	{
		if((talk_id2!="")&&(talk_key2!=""))
		{
			id=talk_id2;
			key=talk_key2;
		}
		else
		{
			id=talk_id1;
		    key=talk_key1;
		}
	}
	
	String url="http://";
	url+=host;
	url+="/talkbacks/";
	url+=id;
	url+="/commands/";
	url+=cdm_id;
	url+="?api_key=";
	url+=key;
	
	State=http.begin(url);
	if(State>0)
	{
       if(State==HTTP_CODE_OK)
	   {
		 //Serial.println("State ok");
		 Getcommand_data=http.getString();
       }
	   	
	}
	else
    {
	  Getcommand_data="Error";
    }  
}
void Thingspeaktalkback2::setDevice_time(int Hr1,int Min1,int Hr2,int Min2)
{
	Talk.SetDevicetime(Hr1,Min1,Hr2,Min2);
}
void Thingspeaktalkback2::setDevice_censor(float data_high,float data_low)
{
	Talk.SetDeviceCensor(data_high,data_low);
}

void Thingspeaktalkback2::writeCommand(String cdm,int type)
{
	Serial.println("Write command to thingspeak command");
	WiFiClient client;
	const int port=80;
	if(!client.connect(host,port))
	{
		Serial.print("Can't connect");
		delay(500);
		return;
	}
	
	if(type==1)
	{
		String line;
		String url="/talkbacks/";
		url+=talk_id1;
		url+="/commands?api_key=";
		url+=talk_key1;
		url+="&command_string=";
		url+=cdm;
		
		Serial.print("Send Request Url:");
		Serial.println(url);
		client.print("POST "+url+" HTTP/1.1\r\n");
		client.print("Host: api.thingspeak.com\r\n");
		client.print("Connection: close\r\n\r\n");
		unsigned long timeout=millis();
		while(client.available()==0)
		{
			if(millis()-timeout>5000)
			{
				Serial.println(">> Client time out");
				client.stop();
				delay(500);
				return;
			}
		}
		
		while(client.available())
		{
			line=client.readStringUntil('\r');
			Serial.println(line);
		}
		Serial.println("\n");
		Serial.println("Close connection");
	}
	else
	{
		String line;
		String url="/talkbacks/";
		url+=talk_id2;
		url+="/commands?api_key=";
		url+=talk_key2;
		url+="&command_string=";
		url+=cdm;
		
		Serial.print("Send Request Url:");
		Serial.println(url);
		client.print("POST "+url+" HTTP/1.1\r\n");
		client.print("Host: api.thingspeak.com\r\n");
		unsigned long timeout=millis();
		while(client.available()==0)
		{
			if(millis()-timeout>5000)
			{
				Serial.println(">> Client time out");
				client.stop();
				delay(500);
				return;
			}
		}
		
		while(client.available())
		{
			line=client.readStringUntil('\r');
			Serial.println(line);
		}
		Serial.println("\n");
		Serial.println("Close connection");
	}
}