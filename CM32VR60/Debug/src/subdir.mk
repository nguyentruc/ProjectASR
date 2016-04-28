################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CM32VR60.c \
../src/_write.c \
../src/bboard_buttons.c \
../src/bboard_leds.c \
../src/bboard_system.c \
../src/crc.c \
../src/main.c \
../src/ring_buffer.c \
../src/spi_eeprom.c \
../src/stm32f1xx_it.c 

OBJS += \
./src/CM32VR60.o \
./src/_write.o \
./src/bboard_buttons.o \
./src/bboard_leds.o \
./src/bboard_system.o \
./src/crc.o \
./src/main.o \
./src/ring_buffer.o \
./src/spi_eeprom.o \
./src/stm32f1xx_it.o 

C_DEPS += \
./src/CM32VR60.d \
./src/_write.d \
./src/bboard_buttons.d \
./src/bboard_leds.d \
./src/bboard_system.d \
./src/crc.d \
./src/main.d \
./src/ring_buffer.d \
./src/spi_eeprom.d \
./src/stm32f1xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall  -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DTRACE -I/home/dangnhat/HAL-Drivers/STM32F1xx_HAL_Driver/Inc -I/home/dangnhat/HAL-Drivers/CMSIS/Include -I/home/dangnhat/HAL-Drivers/CMSIS/Device/ST/STM32F1xx/Include -I"../include" -I"../system/include" -I"../system/include/CMSIS" -I"../system/include/stm32f1xx" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


