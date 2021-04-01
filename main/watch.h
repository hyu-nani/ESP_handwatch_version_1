#define EN2				    35 
#define BAT_voltage			34
#define SD_CS			    33
#define Card_detect			27
#define wireless			26
#define sensor_power		25
#define TFT_DC				15
#define TFT_RST				14
#define TFT_CS				32
#define TFT_LIGHT	  		16
#define SW_U			  	13
#define SW_M			  	12
#define SW_D			  	5
#define charge		  		2
#define ADXL_CS		  		4
#define Power		     	17
#define SCK			    	18
#define MISO			  	19
#define MOSI			  	23
//#define SCL			  	22
//#define SDA			  	21

#define sensorOn()	digitalWrite(sensor_power,HIGH);
#define sensorOff()	digitalWrite(sensor_power,LOW);
#define deviceOn()	digitalWrite(Power,HIGH);
#define deviceOff()	digitalWrite(Power,LOW);

void watch_pinset()
{
	pinMode(SW_U,INPUT_PULLUP);
	pinMode(SW_M,INPUT);
	pinMode(SW_D,INPUT);
	pinMode(BAT_voltage,INPUT);
	pinMode(MOSI,OUTPUT);
	pinMode(MISO,INPUT);
	pinMode(TFT_CS,OUTPUT);
	pinMode(TFT_DC,OUTPUT);
	pinMode(TFT_RST,OUTPUT);
	pinMode(EN2,OUTPUT);
	pinMode(Power,OUTPUT);
	pinMode(ADXL_CS,OUTPUT);
	pinMode(SD_CS,OUTPUT);
	pinMode(SCK,OUTPUT);
	pinMode(charge,INPUT_PULLUP);
	pinMode(sensor_power,OUTPUT);
	//initialization
	digitalWrite(SD_CS,HIGH);
	digitalWrite(ADXL_CS,HIGH);
	digitalWrite(TFT_CS,HIGH);
	deviceOn();
	digitalWrite(EN2,LOW);
	digitalWrite(sensor_power,LOW);
	ledcSetup(0, 5000, 8);
	ledcAttachPin(TFT_LIGHT,0); //TFT_light 0 chenal
}
void watch_init()
{
	batteryVolt = 200*3.635*analogRead(BAT_voltage)/4095;
	//battery_value	=	analogRead(BAT_voltage);
	if(digitalRead(charge)==0)
	charge_state = true;
	else
	charge_state = false;
}