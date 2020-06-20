################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../libraries/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l072xx.s 

OBJS += \
./libraries/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l072xx.o 

S_DEPS += \
./libraries/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l072xx.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/%.o: ../libraries/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/%.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O2 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -x assembler-with-cpp -I"D:\RT-ThreadStudio\workspace\LoRa-L072" -Xassembler -mimplicit-it=thumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

