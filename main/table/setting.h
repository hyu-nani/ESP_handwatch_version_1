void table_set_setting() //pop-up image
{
	table_set_background(0,80,160,80,setting);
	//
	
	//
	table_set_frame(0,80,160,80,frame_popup);	
}

int cursor_x=10,cursor_y=20;

void table_setmode(){
	table_set_background(0,0,160,80,WHITE);
	table_print(cursor_x,cursor_y,"=>",RED,1);
	table_print(10,10,"========SETTING========",BLUE,1);
	table_print(20,20," Backlight",BLACK,1);
	table_print(20,30," GMT-set",BLACK,1);
	table_print(20,40," SUMMER TIME",BLACK,1);
	table_print(20,50," >> NEXT Page",BLACK,1);
	table_print(20,60," << BACK",BLACK,1);
	table_set_frame(0,0,160,80,frame_round);
}
void table_setmode_loop(){
	while(1)
	{
		data = swcheck();
		table_set_background(0,0,160,80,WHITE);
		table_print(cursor_x,cursor_y,"=>",RED,1);
		table_print(10,10,"========SETTING========",BLUE,1);
		table_print(20,20," Backlight",BLACK,1);
		table_print(20,30," GMT-set",BLACK,1);
		table_print(20,40," SUMMER TIME",BLACK,1);
		table_print(20,50," >> NEXT Page",BLACK,1);
		table_print(20,60," << BACK",BLACK,1);
		
		table_set_frame(0,0,160,80,frame_round);
		if(data=='U' && cursor_y !=20){
			cursor_y -= 10;
		}
		else if(data=='D' && cursor_y !=60){
			cursor_y += 10;
		}
		else if(data=='M'){
			if(cursor_y == 60){ //back
				table_set_setting();
				for(int i =-2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=3;
				cursor_x = 10;
				cursor_y = 20;
				break;
			}
			cursor_x +=10;
		}
		print_display(display_x,display_y);
	}
}