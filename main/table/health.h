void table_set_health()
{
	//loadImage(SD,load_image, "/Background_image/health_background.c");
	//loadTableSetBackground(0,80,160,80,load_image);
	table_image(0,80,160,160,health_image);
	table_set_frame(0,80,160,80,frame_popup);	
	Serial.println("set");
}