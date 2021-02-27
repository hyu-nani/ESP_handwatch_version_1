#include <WiFi.h>
#include "time.h"
char* ssid       = "iptime1302_2.4";
char* password   = "0553550772";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void WiFi_begin(){
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println(" CONNECTED");
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

  /*
struct tm
{
int    tm_sec;   //   Seconds [0,60]. 
int    tm_min;   //   Minutes [0,59]. 
int    tm_hour;  //   Hour [0,23]. 
int    tm_mday;  //   Day of month [1,31]. 
int    tm_mon;   //   Month of year [0,11]. 
int    tm_year;  //   Years since 1900. 
int    tm_wday;  //   Day of week [0,6] (Sunday =0). 
int    tm_yday;  //   Day of year [0,365]. 
int    tm_isdst; //   Daylight Savings flag. 
}
 */
struct tm timeinfo;  
void update_time()
{
	if(!getLocalTime(&timeinfo)){
		Serial.println("Failed to obtain time");
		return;
	}
	Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
}
