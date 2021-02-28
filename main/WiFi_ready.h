#include <WiFi.h>
#include "time.h"
char* ssid       = "iptime1302_2.4";
char* password   = "0553550772";
int GMT = 9;
char* ntpServer = "pool.ntp.org";
long  gmtOffset_sec = (GMT*3600);
int   daylightOffset_sec = 0;//3600

void WiFi_begin(){
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println(" CONNECTED");
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}


struct tm timeinfo;  
void update_time()
{
	if(!getLocalTime(&timeinfo)){
		Serial.println("Failed to obtain time");
		return;
	}
	//Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
}
