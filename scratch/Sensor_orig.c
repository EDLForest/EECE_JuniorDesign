#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Sensor.h"

uint16_t distance, distance2;
uint8_t flags;

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE , WE START THE COUNTER, WE WILL SET THE FLAG TO ZERO. WAITING FOR THE FLALING EDGE
// AFTER THE FALLING EDGE , WE GET THE DISTANCE 
ISR(INT0_vect){		
	if(flags & (1 << SENSOR_0_trig)){
		TCNT1 = 0;
	}else{
		distance = (TCNT1)/ 58;
	}
	

	flags &= ~(1 << SENSOR_0_trig);
	
}

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT1 
// ON THE RISING EDGE , WE START THE COUNTER, WE WILL SET THE FLAG TO ZERO. WAITING FOR THE FLALING EDGE
// AFTER THE FALLING EDGE , WE GET THE DISTANCE 
ISR(INT1_vect){	
	if(flags & (1 << SENSOR_1_trig)){
		TCNT1 = 0;
	}else{
		distance2 = (TCNT1)/ 58;
	}
		
	
	flags &= ~(1 << SENSOR_1_trig);
}

void init_sensor(){
	// set PORT5, PORT2 and PORT1 to outputs
	DDRC = (1 << PC5 | 1 << PC1 | 1 << PC0 | 1 << PC4);
  
	
	TCCR1A = TCCR1A_config;
	TCCR1B = TCCR1B_config;	
	EIMSK = EIMSK_config;
	EICRA = EICRA_config;
  
	ACSR &= ~(1 << 2);
  
	// enable global interrupt
	sei();
}

void find_distance(uint8_t sensor_num){
	flags |= (1 << sensor_num);
	
	//DISABLE external interrupt
	EIMSK  = 0x00;
	
	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << sensor_num);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << sensor_num);
	
	//ENABLE external interrupt
	EIMSK  = 0x03;
	
	_delay_ms(60);
	/**WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY**/
	
	//After the delay, check for the distance
	//TODO: define a new concatenation function like the one in the header
	//		to allow concatenation of word distance and number
	/* if ( concat(distance, sensor_num) < 10){
		PORTC |= (1 << SENSOR_0_out);
	}else{
		PORTC &= ~(1 << SENSOR_0_out);
	} */
}

int main() {
  
  init_sensor();
  
  while(1) {
	find_distance(SENSOR_0_trig);
	find_distance(SENSOR_1_trig);
	
	if (distance < 10){
		PORTC |= (1 << SENSOR_0_out);
	}else{
		PORTC &= ~(1 << SENSOR_0_out);
	}
	
	if (distance2 < 10){
		PORTC |= (1 << SENSOR_1_out);
	}else{
		PORTC &= ~(1 << SENSOR_1_out);
	}
  }

  return 0;

}