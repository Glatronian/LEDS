/*
 *   co ntroller.cpp
 *
 *  Created on: 12.04.2015
 *      Author: Christoph
 */

#include "controller.h"

namespace leds {
void controller::init(CRGB* LEDS, uint8_t * PARAMETER, uint8_t * RECEIVEBUFFER){
	//this->NUM_LEDS = NUM_LEDS;
	this->LEDS = LEDS;
	this->PARAMETER = PARAMETER;
	this->RECEIVEBUFFER = RECEIVEBUFFER;
	inCounter = 0;
	colorchange = 0;
	timeDelta = 0;
	timeOld = millis();
	for(int i = 0; i < NUM_LEDS; i++){
		LEDS[i] = CRGB::Black;
	}

	for(int i = 0; i < 232; i++){
		PARAMETER[i] = 0;
	}

	for(int i = 0; i < 64; i++){
		RECEIVEBUFFER[i] = 0;
	}
	for(int i = 0; i < 8 ; i++){
		colors[i] = 0;
		colorsbuf[i] = 0;
	}
	colors[0] = CRGB::DarkBlue;
	colors[1] = CRGB::DarkGoldenrod;
	colors[2] = CRGB::DarkGreen;
	colors[3] = CRGB::Maroon;
	colors[4] = CRGB::MidnightBlue;
	colors[5] = CRGB::Beige;
	colors[6] = CRGB::White;

	FastLED.setCorrection(0xFF4F4F);
	PATTERNS = 1;
	BPM = 60;
	bools = 0;
	pattern1.init(colors, this->LEDS, NUM_LEDS, PARAMETER);
	pattern2.init(colors, this->LEDS, NUM_LEDS, PARAMETER);
}
void controller::communication(){
	/*Serial.write(1);
	_delay_us(200);
	inCounter = 0;
	bools = 0;
	while(Serial.available() > 0 && !bools)
	{
		if(Serial.available() > 1){
			RECEIVEBUFFER[inCounter] = Serial.read();
			RECEIVEBUFFER[inCounter+1] = Serial.read();
			inCounter += 2;
		}
		else
			delayMicroseconds(200);
			bools = 1;
	}*/
	Serial.write(1);
	_delay_us(200);
	uint16_t inCounter = 0;
	uint8_t bools = 0;
	uint8_t available = Serial.available();
	while(available > 0 && !(bools == 3))
	{
		if(available <= 1){
			_delay_us(200);
			bools += 1;
			}
		else{
			RECEIVEBUFFER[inCounter] = Serial.read();
			RECEIVEBUFFER[inCounter+1] = Serial.read();
			inCounter += 2;
		}
		available = Serial.available();
	}

	//Debug


	//Zuweisen
	for(int i = 0; i < inCounter; i += 2)
	{
		switch(RECEIVEBUFFER[i]){
		case 0:
			EVENTS = RECEIVEBUFFER[i + 1];
			break;
		case 1:
			PATTERNS = RECEIVEBUFFER[i + 1];
			for(int i = 0; i < NUM_LEDS; i++){
				LEDS[i] = CRGB::Black;
			}
			break;
		case 2:
			BPM = RECEIVEBUFFER[i+1];
			break;
		case 3:
			BRIGHTNESS = RECEIVEBUFFER[i+1];
			FastLED.setBrightness(BRIGHTNESS);
			break;
///////////Pattern1///////////////
		case 4:
			P1_TYPE = RECEIVEBUFFER[i+1];
			break;
		case 5:
			P1_TIME = RECEIVEBUFFER[i+1];
			break;
		case 6:
			P1_COLOR = RECEIVEBUFFER[i+1];
			break;
		case 7:
			P1_PARAM4 = RECEIVEBUFFER[i+1];
			break;
////////////Pattern2//////////////
		case 8:
			P2_TYPE = RECEIVEBUFFER[i+1];
			break;
		case 9:
			P2_COLOR1 = RECEIVEBUFFER[i+1];
			break;
		case 10:
			P2_COLOR2 = RECEIVEBUFFER[i+1];
			break;
		case 11:
			P2_COLOR3 = RECEIVEBUFFER[i+1];
			break;
/////////////Pattern3///////////////
		case 12:
			P3_PARAM3 = RECEIVEBUFFER[i+1];
			break;
		case 13:
			P4_PARAM1 = RECEIVEBUFFER[i+1];
			break;
		case 14:
			P4_PARAM2 = RECEIVEBUFFER[i+1];
			break;
		case 15:
			P4_PARAM3 = RECEIVEBUFFER[i+1];
			break;
		case 16:
			P5_PARAM1 = RECEIVEBUFFER[i+1];
			break;
		case 17:
			P5_PARAM2 = RECEIVEBUFFER[i+1];
			break;
		case 18:
			P5_PARAM3 = RECEIVEBUFFER[i+1];
			break;
		case 19:
			P6_PARAM1 = RECEIVEBUFFER[i+1];
			break;
		case 20:
			P6_PARAM2 = RECEIVEBUFFER[i+1];
			break;
		case 21:
			P6_PARAM3 = RECEIVEBUFFER[i+1];
			break;
		case 22:
			P7_PARAM1 = RECEIVEBUFFER[i+1];
			break;
		case 23:
			P7_PARAM2 = RECEIVEBUFFER[i+1];
			break;
		case 24:
			P8_PARAM1 = RECEIVEBUFFER[i+1];
			break;
		case 25:
			P8_PARAM2 = RECEIVEBUFFER[i+1];
			break;
		case 26:
			P8_PARAM3 = RECEIVEBUFFER[i+1];
			break;
		case 27:
			colors[0].r = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 28:
			colorsbuf[0].g = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 29:
			colorsbuf[0].b = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 30:
			colorsbuf[1].r = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 31:
			colorsbuf[1].g = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 32:
			colorsbuf[1].b = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 33:
			colorsbuf[2].r = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 34:
			colorsbuf[2].g = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		case 35:
			colorsbuf[2].b = RECEIVEBUFFER[i+1];
			colorchange ++;
			break;
		}
	}
	/*if(RECEIVEBUFFER[1] == 1)
		digitalWrite(13, HIGH);
	else
		digitalWrite(13, LOW);
		*/
	//Farbabgleich
	if(colorchange > 3)
	{
		for(int i = 0; i < 3; i++){
			colors[i] = colorsbuf[i];
		}
		colorchange = 0;
	}


	for( int i = 0; i < 64; i++){
		RECEIVEBUFFER[i] = 0;
	}
	return;
}

void controller::caller(){
	//digitalWrite(13, HIGH);
	//Ruft die aktuellen PATTERNS auf
	timeDelta = millis()-timeOld;
	timeOld = millis();
	//First check if pattern active then check if event or fade
	if(PATTERNS & 0b1){
		if((EVENTS & 0b1) == 1){
			pattern1.eventDetected();
		}
		else
		{
			pattern1.eventFade(&timeDelta);
		}
	}
	if((PATTERNS >> 1) & 0b1 == 1){
		if((EVENTS >> 1) & 0b1 == 1){
			//pattern2
			pattern2.eventDetected();
		}
		else
		{
			//pattern2
			pattern2.eventFade(&timeDelta);
		}
	}
	if((PATTERNS >> 2)%2){
		if((EVENTS >> 2)%2){
			//pattern3
		}
		else
		{
			//pattern3
		}
	}
	if((PATTERNS >> 3)%2){
		if((EVENTS >> 3)%2){
				//pattern4
		}
		else
		{
			//pattern4
		}
	}
	if((PATTERNS >> 4)%2){
		if((EVENTS >> 4)%2){
			//pattern5
		}
		else
		{
			//pattern5
		}
	}
//Reset EVENTS to zero
	EVENTS = 0;
}
} /* namespace leds */
