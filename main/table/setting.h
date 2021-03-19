void table_set_setting() //pop-up image
{
	table_set_background(0,80,160,80,setting);
	//
	
	//
	table_set_frame(0,80,160,80,frame_popup);	
}

int cursor_x=10,cursor_y=20;
int option_page=1;
void menu_select();

void table_setmode(){ //first image set
	table_set_background(0,0,160,80,WHITE);
	table_print(cursor_x,cursor_y,"E>",RED,1);
	table_print(10,10,"=======SETTING/1=======",BLUE,1);
	table_print(20,20," WiFi",BLACK,1);
	table_print(20,30," Bluetooth",BLACK,1);
	table_print(20,40," SD card",BLACK,1);
	table_print(20,50," >> NEXT Page",BLACK,1);
	table_print(20,60," << BACK",BLACK,1);
	table_set_frame(0,0,160,80,frame_round);
}
void table_setmode_loop(){ //setting loop
	while(true)
	{
		reset:
		
		delay(10);
		data = swcheck();
		table_set_background(0,0,160,80,WHITE);
		table_print(cursor_x,cursor_y,"E>",RED,1);
		if(option_page==1){
			table_print(10,10,"=======SETTING/1=======",BLUE,1);
			table_print(20,20," WiFi",BLACK,1);
			table_print(20,30," Bluetooth",BLACK,1);
			table_print(20,40," SD card",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK",BLACK,1);
		}
		else if(option_page==2){
			table_print(10,10,"=======SETTING/2=======",BLUE,1);
			table_print(20,20," Time set",BLACK,1);
			table_print(20,30," GMT",BLACK,1);
			table_print(20,40," Summer time",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK Page",BLACK,1);
		}
		else if(option_page==3){
			table_print(10,10,"=======SETTING/3=======",BLUE,1);
			table_print(20,20," Background color",BLACK,1);
			table_print(20,30," hleath mode",BLACK,1);
			table_print(20,40," time package",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK Page",BLACK,1);
		}
		else if(option_page==4){
			table_print(10,10,"=======SETTING/4=======",BLUE,1);
			table_print(20,20," OMG",BLACK,1);
			table_print(20,30," Please",BLACK,1);
			table_print(20,40," help me",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK Page",BLACK,1);
		}
		else if(option_page==5){
			table_print(10,10,"=======SETTING/5=======",BLUE,1);
			table_print(20,20," oh no",BLACK,1);
			table_print(20,30," to much",BLACK,1);
			table_print(20,40," Turn Off Device",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK Page",BLACK,1);
		}
		table_set_frame(0,0,160,80,frame_round);
		if(data=='U' && cursor_y !=20){
			cursor_y -= 10;
		}
		else if(data=='D' && cursor_y !=60){
			cursor_y += 10;
		}
		else if(data=='M'){
			if(cursor_y == 60&&option_page==1){ //back
				table_set_setting();
				for(int i =-2 ;i<=pg_change_num ;i++){
					display_y+=(9*i*i)/400+1;
					print_display(display_x,display_y);
				}
				mode=5;
				cursor_x = 10;
				cursor_y = 20;
				break;
			}
			else if(cursor_y == 60&&option_page!=1){ //back page
				option_page--;
			}
			else if(cursor_y == 50&&option_page<5){ //next page
				option_page++;
				cursor_x = 10;
				cursor_y = 20;
			}
			
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////                        OPTION                            //////////////
			////////////////////////////////////////////////////////////////////////////////////////
			
			if (cursor_y == 20&&option_page==1)			//wifi
			{
			  table_fill_block(1,WHITE);
			  table_print(10,35,"====== SCANNING.. ======",BLUE,1);
			  print_display(display_x,display_y);
				WiFi_scan();
				int select=0;
				while (true)
				{
					
					delay(10);
					data = swcheck();
					table_fill_block(1,WHITE);				  //
					table_print(10,10,"======= Network =======",BLUE,1);
					table_print(cursor_x,cursor_y,"E>",RED,1);
					for (int i=0;i<5;i++)
					{
						table_print(25,20+(i*10),Network_SSID[i],BLACK,1);
						table_print(100,20+(i*10),Network_RSSI[i],BLACK,1);
					}
					table_set_frame(0,0,160,80,frame_round);
					if(data=='U' && cursor_y !=20){
						cursor_y -= 10;
						select--;
					}
					else if(data=='D' && cursor_y !=60){
						cursor_y += 10;
						select++;
					}
					else if(data=='M'){
						char copy[50];
						Network_SSID[select].toCharArray(copy, 50);
						table_fill_block(1,WHITE);
						table_print(10,35,"===== CONNECTING.. =====",YELLOW,1);
						table_set_frame(0,0,160,80,frame_round);
						print_display(display_x,display_y);
						
						Serial.println(copy);
						WiFi.begin(copy, password);
						long starttime = millis();
						while (WiFi.status() != WL_CONNECTED) {
							delay(500);
							Serial.print(".");
							if(starttime+4000 < millis()){
								table_fill_block(1,WHITE);
								table_print(10,35,"======= FAIL.. =======",RED,1);
								print_display(display_x,display_y);
								delay(100);
								goto reset;
							}
						}
						table_fill_block(1,WHITE);
						table_print(10,35,"====== CONNECTED =======",BLUE,1);
						table_set_frame(0,0,160,80,frame_round);
						print_display(display_x,display_y);
						Serial.println("CONNECTED");
						after_connect();
						delay(500);
						cursor_y=20;
						goto reset;
					}
					print_display(display_x,display_y);
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==1)		//bluetooth
			{
			  table_fill_block(1,WHITE);
			 
			  while(true)
			  {
			    
			  }
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==1)		//SDcard
			{
				SD_CS_Clr();
				cardType = SD.cardType();
				cardSize = SD.totalBytes() / (1024 * 1024);
				cardUse =  SD.usedBytes() / (1024 * 1024);
				SD_CS_Set();
				while (true)
				{
					delay(10);
					data = swcheck();
					table_fill_block(1,WHITE);				  //
					table_print(10,10,"======= SD card =======",BLUE,1);
					int cx=20, cy=20;
					if(cardType == CARD_MMC){
						table_print(cx,cy,"MMC",MAGENTA,2);
						} else if(cardType == CARD_SD){
						table_print(cx,cy,"SDSC",MAGENTA,2);
						} else if(cardType == CARD_SDHC){
						table_print(cx,cy,"SDHC",MAGENTA,2);
						} else {
						table_print(cx,cy,"UNKNOWN",MAGENTA,2);
					}

					table_print(20,40,"Size: ",BLACK,1);
					table_print(50,40,cardSize,LIGHTGREEN,1);
					table_print(82,40,"MB",BLACK,1);
					table_print(20,50,"USE: ",BLACK,1);
					table_print(50,50,cardUse,LIGHTGREEN,1);
					table_print(82,50,"MB",BLACK,1);
					
					table_print(20,60,"Press middle button..",BLACK,1);
					table_set_frame(0,0,160,80,frame_round);
					print_display(display_x,display_y);
					if(data=='M'){
						goto reset;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==2)		//time set
			{
			  table_fill_block(1,WHITE);
			  table_print(10,10,"=======TIME SET=======",BLACK,1);
			  print_display(display_x,display_y);
			  delay(10);
			  while(true)
			  {
			    table_fill_block(1,WHITE);
			    table_print(10,10,"=======TIME SET=======",BLUE,1);
			    table_print(10,30,"1 Sec period =",BLACK,1);
			    //table_print(100,30,sec_period,BLACK,1);
			    print_display(display_x,display_y);
			  }
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==2)		//GMT
			{
			  while(true)
			  {
			    
			  }
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==2)		//summer time
			{
			  while(true)
			  {
			    
			  }
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==3)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==3)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==3)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==4)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==4)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==4)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
	    else if (cursor_y == 20&&option_page==5)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==5)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==5) //Turn Off Device
			{
			  table_fill_block(1,WHITE);
			  table_print(10,35,"DEVICE TURN OFF",RED,2);
			  print_display(display_x,display_y);
			  delay(1000);
			  //Serial.disconnect();
			  //WiFi.disconnect();
			  //SD.disconnect();
			  digitalWrite(Power,LOW); //turn off
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		print_display(display_x,display_y);
	}
}