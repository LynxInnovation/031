-include config.mk

MCU=atmega644p
AVRDUDE_MCU=m644p

F_CPU=8000000LL

CC=avr-gcc
OBJCPY=avr-objcopy
CFLAGS+=-Wall -W -g -O2 -mmcu=$(MCU) -DF_CPU=$(F_CPU)
LDFLAGS+=-g -Os -mmcu=$(MCU)

OBJS=main.o hw.o vs.o sd.o diet.o

all: rmpmp3.hex

rmpmp3.hex: rmpmp3.elf
	$(OBJCPY) -O ihex $< $@

rmpmp3.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hw.o: hw.c hw.h
sd.o: sd.c hw.h sd.h
vs.o: vs.c hw.h vs.h
main.o: main.c hw.h sd.h vs.h
diet.o: sd.h

isp: rmpmp3.hex
	$(AVRDUDE_SUDO) avrdude -c $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -U flash:w:rmpmp3.hex

readfw: rmpmp3.hex
	$(AVRDUDE_SUDO) avrdude -c $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -U flash:r:fw.hex:i


fuses:
	$(AVRDUDE_SUDO) avrdude -c $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -U lfuse:w:0xe2:m -U hfuse:w:0x99:m -U efuse:w:0xff:m -e

clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.hex

