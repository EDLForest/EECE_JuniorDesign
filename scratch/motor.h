/**
* Driver functions for the  Dagu Rover 5
* Created  by I.Sekyonda 2016
*For Atmega328 on PapilioDUO
*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/*Defining a concatinate function which will make our code more readable
Calling port(DDR,D) would concatinate DDR and the letter D to create DDRD
This makes our code more portable and reader friendly
as we only have to change the letter in the H file and it is changed everywhere else
*/
// #define concat(type, letter) type##letter
// #define port(type,letter) concat (type,letter)


/*Defining the Port Letters and locations for the Left motor. Change
Change these to match your locations*/
// #define leftmotorport 	B
// #define leftmotora 		5
// #define leftmotorb 		4
// #define leftquadport 	B
// #define leftquada 		7
// #define leftquadb 		0

/*Defining the Port Letters and locations for the Right motor
Change these to match your locations*/
// #define rightmotorport 	B
// #define rightmotora 	2
// #define rightmotorb 	1
// #define rightquadport 	B
// #define rightquada 		5
// #define rightquadb 		6


void init_motors();

void leftmotor_foward(uint8_t speed);
void leftmotor_reverse(uint8_t speed);
void leftmotor_brake();
void leftmotor_coast();

void rightmotor_foward(uint8_t speed);
void rightmotor_reverse(uint8_t speed);
void rightmotor_brake();
void rightmotor_coast();

void brake();
// uint8_t leftquad_value();
// uint8_t rightquad_value();


#endif
