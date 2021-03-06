// MACROS FOR EASY PIN HANDLING FOR ATMEL GCC-AVR
#ifndef _PINMACROS_H_
#define _PINMACROS_H_
//these macros are used indirectly by other macros , mainly for string concatination
#include <avr/io.h>
#include <stdint.h>

typedef enum { false, true } bool;
#define _SET(type,name,bit)          type ## name  |= _BV(bit)
#define _CLEAR(type,name,bit)        type ## name  &= ~ _BV(bit)
#define _TOGGLE(type,name,bit)       type ## name  ^= _BV(bit)
#define _GET(type,name,bit)          ((type ## name >> bit) &  1)
#define _PUT(type,name,bit,value)    type ## name = ( type ## name & ( ~ _BV(bit)) ) | ( ( 1 & (unsigned char)value ) << bit )

//these macros are used by end user
#define __OUTPUT(pin)         _SET(DDR,pin)
#define __INPUT(pin)          _CLEAR(DDR,pin)
#define __HIGH(pin)           _SET(PORT,pin)
#define __LOW(pin)            _CLEAR(PORT,pin)
#define __TOGGLE(pin)         _TOGGLE(PORT,pin)
#define __READ(pin)           _GET(PIN,pin)

#define RED_LED C,1		  //PIN A1 at Arduino UNO/Duemilanove
#define GREEN_LED C,2	  //PIN A2 at Arduino UNO/Duemilanove
#define BLUE_LED C,0      //PIN A0 at Arduino UNO/Duemilanove
#define RELAY_PIN D,6     //PIN 06 at Arduino UNO/Duemilanove
//SPI Port definitions
#define PORT_SPI    PORTB
#define DDR_SPI     DDRB
#define DD_MISO     DDB4  // PIN 12 at Arduino UNO/Duemilanove
#define DD_MOSI     DDB3  // PIN 11 at Arduino UNO/Duemilanove
#define DD_SCK      DDB5  // PIN 13 at Arduino UNO/Duemilanove
#define SSPin B,2         // PIN 10 at Arduino UNO/Duemilanove
//Temperature chip select pin
#define Sensor_SS       D,5 // PIN 5 at Arduino UNO/Duemilanove
// Rotary encoder pins
#define PinCLK D,2        // Used for generating interrupts using CLK signal, PIN 2 at Arduino UNO/Duemilanove
#define PinDT D,5         // Used for reading DT signal, PIN 4 at Arduino UNO/Duemilanove
#define PinSW D,3 		  // Used for generating interrupts when the button is pressed,PIN 3 at Arduino UNO/Duemilanove
#define pinCLKDIS D,7     // PIN 07 at Arduino UNO/Duemilanove
#define pinDIO B,0		  // PIN 08 at Arduino UNO/Duemilanove
#endif
