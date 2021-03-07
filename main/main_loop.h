/*
 * main_loop.h
 *
 * Created: 2021-03-04 오후 7:10:30
 *  Author: cube_
 */ 

//loop main
void main_loop(){
	//========================================================== 0
	while(mode == 0){ //clock
		Clock_set();
		print_display(display_x,display_y);
		LCD_smooth_on(4,backlight);
		while(1){
			Clock_play();
			print_display(display_x,display_y);
			delay(100);
			data = swcheck();
			if(data == 'D'){
				table_set_health();
				mode=1;
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U'){
				table_set_health();
				mode = 1;
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
		}
	}
	
	//========================================================== 1
	while(mode == 1){   //health
		
		while(1){
			print_display(display_x,display_y);
			delay(10);
			data = swcheck();
			if(data == 'D'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_temp();
				mode=3;
				delay(300);
				for(int i = -2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_motion();
				mode=7;
				delay(300);
				for(int i =-2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=0;
				break;
			}
		}
	}
	
	//==========================================================
	while(mode == 3){   //temp
		
		while(1){
			print_display(display_x,display_y);
			delay(10);
			data = swcheck();
			if(data == 'D'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_setting();
				mode=5;
				delay(300);
				for(int i = -2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_health();
				mode=1;
				delay(300);
				for(int i =-2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=0;
				break;
			}
		}
	}
	
	//========================================================== setting pop-up
	while(mode == 5){   
		
		while(1){
			print_display(display_x,display_y);
			delay(10);
			data = swcheck();
			if(data == 'D'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_motion();
				mode=7;
				delay(300);
				for(int i = -2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_temp();
				mode=3;
				delay(300);
				for(int i =-2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M'){
				table_setmode();
				for(int i = -pg_change_num ;i<=2 ;i++){
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
	while(mode == 7){
		
		while(1){
			print_display(display_x,display_y);
			delay(10);
			data = swcheck();
			if(data == 'D'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_health();
				mode=1;
				delay(300);
				for(int i = -2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'U'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				table_set_setting();
				mode=5;
				delay(300);
				for(int i =-2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				break;
			}
			else if (data == 'M'){
				Clock_set();
				for(int i = -pg_change_num ;i<=2 ;i++){
					display_y-=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=0;
				break;
			}
		}
	}
}
