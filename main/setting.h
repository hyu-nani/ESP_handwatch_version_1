char sw_data='0';
uint16_t SET_BG_color = BLACK;

int h_cursor = 25,w_curcor = 0;
void matrix();
void LCD_menu();
void SETTING()
{
	LCD_Fill(SET_BG_color);
	LCD_menu();
	delay(10);
	LCD_smooth_on(2,backlight);
	while(1)
	{
		sw_data = swcheck();
		int old_h_cursor =h_cursor;
		if(sw_data == 'U'){
			if(h_cursor > 25){
				h_cursor -= 15;
			}
			else{
				h_cursor = 145;
			}
		}
		else if(sw_data == 'M'){w_curcor++;}
		else if(sw_data == 'D'){
			if(h_cursor < 145){
				h_cursor += 15;
			}
			else{
				h_cursor = 25;
			}
		}
		if (h_cursor!=old_h_cursor)
		{
			LCD_fill_Rect(1,old_h_cursor,11,14,SET_BG_color);
			LCD_print(1,h_cursor,"O>",BLUE,1);
		}
		if(h_cursor==145&&w_curcor>0){
			mode = 0;
			h_cursor = 25;
			w_curcor = 0;
			LCD_smooth_off(2);
			break;
		}
		matrix();
		delay(1);
	}
}
void matrix()
{
	if(w_curcor == 1)
	{
		if (h_cursor == 25) //BACKLIGHT SETTING
		{
			LCD_Fill(SET_BG_color);
			LCD_Rect(0,0,80,160,MAGENTA);
			LCD_Rect(10,40,60,100,YELLOW);
			LCD_print(15,5,"backlight",WHITE,1);
			while (1)
			{
				if(digitalRead(sw1)==0&&backlight<1000){
					backlight+=10;
				}
				else if(digitalRead(sw3)==0&&backlight>10){
					backlight-=10;
				}
				else if(digitalRead(sw2)==0){
					LCD_smooth_off(1);
					LCD_Fill(SET_BG_color);
					LCD_menu();
					delay(10);
					LCD_smooth_on(2,backlight);
					w_curcor--;
					break;
				}
				int i = map(backlight,0,1000,99,0);
				LCD_fill_Rect(11,41,58,i,SET_BG_color);
				LCD_fill_Rect(11,41+i,58,100-i,YELLOW);
        ledcWrite(0, backlight);
				delay(10);
			}
		}
		if (h_cursor == 40)
		{
			LCD_Fill(SET_BG_color);
			LCD_Rect(0,0,80,160,MAGENTA);
			LCD_Rect(10,40,60,100,YELLOW);
			LCD_print(15,5,"backimage",WHITE,1);
			while (1)
			{
				
			}
		}
	}
	if(w_curcor == 2)
	{
		
	}
}
void LCD_menu(){
	LCD_Rect(0,0,80,160,MAGENTA);
	LCD_print(22,5,"SET",MAGENTA,2);
	LCD_print(13,25,"Backlight",WHITE,1);
	LCD_print(13,40,"Backimage",WHITE,1);
	LCD_print(13,55,"SETTING 3",WHITE,1);
	LCD_print(13,70,"SETTING 4",WHITE,1);
	LCD_print(13,85,"SETTING 5",WHITE,1);
	LCD_print(13,100,"SETTING 6",WHITE,1);
	LCD_print(13,115,"SETTING 7",WHITE,1);
	LCD_print(13,145,"BACK",WHITE,1);
	LCD_print(1,h_cursor,"O>",BLUE,1);
}
