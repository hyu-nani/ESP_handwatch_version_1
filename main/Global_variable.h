/*
 * Global_variable.h
 *
 * Created: 2021-03-19 오후 8:20:56
 *  Author: cube_
 */ 

//main
int			mode =	0;
int			backlight =						200;
const int	pg_change_num =			20;

//wifi
int		daylightOffset_sec = 0;//3600 summer time
int		GMT = 9;
bool	connect_wifi	= false;

//SD
bool	connect_SD		= false;

	
//bluetooth
bool	connect_BT		= false;

//clock
int now_hour=0,now_minute=0,now_second=0,now_day=0,now_year=0;
int month,weekday;
int old_hour=0,old_minute=0,old_day=0,old_year=0;
unsigned long prev_ms=0,get_time_ms=0;
unsigned long now_ms=millis();
unsigned long sec_period =			1000;
unsigned long update_cycle_time =	60000;

word convert_CtoB(char A){
	unsigned short B=16;
	if (A == '0')
	B = 0;
	else if(A=='1')
	B = 1;
	else if(A=='2')
	B = 2;
	else if(A=='3')
	B = 3;
	else if(A=='4')
	B = 4;
	else if(A=='5')
	B = 5;
	else if(A=='6')
	B = 6;
	else if(A=='7')
	B = 7;
	else if(A=='8')
	B = 8;
	else if(A=='9')
	B = 9;
	else if(A=='A')
	B = 10;
	else if(A=='B')
	B = 11;
	else if(A=='C')
	B = 12;
	else if(A=='D')
	B = 13;
	else if(A=='E')
	B = 14;
	else if(A=='F')
	B = 15;
	if(B != 16)
	return B;
}