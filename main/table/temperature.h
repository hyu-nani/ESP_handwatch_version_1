

void table_set_temp(){
	//loadImage(SD,load_image, "/Background_image/temperature_background.c");
	//loadTableSetBackground(0,80,160,80,load_image);
	//
	//
	table_image(0,80,160,80,temp_image);
	table_set_frame(0,80,160,80,frame_popup);
	Serial.println("Device : set");
}