#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include "PWM.h"

void init_PWM(){
    //might need to put this into the Main.c
    //set the PORTD 3 & 5 & 6 as output
    DDRD |= ((1<<3) | (1<<5) | (1<<6));
    //set the PORTB 3 as output
    DDRB |= (1<<3);

    TCCR0A = TCCR0A_config;
    TCCR0B = TCCR0B_config;
    TCCR2A = TCCR2A_config;
    TCCR2B = TCCR2B_config;
}

void A1_setPWM(uint8_t value){   OCR0A = value;  }
void A2_setPWM(uint8_t value){   OCR0B = value;  }
void B1_setPWM(uint8_t value){   OCR2A = value;  }
void B2_setPWM(uint8_t value){   OCR2B = value;  }
