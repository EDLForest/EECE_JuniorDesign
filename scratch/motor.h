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

void init_motors();

void leftmotor_foward(uint8_t speed);
void leftmotor_reverse(uint8_t speed);
void leftmotor_brake();
void leftmotor_coast();

void rightmotor_foward(uint8_t speed);
void rightmotor_reverse(uint8_t speed);
void rightmotor_brake();
void rightmotor_coast();

void forward(uint8_t speed);
void rightTurn(uint8_t speed);
void leftTurn(uint8_t speed);
void reverse(uint8_t speed);
void brake();


#endif
