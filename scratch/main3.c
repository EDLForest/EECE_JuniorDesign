#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <math.h>

#include "Sensor.h"
#include "motor.h"

void leftTurn90(){
    leftTurn(0x8f);
    _delay_ms(2835);
}
void rightTurn90(){
    rightTurn(0x8f);
    _delay_ms(2835);
}

int main(){

	init_motors();
	init_sensor();

	sei();

    while(1){

        int16_t sideDetect1  = distance_side1();
        int16_t sideDetect2  = distance_side2();
		int16_t frontDetect  = distance_front1();

        //move forward
        if (frontDetect >= 10){
            leftmotor_forward(0xAF);
            rightmotor_forward(0xAF);
        }
        else{
            while( abs(sideDetect1 - sideDetect2) > 30){
                //leftTurn until both side Sensor are parallel with the wall
                leftTurn(0x8f);
                sideDetect1  = distance_side1();
                sideDetect2  = distance_side2();
            }

            // _delay_ms(100);
            // leftmotor_forward(0xAF);
            // rightmotor_forward(0xAF);
            // _delay_ms(100);
            // leftTurn90();
        }


    }

    return 0;
}
