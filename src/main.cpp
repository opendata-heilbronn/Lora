#include "Arduino.h"
#include "RfmTTN.h"

void setup()
{
	Serial.begin(115200);
	Serial.println(F("Startup..."));
	RfmTTN::init();
	Serial.println(F("...done."));
}

void loop()
{
	const uint8_t data[] = {1,2,3,4,5};

	RfmTTN::sendData(data, sizeof(data));

	delay(60000);
}
