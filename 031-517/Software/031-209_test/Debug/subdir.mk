################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../031-209_test.c \
../BoardComms.c \
../Globals.c \
../IIC.c \
../Timer.c \
../UART.c \
../Volume.c \
../Wm8960.c 

OBJS += \
./031-209_test.o \
./BoardComms.o \
./Globals.o \
./IIC.o \
./Timer.o \
./UART.o \
./Volume.o \
./Wm8960.o 

C_DEPS += \
./031-209_test.d \
./BoardComms.d \
./Globals.d \
./IIC.d \
./Timer.d \
./UART.d \
./Volume.d \
./Wm8960.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega164p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


