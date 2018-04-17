#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <avr/io.h>
#include <stdint.h>
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
#define EIMSK_config  0x01
#define PCICR_config  0x04	//enable PCIE2 and PCIE1
#define PCMSK2_config 0x02	//enable PCINT17
#define PCMSK1_config 0x40	//enable PCINT14

// interrupt to be fired
// DETECING BOTH RISING EDGE AND FALLING EDGE OF INT0 AND INTB
#define EICRA_config  0x05
#define Start_Counter 		1
#define SENSOR_trig_port    C
#define SENSOR_Left_trig	5
#define SENSOR_Right_trig	4

void init_sensor();
uint8_t find_distance_Left();
uint8_t find_distance_Right();
#endif
