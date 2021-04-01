/*
 * main_loop.h
 *
 * Created: 2021-03-04 오후 7:10:30
 *  Author: cube_
 */ 

//loop main
void watchBasicTask();
void main_loop(){
	//========================================================== default clock
	while(mode == 0)
	{ //clock
		Clock_set();
		print_display(display_x,display_y);
		LCD_smooth_on(4,backlight);
		while(true)
		{
			Clock_play();
			watchBasicTask();
			print_display(display_x,display_y);
			delay(1);
			data = swcheck();
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
			else if (data == 'U')
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
	while(mode == 1)
	{   
		
		while(true)
		{
			print_display(display_x,display_y);
			delay(1);
			data = swcheck();
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
	while(mode == 2)
	{
	  
	}
	//========================================================== temperature
	while(mode == 3)
	{
		
		while(true)
		{
			print_display(display_x,display_y);
			delay(1);
			data = swcheck();
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
	while(mode == 4)
	{
	  while(true)
	  {
	    
	  }
	}
	//========================================================== setting pop-up
	while(mode == 5)
	{   
		while(true)
		{
			print_display(display_x,display_y);
			delay(1);
			data = swcheck();
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
	while (mode == 6)
	{
		table_setmode_loop();
		break;
	}
	//================================================================ motion mode
	while(mode == 7)
	{
		//initial
		while(true)
		{
			print_display(display_x,display_y);
			delay(1);
			data = swcheck();
			if(data == 'D')
			{
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
}
void watchBasicTask(){
	batteryVolt = 200*3.635*analogRead(BAT_voltage)/4095;
	batteryPercent = map(batteryVolt,320,410,0,100);
	if(digitalRead(charge)==0)
	charge_state = true;
	else
	charge_state = false;
}