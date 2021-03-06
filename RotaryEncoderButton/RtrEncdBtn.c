#include "RtrEncdBtn.h"
#include <stdlib.h>
#include "heatingSys.h"
#include <eeprom_calib.h>
bool clicked=false;
bool doubleClicked=false;
uint8_t holdCnt=0;
//step between Heating/Cooling
uint8_t smartCntUp=0;
uint8_t smartCntDown=0;
uint8_t smartCntFlag=0;
extern volatile uint8_t signalButton = 0;
extern volatile bool up = false;
extern volatile bool TurnDetected = false;
void initRtrEncoder(void) {

	__INPUT(PinCLK);
	__INPUT(PinDT);
	//disable internal pull ups
	__LOW(PinCLK);
	__LOW(PinDT);
	attacheInterrupt();

}

ISR (INT0_vect)
{
	 if (__READ(PinCLK))
	    up = __READ(PinDT);
	  else
	    up = !(__READ(PinDT));
	  TurnDetected = true;
}

ISR(INT1_vect) {

    ArrayOfClicks[pnt].timeOfClick=counter100MS;
    ArrayOfClicks[pnt].clicked=true;
    pnt++;
         //
    if(pnt==5) pnt=0;
    if(signalButton<2) signalButton++;
}
void checkStruct(void) {

  cli();
  pnt=0;
 clicked=false;
 doubleClicked=false;
  for(int i=0;i<5;i++) {
         if(i<4){
         if(ArrayOfClicks[i].clicked==true)  {
             if(ArrayOfClicks[i+1].clicked==true) {
            	int8_t dt= (ArrayOfClicks[i+1].timeOfClick)-(ArrayOfClicks[i].timeOfClick);
               if(dt<7) {
            	   doubleClicked=true;
                   //jump to next incoming signal.
            	   i++;
            	   continue;
                }
               else clicked=true;
             }
             else clicked=true;
         }
       }
       else if(i==4) {
         if(ArrayOfClicks[i].clicked==true)  {
        	if(ArrayOfClicks[0].clicked==true) {
               int8_t dt= (ArrayOfClicks[0].timeOfClick)-(ArrayOfClicks[i].timeOfClick);
               dt=abs(dt);
               if(dt<7) {
            	   doubleClicked=true;
               //i++;
            	   continue;
             }
               else clicked=true;

             }
             else clicked=true;
         }
       }
  }
    for(int i=0;i<5;i++) {
      ArrayOfClicks[i].clicked=false;
      ArrayOfClicks[i].timeOfClick=0;
    }
   sei();
}
uint8_t returnStateofProgram() {return onStateofProgram;}
/*void smartChangeBtwnHeatCool(void) {

	if(smartCntUp>smartCnt_C){ //Calibrations parameter

		if(SOLLtemperature<0)

			{SOLLtemperature= 22;}
	}

	else if(smartCntDown>smartCnt_C) {

		if(SOLLtemperature > 0)

					{SOLLtemperature= -22;}

	}
}*/
void resetSmartCnt(void) {
	if(smartCntFlag) {
		smartCntFlag=0;
	}
	else {
	smartCntUp=0;
	smartCntDown=0;
	}
}
void checkHoldButton(void) {

	if(!__READ(PinSW)) {  			//if button is logical LOW

		holdCnt++;

	}

	else if(__READ(PinSW)) {

		holdCnt=0;

	}

	if(holdCnt>4)  {InitCALvars();} //this task is called every 800ms, for 3 sec we calculate a value ~ 4
}
