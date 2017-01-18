avr-gcc -Wall -Os -DF_CPU=8000000 -mmcu=attiny2313a -o main.elf main.c USI_TWI_Master.c hw_hcms_200x.c
avr-objcopy -O ihex main.elf main.hex
rem avrdude -c usbasp -p t2313 -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
avrdude -c usbasp -p t2313 -U flash:w:main.hex:i