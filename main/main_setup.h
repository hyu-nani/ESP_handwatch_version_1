
void main_setup()
	Serial.begin(115200);
	EEPROM.begin(20);
	EEPROM_Data_Read();
	SPIClass(VSPI);
	SPI.begin();		//SPI begin
	Wire.begin();	//i2c begin
	watch_pinset();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	LCD_Init();
	LCD_image(0,0,LCD_W,LCD_H,loading[0]);
	LCD_smooth_on(4,200);
	delay(10);
	for (int i=0 ; i< 29 ;i++)
	{
		LCD_image(0,0,LCD_W,LCD_H,loading[i]);
	}
	//WiFi_begin();
	SD_init();
	initial_table();
	for (int i=0 ; i< 29 ;i++)
	{
		LCD_image(0,0,LCD_W,LCD_H,loading[i]);
	}
	delay(1);
	LCD_smooth_off(3);

	//configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");{
	
}