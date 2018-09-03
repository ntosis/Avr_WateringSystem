/*
 * eeprom_calib.h
 *
 *  Created on: Jul 5, 2016
 *      Author: unix
 */

#ifndef EEPROM_CALIB_H_
#define EEPROM_CALIB_H_
#include <pinmacros.h>
#include <avr/eeprom.h>
// Create structure
typedef struct {
	float waterConsumption;
	uint8_t resets;

} CAL_PARAM;

void LoadCALvars(void);
void SaveCALvars(void);
void setWaterConsumption(float val);
void readEEWaterConsumption(float *val);
void increaseResetCounter(void);
uint8_t readEEResets(void);
void InitCALvars(void);

extern CAL_PARAM CALinRAM;

#endif /* EEPROM_CALIB_H_ */

