################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../031-516-202.c \
../BoardComms.c \
../Globals.c \
../I2C.c \
../Keyboard.c \
../LampSerial.c \
../MP3.c \
../SPI.c \
../Settings.c \
../Timer.c \
../UART.c \
../diet.c \
../sd.c \
../vs.c 

OBJS += \
./031-516-202.o \
./BoardComms.o \
./Globals.o \
./I2C.o \
./Keyboard.o \
./LampSerial.o \
./MP3.o \
./SPI.o \
./Settings.o \
./Timer.o \
./UART.o \
./diet.o \
./sd.o \
./vs.o 

C_DEPS += \
./031-516-202.d \
./BoardComms.d \
./Globals.d \
./I2C.d \
./Keyboard.d \
./LampSerial.d \
./MP3.d \
./SPI.d \
./Settings.d \
./Timer.d \
./UART.d \
./diet.d \
./sd.d \
./vs.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=24000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


