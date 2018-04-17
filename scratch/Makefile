CCARGS = -mmcu=atmega328 -DF_CPU=1000000UL -Os

default: main program clean

main: main.c motor.o PWM.o Sensor.o Sensor.h motor.h
	avr-gcc $(CCARGS) motor.h Sensor.h PWM.h main.c motor.o PWM.o Sensor.o -o main
	
motor.o: motor.h motor.c PWM.o
	avr-gcc $(CCARGS) -c motor.h PWM.h motor.c

PWM.o: PWM.c PWM.h
	avr-gcc $(CCARGS) -c PWM.h PWM.c
	
Sensor.o: Sensor.c Sensor.h
	avr-gcc $(CCARGS) -c Sensor.h Sensor.c

program: main PWM.o motor.o Sensor.o
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock main main.hex
	avrdude -p atmega328 -c buspirate -P COM5 -U flash:w:main.hex

clean:
	-rm main.hex main *.o *.gch
