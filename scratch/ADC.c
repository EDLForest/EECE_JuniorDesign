#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "ADC.h"

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

void init_ADC();
void detect_Metal();

//Input: From metal detector ADC Pin 23
//Output: To Atmega, binary signal Pin 27 (metal detected = 0, none detected = 1)
//	      To FPGA, pulse from pin 28 (to be processed in order to increment the counter)
//Reference Voltage = TBD, change count compare value based on chosen voltage
uint16_t temp, sum = 0, counter=0;
void init_ADC(){
		//Select V ref as AVcc, ADCReg is right adjusted, Channel is ADC0,
	ADMUX  |= ((1 << REFS0) | (1 << ADLAR));
	//Enable ADC, set auto trigger, clk prescale: 8
	ADCSRA |= ((1 << ADEN) | (1 << ADATE) | (1 << ADPS1) | (1 << ADPS0));

	//set PORTC3 as output

	DDRC |= (1 << 3);

	// set PC0 as input
	DDRC &= ~(1 << 0);

	// start convertion
	ADCSRA |= (1 << ADSC);


	ACSR |= (1 << ACBG) | (1 << ACIE);


}

void detect_Metal(){
	temp = ADCH;

	//If the most significant bit of the digital signal is high
	//increment the sum
	while (counter < 25){
		sum = sum + temp;
	}

	//at 100 samples collected
	//If sum is more than half, then turn on the LED


	if(counter == 100){

	    if(sum & (1 << 7)){
			PORTC |= (1 << 3);
		}
		else{
			PORTC &= ~(1 << 3);
		}
		   sum =0;
		}
	counter++;
}
