/**
* Driver functions for the DAGU Rover 5
* Created by Haosen Zheng 2018
* For Atmega328 micro processor
* Include  motor.h in your main.c file and you can call these functions
*/
#include "motor.h"
#include "PWM.h"


void init_motors (){
    //The output port are set in the PWM module
    //so 
    break();

}

void rightmotor_reverse(uint8_t speed){
    A1_setPWM(0xFF - speed);
    A2_setPWM(0xFF);
}

void leftmotor_reverse(uint8_t speed){
    B1_setPWM(0xFF - speed);
    B2_setPWM(0xFF);
}

void rightmotor_brake(){
    A1_setPWM(0xFF);
    A2_setPWM(0xFF);
}

void leftmotor_brake(){
    B1_setPWM(0xFF);
    B2_setPWM(0xFF);
}

void rightmotor_foward(uint8_t speed){
    A1_setPWM(0xFF);
    A2_setPWM(0xFF - speed);
}

void leftmotor_foward(uint8_t speed){
    B1_setPWM(0xFF);
    B2_setPWM(0xFF - speed);
}

void rightmotor_coast(){
    A1_setPWM(0x00);
    A2_setPWM(0x00);
}

void leftmotor_coast(){
    B1_setPWM(0x00);
    B2_setPWM(0x00);
}

void brake(){
    leftmotor_brake();
    rightmotor_brake();
}
