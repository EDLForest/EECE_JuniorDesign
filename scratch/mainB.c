#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "Sensor.h"
#include "motor.h"

void leftTurn90(){
    leftTurn(0x9f);
    _delay_ms(2635);
}
void rightTurn90(){
    rightTurn(0x9f);
    _delay_ms(2635);
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
	int16_t offWall = 0;

	while(1){

		int16_t sideDetect1  = distance_side1();
        int16_t sideDetect2  = distance_side2();
		int16_t frontDetect  = distance_front1();

		if(sideDetect1 <= 10 * 58 & sideDetect2 <= 10 * 58) PORTC |= (1 << PC0);
		else			PORTC &= ~(1 << PC0);

		if(frontDetect <= 10 * 58) PORTC |= (1 << PC2);
		else			PORTC &= ~(1 << PC2);

		
		if (stuck > 20){
			reverse(0x9F);
			_delay_ms(1000);
			stuck = 0;
		}
		if (sideDetect2 <= (5* 58 + offWall)){
				rightTurn90();
		}
		if (sideDetect1 <= (5* 58 + offWall)){
				leftTurn90();
		}
		if( frontDetect >= 12*58 + offWall){
			/*
			if( sideDetect1 - sideDetect2 > (45*58 + offWall)){
				_delay_ms(700);
				while( sideDetect1 > 25*58 + offWall)
				{
					rightTurn(0x9f);
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
				}
			}//worst case scenario protocol, exchange pivot and right turn for forward
			*/
			
            if (sideDetect1 > (20 * 58 + offWall)){
				forward(0x9F);
				stuck = 0;
            }
			
             else if(sideDetect1 > (12*58 + offWall)){
                //Bear Right
                rightmotor_forward(0x67);
                leftmotor_forward(0x9f);
				stuck = 0;
            }
            else if(sideDetect1 > (7*58 + offWall)){
                rightmotor_forward(0x9F);
                leftmotor_forward(0x67);
				stuck = 0;
            }

            else{
                leftTurn90();
				stuck = 0;
            }
		}
		else {    //If the distance ahead is less than 10 cm
            if (sideDetect1 > (15 * 58 + offWall)){
                leftTurn90();
				stuck = 0;
            }
			else if(sideDetect2 > (12*58 + offWall)){
					rightTurn90();
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
		
		if (CountDown == 500){
			offWall = 20*58;
			reverse(0x8F);
			_delay_ms(500);
		}
		if (CountDown == 750){
			offWall = 40*58;
			reverse(0x8F);
			_delay_ms(500);
		}
		if (CountDown == 1000){
			offWall = 60*58;
			reverse(0x8F);
			_delay_ms(500);
		}
	}


}
