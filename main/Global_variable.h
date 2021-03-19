/*
 * Global_variable.h
 *
 * Created: 2021-03-19 오후 8:20:56
 *  Author: cube_
 */ 

//main
int mode =	0;
int backlight =						200;
const int pg_change_num =			20;

//wifi
int   daylightOffset_sec = 0;//3600 summer time
int   GMT = 9;
bool  connect_wifi = false;


//clock

unsigned long sec_period =			1000;
unsigned long update_cycle_time =	60000;