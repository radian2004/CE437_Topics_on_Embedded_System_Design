################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Diagnostic_Services/ReadDataByID/ReadData.c 

OBJS += \
./Diagnostic_Services/ReadDataByID/ReadData.o 

C_DEPS += \
./Diagnostic_Services/ReadDataByID/ReadData.d 


# Each subdirectory must supply rules for building sources it contributes
Diagnostic_Services/ReadDataByID/%.o Diagnostic_Services/ReadDataByID/%.su Diagnostic_Services/ReadDataByID/%.cyclo: ../Diagnostic_Services/ReadDataByID/%.c Diagnostic_Services/ReadDataByID/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nhakh/Desktop/Document/STM/CE437/Lab03_Sensor/CAN_Handler" -I"C:/Users/nhakh/Desktop/Document/STM/CE437/Lab03_Sensor/Diagnostic_Services" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Diagnostic_Services-2f-ReadDataByID

clean-Diagnostic_Services-2f-ReadDataByID:
	-$(RM) ./Diagnostic_Services/ReadDataByID/ReadData.cyclo ./Diagnostic_Services/ReadDataByID/ReadData.d ./Diagnostic_Services/ReadDataByID/ReadData.o ./Diagnostic_Services/ReadDataByID/ReadData.su

.PHONY: clean-Diagnostic_Services-2f-ReadDataByID

