################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../031-516-2003.c \
../BoardComms.c \
../Keyboard.c \
../LampDirect.c \
../Timer.c 

OBJS += \
./031-516-2003.o \
./BoardComms.o \
./Keyboard.o \
./LampDirect.o \
./Timer.o 

C_DEPS += \
./031-516-2003.d \
./BoardComms.d \
./Keyboard.d \
./LampDirect.d \
./Timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega48 -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


