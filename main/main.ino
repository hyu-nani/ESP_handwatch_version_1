
/*
 *  NANI project : ESP hand watch 
 *  module : ESP32-S
 *  
 *  Arduino Board Set
 *
 *  ESP32 dev module
 *  921600
 *  240MHz(WiFi/BT)
 *  80MHz
 *  QIO
 *  16MB
 *  HUGE APP
 *  None
 *  disable
 
*/
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <EEPROM.h>
#include <math.h>
#include <WiFi.h>

#include "Global_variable.h"
#include "EEPROM_RW.h"

char swcheck();
char swcheck_no_stop();
word data;

boolean		TEST	=	false;

#include "image_source/image.h"
#include "watch.h"
#include "ST7735S.h"
#include "SD_card.h"
#include "LCD_basic.h"
#include "WiFi_ready.h"
#include "bluetooth.h"

#include "MAX30105.h"
#include "heartRate.h"
MAX30105 particleSensor;

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

#include "APDS9960.h"

#include "ADXL362.h"
ADXL362 xl;

#include "DFRobot_SHT20.h" 
DFRobot_SHT20    sht20;
#include "function.h"
#include "table/table.h"
#include "Clock.h"
#include "main_loop.h"

void setup() {
	Wire.begin();
	Serial.begin(115200);
	EEPROM.begin(20);
	EEPROM_Data_Read();
	SPIClass(VSPI);
	SPI.begin();		//SPI begin
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	watch_pinset();
	LCD_Init();
	LCD_image(0,0,LCD_W,LCD_H,loading[0]);
	LCD_smooth_on(4,200);
	delay(10);
	for (int i=0 ; i< 29 ;i++)
	{
		LCD_image(0,0,LCD_W,LCD_H,loading[i]);
	}
	//WiFi_begin();
	watch_init();
	SD_init();
	initial_table();
	for (int i=0 ; i< 29 ;i++)
	{
		LCD_image(0,0,LCD_W,LCD_H,loading[i]);
	}
	delay(1);
	LCD_smooth_off(3);
	//configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
	delay(1);
	//Clock_set();
	//watchBasicTask();
	//data = swcheck_no_stop();
	//APDSInitWatch();
}


void loop() {
  main_loop();
}

char swcheck()
{
	int i=0;
	if (digitalRead(SW_U))
		i += 1;
	if (digitalRead(SW_M))
		i += 3;
	if (digitalRead(SW_D))
		i += 5;
	while (digitalRead(SW_U)){delay(10);}
	while (digitalRead(SW_M)){delay(10);}
	while (digitalRead(SW_D)){delay(10);}
	switch (i)
	{
	case 1:
		return 'U';	//up
		break;
	case 3:
		return 'M';	//middle
		break;
	case 4:
		return 'S'; //middle & up
		break;
	case 5:
		return 'D';	//down
		break;
	case 6:
		return 'A';	//down & up
		break;
	case 8:
		return 'B'; //middle & down
		break;
	case 9:
		return 'A'; //ALL
		break;	
	default:
		return 'n';
		break;
	}
}
char swcheck_no_stop()
{
	int i=0;
	if (digitalRead(SW_U))
		i += 1;
	if (digitalRead(SW_M))
		i += 3;
	if (digitalRead(SW_D))
		i += 5;
	switch (i)
	{
	case 1:
		return 'U';	//up
		break;
	case 3:
		return 'M';	//middle
		break;
	case 4:
		return 'S'; //middle & up
		break;
	case 5:
		return 'D';	//down
		break;
	case 6:
		return 'A';	//down & up
		break;
	case 8:
		return 'B'; //middle & down
		break;
	case 9:
		return 'A'; //ALL
		break;	
	default:
		return 'n';
		break;
	}
}
