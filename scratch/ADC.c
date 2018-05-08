#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

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
//ADSRCB
#define ACME  6

// registers ACSR
#define ACBG 6
#define ACO 5
#define ACIE 3


int main(){

	_delay_ms(3000);

	//Select V ref as AVcc, ADCReg is right adjusted, Channel is ADC0,
	ADMUX  |= ((1 << REFS0) | (1 << ADLAR));
	//Enable ADC, set auto trigger, clk prescale: 8
	ADCSRA |= ((1 << ADEN) | (1 << ADATE) | (1 << ADPS1) | (1 << ADPS0));

	//set PORTC 1, 2, and 3 as output
	DDRC |= (1 << PC4 | 1 << PC3 | 1 << PC2 | 1 << PC1);

	// set PC0 as input
	DDRC &= ~(1 << 0);

	// start convertion
	ADCSRA |= (1 << ADSC);


	ACSR |= (1 << ACBG) | (1 << ACIE);

	uint8_t temp;
	uint8_t sum = 0;
	uint8_t counter = 0;
	uint8_t MetalCount = 0;
	uint8_t MetalDebCtr = 0;
	uint8_t MetalCtFlag = 0;

	while(1)
	{
		counter++;
		temp = ADCH;

		//If the most significant bit of the digital signal is high
		//increment the sum
		if(temp & (1 << 7)){
		   sum++;
		}

		//at 255 samples collected
		//If sum is more than half, then turn off the LED
		if(counter == 255){

		    if(sum & (1 << 7)){
				PORTC &= ~(1 << PC1);
				if(MetalCtFlag == 1){
					MetalCtFlag = 0;
				}
			}
		    else{
				if(MetalCtFlag == 0){
					MetalCount = MetalCount + 1;
					MetalCtFlag = 1;
				}

				PORTC |= (1 << PC1);
		    }
		   counter = 0;
		   sum = 0;
		}

		switch(MetalCount){
			case(0):	//00
				PORTC &= ~(1 << PC2);
				PORTC &= ~(1 << PC3);
				break;
			case(1):	//01
				PORTC |= (1 << PC2);
				PORTC &= ~(1 << PC3);
				break;
			case(2):	//10
				PORTC &= ~(1 << PC2);
				PORTC |= (1 << PC3);
				break;
			case(3):	//11
				PORTC |= (1 << PC2);
				PORTC |= (1 << PC3);
				break;
			case(4):
				PORTC |= (1 << PC4);
				break;
			default:
				break;
		}

	}


	return 0;
}
