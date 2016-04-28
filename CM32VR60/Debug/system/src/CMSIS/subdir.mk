################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dangnhat/HAL-Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c 

S_UPPER_SRCS += \
/home/dangnhat/HAL-Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.S 

OBJS += \
./system/src/CMSIS/startup_stm32f103xe.o \
./system/src/CMSIS/system_stm32f1xx.o 

C_DEPS += \
./system/src/CMSIS/system_stm32f1xx.d 

S_UPPER_DEPS += \
./system/src/CMSIS/startup_stm32f103xe.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/CMSIS/startup_stm32f103xe.o: /home/dangnhat/HAL-Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall  -g3 -x assembler-with-cpp -DDEBUG -DTRACE -I"../include" -I"../system/include" -I"../system/include/CMSIS" -I"../system/include/stm32f1xx" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/CMSIS/system_stm32f1xx.o: /home/dangnhat/HAL-Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall  -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DTRACE -I/home/dangnhat/HAL-Drivers/STM32F1xx_HAL_Driver/Inc -I/home/dangnhat/HAL-Drivers/CMSIS/Include -I/home/dangnhat/HAL-Drivers/CMSIS/Device/ST/STM32F1xx/Include -I"../include" -I"../system/include" -I"../system/include/CMSIS" -I"../system/include/stm32f1xx" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


