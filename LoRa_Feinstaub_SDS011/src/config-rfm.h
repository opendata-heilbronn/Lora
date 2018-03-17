#pragma once

#include "config-priv.h"

/////////////////////////////////
// RFM96
/////////////////////////////////

// Pin mapping
const lmic_pinmap lmic_pins = {
	.nss = 5,
	.rxtx = LMIC_UNUSED_PIN,
	.rst = 6,
	.dio = {7, 9, 8},
};
