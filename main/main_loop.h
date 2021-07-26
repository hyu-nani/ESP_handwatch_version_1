/*
 * main_loop.h
 *
 * Created: 2021-03-04 ?¤í›„ 7:10:30
 *  Author: cube_
 */ 

//loop main
void watchBasicTask();
void main_loop(){
	//========================================================== default clock
	if(mode == 0)
	{ //clock
		Clock_set();
		print_display(display_x,display_y);
		LCD_smooth_on(4,backlight);
		while(true)
		{
			Clock_play();
			watchBasicTask();
			print_display(display_x,display_y);
		//	delay(1);
			data = swcheck_no_stop();
			if(data == 'D')
			{
				table_set_health();
				mode=1;
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_fill_block(1,BLACK);
				break;
			}
			else if(data == 'U')
			{
				table_set_health();
				mode = 1;
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_fill_block(1,BLACK);
				break;
			}
		}
	}
	
	//========================================================== health mode
	else if(mode == 1)
	{   
		//health_setup();
		while(true)
		{
			health_loop();
			print_display(display_x,display_y);
			data = swcheck_no_stop();
			if(data == 'D')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_temp();
				mode=3;
				for(int i = -2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_folder();
				mode=9;
				for(int i =-2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M')
			{
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=0;
				break;
			}
		}
	}
	//========================================================== into health
	else if(mode == 2)
	{
	  
	}
	//========================================================== temperature
	else if(mode == 3)
	{
		while(true)
		{
			print_display(display_x,display_y);
		//	delay(1);
			data = swcheck_no_stop();
			if(data == 'D')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_setting();
				mode=5;
				for(int i = -2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_health();
				mode=1;
				for(int i =-2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M')
			{
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=0;
				break;
			}
		}
	}
	//========================================================== into temperature
	else if(mode == 4)
	{
		while(true)
		{
			
		}
	}
	//========================================================== setting pop-up
	else if(mode == 5)
	{   
		while(true)
		{
			print_display(display_x,display_y);
		//	delay(1);
			data = swcheck_no_stop();
			if(data == 'D'){
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_motion();
				mode=7;
				for(int i = -2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_temp();
				mode=3;
				for(int i =-2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M')
			{
				table_setmode();
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=6;
				break;
			}
		}
	}
	//================================================================ into setup
	//option
	else if(mode == 6)
	{
		table_setmode_loop();
	}
	//================================================================ motion mode
	else if(mode == 7)
	{
		//initial
		while(true)
		{
			print_display(display_x,display_y);
			delay(1);
			data = swcheck_no_stop();
			if(data == 'D')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_folder();
				mode=9;
				for(int i = -2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_setting();
				mode=5;
				for(int i =-2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M')
			{
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=0;
				break;
			}
		}
	}
	else if(mode == 8)
	{
		
	}
	//================================================================ folder mode
	else if(mode == 9)
	{
		while(true)
		{
			print_display(display_x,display_y);
			delay(1);
			data = swcheck_no_stop();
			if(data == 'D'){
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_health();
				mode=1;
				for(int i = -2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U')
			{
				table_fill_block(1,BLACK);
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_motion();
				mode=7;
				for(int i =-2 ;i<=pg_change_num ;i++)
				{
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M')
			{
				table_setmode();
				for(int i = -pg_change_num ;i<=2 ;i++)
				{
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=6;
				break;
			}
		}
		
	}
	else if(mode == 10)
	{
		table_folder_loop();
	}
}
void watchBasicTask(){
	batteryVolt = 200*3.635*analogRead(BAT_voltage)/4095;
	batteryPercent = map(batteryVolt,320,410,0,100);
	if(digitalRead(charge)==0)
	charge_state = true;
	else
	charge_state = false;
	if (digitalRead(Card_detect))
	connect_SD = true;
	else
	connect_SD = false;
	if (batteryVolt < 320)
	{
		EEPROM_Data_Save();
		SD.end();
		table_fill_block(1,WHITE);
		table_print(10,35,"DEVICE TURN OFF",RED,1);
		table_set_frame(0,0,160,80,frame_round);
		print_display(display_x,display_y);
		LCD_smooth_off(100);
		table_fill_block(1,BLACK);
		table_print(10,35,"Press and hold, please.",BLUE,1);
		digitalWrite(Power,LOW); //turn off
	}
}
