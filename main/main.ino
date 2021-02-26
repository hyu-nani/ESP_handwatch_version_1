/*
 *  NANI project : ESP hand watch 
 *  Upload Speeed : 51200 
 *  CPU frequency : 160MHz
 *  Flash size : 4MB (FS:3MB)
*/

#include "image_source/image.h"
#include "ST7735S.h"
#include "LCD_basic.h"
#include "LCD_action.h"
#include "WiFi.h"
#include <math.h>

#define sw1 D0
#define sw2 D3
#define sw3 D4

int backlight = 1000;
char swcheck();
void modechange(char a);
int mode = 0;
int display_x=0,display_y=0;

const int pg_change_num = 20;

//mode
#include "Clock.h"
#include "setting.h"
#include "Display.h"

void setup() {
	Serial.begin(115200);
	SPI.begin();
	LCD_portset();
	mySPISettings = SPISettings(20000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	pinMode(sw1,INPUT_PULLUP);
	pinMode(sw2,INPUT);
	pinMode(sw3,INPUT);
	LCD_Init();
  //LCD_image(0,0,LCD_W,LCD_H,loading[0]);
	LCD_smooth_on(3,backlight);
  delay(10);
  for (int i=0 ; i< 29 ;i++)
  {
    //LCD_image(0,0,LCD_W,LCD_H,loading[i]);
  }
  //wifi_init();
  delay(1);
  initial_display();
  for (int i=0 ; i< 29 ;i++)
  {
   // LCD_image(0,0,LCD_W,LCD_H,loading[i]);
  }
  delay(1);
	LCD_smooth_off(2);
	now = time(nullptr);
	//configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
}



void loop() {
  //==========================================================
  while(mode == 0){
    print_display(display_x,display_y);
    LCD_smooth_on(3,backlight);
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        display_set_bio();
        display_frame();
        mode=1;
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y+=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        break;
      }
      else if (data == 'U'){
        display_set_setting();
        display_frame();
        mode = 2;
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
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        display_set_setting();
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
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        display_set_temp();
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
  while(mode == 2){   //setting
    
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        display_set_temp();
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
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        display_set_bio();
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
  while(mode == 3){   //temp
    
    while(1){
      print_display(display_x,display_y);
      delay(10);
      data = swcheck();
      if(data == 'D'){
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        display_set_bio();
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
        for(int i = -pg_change_num ;i<=2 ;i++){
          display_y-=(9*i*i)/400+1;
          print_display(display_x,display_y);
        }
        display_set_setting();
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
        mode=0;
        break;
      }
    }
  }
}
char swcheck()
{
	int i=0;
	if (digitalRead(sw1)==0)
	{
		i += 1;
	}
	if (digitalRead(sw2)==0)
	{
		i += 3;
	}
	if (digitalRead(sw3)==0)
	{
		i += 5;
	}
	while (digitalRead(sw1)==0){delay(100);}
	while (digitalRead(sw2)==0){delay(100);}
	while (digitalRead(sw3)==0){delay(100);}
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
