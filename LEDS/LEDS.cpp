#include "LEDS.h"
#define WS8211
using namespace leds;

//globale Variabeln

// Define the array of leds
CRGB fleds[NUM_LEDS];
uint8_t PARAMETER[232];
uint8_t RECEIVEBUFFER[64];
leds::controller CONTROLLER;
#ifdef LPD6803_DEF
LPD6803 strip = LPD6803(NUM_LEDS, DATA_PIN, CLOCK_PIN);
CRGB* ptr;
#endif


void setup(){
	//controller.initController();
	digitalWrite(53, HIGH);
	pinMode(53, OUTPUT);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	Serial.begin(57600);
	CONTROLLER.init(fleds, PARAMETER, RECEIVEBUFFER);

#ifdef WS2811_DEF
	FastLED.addLeds<WS2811, DATA_PIN, BRG>(fleds, NUM_LEDS);
	FastLED.setCorrection(0xFF6F7F);
	FastLED.show();
#endif
#ifdef LPD6803_DEF
strip.setCPUmax(50);
strip.begin();
strip.show();
#endif

}

void loop() {
	CONTROLLER.communication();
	CONTROLLER.caller();
#ifdef WS2811_DEF
	FastLED.show();
#endif
#ifdef LPD6803_DEF
	ptr = fleds;
	for(uint8_t i = 0; i < NUM_LEDS; i++){
		strip.setPixelColor(i, ptr->r, ptr->g, ptr->b);
	}
	strip.show();
#endif
}
