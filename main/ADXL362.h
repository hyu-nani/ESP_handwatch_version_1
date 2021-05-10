/*
 * ADXL362.h
 *
 * Created: 2021-04-07 오전 11:32:04
 *  Author: cube_
 */ 
#define adxl_freq 10000000

class ADXL362
{
	public:

	ADXL362();
	
	//
	// Basic Device control and readback functions
	//
	//void begin(int16_t chipSelectPin = 10);
	void beginMeasure();
	int16_t readXData();
	int16_t readYData();
	int16_t readZData();
	void readXYZTData(int16_t &XData, int16_t &YData, int16_t &ZData, int16_t &Temperature);
	int16_t readTemp();
	
	//
	// Activity/Inactivity interrupt functions
	//
	void setupDCActivityInterrupt(int16_t threshold, byte time);
	void setupDCInactivityInterrupt(int16_t threshold, int16_t time);
	void setupACActivityInterrupt(int16_t threshold, byte time);
	void setupACInactivityInterrupt(int16_t threshold, int16_t time);
	
	// need to add the following functions
	// void mapINT1(
	// void mapINT2
	// void autoSleep
	// void activityInterruptControl
	//		-Activity, Inactivity, Both
	//		- Referenced, Absolute
	//		- Free Fall, Linked Mode, Loop Mode
	
	void checkAllControlRegs();
	

	
	//  Low-level SPI control, to simplify overall coding
	byte SPIreadOneRegister(byte regAddress);
	void SPIwriteOneRegister(byte regAddress, byte regValue);
	int16_t  SPIreadTwoRegisters(byte regAddress);
	void SPIwriteTwoRegisters(byte regAddress, int16_t twoRegValue);

	private:

	
};


ADXL362::ADXL362() {
}


void ADXL362::beginMeasure() {
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	byte tempADXL = SPIreadOneRegister(0x2D);	// read Reg 2D before modifying for measure mode

	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : Setting Measeurement Mode - Reg 2D before = ");
	Serial.print(temp);
	#endif

	// turn on measurement mode
	byte tempwrite = tempADXL | 0x02;			// turn on measurement bit in Reg 2D
	SPIwriteOneRegister(0x2D, tempwrite);		// Write to POWER_CTL_REG, Measurement Mode
	delay(10);
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	
	#ifdef ADXL362_DEBUG
	temp = SPIreadOneRegister(0x2D);
	Serial.print("ADXL : , Reg 2D after = ");
	Serial.println(tempADXL);
	Serial.println();
	#endif
}

//
//  readXData(), readYData(), readZData(), readTemp()
//  Read X, Y, Z, and Temp registers
//
int16_t ADXL362::readXData(){
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	int16_t XDATA = SPIreadTwoRegisters(0x0E);
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : XDATA = ");
	Serial.println(XDATA);
	#endif
	
	return XDATA;
}

int16_t ADXL362::readYData(){
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	int16_t YDATA = SPIreadTwoRegisters(0x10);
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : \tYDATA = ");
	Serial.println(YDATA);
	#endif
	
	return YDATA;
}

int16_t ADXL362::readZData(){
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	int16_t ZDATA = SPIreadTwoRegisters(0x12);
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : \tZDATA = ");
	Serial.println(ZDATA);
	#endif

	return ZDATA;
}

int16_t ADXL362::readTemp(){
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	int16_t TEMP = SPIreadTwoRegisters(0x14);
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : \tTEMP = ");
	Serial.println(TEMP);
	#endif

	return TEMP;
}

void ADXL362::readXYZTData(int16_t &XData, int16_t &YData, int16_t &ZData, int16_t &Temperature){
	// burst SPI read
	// A burst read of all three axis is required to guarantee all measurements correspond to same sample time
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPI.beginTransaction(mySPISettings);			//translate succed
	SPI.transfer(0x0B);  // read instruction
	SPI.transfer(0x0E);  // Start at XData Reg
	XData = SPI.transfer(0x00);
	XData = XData + (SPI.transfer(0x00) << 8);
	YData = SPI.transfer(0x00);
	YData = YData + (SPI.transfer(0x00) << 8);
	ZData =	SPI.transfer(0x00);
	ZData = ZData + (SPI.transfer(0x00) << 8);
	Temperature = SPI.transfer(0x00);
	Temperature = Temperature + (SPI.transfer(0x00) << 8);
	SPI.endTransaction();
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : XDATA = "); Serial.print(XData);
	Serial.print("\tYDATA = "); Serial.print(YData);
	Serial.print("\tZDATA = "); Serial.print(ZData);
	Serial.print("\tTemperature = "); Serial.println(Temperature);
	#endif
}

void ADXL362::setupDCActivityInterrupt(int16_t threshold, byte time){
	//  Setup motion and time thresholds
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPIwriteTwoRegisters(0x20, threshold);
	SPIwriteOneRegister(0x22, time);

	// turn on activity interrupt
	byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);  // Read current reg value
	ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x01);     // turn on bit 1, ACT_EN
	SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);       // Write new reg value
	ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);       // Verify properly written
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : DC Activity Threshold set to ");  	Serial.print(SPIreadTwoRegisters(0x20));
	Serial.print(", Time threshold set to ");  		Serial.print(SPIreadOneRegister(0x22));
	Serial.print(", ACT_INACT_CTL Register is ");  	Serial.println(ACT_INACT_CTL_Reg, HEX);
	#endif
}

void ADXL362::setupACActivityInterrupt(int16_t threshold, byte time){
	//  Setup motion and time thresholds
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPIwriteTwoRegisters(0x20, threshold);
	SPIwriteOneRegister(0x22, time);
	
	// turn on activity interrupt
	byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);  // Read current reg value
	ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x03);     // turn on bit 2 and 1, ACT_AC_DCB, ACT_EN
	SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);       // Write new reg value
	ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);       // Verify properly written
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : AC Activity Threshold set to ");  	Serial.print(SPIreadTwoRegisters(0x20));
	Serial.print(", Time Activity set to ");  		Serial.print(SPIreadOneRegister(0x22));
	Serial.print(", ACT_INACT_CTL Register is ");  Serial.println(ACT_INACT_CTL_Reg, HEX);
	#endif
}

void ADXL362::setupDCInactivityInterrupt(int16_t threshold, int16_t time){
	// Setup motion and time thresholds
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPIwriteTwoRegisters(0x23, threshold);
	SPIwriteTwoRegisters(0x25, time);

	// turn on inactivity interrupt
	byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);   // Read current reg value
	ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x04);      // turn on bit 3, INACT_EN
	SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);        // Write new reg value
	ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);        // Verify properly written
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : DC Inactivity Threshold set to ");  Serial.print(SPIreadTwoRegisters(0x23));
	Serial.print(", Time Inactivity set to ");  Serial.print(SPIreadTwoRegisters(0x25));
	Serial.print(", ACT_INACT_CTL Register is ");  Serial.println(ACT_INACT_CTL_Reg, HEX);
	#endif
}

void ADXL362::setupACInactivityInterrupt(int16_t threshold, int16_t time){
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	//  Setup motion and time thresholds
	SPIwriteTwoRegisters(0x23, threshold);
	SPIwriteTwoRegisters(0x25, time);
	
	// turn on inactivity interrupt
	byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);   // Read current reg value
	ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x0C);      // turn on bit 3 and 4, INACT_AC_DCB, INACT_EN
	SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);        // Write new reg value
	ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);        // Verify properly written
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
	#ifdef ADXL362_DEBUG
	Serial.print("ADXL : AC Inactivity Threshold set to ");  Serial.print(SPIreadTwoRegisters(0x23));
	Serial.print(", Time Inactivity set to ");  Serial.print(SPIreadTwoRegisters(0x25));
	Serial.print(", ACT_INACT_CTL Register is ");  Serial.println(ACT_INACT_CTL_Reg, HEX);
	#endif
}

void ADXL362::checkAllControlRegs(){
	//byte filterCntlReg = SPIreadOneRegister(0x2C);
	//byte ODR = filterCntlReg & 0x07;  Serial.print("ODR = ");  Serial.println(ODR, HEX);
	//byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);      Serial.print("ACT_INACT_CTL_Reg = "); Serial.println(ACT_INACT_CTL_Reg, HEX);
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPI.beginTransaction(mySPISettings);
	SPI.transfer(0x0B);  // read instruction
	SPI.transfer(0x20);  // Start burst read at Reg 20
	#ifdef ADXL362_DEBUG
	Serial.println("ADXL : Start Burst Read of all Control Regs - Library version 6-5-2014:");
	Serial.print("ADXL : Reg 20 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 21 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 22 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 23 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 24 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 25 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 26 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 27 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 28 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 29 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 2A = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 2B = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 2C = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 2D = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("ADXL : Reg 2E = "); 	Serial.println(SPI.transfer(0x00), HEX);
	#endif
	SPI.endTransaction();
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
}

// Basic SPI routines to simplify code
// read and write one register
byte ADXL362::SPIreadOneRegister(byte regAddress){
	byte regValue = 0;
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPI.beginTransaction(mySPISettings);
	SPI.transfer(0x0B);  // read instruction
	SPI.transfer(regAddress);
	regValue = SPI.transfer(0x00);
	SPI.endTransaction();
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4

	return regValue;
}

void ADXL362::SPIwriteOneRegister(byte regAddress, byte regValue){
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPI.beginTransaction(mySPISettings);
	SPI.transfer(0x0A);  // write instruction
	SPI.transfer(regAddress);
	SPI.transfer(regValue);
	SPI.endTransaction();
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
}

int16_t ADXL362::SPIreadTwoRegisters(byte regAddress){
	int16_t twoRegValue = 0;
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPI.beginTransaction(mySPISettings);
	SPI.transfer(0x0B);  // read instruction
	SPI.transfer(regAddress);
	twoRegValue = SPI.transfer(0x00);
	twoRegValue = twoRegValue + (SPI.transfer(0x00) << 8);
	SPI.endTransaction();
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4

	return twoRegValue;
}

void ADXL362::SPIwriteTwoRegisters(byte regAddress, int16_t twoRegValue){
	byte twoRegValueH = twoRegValue >> 8;
	byte twoRegValueL = twoRegValue;
	mySPISettings = SPISettings(adxl_freq, MSBFIRST, SPI_MODE0); //ESP speed /4
	ADXL_CS_Clr();
	SPI.beginTransaction(mySPISettings);
	SPI.transfer(0x0A);  // write instruction
	SPI.transfer(regAddress);
	SPI.transfer(twoRegValueL);
	SPI.transfer(twoRegValueH);
	SPI.endTransaction();
	ADXL_CS_Set();
	mySPISettings = SPISettings(60000000, MSBFIRST, SPI_MODE0); //ESP speed /4
}