#include "heatingSys.h"

bool WaterTimeEnabled=false;

// On/Off time Array
// Sunday->Saturday ontime/offtime
  const uint16_t onTimesPM[7] PROGMEM =
  //ontime
  {2200,2200,2200,2200,2200,2200,2200} ;

  const uint16_t offTimesPM[7] PROGMEM =
  //offtime
  {2205,2205,2205,2205,2205,2205,2205};

void autoProgram(void) {


  uint16_t convertedTime= GetHH()*100 +GetMM();

  uint16_t onTimePM= pgm_read_word_near(onTimesPM + 1);
  uint16_t offTimePM= pgm_read_word_near(offTimesPM +1);

  if((onTimePM<convertedTime&&convertedTime<offTimePM)) {

	  WaterTimeEnabled=true;

  }
  else
    {

	  WaterTimeEnabled=false;
  }

}
uint16_t returnDebugInfo() {
	return GetHH()*100 +GetMM();

}
