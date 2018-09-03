#include "flowsensor.h"
#include "timerInterrupt.h"
#include "heatingSys.h"
#include "eeprom_calib.h"



volatile uint16_t overflows=0;
uint16_t freq=0;
float waterConsumption =0;
float calcflow =0;
const uint8_t maxWaterConsumption = 200; // Liter
uint8_t ErrorCodes=0;
uint8_t resetTriesFlag=0;


flowsensor2dtable_t lookuptable[7] =
{
    {0, 0},
    {16, 2},
    {32.5, 4},
    {49.3, 6},
    {65.5,8},
    {82,10},
    {90.1,12}
};

float interpolation( flowsensor2dtable_t* c, float x, uint8_t n )
{
	uint8_t i;

    for( i = 0; i < n-1; i++ )
    {
        if ( c[i].freq <= x && c[i+1].freq >= x )
        {
        	ErrorCodes &= ~ (1<< FLOWSENSORERROR); /* Clear sensor error*/
            double diffx = x - c[i].freq;
            double diffn = c[i+1].freq - c[i].freq;

            return c[i].flow + ( c[i+1].flow - c[i].flow ) * diffx / diffn;
        }
    }

    ErrorCodes |= 1<< FLOWSENSORERROR;
    return 0; // Not in Range
}

void initTimer0Counter(void) {

	  DDRD &= ~(1 << DDD4);     // Clear the PD4 pin
	  // PD4 is now an input

	  PORTD |= (1 << PORTD4);   // turn On the Pull-up
	  // PD4 is now an input with pull-up enabled

	  /* Reset all registers*/
	  TCCR0B =0;TCCR0A=0;TCNT0=0;TIMSK0=0;TIFR0=0;

	  TIMSK0 |= (1 << TOIE0);    // enable timer interrupt

	  TCCR0B |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	  // Turn on the counter, Clock on Risf
}
void initWaterConsumption(void) {

	readEEWaterConsumption(&waterConsumption);

}
void readFlowSensorFreq(void){
	 static uint16_t events_prv;
	 static uint16_t time_prv=0;

	 uint16_t time_now_MS=GlobalCounterInMS;

	 uint16_t events = (overflows * 255) + TCNT0;
	if(time_now_MS==time_prv){
		sensorTimerErrorFlag=1; /* Sensor Error*/
	}
	else {
		freq = (events-events_prv);
		sensorTimerErrorFlag=0; /* Sensor Ok*/
	}
	   events_prv=events;
	   time_prv=time_now_MS;
}
/* call this function every second*/
void calcWaterFlow(void) {

calcflow = interpolation(lookuptable,freq,7);

waterConsumption += ((calcflow)/60);
setWaterConsumption(waterConsumption);


}
void storeWaterFlowinEEP(void) {
	static uint8_t counter=0;
	/* this function runs every 1min, use the counter to store every 4min the values in eeprom*/
	if(WaterTimeEnabled){
		SaveCALvars();
	}
	else if(counter>4){
		SaveCALvars();
		counter=0; /*reset counter*/
	}
	counter++; /*increase counter*/
}
void checkErrors(void) {
	static uint16_t tmNow=0;
	static uint8_t tries=0;

	if(resetTriesFlag==1) { /*Task 1 second triggert a reset*/
		resetTriesFlag=0;
		tries=0;

	}
	if(waterConsumption>maxWaterConsumption) {
		ErrorCodes |= 1<< MAXWATERCONSUMPTIONERROR;
	}
	else if((WaterTimeEnabled)&&(calcflow==0)&&((GlobalCounterInMS)-tmNow>3000)){

		ErrorCodes |= 1<< NOWATER;
		tmNow = GlobalCounterInMS;
	}
	else if((WaterTimeEnabled)&&(calcflow==0)&&(((GlobalCounterInMS)-tmNow<3000))) {

		tries++;
		if(tries<6) ErrorCodes &= ~ (1<< NOWATER);

	}
	else if(sensorTimerErrorFlag==1) {
		ErrorCodes |= 1<< SENSORERROR;
	}
	else if(sensorTimerErrorFlag==0) {
		ErrorCodes &= ~ (1<< SENSORERROR);
		}

}

ISR(TIMER0_OVF_vect){
	overflows++;
}
