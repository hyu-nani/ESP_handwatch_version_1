
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

//mode
#include "Clock.h"
#include "setting.h"

void setup() {
	Serial.begin(115200);
	SPI.begin();
	LCD_portset();
	mySPISettings = SPISettings(20000000, MSBFIRST, SPI_MODE0); //ESP max speed 80MHz
	wifi_init();
	pinMode(sw1,INPUT_PULLUP);
	pinMode(sw2,INPUT);
	pinMode(sw3,INPUT);
	LCD_Init();
	LCD_image(0,0,LCD_W,LCD_H,rogo);
	LCD_smooth_on(3,backlight);
	delay(500);
	LCD_smooth_off(2);
	LCD_Fill(BLACK);
	now = time(nullptr);
	configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
}

void loop() {
	startpoint:
	while (mode == -1)
	{
		mode = 0;
		LCD_smooth_off(2);
		break;
	}
	while (mode == 0)
	{	
    LCD_smooth_on(2,backlight);
	  while(1){
      int i=mode;
      char d = 'n';
      for (int i=0 ; i< 29 ;i++)
      {
        LCD_image(0,0,LCD_W,LCD_H,loading[i]);
        delay(1);
        char k =swcheck();
        if( 0 != k){d = k;}
      }
			modechange(d);
			if(i!=mode){LCD_smooth_off(2);break;}
			delay(10);
		}
	}
	while (mode == 1)
	{
		CLOCK();
	}
	while (mode == 2)
	{	
		LCD_image(0,0,LCD_W,LCD_H,rogo);
		delay(10);
		LCD_smooth_on(2,backlight);
		while(1){
			sw_data=swcheck();
			int i = mode;
			if(sw_data=='M'){SETTING();}
			modechange(sw_data);
			if(i!=mode){LCD_smooth_off(2);break;}
			delay(10);
		}
	}
	while (mode == 3)
	{	
		mode = 0;
		LCD_smooth_off(2);
		break;
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