
static int now_hour=0,now_minute=0,now_second=0,now_day=0,now_year=0;
static int month,weekday;
static int old_hour=0,old_minute=0,old_day=0,old_year=0;
unsigned long prev_ms=0,get_time_ms=0;
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
	if (connect_wifi == true)
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
}
void Clock_set();
int H_x = 10,H_y = 10;
int M_x = 60,M_y = 10;
int S_x = 130,S_y = 50;
int D_x = 120,D_y = 20;

void Clock_play()
{
	now_ms = millis();
	if(now_ms - prev_ms > sec_period*4){
		table_fill_block(1,BLACK);
		now_second++;
		prev_ms = now_ms;
		if(now_second == 60){
			now_second =0;
			now_minute++;
		}
		Clock_set();
	}
	if(now_ms - get_time_ms > update_cycle_time){
		Clock_update();
		get_time_ms = now_ms;
		Serial.println(update_cycle_time);
	}
}
void Clock_set()
{
  Clock_update();
  table_fill_block(1,BLACK);
  table_print_SevenSegNumFont32X50(5,10,now_hour,BLUE);
	table_print_SevenSegNumFont32X50(90,10,now_minute,GREEN);
	table_print(70,60,now_second,RED,2);
}
