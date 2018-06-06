#MACROS
TARGET_C = motor_pwm.c
TARGET_O = motor_pwm.o
TARGET_E = motor_pwm.elf
TARGET_H = motor_pwm.hex
TARGET_F = flash:w:motor_pwm.hex:i

compile:
	rm -f *.o *.elf *.hex
	avr-gcc -g -Os -mmcu=atmega128 -c $(TARGET_C)
	avr-gcc -g -mmcu=atmega128 -o $(TARGET_E) $(TARGET_O)
	avr-objcopy -j .text -j .data -O ihex $(TARGET_E) $(TARGET_H)
	#cat $(TARGET_H)
	echo "$$(tput setaf 2)Compiled OK"

flash:
	sudo avrdude -p m128 -c jtagmkI -P /dev/ttyUSB0 -U $(TARGET_F)
	echo "$$(tput setaf 2)Flashed OK"


	
