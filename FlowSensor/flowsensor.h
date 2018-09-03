/*
 * flowsensor.h
 *
 *  Created on: Jul 7, 2018
 *      Author: unix
 */

#ifndef FLOWSENSOR_H_
#define FLOWSENSOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pinmacros.h"
#include "eeprom_calib.h"

extern volatile uint16_t overflows;
extern float waterConsumption;
extern uint16_t freq;
extern bool WaterTimeEnabled;
extern float calcflow;
extern uint8_t ErrorCodes;
extern uint8_t resetTriesFlag;

static uint8_t sensorTimerErrorFlag=0;

typedef struct { float freq; uint8_t flow;  } flowsensor2dtable_t;
float interpolation( flowsensor2dtable_t* c, float x, uint8_t n );
void readFlowSensorFreq(void);
void calcWaterFlow(void);
void storeWaterFlowinEEP(void);
void initTimer0Counter(void);
void initWaterConsumption(void);
void checkErrors(void);
/* Error Codes */
#define MAXWATERCONSUMPTIONERROR 0
#define FLOWSENSORERROR 1
#define NOWATER 2
#define SENSORERROR 3

#endif /* FLOWSENSOR_H_ */
