
static int now_h=0,now_m=0,now_s=0,now_d=0;
static int old_h=0,old_m=0,old_d=0;

uint16_t CLK_BG_color = BLACK;

void CLOCK()
{
  int H_x = 10,H_y = 10;
  int M_x = 80,M_y = 10;
  int S_x = 130,S_y = 50;
  int D_x = 130,D_y = 20;
  
	LCD_Fill(CLK_BG_color);
	LCD_VLine(30,10,60,CYAN);
	int timer = time(nullptr);
	now_h = int((timer%86400)/3600)-3;
	now_m = int((timer%3600)/60);
	now_s = int(timer%60);
	now_d = int((timer/86400)%7);
	prev_ms = now_ms;
 
	LCD_print(H_x,H_y,now_h,YELLOW,4);
	old_h = now_h;
	LCD_print(M_x,M_y,now_m,YELLOW,4);
	old_m = now_m;
  
	if(now_d == 2)
	LCD_print_background(D_x,D_y,"SAT",CYAN,CLK_BG_color,2);
	else if(now_d == 3)
	LCD_print_background(D_x,D_y,"SUN",BLUE,CLK_BG_color,2);
	else if(now_d == 4)
	LCD_print_background(D_x,D_y,"MON",RED,CLK_BG_color,2);
	else if(now_d == 5)
	LCD_print_background(D_x,D_y,"TUE",RED,CLK_BG_color,2);
	else if(now_d == 6)
	LCD_print_background(D_x,D_y,"WED",YELLOW,CLK_BG_color,2);
	else if(now_d == 7)
	LCD_print_background(D_x,D_y,"THU",YELLOW,CLK_BG_color,2);
	else if(now_d == 1)
	LCD_print_background(D_x,D_y,"FRI",RED,CLK_BG_color,2);
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
				//LCD_fill_Rect(H_x,H_y,60,35,CLK_BG_color);
				LCD_print(H_x,H_y,now_h,YELLOW,4);
				old_h = now_h;
			}
			if (now_m != old_m){
				//LCD_fill_Rect(M_x,M_y,60,35,CLK_BG_color);
				LCD_print(M_x,M_y,now_m,YELLOW,4);
				old_m = now_m;
			}
			//LCD_fill_Rect(S_x,S_y,30,20,CLK_BG_color);
			LCD_print(S_x,S_y,now_s,GREEN,2);
			if (now_d != old_d){
				if(now_d == 2)
				LCD_print_background(D_x,D_y,"SAT",CYAN,CLK_BG_color,2);
				else if(now_d == 3)
				LCD_print_background(D_x,D_y,"SUN",BLUE,CLK_BG_color,2);
				else if(now_d == 4)
				LCD_print_background(D_x,D_y,"MON",RED,CLK_BG_color,2);
				else if(now_d == 5)
				LCD_print_background(D_x,D_y,"TUE",RED,CLK_BG_color,2);
				else if(now_d == 6)
				LCD_print_background(D_x,D_y,"WED",YELLOW,CLK_BG_color,2);
				else if(now_d == 7)
				LCD_print_background(D_x,D_y,"THU",YELLOW,CLK_BG_color,2);
				else if(now_d == 1)
				LCD_print_background(D_x,D_y,"FRI",RED,CLK_BG_color,2);
				old_d = now_d;
			}
		}
		int i = mode;
		modechange(swcheck());
		if(i!=mode){LCD_smooth_off(2);break;}
	}
}
