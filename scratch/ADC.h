#ifndef __SENSOR_H__
#define __SENSOR_H__

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

void init_ADC();
void detect_Metal();

#endif