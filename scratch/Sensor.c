#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Sensor.h"

//Global Volatile variables that can be changed by interrupts
/* uint8_t distanceLeft = 0x00;
uint8_t distanceRight = 0x00; */
uint8_t flags = 0x00;
uint16_t front1 = 0x0000;
uint16_t front2 = 0x0000;
uint16_t side1  = 0x0000;
uint16_t side2  = 0x0000;



// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE, WE START THE COUNTER,
// SET THE FLAG TO ZERO. WAITING FOR THE FALLING EDGE
// AFTER THE FALLING EDGE, WE CALCULATE THE DISTANCE
ISR(INT0_vect){
	if(flags & (1 << SENSOR_FRONT1)) { TCNT1 = 0; }
	else  {	front1 = TCNT1;
	/* distanceLeft = (TCNT1)/ 58;  */}

	flags &= ~(1 << SENSOR_FRONT1);


	flags &= ~(1 << 0);
}
//
// ISR(INT1_vect){
// 	if(flags & (1 << SENSOR_FRONT2)) { TCNT1 = 0; }
// 	else  {	front2 = TCNT1;
// 	/* distanceLeft = (TCNT1)/ 58;  */}
//
// 	flags &= ~(1 << SENSOR_FRONT2);
//
//
// 	flags &= ~(1 << 0);
// }

//use PCINT17
ISR(PCINT2_vect){
	if(flags & (1 << SENSOR_SIDE1)) { TCNT1 = 0; }
	else { side1 = TCNT1;
	/* distanceRight = (TCNT1)/ 58; */ }

	flags &= ~(1 << SENSOR_SIDE1);
}

//use PCINT08
ISR(PCINT1_vect){
	if(flags & (1 << SENSOR_SIDE2)) { TCNT1 = 0; }
	else { side2 = TCNT1;
	/* distanceRight = (TCNT1)/ 58; */ }

	flags &= ~(1 << SENSOR_SIDE2);
}

void init_sensor(){
	// set PORTC 5,4,3 as Sensor trigger outputs
	DDRC |= (1 << PC5 | 1 << PC4 | 1 << PC3);
	// DDRB |= (1 << PB5 | 1 << PB4 | 1 << PB3 | 1 << PB2);

	TCCR1A = TCCR1A_config;
	TCCR1B = TCCR1B_config;

	PCICR  = PCICR_config;
	PCMSK2 = PCMSK2_config;
	PCMSK1 = PCMSK1_config;
	EIMSK  = EIMSK_config;
	EICRA  = EICRA_config;

	//ACSR &= ~(1 << 2);

	// enable global interrupt
	sei();
}

//use INT0
uint16_t distance_front1(){
	flags |= (1 << SENSOR_FRONT1);
	//threshold = 58 * threshold;

	//DISABLE external interrupt
	EIMSK  = 0x00;

	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << SENSOR_FRONT1);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << SENSOR_FRONT1);

	//ENABLE external interrupt at INT0
	EIMSK  = 0x01;

	_delay_ms(60);
	/**
	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	*	Interrupt is expected to fire twice, first time to reset
	*	The counter, second time to read the value of the counter
	*	and compute the distance.
	*/
	return front1;
}
//
// //Use INT1
// uint16_t distance_front2(){
// 	flags |= (1 << SENSOR_FRONT2);
// 	//threshold = 58 * threshold;
//
// 	//DISABLE external interrupt
// 	EIMSK  = 0x00;
//
// 	// send 50us pulse to sensors
// 	port(PORT,SENSOR_trig_port) |= (1 << SENSOR_FRONT2);
// 	_delay_us(50);
// 	port(PORT,SENSOR_trig_port) &= ~(1 << SENSOR_FRONT2);
//
// 	//ENABLE external interrupt at INT1
// 	EIMSK  = 0x02;
//
// 	_delay_ms(60);
// 	/**
// 	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
// 	*	Interrupt is expected to fire twice, first time to reset
// 	*	The counter, second time to read the value of the counter
// 	*	and compute the distance.
// 	*/
// 	return front2;
// }

//Use PCINT17
uint16_t distance_side1(){
	flags |= (1 << SENSOR_SIDE1);
	//threshold = 58 * threshold;

	//DISABLE external interrupt
	PCMSK2  = 0x00;

	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << SENSOR_SIDE1);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << SENSOR_SIDE1);

	//ENABLE Pin change external interrupt for PCINT17
	PCMSK2  = PCMSK2_config;

	_delay_ms(60);
	/**
	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	*	Interrupt is expected to fire twice, first time to reset
	*	The counter, second time to read the value of the counter
	*	and compute the distance.
	*/
	return side1;
}

//Use PCINT09
uint16_t distance_side2(){
	flags |= (1 << SENSOR_SIDE2);
	//threshold = 58 * threshold;

	//DISABLE external interrupt
	PCMSK1  = 0x00;

	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << SENSOR_SIDE2);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << SENSOR_SIDE2);

	//ENABLE Pin change external interrupt for PCINT08
	PCMSK1  = PCMSK1_config;

	_delay_ms(60);
	/**
	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	*	Interrupt is expected to fire twice, first time to reset
	*	The counter, second time to read the value of the counter
	*	and compute the distance.
	*/
	return side2;
}
