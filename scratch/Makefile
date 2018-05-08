CCARGS = -mmcu=atmega328 -DF_CPU=1000000UL -Os

default: main2 program clean

main2: main2.c motor.o PWM.o Sensor.o Sensor.h motor.h
	avr-gcc $(CCARGS) motor.h Sensor.h PWM.h main2.c motor.o PWM.o Sensor.o -o main2

motor.o: motor.h motor.c PWM.o
	avr-gcc $(CCARGS) -c motor.h PWM.h motor.c

PWM.o: PWM.c PWM.h
	avr-gcc $(CCARGS) -c PWM.h PWM.c

Sensor.o: Sensor.c Sensor.h
	avr-gcc $(CCARGS) -c Sensor.h Sensor.c

program: main2 PWM.o motor.o Sensor.o
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock main2 main2.hex
	sudo avrdude -p atmega328 -c buspirate -P /dev/ttyUSB0 -U flash:w:main2.hex

clean:
	-rm main2.hex main2 *.o *.gch
