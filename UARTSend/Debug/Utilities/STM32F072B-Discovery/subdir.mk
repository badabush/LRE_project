################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F072B-Discovery/stm32f072b_discovery.c \
../Utilities/STM32F072B-Discovery/stm32f072b_discovery_i2c_ee.c \
../Utilities/STM32F072B-Discovery/stm32f072b_discovery_l3gd20.c 

OBJS += \
./Utilities/STM32F072B-Discovery/stm32f072b_discovery.o \
./Utilities/STM32F072B-Discovery/stm32f072b_discovery_i2c_ee.o \
./Utilities/STM32F072B-Discovery/stm32f072b_discovery_l3gd20.o 

C_DEPS += \
./Utilities/STM32F072B-Discovery/stm32f072b_discovery.d \
./Utilities/STM32F072B-Discovery/stm32f072b_discovery_i2c_ee.d \
./Utilities/STM32F072B-Discovery/stm32f072b_discovery_l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F072B-Discovery/%.o: ../Utilities/STM32F072B-Discovery/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F072RBTx -DSTM32F072B_DISCO -DDEBUG -DSTM32F072 -DUSE_STDPERIPH_DRIVER -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/StdPeriph_Driver/inc" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/Utilities/STM32F072B-Discovery" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/inc" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/CMSIS/device" -I"/Users/Lee/tubCloud/LRE/eclipse_ws/HW6/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


