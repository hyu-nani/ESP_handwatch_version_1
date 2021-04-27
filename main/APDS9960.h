/*
 * APDS9960.h
 *
 * Created: 2021-04-28 오전 1:04:24
 *  Author: cube_
 */ 
// Initialize interrupt service routine
void APDSInitWatch()
{
	if(!apds.begin()){
		Serial.println("APDS : failed to initialize device! Please check your wiring.");
	}
	else Serial.println("APDS : Device initialized!");

	//gesture mode will be entered once proximity mode senses something close
	apds.enableProximity(true);
	apds.enableGesture(true);
}
