#include "Arduino.h"
#include "RfmTTN.h"


struct payload_t {
	uint16_t pm10;
	uint16_t pm25;
	int16_t temp;
	int16_t humid; 
} payload;

void setup()
{
	delay(5000);
	Serial.begin(115200);
	Serial.println(F("LoRa Startup..."));
	RfmTTN::init();
	Serial.println(F("...done."));
	Serial.println(sizeof(payload));
}

void debug(uint8_t *data, uint8_t size) {
	for(int i = 0; i < size; i++) {
		Serial.print(data[i], 16);
		Serial.print(" ");
	}
	Serial.println();
}

void loop()
{
	payload.pm10 = 10;
	payload.pm25 = 25;
	payload.temp = 1000; //temperature times 100
	payload.humid = 5000; //humidity times 100

	debug(reinterpret_cast<uint8_t*>(&payload), sizeof(payload));
	RfmTTN::sendData(reinterpret_cast<uint8_t*>(&payload), sizeof(payload));
	
	delay(60000);
}
