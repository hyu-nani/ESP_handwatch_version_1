
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

#include "image_source/image.h"
#include "watch.h"
#include "ST7735S.h"
#include "SD_card.h"
#include "LCD_basic.h"
#include "WiFi_ready.h"
#include <math.h>

int backlight = 200;
char swcheck();
void modechange(char a);
int mode = 0;

const int pg_change_num = 20;
//mode

#include "setting.h"
#include "Display_table.h"

#include "Clock.h"


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
  SD_init();
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
  //==========================================================
  while(mode == 0){
    Clock_set();
    print_display(display_x,display_y);
    LCD_smooth_on(4,backlight);
    while(1){
      Clock_play();
      print_display(display_x,display_y);
      delay(100);
      data = swcheck();
      if(data == 'D'){
        table_set_bio();
        display_frame();
        mode=1;
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'U'){
        table_set_bio();
        display_frame();
        mode = 1;
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
    }
  }
  
  //==========================================================
  while(mode == 1){   //bio
    
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_temp();
        display_frame();
        mode=2;
        delay(300);
        for(int i = -2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'U'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_acc();
        display_frame();
        mode=4;
        delay(300);
        for(int i =-2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'M'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        mode=0;
        break;
      }
    }
  }
  
  //==========================================================
  while(mode == 2){   //temp
    
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_setting();
        display_frame();
        mode=3;
        delay(300);
        for(int i = -2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'U'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_bio();
        display_frame();
        mode=1;
        delay(300);
        for(int i =-2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'M'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        mode=0;
        break;
      }
    }
  }
  
  //==========================================================
  while(mode == 3){   //setting
    
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_acc();
        display_frame();
        mode=4;
        delay(300);
        for(int i = -2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'U'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_temp();
        display_frame();
        mode=2;
        delay(300);
        for(int i =-2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'M'){
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        mode=5;
        break;
      }
    }
  }
  //==========================================================
  while(mode == 4){   //acc
    
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_bio();
        display_frame();
        mode=1;
        delay(300);
        for(int i = -2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'U'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        table_set_setting();
        display_frame();
        mode=3;
        delay(300);
        for(int i =-2 ;i<=pg_change_num ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'M'){
        Clock_set();
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        mode=0;
        break;
      }
    }
  }
  //================================================================
  //option
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
	if (i!=0)
	{
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
		}
	}
	return 0;
}

void modechange(char a)
{
	if (a =='U')
	{
		mode++;
	}
	else if (a == 'M')
	{
		mode=0;
	}
	else if (a == 'D')
	{
		mode--;
	}
}
