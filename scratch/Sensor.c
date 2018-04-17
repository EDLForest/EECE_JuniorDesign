#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Sensor.h"

//Global Volatile variables that can be changed by interrupts
uint8_t distanceLeft = 0x00;
uint8_t distanceRight = 0x00;
uint8_t flags = 0x00;
uint16_t Sensor_value=0x0000;

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE, WE START THE COUNTER,
// SET THE FLAG TO ZERO. WAITING FOR THE FALLING EDGE
// AFTER THE FALLING EDGE, WE CALCULATE THE DISTANCE
ISR(INT0_vect){
	if(flags & (1 << SENSOR_Left_trig)) { TCNT1 = 0; }
	else  {	Sensor_value = TCNT1;
	/* distanceLeft = (TCNT1)/ 58;  */}

	flags &= ~(1 << SENSOR_Left_trig);
	

	flags &= ~(1 << 0);
}

ISR(PCINT2_vect){
	if(flags & (1 << SENSOR_Right_trig)) { TCNT1 = 0; }
	else { Sensor_value = TCNT1;
	/* distanceRight = (TCNT1)/ 58; */ }

	flags &= ~(1 << SENSOR_Right_trig);
}

void init_sensor(){
	// set PORT5, PORT2 and PORT1 to outputs
	DDRC |= (1 << PC5 | 1 << PC1 | 1 << PC0 | 1 << PC4);

	TCCR1A = TCCR1A_config;
	TCCR1B = TCCR1B_config;
	
	PCICR = PCICR_config;
	PCMSK2 = PCMSK2_config;
	PCMSK1 = PCMSK1_config;
	EIMSK  = EIMSK_config;
	EICRA  = EICRA_config;

	ACSR &= ~(1 << 2);

	// enable global interrupt
	sei();
}
//use INT0
bool find_distance_Left(uint16_t threshold){
	flags |= (1 << SENSOR_Left_trig);
	threshold = 58 * threshold;
	
	//DISABLE external interrupt
	EIMSK  = 0x00;

	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << SENSOR_Left_trig);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << SENSOR_Left_trig);

	//ENABLE external interrupt
	EIMSK  = 0x01;

	_delay_ms(60);
	/**
	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	*	Interrupt is expected to fire twice, first time to reset
	*	The counter, second time to read the value of the counter
	*	and compute the distance.
	*/
	return Sensor_value <= threshold;
}

//Use PCINT17
bool find_distance_Right(uint16_t threshold){
	flags |= (1 << SENSOR_Right_trig);
	threshold = 58 * threshold;

	//DISABLE external interrupt
	PCMSK2  = 0x00;

	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << SENSOR_Right_trig);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << SENSOR_Right_trig);

	//ENABLE Pin change external interrupt
	PCMSK2  = 0x02;

	_delay_ms(60);
	/**
	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	*	Interrupt is expected to fire twice, first time to reset
	*	The counter, second time to read the value of the counter
	*	and compute the distance.
	*/
	return Sensor_value < threshold;
}
