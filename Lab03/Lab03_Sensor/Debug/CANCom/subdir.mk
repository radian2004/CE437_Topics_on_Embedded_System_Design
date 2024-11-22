################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANCom/CANCom.c 

OBJS += \
./CANCom/CANCom.o 

C_DEPS += \
./CANCom/CANCom.d 


# Each subdirectory must supply rules for building sources it contributes
CANCom/%.o CANCom/%.su CANCom/%.cyclo: ../CANCom/%.c CANCom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab03_Sensor/CANCom" -I"D:/STUDY/Embedded/STM32/CE437.P11.1_Topics on Embedded System Design/References/Lab03_Sensor/utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANCom

clean-CANCom:
	-$(RM) ./CANCom/CANCom.cyclo ./CANCom/CANCom.d ./CANCom/CANCom.o ./CANCom/CANCom.su

.PHONY: clean-CANCom

