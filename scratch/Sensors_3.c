#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define STARTCOUNT 	7
#define SENSOR0		0
#define SENSOR1		1
#define SENSOR2		2

volatile uint16_t distance0, distance1, distance2;
uint8_t flags = 0x00;

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE , WE RESET THE COUNTER AND SET COUNTER FLAG TO ZERO.
// THEN WE WAITING FOR THE FALLING EDGE
// AFTER THE FALLING EDGE , WE CALCULATE THE DISTANCE
ISR(INT0_vect){

	if(flags & (1 << STARTCOUNT)){
		TCNT1 = 0;		//set counter to 0
	}else{

		switch (flags){
			case 0x01:
				distance0 = (TCNT1)/ 58;
				flags &= ~(1 << SENSOR0);
				break;
			case 0x02:
				distance1 = (TCNT1)/ 58;
				flags &= ~(1 << SENSOR1);
				break;
			case 0x04:
				distance2 = (TCNT1)/ 58;
				flags &= ~(1 << SENSOR2);
				break;
			default:
				//none of the sensor flag is on, do nothing
				break;
		}

	}


	flags &= ~(1 << STARTCOUNT);

}

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT1
// ON THE RISING EDGE , WE START THE COUNTER, WE WILL SET THE FLAG TO ZERO. WAITING FOR THE FLALING EDGE
// AFTER THE FALLING EDGE , WE GET THE DISTANCE
/* ISR(INT1_vect){
	if(flags & (1 << 1)){
		TCNT1 = 0;
	}else{
		distance2 = (TCNT1)/ 58;
	}


	flags &= ~(1 << 1);
} */

void find_distance0(){
	flags |= (1 << SENSOR0);
	flags |= (1 << STARTCOUNT);
	//DISABLE external interrupt
	EIMSK  = 0x00;

	// send 10us pulse to sensors
	PORTC |= (1 << PC5);
	_delay_us(50);
	PORTC &= ~(1 << PC5);

	//ENABLE external interrupt
	EIMSK  = 0x03;

	_delay_ms(60);

	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

void find_distance1(){
	flags |= (1 << SENSOR1);
	flags |= (1 << STARTCOUNT);

	//DISABLE external interrupt
	EIMSK  = 0x00;

	// send 10us pulse to sensors
	PORTC |= (1 << PC4);
	_delay_us(50);
	PORTC &= ~(1 << PC4);

	//ENABLE external interrupt
	EIMSK  = 0x03;

	_delay_ms(60);

	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

void find_distance2(){
	flags |= (1 << SENSOR2);
	flags |= (1 << STARTCOUNT);

	//DISABLE external interrupt
	EIMSK  = 0x00;

	// send 10us pulse to sensors
	PORTC |= (1 << PC3);
	_delay_us(50);
	PORTC &= ~(1 << PC3);

	//ENABLE external interrupt
	EIMSK  = 0x03;

	_delay_ms(60);

	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

int main() {

  // set PORTC 5-0 as output
  DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3 | 1 << PC2 | 1 << PC1 | 1 << PC0);
  //set PIND2 as input
  DDRD = (1 << PD2);		
  
  //set clock no scaling
  //set WGM = 4: CTC mode clear on OCR1A
  TCCR1A = 0x00;
  TCCR1B = 0x01;

  //ENABLE external interrupt for INT0
  EIMSK = 0x01;

  // interrupt to be fired
// DETECING BOTH RISING EDGE AND FALLING EDGE OF INT0 AND INT1
  EICRA = 0x01;

  // setting ACIC to 0
  ACSR &= ~(1 << 2);

  // enable global interrupt
  sei();


  while(1) {
	find_distance0();
	find_distance1();
	find_distance2();

	if (distance0 < 10){
		PORTC |= (1 << PC0);
	}else{
		PORTC &= ~(1 << PC0);
	}

	if (distance1 < 10){
		PORTC |= (1 << PC1);
	}else{
		PORTC &= ~(1 << PC1);
	}

	if (distance2 < 10){
		PORTC |= (1 << PC2);
	}else{
		PORTC &= ~(1 << PC2);
	}
  }

  return 0;

}
