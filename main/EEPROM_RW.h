/*
 * EEPROM_RW.h
 *
 * Created: 2021-03-19 오후 9:49:07
 *  Author: cube_
 */ 
void EEPROM_Data_Save(){
	EEPROM.write(1,backlight);
	EEPROM.write(2,sec_period);
	EEPROM.write(3,update_cycle_time);
	EEPROM.write(4,GMT);
	EEPROM.write(5,daylightOffset_sec);
	EEPROM.commit();
}
void EEPROM_Data_Read(){
	backlight         = EEPROM.read(1);
	sec_period        = EEPROM.read(2);
	update_cycle_time = EEPROM.read(3);
	GMT               = EEPROM.read(4);
  daylightOffset_sec= EEPROM.read(5);
}
