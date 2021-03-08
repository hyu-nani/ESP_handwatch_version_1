#include <WiFi.h>
#include "time.h"

char* ssid       = "613";
char* password   = "happy613";
int GMT = 9;
char* ntpServer = "pool.ntp.org";
long  gmtOffset_sec = (GMT*3600);
int   daylightOffset_sec = 0;//3600 summer time

void WiFi_begin(){
	//WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println(" CONNECTED");
	connect_wifi = true;
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}


struct tm timeinfo;  

void update_time()
{
	if(!getLocalTime(&timeinfo)){
		Serial.println("Failed to obtain time");
		connect_wifi = false;
		return;
	}
	//Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
}
String Network_SSID[10];
int32_t Network_RSSI[10];
String Network_PSWD[10];

bool connect_wifi = false;

void WiFi_scan(){
	Serial.println("scan start");
	int n = WiFi.scanNetworks();
	Serial.println("scan done");
	if (n == 0) {
		Serial.println("no networks found");
		} else {
		Serial.print(n);
		Serial.println(" networks found");
		for (int i = 0; i < n; ++i) {
			// Print SSID and RSSI for each network found
			Serial.print(i + 1);
			Serial.print(": ");
			Network_SSID[i] = WiFi.SSID(i);
			Serial.print(Network_SSID[i]);
			Serial.print(" (");
			Network_RSSI[i] = WiFi.RSSI(i);
			Serial.print(Network_RSSI[i]);
			Serial.print(")");
			Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
			delay(10);
		}
	}
}

void after_connect(){
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	connect_wifi = true;
}
