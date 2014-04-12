FIRMWARE_PATH=../031-517-202/Debug/031-517-202.hex
OUTPUT=../031-517-202/Debug/031-505-065for031-517-202_BBY4FT_V1.1.1_Boot_1_11.hex

isp: $(TARGET).hex
	avrdude -c usbtiny -P usb -p $(MCU) -U flash:w:$(TARGET).hex
