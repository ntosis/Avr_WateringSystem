#include <avr/io.h>
#include <avr/delay.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include "math.h"
#include "RtrEncdBtn.h"
#include "timerInterrupt.h"
#include "heatingSys.h"
#include "u8g.h"
#include <avr/pgmspace.h>
#include <eeprom_calib.h>
#include <stdio.h>
#include <OLED_graphics.h>
#include "flowsensor.h"
//#include "pinmacros.h"


void task_800ms(void);
void task_700ms(void);
void task_200ms(void);
void task_500ms(void);
void task_1min(void);
void task_1sec(void);
void task_1x5sec(void);
void displayController(void);
void commandToRelay(void);
void u8g_setup(void);
void draw(void);
void drawTime(void);
extern bool WaterTimeEnabled;
void showDebugInfo(void);
void showTimeNow(void);

extern u8g_t u8g;



char buf[80];

int main(void)
{
	cli();
	//set the day
		uint8_t dd = dec2bcd((uint8_t)1);
		i2c_writeReg(ds1307_adr,0x03,&dd,1);
	wdt_disable();
	__OUTPUT(RELAY_PIN); /* Init disable pump */
	__HIGH(RELAY_PIN);
	LoadCALvars(); /* Load eeprom variables*/
	increaseResetCounter();
	_delay_ms(20);
	//initRtrEncoder();
	u8g_setup();
	timerInit();
	initTimer0Counter();
	initWaterConsumption();
	// set up the task list
    initScheduler();
	// add tasks, id is arbitrary
	// task1 runs every 800ms second
	addTask(1,task_800ms, 8);
	// task2 runs every 700ms seconds
	addTask(2,task_700ms,7);
	// task3 runs every 1 seconds
	addTask(3, task_1sec, 10);
	// task4 runs every 1.5 seconds
	addTask(4, task_1x5sec,15);
	//task5
	addTask(5, task_500ms, 5);
	//task 6 autoProgram runs every a min
	addTask(6,task_1min,600);
	//send command to relay
	addTask(7, task_200ms,2);
	//enable Watch dog
	wdt_enable(WDTO_1S);
	//enable interrupts
	sei();
  while(1)
  {
	  	  //Task manager runs
	      dispatchTasks();

  }
}
void task_200ms(void) {
wdt_reset();
}

void task_500ms(void) {
	autoProgram();
}

void task_1min(void) {
	storeWaterFlowinEEP();
	resetTriesFlag=1;
}

void task_700ms(void) {
}

void task_800ms(void) {
	checkHoldButton(); //inline function to check hold buton.();
}
void task_1sec(void) {
	readFlowSensorFreq();
	calcWaterFlow();
	commandToRelay();
	checkErrors();


}
void task_1x5sec(void) {
	displayController();
}


//The pin have to be HIGH to turn off the heating system
void commandToRelay() {
	if(WaterTimeEnabled&&(ErrorCodes==0)) {
		__LOW(RELAY_PIN);
	}
	//If the Thermostat is in OFF state means that we have two turn off the heating system completely.
	else {
		__HIGH(RELAY_PIN);
	}
}
void displayController() {
/*	static uint8_t count=0;
	count++;
	switch(count) {
	case 1:
		if(1) { showDebugInfo(); }
		break;
	case 3:
		showTimeNow();
		break;
		}
	if(count==4) count=0;*/
	showDebugInfo();
}

void u8g_setup(void)
{
  _delay_ms(5);
  u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x64_i2c, U8G_I2C_OPT_FAST);
}
void draw(void)
{
  u8g_SetFont(&u8g, u8g_font_6x10);
  sprintf_P(buf,PSTR("WaterPumpIsOn= %u"),WaterTimeEnabled);
  u8g_DrawStr(&u8g, 0,10,buf);
  sprintf_P(buf,PSTR("SnsrFq %d Hz"),freq);
  u8g_DrawStr(&u8g, 0,20,buf);
  sprintf_P(buf,PSTR("WtrFlow %2.2fL/min"),calcflow);
  u8g_DrawStr(&u8g, 0,30,buf);
  sprintf_P(buf,PSTR("Wtr cnsump. %2.2fLiter"),waterConsumption);
  u8g_DrawStr(&u8g, 0,40,buf);
  char binary[12];
  itoa (ErrorCodes,binary,2);
  sprintf_P(buf,PSTR("Error= %s"),binary);
  u8g_DrawStr(&u8g, 0,50,buf);
  sprintf_P(buf,PSTR("Resets= %d"),readEEResets());
  u8g_DrawStr(&u8g, 0,60,buf);


  u8g_SetFont(&u8g,u8g_font_9x18r);
  sprintf_P(buf,PSTR("%d:%02d"),GetHH(),GetMM());
  u8g_DrawStr(&u8g, 65,60,buf);
}
void showDebugInfo(void) {
	u8g_FirstPage(&u8g);
		    do
		    {
		      draw();
		    } while ( u8g_NextPage(&u8g) );
}
void showTimeNow(void) {
	u8g_FirstPage(&u8g);
			    do
			    {
			      drawTime();
			    } while ( u8g_NextPage(&u8g) );
}
void drawTime(void){

	u8g_SetFont(&u8g,u8g_font_9x18r);
	sprintf_P(buf,PSTR("%d:%02d"),GetHH(),GetMM());
	u8g_DrawStr(&u8g, 15,15,buf);

	u8g_SetFont(&u8g,u8g_font_9x18r);
	sprintf_P(buf,PSTR("%02d/%02d/%4d"),GetDD(),GetMonth(),2000+GetYY());
	u8g_DrawStr(&u8g, 15,30,buf);

}


