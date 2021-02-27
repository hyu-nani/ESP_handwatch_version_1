
static int now_hour=0,now_minute=0,now_second=0,now_day=0,now_year=0;
static int month,weekday;
static int old_hour=0,old_minute=0,old_day=0,old_year=0;
int now_ms,prev_ms,timer;
uint16_t CLOCK_BG_color = BLACK;
void Clock_init()
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
void Clock_play()
{
  int H_x = 10,H_y = 10;
  int M_x = 60,M_y = 10;
  int S_x = 130,S_y = 50;
  int D_x = 120,D_y = 20;
  table_fill_block(1,BLACK);
  Clock_init();
  table_print(10,10,now_hour,RED,1);
  table_print(10,30,now_minute,RED,1);
  table_print(10,50,now_second,RED,1);
  table_print(100,10,now_year,RED,1);
  delay(100);
  
}
