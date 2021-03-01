void table_set_setting() //pop-up image
{
	table_set_background(0,80,160,80,setting);
	table_set_frame(0,80,160,80,frame_popup);	
}

void table_setmode(){
	table_set_background(0,0,160,80,BLUE);
	table_print(10,20,"setting mode",MAGENTA,2);
	table_set_frame(0,0,160,80,frame_round);
	
}