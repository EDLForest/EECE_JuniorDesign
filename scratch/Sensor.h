#ifndef __SENSOR4_H__
#define __SENSOR4_H__

#include <avr/io.h>
#include <stdint.h>
// #include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*Defining a concatenate function which will make our code more readable
Calling port(DDR,D) would concatenate DDR and the letter D to create DDRD
This makes our code more portable and reader friendly
as we only have to change the letter in the H file and it is changed everywhere else
*/
#define concat(type, letter) type##letter
#define port(type,letter) concat (type,letter)

//Defining the values for the control reg

//set clock no scaling
//set WGM = 4: CTC mode clear on OCR1A
#define TCCR1A_config 0x00
#define TCCR1B_config 0x01

//ENABLE external interrupt
#define EIMSK_config  0x01	//enable INT0 and INT1
#define PCICR_config  0x06	//enable PCIE2 and PCIE1
#define PCMSK2_config 0x02	//enable PCINT17
#define PCMSK1_config 0x02	//enable PCINT09

// interrupt to be fired
// DETECING BOTH RISING EDGE AND FALLING EDGE OF INT0 AND INTB
#define EICRA_config  		0x05
#define SENSOR_trig_port    C
#define SENSOR_FRONT1		5
// #define SENSOR_FRONT2		4
#define SENSOR_SIDE1		4
#define SENSOR_SIDE2		3

void init_sensor();
uint16_t distance_front1();
//uint16_t distance_front2();
uint16_t distance_side1();
uint16_t distance_side2();
#endif
