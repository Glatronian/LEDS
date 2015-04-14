/*
 * controller.h
 *
 *  Created on: 12.04.2015
 *      Author: Christoph
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
//add your includes for the project Blitzdings here
#include <Arduino.h>
#include <util/delay.h>
#include <FastLED.h>
#include "defines.h"
#include "Wabern.h"
//end of add your includes here

namespace leds {

class controller {
private:
	CRGB* LEDS;
	uint8_t* PARAMETER;
	uint8_t* RECEIVEBUFFER;
	//int NUM_LEDS;
	uint8_t inCounter;
	uint8_t bools = 0;

	uint8_t colorchange;
	CRGB colors[8];
	CRGB colorsbuf[8];

	long timeDelta;
	long timeOld;

	Wabern pattern1;


public:
	void init(CRGB* LEDS, uint8_t * PARAMETER, uint8_t * RECEIVEBUFFER);
	void communication();
	void caller();
};

} /* namespace leds */

#endif /* CONTROLLER_H_ */
