
#include "time.h"

char* ssid       = "921";
char* password   = "12345678";
char* ntpServer  = "pool.ntp.org";
long  gmtOffset_sec = (GMT*3600);

void WiFi_begin(){
	//WiFi.begin(ssid, password);
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
		return;
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


void WiFi_scan(){
	if (TEST == true)
		Serial.println("scan start");
	int n = WiFi.scanNetworks();
	if (TEST == true)
		Serial.println("scan done");
	if (n == 0) {
		if (TEST == true)
			Serial.println("no networks found");
	} 
	else {
		if (TEST == true){
			Serial.print(n);
			Serial.println(" networks found");
		}
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
