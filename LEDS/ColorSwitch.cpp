/*
 * ColorSwitch.cpp
 *
 *  Created on: 01.04.2015
 *      Author: Christoph
 */

#include "ColorSwitch.h"

ColorSwitch::ColorSwitch(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter) {
	// TODO Auto-generated constructor stub
	numLeds = length;
	ptrleds = leds;
	ptrColors = colors;
	this->PARAMETER = parameter;
	P2_TYPE = 0;
	P2_COLOR1 = 1;
	P2_COLOR2 = 2;
	P2_COLOR3 = 3;
}
ColorSwitch::ColorSwitch(){

}

ColorSwitch::~ColorSwitch() {
	// TODO Auto-generated destructor stub
}
void ColorSwitch::init(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter){
	numLeds = length;
		ptrleds = leds;
		ptrColors = colors;
		this->PARAMETER = parameter;
		P2_TYPE = 0;
		P2_COLOR1 = 1;
		P2_COLOR2 = 2;
		P2_COLOR3 = 3;
}
void ColorSwitch::eventDetected(){
	CRGB* ptr = ptrleds;
	switch (P2_TYPE)
	{
	case 0:
		for(uint16_t i = 0; i < numLeds; i++){
			ptrleds[i] = ptrColors[P2_COLOR1];
		}
		break;
	case 1:

		break;
	case 2:
		//Dreieck
		break;
	}
}

void ColorSwitch::eventFade(long *deltaT){
	switch (P2_TYPE)
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	}
}

