################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dio_Prog.c \
../EEPROM_Prog.c \
../LCD_Prog.c \
../LED.c \
../SPI_PROG.c \
../keyad_driver.c \
../main.c \
../menu.c \
../timer0_prog.c 

OBJS += \
./Dio_Prog.o \
./EEPROM_Prog.o \
./LCD_Prog.o \
./LED.o \
./SPI_PROG.o \
./keyad_driver.o \
./main.o \
./menu.o \
./timer0_prog.o 

C_DEPS += \
./Dio_Prog.d \
./EEPROM_Prog.d \
./LCD_Prog.d \
./LED.d \
./SPI_PROG.d \
./keyad_driver.d \
./main.d \
./menu.d \
./timer0_prog.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


