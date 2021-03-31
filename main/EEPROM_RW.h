/*
 * EEPROM_RW.h
 *  EEPROM 에 관한 모든 정보 기입
 * Created: 2021-03-19 오후 9:49:07
 *  Author: cube_
 */ 
 
void EEPROM_Data_Save(){
	EEPROM.write(1,backlight);
	EEPROM.write(2,sec_period);
	EEPROM.write(3,update_cycle_time);
	EEPROM.write(4,GMT);
	EEPROM.write(5,daylightOffset_sec);
	EEPROM.write(6,now_hour);
	EEPROM.write(7,now_minute);
	EEPROM.write(8,now_second);
	EEPROM.commit();
}
void EEPROM_Data_Read(){
	backlight			= EEPROM.read(1);
	sec_period			= EEPROM.read(2);
	update_cycle_time	= EEPROM.read(3);
	GMT					= EEPROM.read(4);
	daylightOffset_sec	= EEPROM.read(5);
	now_hour			= EEPROM.read(6);
	now_minute			= EEPROM.read(7);
	now_second			= EEPROM.read(8);
	if(now_hour == 255)
	now_hour = 0;
	if(now_minute==255)
	now_minute=0;
	if(now_second==255)
	now_second=0;
}
