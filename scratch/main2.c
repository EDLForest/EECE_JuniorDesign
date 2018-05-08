#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "Sensor.h"
#include "motor.h"

void leftTurn90()
{
    leftTurn(0x7f);
    _delay_ms(2500);
}
void rightTurn90()
{
    rightTurn(0x7f);
    _delay_ms(2835);
}

int main()
{
    _delay_ms(3000);

    DDRC |= (1 << PC2 | 1 << PC0);
	DDRB |= (1 << PB5);

	init_motors();
	init_sensor();

	sei();

    uint16_t CountDown = 0;
	uint16_t CountDown2 = 0;
	int16_t offWall = 0;

	while(1){

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


		int16_t sideDetect1  = distance_side1();
        int16_t sideDetect2  = distance_side2();
		int16_t frontDetect  = distance_front1();


		if(sideDetect1 <= 10 * 58 && sideDetect2 <= 10 * 58) PORTC |= (1 << PC0);
		else			PORTC &= ~(1 << PC0);

		if(frontDetect <= 10 * 58) PORTC |= (1 << PC2);
		else			PORTC &= ~(1 << PC2);



		if( frontDetect >= 12*58 + offWall){
			if( sideDetect1 - sideDetect2 > (45*58 + offWall)){
				_delay_ms(700);
				while( sideDetect1 > 25*58 + offWall && frontDetect > 10*58){
					forward(0xAF);
					sideDetect1 = distance_side1();
                    frontDetect = distance_front1();
				}
			}
			else if(sideDetect1 > (15*58 + offWall)){
				//Bear Right
				rightmotor_forward(0x67);
				leftmotor_forward(0x9f);
			}
			else if(sideDetect1 > (10*58 + offWall)){
				rightmotor_forward(0x9F);
				leftmotor_forward(0x67);
			}
			else{
				leftTurn90();
			}

		}


		else {    //If the distance ahead is less than 10 cm
			if (sideDetect1 > (15 * 58 + offWall)){
				leftTurn90();
			}
			else{
				leftTurn90();
			}
		}

	}


}
