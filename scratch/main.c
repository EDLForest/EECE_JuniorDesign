#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "Sensor.h"
#include "motor.h"


int main() {

	init_motors();
	init_sensor();
	sei();
	
	uint8_t side_threshold	 = 10;
	uint8_t front_threshold  = 10;
	
	while(1){
		
		
		bool sideDetect  = (find_distance_Left(side_threshold));
		bool frontDetect = (find_distance_Right(front_threshold));
		
		if(!sideDetect && !frontDetect){
			/* PORTC |= (1<<PC1); */
			rightTurn(0xAF);
		}
		else if( !sideDetect && frontDetect){
			/* PORTC &= ~(1<<PC1); */
			leftTurn(0xAF);
		}
		else if( sideDetect && !frontDetect){
			/* PORTC |= (1<<PC0); */
			forward(0xAF);
		}
		else if (sideDetect && frontDetect){
			leftTurn(0xAF);
		}
		else{
			reverse(0xAF);
		}
		
		
					

	}
	
    return 1;
}
