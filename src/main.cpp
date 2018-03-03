#include "Arduino.h"
#include "RfmTTN.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN		9
#define DHTTYPE		DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
	Serial.begin(115200);
	Serial.println(F("Startup..."));
	RfmTTN::init();
	Serial.println(F("...done."));
	dht.begin();
}

uint8_t buffer[100];

void loop()
{
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	uint8_t humi = (uint8_t)h;
	int8_t temp = (int8_t)t;

	buffer[0] = humi;
	buffer[1] = *((uint8_t*)&temp);

	RfmTTN::sendData(buffer, 2);

	delay(60000);
}
