################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../INA219/INA219.c 

OBJS += \
./INA219/INA219.o 

C_DEPS += \
./INA219/INA219.d 


# Each subdirectory must supply rules for building sources it contributes
INA219/%.o INA219/%.su INA219/%.cyclo: ../INA219/%.c INA219/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nhakh/Desktop/Document/STM/CE437/Lab02/INA219" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-INA219

clean-INA219:
	-$(RM) ./INA219/INA219.cyclo ./INA219/INA219.d ./INA219/INA219.o ./INA219/INA219.su

.PHONY: clean-INA219

