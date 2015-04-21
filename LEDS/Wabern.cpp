/*
 * Wabern.cpp
 *
 *  Created on: 01.04.2015
 *      Author: Christoph
 */

#include "Wabern.h"

Wabern::Wabern(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter) {
	// TODO Auto-generated constructor stub

}
Wabern::Wabern(){
	farbwert = 0;
}

Wabern::~Wabern() {
	// TODO Auto-generated destructor stub
}
void Wabern::init(CRGB *colors, CRGB *leds, uint16_t length, uint8_t * parameter){
	ptrColors = colors;
	ptrleds = leds;
	numLeds = length;
	this->PARAMETER = parameter;
	P1_TYPE = 0;
	P1_COLOR = 0;
	P1_TIME = 255;
	farbwert = CRGB(0,0,0);
}
void Wabern::eventDetected(){
	CRGB* ptr = ptrleds;
	switch (P1_TYPE)
	{
	case 0:
		//standard Waveform
		//berechne Abfallgeschwindigkeit
		vAbfallr = (float)ptrColors[P1_COLOR].r/(((float)P1_TIME)/255*(60000/((float)BPM)));
		vAbfallg = (float)ptrColors[P1_COLOR].g/(((float)P1_TIME)/255*(60000/((float)BPM)));
		vAbfallb = (float)ptrColors[P1_COLOR].b/(((float)P1_TIME)/255*(60000/((float)BPM)));

		//speichere Startfarbe um nicht zu viel Abfall zu erzeugen
		farbwert = ptrColors[P1_COLOR];

		//setze Farbwert


		for(int i = 0; i < numLeds; i++)
		{

			ptr->r = qadd8(ptr->r, farbwert.r);
			ptr->g = qadd8(ptr->g, farbwert.g);
			ptr->b = qadd8(ptr->b, farbwert.b);
			ptr++;
		}

		break;
	case 1:
		deltaTime = round(P1_TIME/((float)255)*(60000/((float)BPM)));
		deltaTimePassed = 0;
		//Rectangle
		farbwert = ptrColors[P1_COLOR];

		//setze Farbwert


		for(int i = 0; i < numLeds; i++)
		{

			ptr->r = qadd8(ptr->r, farbwert.r);
			ptr->g = qadd8(ptr->g, farbwert.g);
			ptr->b = qadd8(ptr->b, farbwert.b);
			ptr++;
		}
		break;
	case 2:
		//Dreieck
		break;
	}
}

void Wabern::eventFade(long *deltaT){
	switch (P1_TYPE)
	{
	case 0:
		//standard Waveform
		standardWave(deltaT);
		break;
	case 1:
		//Rectangle
		rectangleWave(deltaT);
		break;
	case 2:
		//Dreieck
		break;
	}
}

void Wabern::standardWave(long *deltaT)
{
	//berechne Schrittabfall
	dFarber += float(*deltaT) * vAbfallr;

	dFarbeg += float(*deltaT) * vAbfallg;

	dFarbeb += float(*deltaT) * vAbfallb;

	//berechen neue Ledmatrix

	if(dFarber >= 1){
		if(farbwert.r >= 0){
			for(int i=0; i < numLeds; i++)
				ptrleds[i].r = qsub8(ptrleds[i].r, round(dFarber));
			farbwert.r = qsub8(farbwert.r, round(dFarber));
		}
		dFarber = 0;

	}
	if(dFarbeg >= 1){
		if(farbwert.g >= 0){
			for(int i=0; i < numLeds; i++)
				ptrleds[i].g = qsub8(ptrleds[i].g, round(dFarbeg));
			farbwert.g = qsub8(farbwert.g, round(dFarbeg));
		}
		dFarbeg = 0;
	}
	if(dFarbeb >= 1){
		if(farbwert.b >= 0){
			for(int i=0; i < numLeds; i++)
				ptrleds[i].b = qsub8(ptrleds[i].b, round(dFarbeb));
			farbwert.b = qsub8(farbwert.b, round(dFarbeb));
		}

		dFarbeb = 0;
	}




}

void Wabern::rectangleWave(long *deltaT){
	deltaTimePassed += *deltaT;

	if(deltaTimePassed >= deltaTime)
	{
		CRGB* ptr = ptrleds;
		for(int i = 0; i < numLeds; i++){
			ptr->r = qsub8(ptr->r, farbwert.r);
			ptr->g = qsub8(ptr->g, farbwert.g);
			ptr->b = qsub8(ptr->b, farbwert.b);
			ptr++;
		}
		deltaTimePassed = 0;
	}
}
