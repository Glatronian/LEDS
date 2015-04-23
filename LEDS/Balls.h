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
#include "Wabern.h"
#ifndef PATTERNS_BALLS_H_
#define PATTERNS_BALLS_H_

#include "Pattern.h"

struct ball{
	uint8_t active;
	uint8_t position;
	CRGB * farbe;

};

class BallSubStrip {
private:
	CRGB * start;
	uint16_t length;
	ball balls[20];
	uint8_t findFreeBall();
public:
	BallSubStrip(CRGB* start, uint16_t length);
	BallSubStrip();
	void init(CRGB* start, uint16_t length);
	void continueBall0(CRGB* farbwert);
	void continueBall1(CRGB* farbwert);
	void newBall0(CRGB* farbe);
	void newBall1(CRGB* farbe);

};







class Balls: public Pattern {
private:


protected:
	uint8_t bpm;
	uint8_t mood;
	uint8_t param3;
	uint8_t param4;
	uint8_t param5;
	long delta;
	CRGB * farbwert;
	BallSubStrip subStrips[5];




public:
	Balls(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter);
	Balls();
	virtual ~Balls();
	void  init(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter, CRGB *farbwertin);
	void  eventDetected();
	void  eventFade(long *deltaT);
	void  fader0(long *deltaT);
	void  fader1(long *deltaT);
};


#endif /* PATTERNS_WABERN_H_ */
