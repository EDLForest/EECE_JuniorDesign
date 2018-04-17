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

//Input: From metal detector ADC Pin 23
//Output: To Atmega, binary signal Pin 27 (metal detected = 0, none detected = 1)
//Reference Voltage = TBD, change count compare value based on chosen voltage

int main(){

	//Select V ref as AVcc, ADCReg is right adjusted, Channel is ADC0, 
	ADMUX  |= ((1 << REFS0) | (1 << ADLAR));
	//Enable ADC, set auto trigger, clk prescale: 8
	ADCSRA |= ((1 << ADEN) | (1 << ADATE) | (1 << ADPS1) | (1 << ADPS0));
	
	//set PORTC5 as output, set PINC0 as input
	DDRC |= (1 << 5);
	DDRC &= ~(1 << 0);
	ADCSRA |= (1 << ADSC);
	
	uint16_t count;
	uint8_t countavg;
	uint8_t i;
	while(1)
	{
		while(i < 20){
			count = count + ADCH;
			i++;
		}
		
		countavg = count/20;
		
		if( countavg & (1<<7) ){
			PORTC |= (1<<4);
		}
		else{
			PORTC &= ~(1<<4);
		}
		_delay_ms(1);
	}


	return 0;
}
