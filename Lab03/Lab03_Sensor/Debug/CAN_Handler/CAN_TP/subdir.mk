################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CAN_Handler/CAN_TP/CAN_TP.c 

OBJS += \
./CAN_Handler/CAN_TP/CAN_TP.o 

C_DEPS += \
./CAN_Handler/CAN_TP/CAN_TP.d 


# Each subdirectory must supply rules for building sources it contributes
CAN_Handler/CAN_TP/%.o CAN_Handler/CAN_TP/%.su CAN_Handler/CAN_TP/%.cyclo: ../CAN_Handler/CAN_TP/%.c CAN_Handler/CAN_TP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nhakh/Desktop/Document/STM/CE437/Lab03_Sensor/CAN_Handler" -I"C:/Users/nhakh/Desktop/Document/STM/CE437/Lab03_Sensor/Diagnostic_Services" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CAN_Handler-2f-CAN_TP

clean-CAN_Handler-2f-CAN_TP:
	-$(RM) ./CAN_Handler/CAN_TP/CAN_TP.cyclo ./CAN_Handler/CAN_TP/CAN_TP.d ./CAN_Handler/CAN_TP/CAN_TP.o ./CAN_Handler/CAN_TP/CAN_TP.su

.PHONY: clean-CAN_Handler-2f-CAN_TP

