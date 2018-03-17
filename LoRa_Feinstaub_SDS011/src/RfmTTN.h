#pragma once
#include "Arduino.h"

class RfmTTN {
public:
	static void init();
	static bool sendData(uint8_t* data, uint8_t size);
};
