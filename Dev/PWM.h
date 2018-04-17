
#ifndef __PWM_H__
#define __PWM_H__

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

//Configuration for the counters
//Set WGM(2:0) 	= 3 Fast FWM with TOP as FF
//Set COM0A(1:0) 	= 2 Clear OC0A on compare match, Set on BOTTOM
//Set CS(2:0)	= 1 Use clock with no Pre-scaling
#define TCCR0A_config 0xA3
#define TCCR0B_config 0x01
#define TCCR2A_config 0xA3
#define TCCR2B_config 0x01


//These function will set the PWM output
//For the corresponding input on H-bridge
void A1_setPWM(uint8_t value);
void A2_setPWM(uint8_t value);
void B1_setPWM(uint8_t value);
void B2_setPWM(uint8_t value);

void init_PWM();

#endif
