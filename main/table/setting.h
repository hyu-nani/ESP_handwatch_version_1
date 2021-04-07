void table_set_setting() //pop-up image
{
	//loadImage(SD,load_image, "/Background_image/setting_background.c");
	//loadTableSetBackground(0,80,160,80,load_image);
	//
	table_image(0,80,160,80,set_image);
	//
	table_set_frame(0,80,160,80,frame_popup);	
}

int cursor_x=10,cursor_y=20;
int option_page=1;
bool option_active = false;
void menu_select();
void deviceTurnOff();
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
			table_print(20,30," Backlight",BLACK,1);
			table_print(20,40," set",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK Page",BLACK,1);
		}
		else if(option_page==3){
			table_print(10,10,"=======SETTING/3=======",BLUE,1);
			table_print(20,20," SHT20 test",BLACK,1);
			table_print(20,30," MAX test",BLACK,1);
			table_print(20,40," ADXL test",BLACK,1);
			table_print(20,50," >> NEXT Page",BLACK,1);
			table_print(20,60," << BACK Page",BLACK,1);
		}
		else if(option_page==4){
			table_print(10,10,"=======SETTING/4=======",BLUE,1);
			table_print(20,20," I2C address",BLACK,1);
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
			table_print(20,50," ",BLACK,1);
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
				//cursor_y = 20;
			}
			else{
				option_active = true;
			}
			
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////                        OPTION                            //////////////
			////////////////////////////////////////////////////////////////////////////////////////
			
			if (cursor_y == 20&&option_page==1&&option_active == true)			//wifi
			{
				table_fill_block(1,WHITE);
				table_print(10,35,"====== SCANNING.. ======",BLUE,1);
				table_set_frame(0,0,160,80,frame_round);
				print_display(display_x,display_y);
				WiFi_scan();
				int select_wifi=0;
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
						select_wifi--;
					}
					else if(data=='D' && cursor_y !=60){
						cursor_y += 10;
						select_wifi++;
					}
					else if(data=='M'){
						char copy[50];
						Network_SSID[select_wifi].toCharArray(copy, 50);
						table_fill_block(1,WHITE);
						table_print(10,35,"===== CONNECTING.. =====",BLUE,1);
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
								table_print(10,35,"======== FAIL.. ========",RED,1);
								table_set_frame(0,0,160,80,frame_round);
								print_display(display_x,display_y);
								delay(1000);
								cursor_y=20;
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
						//cursor_y=20;
						option_active = false;
						goto reset;
					}
					print_display(display_x,display_y);
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==1&&option_active == true)		//bluetooth
			{
			  table_fill_block(1,WHITE);
			 
			  while(true)
			  {
			    
			  }
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==1&&option_active == true)		//SDcard
			{
				SD_CS_Clr();
				SD.end();
				delay(100);
				if(!SD.begin(SD_CS)){
					Serial.println("Card Mount Failed");
					connect_SD = false;
				}
				else
					connect_SD = true;
				cardType = SD.cardType();
				cardSize = SD.totalBytes() / (1024 * 1024);
				cardUse =  SD.usedBytes() / (1024 * 1024);
				table_fill_block(1,WHITE);
				SD_CS_Set();
				while (true)
				{
					delay(10);
					data = swcheck();
					//table_fill_block(1,WHITE);				  //
					table_fill_block(1,WHITE);
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
						option_active = false;
						goto reset;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==2&&option_active == true)		//time set
			{
				bool set_active = false;
				cursor_y = 20;
				if (daylightOffset_sec%600!=0)
				daylightOffset_sec = 0;
				if (GMT > 20)
				GMT = 0;					
				while(true)
				{
					TIME_SET:
					table_fill_block(1,WHITE);
					if(set_active==false)
					table_print(10,cursor_y,"E>",RED,1);
					else
					table_print(10,cursor_y,"S>",RED,1);
					
					table_print(10,10,"=======TIME SET=======",BLUE,1);
					table_print(20,20," Summer Time=",BLACK,1);table_print(100,20,daylightOffset_sec,BLACK,1);table_print(130,20,"ms",BLACK,1);
					table_print(20,30," Sec period =",BLACK,1);table_print(100,30,sec_period*4,BLACK,1);table_print(130,30,"ms",BLACK,1);
					table_print(20,40," +GMT Set   =",BLACK,1);table_print(100,40,GMT,BLACK,1);table_print(130,40,"hour",BLACK,1);
					table_print(20,50," CLOCK SET >>",BLACK,1);
					table_print(20,60," << BACK Page",BLACK,1);
			
					table_set_frame(0,0,160,80,frame_round);
					print_display(display_x,display_y);
					
					data = swcheck();
					
					if(cursor_y == 20&&set_active==true)      //SUMMER TIME
					{
						if(data == 'U')
						daylightOffset_sec +=600;
						else if(data == 'D')
						daylightOffset_sec -=600;
						else if(data == 'M')						
						{
							set_active = false;
							goto TIME_SET;
						}
					}
					else if(cursor_y == 30&&set_active==true)//sec_period
					{
						if(data == 'U')
						sec_period += 1;
						else if(data == 'D')
						sec_period -= 1;
					    else if(data == 'M')
					    {
							set_active = false;
							goto TIME_SET;
					    }
					}
					else if(cursor_y == 40&&set_active==true)//GMT
					{
						if(data == 'U')
						GMT += 1;
					    else if(data == 'D')
						GMT -= 1;
					    else if(data == 'M')
					    {
							set_active = false;
							goto TIME_SET;
					    }
					}
					else if(cursor_y == 50&&set_active==true)
					{
						set_active=false;
						cursor_y =20;
					    while(true)
					    {
							CLOCK_SET:
							
							table_fill_block(1,WHITE);
      						if(set_active==false)
      						table_print(10,cursor_y,"E>",RED,1);
      						else
      						table_print(10,cursor_y,"S>",RED,1);
							  
							table_print(10,10,"=======CLOCK SET=======",BLUE,1);
							table_print(20,20," hour   =",BLACK,1);table_print(90,20,now_hour,BLACK,1);
							table_print(20,30," Minute =",BLACK,1);table_print(90,30,now_minute,BLACK,1);
							table_print(20,40," Second =",BLACK,1);table_print(90,40,now_second,BLACK,1);
							table_print(20,50," WiFi update",BLACK,1);
							table_print(20,60," << BACK Page",BLACK,1);
							table_set_frame(0,0,160,80,frame_round);
							print_display(display_x,display_y);
							data = swcheck();
							
							if(cursor_y == 20&&set_active==true)
							{
								if(data == 'U')
								now_hour ++;
								else if(data == 'D')
								now_hour --;
								else if(data == 'M')
								{
									set_active = false;
									goto CLOCK_SET;
								}
							}
							else if(cursor_y == 30&&set_active==true)
							{
								if(data == 'U')
								now_minute ++;
								else if(data == 'D')
								now_minute --;
								else if(data == 'M')
								{
									set_active = false;
									goto CLOCK_SET;
								}
							}
							else if(cursor_y == 40&&set_active==true)
							{
								if(data == 'U')
								now_second ++;
								else if(data == 'D')
								now_second --;
								else if(data == 'M')
								{
									set_active = false;
									goto CLOCK_SET;
								}
							}
							if(data == 'U'&&set_active == false&&cursor_y>20)
							cursor_y-=10;
							else if(data == 'D'&&set_active == false&&cursor_y<60)
							cursor_y+=10;
							else if(data == 'M'&&cursor_y != 60)
							set_active = true;
							else if(data == 'M'&&cursor_y==60)
							{
								set_active = false;
								goto TIME_SET;
							}
						}
					}
					if(data == 'U'&&set_active == false&&cursor_y>20)
					cursor_y-=10;
					else if(data == 'D'&&set_active == false&&cursor_y<60)
					cursor_y+=10;
					else if(data == 'M'&&cursor_y != 60)
					set_active = true;
					else if(data == 'M'&&cursor_y == 60)
					{
						option_active = false;
						EEPROM_Data_Save();
						goto reset;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==2&&option_active == true)		//Backlight
			{
				while(true)
				{
					table_fill_block(1,WHITE);
					int val = map(backlight,0,255,0,120);
					table_print(10,10,"====== Backlight ======",BLUE,1);
					table_Rect(20,35,120,10,GREEN);
					table_fill_Rect(20,35,val,10,GREEN);
					table_set_frame(0,0,160,80,frame_round);
					table_print(70,60,backlight-1,BLUE,1);
					print_display(display_x,display_y);
					data = swcheck_no_stop();
					LCD_smooth_on(1,backlight);
					if(data == 'M'){
						option_active = false;
						EEPROM_Data_Save();
						data = swcheck();
						goto reset;
					}
					else if(data == 'U'&&backlight<250)
					backlight+=10;
					else if(data == 'D'&&backlight>1)
					backlight-=10;
					if(backlight%10!=1)
					backlight--;
						
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==2&&option_active == true)		//
			{
			  listDir(SD, "/", 0);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==3&&option_active == true)
			{
				sensorOn();
				delay(100);
				sht20.initSHT20();   // Init SHT20 Sensor
				delay(100);
				sht20.checkSHT20();  // Check SHT20 Sensor
				while(true)
				{
					data = swcheck();
					humd = sht20.readHumidity();                  // Read Humidity
					temp = sht20.readTemperature();               // Read Temperature
					Serial.print("Time:");
					Serial.print(millis());
					Serial.print(" Temperature:");
					Serial.print(temp, 1);
					Serial.print("C");
					Serial.print(" Humidity:");
					Serial.print(humd, 1);
					Serial.print("%");
					Serial.println();
					table_fill_block(1,WHITE);
					table_print(10,10,"====== SHT20 test ======",BLUE,1);
					table_print(20,20,"TEMP:",BLACK,2);
					table_print(20,40,"HUMD:",BLACK,2);
					table_print(90,20,temp,BLUE,2);
					table_print(90,40,humd,GBLUE,2);
					table_set_frame(0,0,160,80,frame_round);
					print_display(display_x,display_y);
					delay(100);
					if(data == 'M'){
						option_active = false;
						sensorOff();
						goto reset;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==3&&option_active == true)
			{
				Serial.println("Initializing...");
				sensorOn();
				// Initialize sensor
				if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
				{
					Serial.println("MAX30105 was not found. Please check wiring/power. ");
					while (1);
				}
				Serial.println("Place your index finger on the sensor with steady pressure.");

				particleSensor.setup(); //Configure sensor with default settings
				particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
				particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
				while (true)
				{
					data = swcheck();
					if(data == 'M'){
						option_active = false;
						sensorOff();
						goto reset;
					}
					
					long irValue = particleSensor.getIR();

					if (checkForBeat(irValue) == true)
					{
						//We sensed a beat!
						long delta = millis() - lastBeat;
						lastBeat = millis();

						beatsPerMinute = 60 / (delta / 1000.0);

						if (beatsPerMinute < 255 && beatsPerMinute > 20)
						{
							rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
							rateSpot %= RATE_SIZE; //Wrap variable

							//Take average of readings
							beatAvg = 0;
							for (byte x = 0 ; x < RATE_SIZE ; x++)
							beatAvg += rates[x];
							beatAvg /= RATE_SIZE;
						}
					}

					Serial.print("IR=");
					Serial.print(irValue);
					Serial.print(", BPM=");
					Serial.print(beatsPerMinute);
					Serial.print(", Avg BPM=");
					Serial.print(beatAvg);

					if (irValue < 50000)
					Serial.print(" No finger?");

					Serial.println();
					table_fill_block(1,WHITE);
					table_print(10,10,"====== MAX test ======",BLUE,1);
					table_print(20,20,"BEAT:",BLACK,2);
					table_print(20,40,"AVER:",BLACK,2);
					table_print(90,20,beatsPerMinute,RED,2);
					table_print(90,40,beatAvg,BLUE,2);
					table_set_frame(0,0,160,80,frame_round);
					print_display(display_x,display_y);
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==3&&option_active == true)
			{
				
				table_fill_block(1,WHITE);
				table_print(10,30,"====== Scanning ======",BLUE,1);
				//table_print(10,40,"Pls, connect to Serial",BLACK,1);
				table_set_frame(0,0,160,80,frame_round);
				print_display(display_x,display_y);
				xl.beginMeasure();              // Switch ADXL362 to measure mode
				int direction=0;
				Serial.println("Start Demo: Simple Read");
				int xv=0,yv=0,zv=0;
				delay(500);
				
				int A = 500;
				int a,b,c,d;
				
				while (true)
				{
					data = swcheck();
					if(data == 'M'){
						option_active = false;
						goto reset;
					}
				//	xl.beginMeasure();  
					xl.readXYZTData(XValue, YValue, ZValue, Temperature);
				//	ADXL_CS_Clr();
				//	XValue=xl.readXData();
				//	YValue=xl.readYData();
				//	ZValue=xl.readZData();
				//	ADXL_CS_Set();
					
					if (XValue>A)
					XValue=A;
					if (YValue>A)
					YValue=A;
					if (ZValue>A)
					ZValue=A;
					
					xv = (map(XValue,-A,A,0,110)+xv*4)/5;
					yv = (map(YValue,-A,A,0,110)+yv*4)/5;
					zv = (map(ZValue,-A,A,0,110)+zv*4)/5;
				//	xv = map(XValue,-255,255,0,110);
				//	yv = map(YValue,-255,255,0,110);
				//	zv = map(ZValue,-255,255,0,110);
				//	if (xv>110)
				//	direction = 1;	//stand
				//	else if(yv>110)
				//	direction = 2;	//side
				//	else if(zv>110)
				//	direction = 3;	//lay
					if(charge_state == true){
						Serial.print("XVALUE=");
						Serial.print(XValue);
						Serial.print("\tYVALUE=");
						Serial.print(YValue);
						Serial.print("\tZVALUE=");
						Serial.print(ZValue);
						Serial.print("\tTEMPERATURE=");
						Serial.println(Temperature);
					}
					if(a!=xv||b!=yv||c!=zv||d!=Temperature){
						table_fill_block(1,WHITE);
						table_print(15,20,"X",BLUE,1);
						table_print(15,30,"Y",BLUE,1);
						table_print(15,40,"Z",BLUE,1);
						table_Rect(30,20,110,5,RED);
						table_Rect(30,30,110,5,RED);
						table_Rect(30,40,110,5,RED);
						
						table_fill_Rect(30,20,xv,5,RED);
						table_fill_Rect(30,30,yv,5,RED);
						table_fill_Rect(30,40,zv,5,RED);
						table_print(75,60,Temperature,MAGENTA,1);
						
						table_Line(85,17,85,48,1,BLUE);
						table_set_frame(0,0,160,80,frame_round);
						print_display(display_x,display_y);
						LCD_CS_Set();
					}
					else{
						xl.beginMeasure();              // Switch ADXL362 to measure mode
						delay(10);
					}
					a=xv;b=yv,c=zv,d=Temperature;
					delay(1);
					
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==4&&option_active == true)
			{
				sensorOn();
				byte error, address;
				int nDevices;
				Wire.begin();
				Serial.println("Scanning...");
				nDevices = 0;
				table_fill_block(1,WHITE);
				table_print(10,30,"====== Scanning ======",BLUE,1);
				table_print(10,40,"Pls, connect to Serial",BLACK,1);
				table_set_frame(0,0,160,80,frame_round);
				print_display(display_x,display_y);
				while(true)
				{
					data = swcheck();
					if(data == 'M'){
						option_active = false;
						sensorOff();
						goto reset;
					}
					for(address = 1; address < 127; address++ )
					{
						// The i2c_scanner uses the return value of
						// the Write.endTransmisstion to see if
						// a device did acknowledge to the address.
						Wire.beginTransmission(address);
						error = Wire.endTransmission();
						
						if (error == 0)
						{
							Serial.print("I2C device found at address 0x");
							if (address<16)
							Serial.print("0");
							Serial.print(address,HEX);
							Serial.println("  !");
							
							nDevices++;
						}
						else if (error==4)
						{
							Serial.print("Unknown error at address 0x");
							if (address<16)
							Serial.print("0");
							Serial.println(address,HEX);
						}
					}
					if (nDevices == 0)
					Serial.println("No I2C devices found\n");
					else
					Serial.println("done\n");
					
					delay(5000);           // wait 5 seconds for next scan
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==4&&option_active == true)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==4&&option_active == true)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 20&&option_page==5&&option_active == true)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 30&&option_page==5&&option_active == true)
			{
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (cursor_y == 40&&option_page==5&&option_active == true) //Turn Off Device
			{
				
				option_active = false;
				deviceTurnOff();
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		print_display(display_x,display_y);
	}
}
void deviceTurnOff(){
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