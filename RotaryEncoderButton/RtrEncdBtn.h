#ifndef _RTRENCDBTN_H_
#define _RTRENCDBTN_H_

#include "pinmacros.h"
#include <avr/interrupt.h>
#include "timerInterrupt.h"
#include "ds1307.h"
/*
 * The ports for the pins are defined in pinmacros.h
 * The PD2 PD3 PD 4 are used for the rotary encoder
 */
void initRtrEncoder(void);
void inline attacheInterrupt(void);
void checkHoldButton(void);
void checkStruct(void);
void resetSmartCnt(void);
uint8_t returnStateofProgram();
void smartChangeBtwnHeatCool(void);

extern volatile bool TurnDetected;
extern volatile bool up;
extern int8_t SOLLtemperature;
typedef struct {
long int timeOfClick;
bool clicked;
} click;

static click ArrayOfClicks[5];
extern bool clicked;
extern bool doubleClicked;
extern bool onStateofProgram;
extern volatile uint8_t signalButton; // not to be optimized
volatile static uint8_t pnt=0;
uint8_t holdCnt;

void inline attacheInterrupt(void) {

	EICRA |= (1 << ISC01)|(1<<ISC11)|(1<<ISC10);    //  The rising edge of INT1 and falling edges from INT0 generates an interrupt request
	EIMSK |= (1 << INT0)|(1<<INT1);     // Turns on INT0 & INT1
}



#endif
