FIRMWARE_PATH=../031-517-202_nofunction/Debug/031-517-202_nofunction.hex
OUTPUT=../031-517-202_nofunction/Debug/031-505-065for031-517-202_nofunction.hex

isp: $(TARGET).hex
	avrdude -c usbtiny -P usb -p $(MCU) -U flash:w:$(TARGET).hex
