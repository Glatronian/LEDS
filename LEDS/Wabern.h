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
#ifndef PATTERNS_WABERN_H_
#define PATTERNS_WABERN_H_

#include "Pattern.h"

class Wabern: public Pattern {
private:
	void standardWave(long *deltaT);
	void rectangleWave(long *deltaT);
	void leaveOneOut();

protected:
	uint8_t bpm;
	uint8_t mood;
	uint8_t param3;
	uint8_t param4;
	uint8_t param5;
	float vAbfallr;
	float vAbfallg;
	float vAbfallb;
	float dFarber;				//Generalz�hler
	float dFarbeg;
	float dFarbeb;
	long deltaTime;
	long deltaTimePassed;
	CRGB farbwert;
	uint32_t time;
	uint32_t dtime;

public:
	Wabern(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter);
	Wabern();
	virtual ~Wabern();
	void  init(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter);
	void  eventDetected();
	void  eventFade(long *deltaT);
};

#endif /* PATTERNS_WABERN_H_ */
