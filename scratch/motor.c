#include "motor.h"
#include "PWM.h"

void init_motors (){
    //The output port are set in the PWM module
    //so to initialize, just call init_PWM
	init_PWM();
    brake();

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

void rightmotor_forward(uint8_t speed){
    A1_setPWM(0xFF);
    A2_setPWM(0xFF - speed);
}

void leftmotor_forward(uint8_t speed){
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


void forward(uint8_t speed){
	leftmotor_forward(speed);
	rightmotor_forward(speed);
}
void rightTurn(uint8_t speed){
	leftmotor_forward(speed);
	rightmotor_reverse(speed);
}
void leftTurn(uint8_t speed){
	leftmotor_reverse(speed);
	rightmotor_forward(speed);
}
void reverse(uint8_t speed){
	leftmotor_reverse(speed);
	rightmotor_reverse(speed);
}
void brake(){
    leftmotor_brake();
    rightmotor_brake();
}
