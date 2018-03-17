#pragma once

#include "config-priv.h"

/////////////////////////////////
// RFM96
/////////////////////////////////

// Pin mapping
const lmic_pinmap lmic_pins = {
	.nss = 10,
	.rxtx = LMIC_UNUSED_PIN,
	.rst = 5,
	.dio = {2, 3, LMIC_UNUSED_PIN},
};
