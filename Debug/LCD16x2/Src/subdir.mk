################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD16x2/Src/lcd16x2.c 

OBJS += \
./LCD16x2/Src/lcd16x2.o 

C_DEPS += \
./LCD16x2/Src/lcd16x2.d 


# Each subdirectory must supply rules for building sources it contributes
LCD16x2/Src/%.o LCD16x2/Src/%.su LCD16x2/Src/%.cyclo: ../LCD16x2/Src/%.c LCD16x2/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Monster/STM32CubeIDE/workspace_1.16.0/deneme/LCD16x2/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LCD16x2-2f-Src

clean-LCD16x2-2f-Src:
	-$(RM) ./LCD16x2/Src/lcd16x2.cyclo ./LCD16x2/Src/lcd16x2.d ./LCD16x2/Src/lcd16x2.o ./LCD16x2/Src/lcd16x2.su

.PHONY: clean-LCD16x2-2f-Src

