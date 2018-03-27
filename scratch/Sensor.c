#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Sensor.h"
#include "externalVar.h"

uint16_t distanceLeft = 0xFFFF;
uint16_t distanceRight = 0xFFFF;
uint8_t flags;

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE, WE START THE COUNTER,
// SET THE FLAG TO ZERO. WAITING FOR THE FALLING EDGE
// AFTER THE FALLING EDGE, WE CALCULATE THE DISTANCE
ISR(INT0_vect){
	if(flags & (1 << SENSOR_Left_trig)) { TCNT1 = 0; }
	else  {	distanceLft = (TCNT1)/ 58;	}

	flags &= ~(1 << SENSOR_Right_trig);
}

ISR(INT1_vect){
	if(flags & (1 << SENSOR_1_trig)) { TCNT1 = 0; }
	else { distanceRight = (TCNT1)/ 58; }

	flags &= ~(1 << SENSOR_1_trig);
}

void init_sensor(){
	// set PORT5, PORT2 and PORT1 to outputs
	DDRC = (1 << PC5 | 1 << PC1 | 1 << PC0 | 1 << PC4);

	TCCR1A = TCCR1A_config;
	TCCR1B = TCCR1B_config;
	EIMSK  = EIMSK_config;
	EICRA  = EICRA_config;

	ACSR &= ~(1 << 2);

	// enable global interrupt
	sei();
}

void find_distance(uint8_t trigger_port_num){
	flags |= (1 << sensor_num);

	//DISABLE external interrupt
	EIMSK  = 0x00;

	// send 50us pulse to sensors
	port(PORT,SENSOR_trig_port) |= (1 << trigger_port_num);
	_delay_us(50);
	port(PORT,SENSOR_trig_port) &= ~(1 << trigger_port_num);

	//ENABLE external interrupt
	EIMSK  = 0x03;

	_delay_ms(60);
	/**
	*	WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	*	Interrupt is expected to fire twice, first time to reset
	*	The counter, second time to read the value of the counter
	*	and compute the distance.
	*/
}
