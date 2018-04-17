#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//ADMUX
#define REFS1 7
#define REFS0 6
#define ADLAR 5
//ADCCSRA
#define ADEN  7
#define ADSC  6
#define ADATE 5
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0


int main(){

	//Select V ref as AVcc, ADCReg is right adjusted, Channel is ADC0, 
	ADMUX  |= ((1 << REFS0) | (1 << ADLAR));
	//Enable ADC, set auto trigger, clk prescale: 8
	ADCSRA |= ((1 << ADEN) | (1 << ADATE) | (1 << ADPS1) | (1 << ADPS0));
	
	//set PORTC5 as output, set PINC0 as input
	DDRC |= (1 << 5);
	DDRC &= ~(1 << 0);
	ADCSRA |= (1 << ADSC);
	
	uint8_t count;
	while(1)
	{
		count = ADCH;		
		if( count & (1<<7) ){
			PORTC |= (1<<5);
		}
		else{
			PORTC &= ~(1<<5);
		}
		_delay_ms(1);
	}


	return 0;
}
