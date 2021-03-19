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
int now_hour=0,now_minute=0,now_second=0,now_day=0,now_year=0;
int month,weekday;
int old_hour=0,old_minute=0,old_day=0,old_year=0;
unsigned long prev_ms=0,get_time_ms=0;
unsigned long now_ms=millis();
unsigned long sec_period =			1000;
unsigned long update_cycle_time =	60000;