void table_set_folder()
{
	//loadImage(SD,load_image, "/Background_image/health_background.c");
	//loadTableSetBackground(0,80,160,80,load_image);
	table_image(0,80,160,160,folder_image);
	table_set_frame(0,80,160,80,frame_popup);
	Serial.println("set");
}

void table_folder_loop()
{
	while (true)
	{
		reset:
		
		delay(10);
		data = swcheck();
		table_set_background(0,0,160,80,WHITE);
		table_print(cursor_x,cursor_y,"E>",RED,1);
	}
}