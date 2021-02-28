
static int now_hour=0,now_minute=0,now_second=0,now_day=0,now_year=0;
static int month,weekday;
static int old_hour=0,old_minute=0,old_day=0,old_year=0;
unsigned long prev_ms=0;
uint16_t CLOCK_BG_color = BLACK;
unsigned long now_ms=millis();
  /*
struct tm
{
int    tm_sec;   //   Seconds [0,60]. 
int    tm_min;   //   Minutes [0,59]. 
int    tm_hour;  //   Hour [0,23]. 
int    tm_mday;  //   Day of month [1,31]. 
int    tm_mon;   //   Month of year [0,11]. 
int    tm_year;  //   Years since 1900. 
int    tm_wday;  //   Day of week [0,6] (Sunday =0). 
int    tm_yday;  //   Day of year [0,365]. 
int    tm_isdst; //   Daylight Savings flag. 
}
 */
void Clock_update()
{
  update_time();
  now_second = timeinfo.tm_sec;
  now_minute = timeinfo.tm_min;
  now_hour = timeinfo.tm_hour;
  now_day = timeinfo.tm_mday;
  month = timeinfo.tm_mon + 1;
  now_year = timeinfo.tm_year + 1900;
  weekday = timeinfo.tm_wday +1;
  
}

int H_x = 10,H_y = 10;
int M_x = 60,M_y = 10;
int S_x = 130,S_y = 50;
int D_x = 120,D_y = 20;
void Clock_play()
{
	now_ms = millis();
	if((now_ms - prev_ms)%1000<100){
		table_fill_block(1,BLACK);
		now_second++;
    if(now_second == 60){
      now_second =0;
      now_minute++;
    }
		table_print(10,10,now_hour,RED,2);
		table_print(40,10,"Hour",BLUE,2);
		table_print(10,30,now_minute,RED,2);
		table_print(40,30,"Minute",BLUE,2);
		table_print(10,50,now_second,RED,2);
		table_print(40,50,"Seccond",BLUE,2);
		table_print(100,10,now_year,RED,1);
		table_print(130,10,"Year",BLUE,1);
	}
	if(now_ms - prev_ms>60000){
		Clock_update();
		prev_ms = now_ms;
	}
}
