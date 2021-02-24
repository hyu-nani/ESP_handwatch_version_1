
static int now_h=0,now_m=0,now_s=0,now_d=0;
static int old_h=0,old_m=0,old_d=0;

uint16_t CLK_BG_color = BLACK;

void CLOCK()
{
	LCD_Fill(CLK_BG_color);
	LCD_HLine(10,52,60,CYAN);
	int timer = time(nullptr);
	now_h = int((timer%86400)/3600)-3;
	now_m = int((timer%3600)/60);
	now_s = int(timer%60);
	now_d = int((timer/86400)%7);
	prev_ms = now_ms;
	LCD_print(12,10,now_h,YELLOW,5);
	old_h = now_h;
	LCD_print(12,60,now_m,YELLOW,5);
	old_m = now_m;
	int x=30,y=140; //
	if(now_d == 2)
	LCD_print_background(x,y,"SAT",CYAN,CLK_BG_color,2);
	else if(now_d == 3)
	LCD_print_background(x,y,"SUN",BLUE,CLK_BG_color,2);
	else if(now_d == 4)
	LCD_print_background(x,y,"MON",RED,CLK_BG_color,2);
	else if(now_d == 5)
	LCD_print_background(x,y,"TUE",RED,CLK_BG_color,2);
	else if(now_d == 6)
	LCD_print_background(x,y,"WED",YELLOW,CLK_BG_color,2);
	else if(now_d == 7)
	LCD_print_background(x,y,"THU",YELLOW,CLK_BG_color,2);
	else if(now_d == 1)
	LCD_print_background(x,y,"FRI",RED,CLK_BG_color,2);
	delay(10);
	LCD_smooth_on(2,backlight);
	while (1)
	{
		now_ms = millis();
		if(now_ms-prev_ms>950){
			delay(10);
			int timer = time(nullptr);
			now_h = int((timer%86400)/3600)-3;
			now_m = int((timer%3600)/60);
			now_s = int(timer%60);
			now_d = int((timer/86400)%7);
			prev_ms = now_ms;
			
			if(now_h != old_h){
				LCD_fill_Rect(12,10,60,35,CLK_BG_color);
				LCD_print(12,10,now_h,YELLOW,5);
				old_h = now_h;
			}
			if (now_m != old_m){
				LCD_fill_Rect(12,60,60,35,CLK_BG_color);
				LCD_print(12,60,now_m,YELLOW,5);
				old_m = now_m;
			}
			LCD_fill_Rect(40,110,30,20,CLK_BG_color);
			LCD_print(40,110,now_s,GREEN,2);
			if (now_d != old_d){
				if(now_d == 2)
				LCD_print_background(x,y,"SAT",CYAN,CLK_BG_color,2);
				else if(now_d == 3)
				LCD_print_background(x,y,"SUN",BLUE,CLK_BG_color,2);
				else if(now_d == 4)
				LCD_print_background(x,y,"MON",RED,CLK_BG_color,2);
				else if(now_d == 5)
				LCD_print_background(x,y,"TUE",RED,CLK_BG_color,2);
				else if(now_d == 6)
				LCD_print_background(x,y,"WED",YELLOW,CLK_BG_color,2);
				else if(now_d == 7)
				LCD_print_background(x,y,"THU",YELLOW,CLK_BG_color,2);
				else if(now_d == 1)
				LCD_print_background(x,y,"FRI",RED,CLK_BG_color,2);
				old_d = now_d;
			}
		}
		int i = mode;
		modechange(swcheck());
		if(i!=mode){LCD_smooth_off(2);break;}
	}
}