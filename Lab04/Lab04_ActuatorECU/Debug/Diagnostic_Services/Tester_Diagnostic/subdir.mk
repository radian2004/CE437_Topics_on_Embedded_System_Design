################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.c 

OBJS += \
./Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.o 

C_DEPS += \
./Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.d 


# Each subdirectory must supply rules for building sources it contributes
Diagnostic_Services/Tester_Diagnostic/%.o Diagnostic_Services/Tester_Diagnostic/%.su Diagnostic_Services/Tester_Diagnostic/%.cyclo: ../Diagnostic_Services/Tester_Diagnostic/%.c Diagnostic_Services/Tester_Diagnostic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab04_ActuatorECU/CanTP_Handler" -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab04_ActuatorECU/Diagnostic_Services" -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab04_ActuatorECU/isotp-c" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Diagnostic_Services-2f-Tester_Diagnostic

clean-Diagnostic_Services-2f-Tester_Diagnostic:
	-$(RM) ./Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.cyclo ./Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.d ./Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.o ./Diagnostic_Services/Tester_Diagnostic/Tester_Diagnostic.su

.PHONY: clean-Diagnostic_Services-2f-Tester_Diagnostic

