################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f072.s 

OBJS += \
./startup/startup_stm32f072.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/StdPeriph_Driver/inc" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/Utilities/STM32F072B-Discovery" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/inc" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/CMSIS/device" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/CMSIS/core" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


