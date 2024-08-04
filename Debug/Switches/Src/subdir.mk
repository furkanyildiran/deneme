################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Switches/Src/switches.c 

OBJS += \
./Switches/Src/switches.o 

C_DEPS += \
./Switches/Src/switches.d 


# Each subdirectory must supply rules for building sources it contributes
Switches/Src/%.o Switches/Src/%.su Switches/Src/%.cyclo: ../Switches/Src/%.c Switches/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Monster/STM32CubeIDE/workspace_1.16.0/deneme/LCD/Inc" -I"C:/Users/Monster/STM32CubeIDE/workspace_1.16.0/deneme/Switches/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Switches-2f-Src

clean-Switches-2f-Src:
	-$(RM) ./Switches/Src/switches.cyclo ./Switches/Src/switches.d ./Switches/Src/switches.o ./Switches/Src/switches.su

.PHONY: clean-Switches-2f-Src

