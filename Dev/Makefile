CCARGS = -mmcu=atmega328 -DF_CPU=1000000UL -Os

default: main

main: main.c PWM.o Sensor.o
	avr-gcc  $(CCARGS) main.c -o main

PWM.o: PWM.c PWM.h
	avr-gcc $(CCARGS) PWM.c -o PWM

Sensor.o: Sensor.c Sensor.h
	avr-gcc $(CCARGS) Sensor.c -o Sensor

program: test
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock main main.hex
	avrdude -p atmega328 -c buspirate -P COM5 -U flash:w:main.hex

clean:s
	-rm main.bit main.mem main.hex main *.o	 *.gch

