/*
 * APDS9960.h
 *
 * Created: 2021-04-28 ¿ÀÀü 1:04:24
 *  Author: cube_
 */ 
// Initialize interrupt service routine
void APDSInitWatch()
{
	if(initStateAPDS == false)
		if(!apds.begin()){
			Serial.println("APDS : failed to initialize device! Please check your wiring.");
		}
		else{
			initStateAPDS = true;
			Serial.println("APDS : Device initialized!");
			apds.enableProximity(true);
			apds.enableGesture(true);
		}
	//gesture mode will be entered once proximity mode senses something close
}
