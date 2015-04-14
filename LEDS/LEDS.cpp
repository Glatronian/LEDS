#include "LEDS.h"
#include "defines.h"
using namespace leds;

//globale Variabeln

// Define the array of leds
CRGB fleds[NUM_LEDS];
uint8_t PARAMETER[232];
uint8_t RECEIVEBUFFER[64];
leds::controller CONTROLLER;


void setup(){
	//controller.initController();
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	Serial.begin(115200);
	CONTROLLER.init(fleds, PARAMETER, RECEIVEBUFFER);
#ifdef WS2811
	FastLED.addLeds<WS2811, DATA_PIN, BRG>(fleds, NUM_LEDS);
	FastLED.setCorrection(0xFF6F7F);
	FastLED.show();
#endif

}

void loop() {
	CONTROLLER.communication();
	CONTROLLER.caller();
#ifdef WS2811
	FastLED.show();
#endif
}
