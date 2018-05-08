CCARGS = -mmcu=atmega328 -DF_CPU=1000000UL -Os

default: mainB program clean

mainB: mainB.c motor.o PWM.o Sensor.o ADC.o Sensor.h motor.h ADC.h
	avr-gcc $(CCARGS) motor.h Sensor.h PWM.h ADC.h mainB.c motor.o PWM.o Sensor.o ADC.o -o mainB

motor.o: motor.h motor.c PWM.o
	avr-gcc $(CCARGS) -c motor.h PWM.h motor.c

PWM.o: PWM.c PWM.h
	avr-gcc $(CCARGS) -c PWM.h PWM.c

Sensor.o: Sensor.c Sensor.h
	avr-gcc $(CCARGS) -c Sensor.h Sensor.c

ADC.o:	ADC.c ADC.h
	avr-gcc $(CCARGS) -c ADC.h ADC.c

program: mainB PWM.o motor.o Sensor.o
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock mainB mainB.hex
	avrdude -p atmega328 -c buspirate -P COM5 -U flash:w:mainB.hex

clean:
	-rm mainB.hex mainB *.o *.gch
