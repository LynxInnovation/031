TARGET=ONETIMEISP
MCU=atmega644p
F_CPU=1000000

OBJS := onetimeisp.o

all: $(TARGET).hex

-include config.mk

CFLAGS += -Wall -W -mmcu=$(MCU) -DF_CPU=$(F_CPU)LL -Os
LDFLAGS += -mmcu=$(MCU) -Os -Wl,-Map,$(TARGET).map


$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex $< $@
	cp $(TARGET).hex $(OUTPUT)

$(TARGET).elf: $(OBJS)
	avr-gcc $(LDFLAGS) $^ -o $@

%.o: %.c
	avr-gcc -c $(CFLAGS) $< -o $@

onetimeisp.o: onetimeisp.c hw.h target.h

target.h: $(FIRMWARE_PATH)
	avr-objcopy -I ihex $(FIRMWARE_PATH) -O binary fw.bin
	avr-objcopy -I ihex ../031-517-202/Debug/031-517-202_1.hex -O binary fw1.bin
	echo "#include <avr/pgmspace.h>" > target.h
	xxd -i fw.bin >> target.h
	xxd -i fw1.bin >> target.h
	sed -i 's/^\(.*\) = {/const \1 PROGMEM = {/' target.h
	rm fw.bin
	rm fw1.bin

clean:
	rm -f $(TARGET).elf
	rm -f $(TARGET).hex
	rm -f $(TARGET).map
	rm -f *.o

.PHONY: all clean target.h

