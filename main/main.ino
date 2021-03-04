
/*
 *  NANI project : ESP hand watch 
 *  module : ESP32-S
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

int mode = 0;
int backlight = 200;
const int pg_change_num = 20;
char swcheck();
word data;

#include "image_source/image.h"
#include "watch.h"
#include "ST7735S.h"
#include "SD_card.h"
#include "LCD_basic.h"
#include "WiFi_ready.h"
#include <math.h>
#include "table/table.h"
#include "Clock.h"
#include "main_loop.h"


void setup() {
	Serial.begin(115200);
	SPIClass(VSPI);
	SPI.begin();		//SPI begin
	Wire.begin();	//i2c begin
	watch_pinset();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	LCD_Init();
	LCD_image(0,0,LCD_W,LCD_H,loading[0]);
	LCD_smooth_on(4,backlight);
	delay(10);
	for (int i=0 ; i< 29 ;i++)
	{
		LCD_image(0,0,LCD_W,LCD_H,loading[i]);
	}
	WiFi_begin();
	//SD_init();
	initial_table();
	for (int i=0 ; i< 29 ;i++)
	{
		LCD_image(0,0,LCD_W,LCD_H,loading[i]);
	}
	delay(1);
	LCD_smooth_off(3);
	
	//configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
}


void loop() {
  main_loop();
}

char swcheck()
{
	int i=0;
	if (digitalRead(SW_U))
	{
		i += 1;
	}
	if (digitalRead(SW_M))
	{
		i += 3;
	}
	if (digitalRead(SW_D))
	{
		i += 5;
	}
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
