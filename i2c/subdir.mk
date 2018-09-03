################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PID/i2c/i2c.c 

OBJS += \
./PID/i2c/i2c.o 

C_DEPS += \
./PID/i2c/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
PID/i2c/%.o: ../PID/i2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/HeatingSystem -I"/home/unix/MyCODE/Eclipse/workspace/WateringStm/FlowSensor" -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/eeprom_calib -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/ctrlSystem -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/u8glib -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/OLED_graphics -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/PID -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/tm1637 -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/timerInterrupt -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/ds1307 -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/adt7301 -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/SPI -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/RotaryEncoderButton -I/home/unix/Arduino/Thermostat_RottaryButton/Phaethon/atmega328_Core/i2c -DF_CPU=16000000UL -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


