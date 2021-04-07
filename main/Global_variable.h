/*
 * Global_variable.h
 *
 * Created: 2021-03-19 오후 8:20:56
 *  Author: cube_
 */ 
//main
int			mode =	0;
int			backlight =				201;
const int	pg_change_num	=		20;
float		batteryVolt		=		370;
int			batteryPercent	=		50;
bool		charge_state	=		false;
	
//wifi
int			daylightOffset_sec	=	0;//3600 summer time
int			GMT					=	9;
bool		connect_wifi		=	false;

//SD
bool			connect_SD		=		false;
#define			Image_width		160
#define			Image_hight		80
unsigned short	load_image[Image_hight*Image_width] = {0};
char*			listDirName[20];

//ADXL

//MAX30102
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

//int16_t temp;
int16_t XValue, YValue, ZValue, Temperature;

//bluetooth
bool			connect_BT		=		false;

//SHT20
float temp;
float humd;

//clock
int now_hour=0,now_minute=0,now_second=0,now_day=0,now_year=0;
int month,weekday;
int old_hour=0,old_minute=0,old_day=0,old_year=0;
unsigned long prev_ms=0,get_time_ms=0;
unsigned long now_ms=millis();
unsigned long sec_period		=	1000;
unsigned long update_cycle_time =	60000;

word convert_CtoB(char A){
	unsigned short B=16;
	switch(A)
	{
		case  '0' :
			B = 0;
			break;
		case  '1' :
			B = 1;
			break;
		case  '2' :
			B = 2;
			break;
		case  '3' :
			B = 3;
			break;
		case  '4' :
			B = 4;
			break;
		case  '5' :
			B = 5;
			break;
		case  '6' :
			B = 6;
			break;
		case  '7' :
			B = 7;
			break;
		case  '8' :
			B = 8;
			break;
		case  '9' :
			B = 9;
			break;
		case  'A' :
			B =10;
			break;
		case  'B' :
			B =11;
			break;
		case  'C' :
			B =12;
			break;
		case  'D' :
			B =13;
			break;
		case  'E' :
			B =14;
			break;
		case  'F' :
			B =15;
			break;
		default:
			break;
	}
	if(B != 16)
	return B;
}