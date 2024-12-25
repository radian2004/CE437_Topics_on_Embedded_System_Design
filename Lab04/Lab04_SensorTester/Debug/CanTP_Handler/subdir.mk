################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanTP_Handler/CanTP.c 

OBJS += \
./CanTP_Handler/CanTP.o 

C_DEPS += \
./CanTP_Handler/CanTP.d 


# Each subdirectory must supply rules for building sources it contributes
CanTP_Handler/%.o CanTP_Handler/%.su CanTP_Handler/%.cyclo: ../CanTP_Handler/%.c CanTP_Handler/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab04_SensorTester/isotp-c" -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab04_SensorTester/CanTP_Handler" -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab04_SensorTester/Diagnostic_Services" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CanTP_Handler

clean-CanTP_Handler:
	-$(RM) ./CanTP_Handler/CanTP.cyclo ./CanTP_Handler/CanTP.d ./CanTP_Handler/CanTP.o ./CanTP_Handler/CanTP.su

.PHONY: clean-CanTP_Handler

