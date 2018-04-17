#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "Sensor.h"
#include "motor.h"
#include "externalVar.h"

int main() {

	init_motors();
	init_sensor();
	sei();
	
	uint8_t distance_Right = 0;
	uint8_t distance_Left = 0;
	
	while(1){
		distance_Left = find_distance_Left();
		distance_Right = find_distance_Right();
		
		if(distance_Right < 10){
			PORTC |= (1<<PC1);
			leftmotor_brake();
		}
		else{
			PORTC &= ~(1<<PC1);
			leftmotor_reverse(0x7F);
		}
		
		if(distance_Left < 10){
			PORTC |= (1<<PC0);
			rightmotor_brake();
		}
		else{
			PORTC &= ~(1<<PC0);
			rightmotor_forward(0xBF);
		}
		
		
					

	}
	
    return 1;
}
