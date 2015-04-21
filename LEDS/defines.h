/*
 * defines.h
 *
 *  Created on: 06.04.2015
 *      Author: Christoph
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define NUM_LEDS 80
#define DATA_PIN 50
#define CLOCK_PIN 51
//#define LPD6803_DEF
#define WS2811_DEF
//PARAMETERfeld

////Globale Parameter///
#define EVENTS PARAMETER[0]
#define PATTERNS PARAMETER[1]
#define BPM PARAMETER[2]
#define BRIGHTNESS PARAMETER[3]

//////Pattern1////
#define P1_TYPE PARAMETER[4]
#define P1_TIME PARAMETER[5]
#define P1_COLOR PARAMETER[6]
#define P1_PARAM4 PARAMETER[7]

/////Pattern2/////
#define P2_TYPE PARAMETER[8]
#define P2_COLOR1 PARAMETER[9]
#define P2_COLOR2 PARAMETER[10]
#define P2_COLOR3 PARAMETER[11]

/////Pattern3//////
#define P3_TYPE PARAMETER[12]
#define P3_TEMPO PARAMETER[13]
#define P3_COLOR PARAMETER[14]
#define P3_END PARAMETER[15]

#define P3_LENGTH1 11
#define P3_LENGTH2 12

#define P5_PARAM1 PARAMETER[16]
#define P5_PARAM2 PARAMETER[17]
#define P5_PARAM3 PARAMETER[18]
#define P6_PARAM1 PARAMETER[19]
#define P6_PARAM2 PARAMETER[20]
#define P6_PARAM3 PARAMETER[21]
#define P7_PARAM1 PARAMETER[22]
#define P7_PARAM2 PARAMETER[23]
#define P7_PARAM3 PARAMETER[24]
#define P8_PARAM1 PARAMETER[25]
#define P8_PARAM2 PARAMETER[26]
#define P8_PARAM3 PARAMETER[27]


//ColorFeld

#endif /* DEFINES_H_ */
