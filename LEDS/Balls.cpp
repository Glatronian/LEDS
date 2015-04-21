/*
 * Balls.cpp
 *
 *  Created on: 01.04.2015
 *      Author: Christoph
 */

#include "Balls.h"
BallSubStrip::BallSubStrip(){

}
BallSubStrip::BallSubStrip(CRGB* start, uint16_t length){
	this->start = start;
	this->length = length;
	for(uint8_t i = 0; i < 20; i++){
		balls[i].active = 0;
		balls[i].position = 0;
	}

}
void BallSubStrip::init(CRGB* start, uint16_t length){
	this->start = start;
	this->length = length;
	for(uint8_t i = 0; i < 20; i++){
		balls[i].active = 0;
		balls[i].position = 0;
	}
}

uint8_t BallSubStrip::findFreeBall(){
	for(uint8_t i = 0; i < 20; i++){
		if(balls[i].active == 0)
			return i;
	}
	return 21;
}

void BallSubStrip::continueBall0(CRGB * farbwert){
	//Serial.write(5);
	for(uint8_t i =  0; i < 20; i++){
		if(balls[i].active == 1 ){
			start[balls[i].position] = *farbwert;
			balls[i].position++;
			if(balls[i].position == length)
			{
				balls[i].position = 0;
				balls[i].active = 0;
			}
			else{
				start[balls[i].position] = *(balls[i].farbe);
			}
		}
	}
}
void BallSubStrip::continueBall1(CRGB * farbwert){
	//Serial.write(5);
	for(uint8_t i =  0; i < 20; i++){
		if(balls[i].active == 1 ){
			start[balls[i].position] = *farbwert;
			balls[i].position--;
			if(balls[i].position == 255)
			{
				balls[i].position = length-1;
				balls[i].active = 0;
			}
			else{
				start[balls[i].position] = *(balls[i].farbe);
			}
		}
	}
}

void BallSubStrip::newBall0(CRGB *farbe){
	if(findFreeBall() < 21){

		balls[findFreeBall()].farbe = farbe;
		start[0] = *farbe;
		balls[findFreeBall()].active = 1;

	}
}
void BallSubStrip::newBall1(CRGB *farbe){
	if(findFreeBall() < 21){

		balls[findFreeBall()].farbe = farbe;
		start[length-1] = *farbe;
		balls[findFreeBall()].active = 1;

	}
}

/////////////////////////////////////////////////////////////////////////
/*
 *
 * 			Balls
 *
 */
/////////////////////////////////////////////////////////////////////////


Balls::Balls(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter) {
	// TODO Auto-generated constructor stub
	numLeds = length;
	ptrleds = leds;
	ptrColors = colors;
	delta = 0;
	this->PARAMETER = parameter;
	P3_TYPE = 0;
	P3_TEMPO = 1;
	farbwert = 0;
	//wabern = Wabern();
}
Balls::Balls(){
	delta = 0;
	farbwert = 0;
}

Balls::~Balls() {
	// TODO Auto-generated destructor stub
}
void Balls::init(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter, CRGB *farbwertin){
	numLeds = length;
	ptrleds = leds;
	ptrColors = colors;
	this->PARAMETER = parameter;
	P3_TYPE = 0;
	P3_TEMPO = 50;
	P3_COLOR = 6;
	subStrips[0].init(leds, P3_LENGTH1);
	subStrips[1].init(leds+P3_LENGTH1, P3_LENGTH2);
	farbwert = farbwertin;
	//delay(10000);
	delta = 0;
}
void Balls::eventDetected(){
	CRGB* ptr = ptrleds;
	switch (P3_TYPE)
	{
	case 0:
		//Serial.write(3);
		subStrips[0].newBall0(&ptrColors[P3_COLOR]);
		subStrips[1].newBall1(&ptrColors[P3_COLOR]);
		break;
	case 1:

		break;
	case 2:
		//Dreieck
		break;
	}
}

void Balls::eventFade(long * deltaT){
	switch (P3_TYPE)
	{
	case 0:
		fader(deltaT);
		break;
	case 1:

		break;
	case 2:

		break;
	}
}
void Balls::fader(long * deltaT){
	delta = delta + *deltaT;
	//Serial.write(delta);
	if(delta >= P3_TEMPO ){

		delta = 0;
		//Serial.write(farbwert->b);
		subStrips[0].continueBall0(farbwert);
		subStrips[1].continueBall1(farbwert);
	}
}
