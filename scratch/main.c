#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <math.h>

#include "Sensor.h"
#include "motor.h"

void leftTurn90(){
    leftTurn(0x7f);
    _delay_ms(2735);
}

void rightTurn90(){
    rightTurn(0x7f);
    _delay_ms(2735);
}

int main() {

    _delay_ms(4000);

	DDRC |= (1 << PC2 | 1 << PC0);
    DDRB |= (1 << PB5);

	init_motors();
	init_sensor();

	sei();

	// uint8_t side_threshold	 = 10;
	// uint8_t front_threshold  = 10;
	uint8_t countmain = 0;
    uint16_t CountDown = 0;

	while(CountDown < 750){


		int16_t sideDetect1  = distance_side1();
        int16_t sideDetect2  = distance_side2();
		int16_t frontDetect  = distance_front1();

		if(sideDetect1 <= 10 * 58) PORTC |= (1 << PC0);
		else			PORTC &= ~(1 << PC0);

		if(sideDetect2 <= 10 * 58) PORTC |= (1 << PC2);
		else			PORTC &= ~(1 << PC2);

        if(frontDetect <= 10 * 58) PORTB |= (1 << PB5);
		else			PORTB &= ~(1 << PB5);


        //First, need to navigate the four corner
        //Hug the wall, remember the numbers of corners turned
        //need to right turn 4 times, each left turn decrement a counter,
        //each right turn increment the counter. When counter hits 0,
        //Wait for a little bit to make sure it is not an obstacle.

        //Then Switch operating mode to zigzag, which the rover will make
        //and u-turn  when hit a wall and repeat.
        //or
        //Spiral: the rover will slowly increase the sensor distance and it
        // goes through a 4 turn cycle. But toward the center, the sensor's
        //reliability will likely be conpromised.


		if( frontDetect >= 10*58){
			if(sideDetect1 >= 20*58 && sideDetect2 >= 20*58){
                		rightTurn(0x7f);
			}
			//if we are out in the open turn right. Can effect turns around obstacles

            		else if( sideDetect1 - sideDetect2 > 30*58){
               			//pivot right
                		_delay_ms(500);
                		rightmotor_brake();
                		leftmotor_forward(0x87);
              			_delay_ms(2350);
           		}
			//Used to get around the end of an obstacle
			//This was our issue when using only 2 sensors
			//Why dont we just add this to original code?

			else if( (sideDetect1 - sideDetect2) > 2*58 ){
                		//Bear right
				rightmotor_forward(0x47);
				leftmotor_forward(0x7F);
			}
			//Side1 is farther from the wall than Side2, adjust
			//We can either enter a loop when turn detected or
			//alter this part of code to avoid right turning in corners

           		else if( (sideDetect2 - sideDetect1) > 2*58 ){
                		//Bear left
				leftmotor_forward(0x47);
				rightmotor_forward(0x7F);
			}
			//Side2 is farther from the wall than Side1, adjust

			else{
				forward(0x7F);
			}
			//Something weird is happening
		}
	else {    //If the distance ahead is less than 10 cm

            leftTurn(0x7f);
            _delay_ms(1550);
            while( abs(sideDetect1-sideDetect2) > 3*58 ){
            	sideDetect1  = distance_side1();
            	sideDetect2  = distance_side2();
            	leftTurn(0x7F);
            }
	//Front is close to a wall, we need to turn. Midway through the turn, the sensors are farther from the wall and adjust
	//To fix, once a corner is detected, do not stop turning left until both side sensors have lined up again

			// if(sideDetect1 >= 15 * 58 && sideDetect2 >= 15*58){
			// 	leftTurn(0x7F);
            //     _delay_ms(500);
			// }
            // else if(sideDetect1 >= 5 * 58){
			// 	leftTurn(0x7F);
			// }
			// else{
			// 	leftTurn(0x6f);
			// }
		}
        CountDown = CountDown+1;

	}

    while(1){

        reverse(0x7f);
    }

    return 1;
}
