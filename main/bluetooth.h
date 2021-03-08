/*
 * bluetooth.h
 *
 * Created: 2021-03-08 오후 9:28:11
 *  Author: cube_
 */ 
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

#define SERVICE_UUID           "599f424f-5382-4386-b7ae-9f26a41a1bd2" // UART service UUID
#define CHARACTERISTIC_UUID_RX "599f424f-5382-4386-b7ae-9f26a41a1bd2"
#define CHARACTERISTIC_UUID_TX "599f424f-5382-4386-b7ae-9f26a41a1bd2"

class MyServerCallbacks: public BLEServerCallbacks {
	void onConnect(BLEServer* pServer) {
		deviceConnected = true;
	};

	void onDisconnect(BLEServer* pServer) {
		deviceConnected = false;
	}
};

class MyCallbacks: public BLECharacteristicCallbacks {
	void onWrite(BLECharacteristic *pCharacteristic) {
		std::string rxValue = pCharacteristic->getValue();

		if (rxValue.length() > 0) {
			Serial.println("*********");
			Serial.print("Received Value: ");
			for (int i = 0; i < rxValue.length(); i++)
			Serial.print(rxValue[i]);

			Serial.println();
			Serial.println("*********");
		}
	}
};

void bluetooth_init(){
	BLEDevice::init("");
	
}

