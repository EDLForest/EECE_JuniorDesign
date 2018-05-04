#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "Sensor.h"
#include "motor.h"

void leftTurn90(){
    leftTurn(0x7f);
    _delay_ms(2835);
}
void rightTurn90(){
    rightTurn(0x7f);
    _delay_ms(2835);
}

int main(){
    DDRC |= (1 << PC2 | 1 << PC0);
	DDRB |= (1 << PB5);

	init_motors();
	init_sensor();

	sei();

	// uint8_t side_threshold	 = 10;
	// uint8_t front_threshold  = 10;
	uint8_t countmain = 0;
    uint16_t CountDown = 0;
	uint8_t stuck = 0;

	while(CountDown < 750){


		int16_t sideDetect1  = distance_side1();
        int16_t sideDetect2  = distance_side2();
		int16_t frontDetect  = distance_front1();

		if(sideDetect1 <= 10 * 58 & sideDetect2 <= 10 * 58) PORTC |= (1 << PC0);
		else			PORTC &= ~(1 << PC0);

		if(frontDetect <= 10 * 58) PORTC |= (1 << PC2);
		else			PORTC &= ~(1 << PC2);


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
        //reliability will likely be compromised.
		if (stuck > 50){
			reverse(0x7F);
			_delay_ms(1000);
			stuck = 0;
		}

		if( frontDetect >= 12*58){
			if( sideDetect1 - sideDetect2 > 45*58){
				_delay_ms(700);
				while( sideDetect1 > 25*58)
				{
					rightTurn(0x8f);
					sideDetect1 = distance_side1();
				}
				stuck = 0;
				/*while((sideDetect1 - sideDetect2 > 30*58))//pivot right
				{
					rightmotor_forward(0x37);
					leftmotor_forward(0xAF);
					sideDetect1  = distance_side1();
					sideDetect2  = distance_side2();
					//_delay_ms(750);
				}*/
			}
			
            else if (sideDetect1 > 20 * 58){
                //turn right
                rightTurn(0x7F);
				stuck++;
            }
			
            else if(sideDetect1 > 12*58){
                //Bear Right
                rightmotor_forward(0x57);
                leftmotor_forward(0x8f);
				stuck = 0;
            }
            else if(sideDetect1 > 7*58){
                rightmotor_forward(0x8F);
                leftmotor_forward(0x57);
				stuck = 0;
            }
            else{
                leftTurn(0x87);
				stuck = 0;
            }
		}
		else {    //If the distance ahead is less than 10 cm
            if (sideDetect1 > 15 * 58){
                leftTurn(0x7f);
				stuck = 0;
            }
            else{
                leftTurn90();
				stuck = 0;
            }

        }

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
		
        CountDown = CountDown+1;

	}

    while(1){
        reverse(0x7f);
    }

}
