#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"

#include "RfmTTN.h"
#include <SDS011.h>
#include <Adafruit_BMP280.h>

#define SERIAL_DEBUG false

struct payload_t {
	uint16_t pm10;
	uint16_t pm25;
	int16_t temp =  -30000;
	int16_t humid = -30000; 
	int16_t press = -30000;
} payload;

SDS011 pmSensor;
float pm10, pm25;

Adafruit_BMP280 bmp;

void setup()
{
	delay(5000);
	Serial.begin(115200);

	pmSensor.begin(&Serial1);


	#if SERIAL_DEBUG
		Serial.print(F("BMP280 Startup..."));
	#endif
	if(!bmp.begin(0x76)) {
		#if SERIAL_DEBUG
			Serial.println("ERROR: No valid BMP280 sensor found. No temperature/pressure measurements will be taken");
		#endif
	}
	#if SERIAL_DEBUG
		Serial.println(F("done."));

		Serial.print(F("LoRa Startup..."));
	#endif
	RfmTTN::init();
	#if SERIAL_DEBUG
		Serial.println(F("done."));
	#endif
}

#if SERIAL_DEBUG
	void debug(uint8_t *data, uint8_t size) {
		for(int i = 0; i < size; i++) {
			Serial.print(data[i], 16);
			Serial.print(" ");
		}
		Serial.println();
	}
#endif

void loop()
{
	pmSensor.wakeup();
	delay(15000); //TODO: replace with sleep
	pmSensor.read(&pm25, &pm10);
	pmSensor.sleep();
	payload.pm10 = (int)pm10;
	payload.pm25 = (int)pm25;

	#if SERIAL_DEBUG
		Serial.print(F("PM Sensor data: 2.5µm: "));
		Serial.print(pm25);
		Serial.print(F("  10µm: "));
		Serial.println(pm10);
	#endif


	float temp = bmp.readTemperature();
	float pres = bmp.readPressure();

	if(temp > -139 && pres < 128000 && pres > 0) {
		payload.temp  = temp * 100; //temperature times 100
		payload.press = pres / 100; //pressure in hpa

		#if SERIAL_DEBUG
			Serial.print("Temperature = ");
			Serial.print(bmp.readTemperature());
			Serial.println(" *C");
			
			Serial.print("Pressure = ");
			Serial.print(bmp.readPressure());
			Serial.println(" Pa");
		#endif
	}

	#if SERIAL_DEBUG
		debug(reinterpret_cast<uint8_t*>(&payload), sizeof(payload));
	#endif
	RfmTTN::sendData(reinterpret_cast<uint8_t*>(&payload), sizeof(payload));
	
	delay((1 * 60 * 1000L) - 15000); //TODO: replace with sleep
}
