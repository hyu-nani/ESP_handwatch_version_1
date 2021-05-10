void table_set_health()
{
	//loadImage(SD,load_image, "/Background_image/health_background.c");
	//loadTableSetBackground(0,80,160,80,load_image);
	table_image(0,80,160,160,health_image);
	table_set_frame(0,80,160,80,frame_popup);	
	Serial.println("Device : set");
}
void health_setup(){
	sensorOn();
	if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
	{
		Serial.println("MAX : MAX30105 was not found. Please check wiring/power. ");
	}
	if(charge_state ==true)
	Serial.println("MAX : Place your index finger on the sensor with steady pressure.");
	particleSensor.setup(); //Configure sensor with default settings
	particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
	particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}
void health_loop(){
	/*
	long irValue = particleSensor.getIR();
	Serial.println("1");
	if (checkForBeat(irValue) == true)
	{
		//We sensed a beat!
		long delta = millis() - lastBeat;
		Serial.println("2");
		lastBeat = millis();
		Serial.println("3");
		beatsPerMinute = 60 / (delta / 1000.0);

		if (beatsPerMinute < 255 && beatsPerMinute > 20)
		{
			rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
			rateSpot %= RATE_SIZE; //Wrap variable
			Serial.println("3");
			//Take average of readings
			beatAvg = 0;
			for (byte x = 0 ; x < RATE_SIZE ; x++)
			beatAvg += rates[x];
			beatAvg /= RATE_SIZE;
		}
	}
	if(charge_state == true){
		Serial.print("MAX : IR=");
		Serial.print(irValue);
		Serial.print(", BPM=");
		Serial.print(beatsPerMinute);
		Serial.print(", Avg BPM=");
		Serial.println(beatAvg);
	}
	if (irValue < 50000){
		Serial.println("MAX : No finger?");
	}
	else{
		table_graph(10,100,140,48,irValue,IR_min,IR_max,BLUE,BLACK,CYAN);
		IR_val[GraphCount] = irValue;
		int Gmin=120000,Gmax=100000;
		for(int i=0;i<140;i++){
			if(		IR_val[i]<Gmin)	Gmin = IR_val[i];
			else if(IR_val[i]>Gmax)	Gmax = IR_val[i];
		}
		Serial.println("4");
		IR_min = Gmin-5000;
		IR_max = Gmax;
	}
	delay(10);
	*/
}