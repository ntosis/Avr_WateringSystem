/*
 * heatingsys.h
 *
 *  Created on: Nov 27, 2015
 *      Author: unix
 */

#ifndef HEATINGSYS_H_
#define HEATINGSYS_H_

#include <avr/pgmspace.h>
#include "pinmacros.h"
#include "ds1307.h"
#include "RtrEncdBtn.h"

void autoProgram();
void LEDfunction(void);
uint16_t returnDebugInfo();
extern bool WaterTimeEnabled;



#endif /* HEATINGSYS_H_ */
