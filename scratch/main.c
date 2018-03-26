#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include "Sensor.h"
#include "motor.h"
#include "externalVar.h"

int main() {

    //If the Right Sensor detects object and left don't, turn left
    //If the Left Sensor detects object and right don't, turn right
    //If both Sensors detects object, spin left/right
    //If both Sensors did not detect anything, go forward
    while(1){
        if (distanceLeft<10 && distanceRight<10){
            leftmotor_reverse(0x7F);
            rightmotor_reverse(0x7F);
        }
        else if(dstanceLeft<10 && !(distanceRight<10) ){
            leftmotor_foward(0x7F);
            rightmotor_reverse(0x7F);
        }
        else if( !(dstanceLeft<10) && distanceRight<10 ){
            leftmotor_reverse(0x7F);
            rightmotor_forward(0x7F);
        }
        else{
            leftmotor_forward(0x7F);
            rightmotor_forward(0x7F);
        }
    }
    return 1;
}
