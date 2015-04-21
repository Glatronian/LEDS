/*
 * Wabern.h
 *
 *  Created on: 01.04.2015
 *      Author: Christoph
 */
#include <Arduino.h>
#include <math.h>

#include <FastLED.h>
#include "defines.h"
#ifndef PATTERNS_COLORSWITCH_H_
#define PATTERNS_COLORSWITCH_H_

#include "Pattern.h"

class ColorSwitch: public Pattern {
private:
	void switchColor();
	void leaveOneOut();

protected:
	uint8_t bpm;
	uint8_t mood;
	uint8_t param3;
	uint8_t param4;
	uint8_t param5;


public:
	ColorSwitch(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter);
	ColorSwitch();
	virtual ~ColorSwitch();
	void  init(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter);
	void  eventDetected();
	void  eventFade(long *deltaT);
};

#endif /* PATTERNS_WABERN_H_ */
