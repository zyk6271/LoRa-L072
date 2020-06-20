################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../RF/boards/B-L072Z-LRWAN1/cmsis/arm-std/startup_stm32l072xx.s 

OBJS += \
./RF/boards/B-L072Z-LRWAN1/cmsis/arm-std/startup_stm32l072xx.o 

S_DEPS += \
./RF/boards/B-L072Z-LRWAN1/cmsis/arm-std/startup_stm32l072xx.d 


# Each subdirectory must supply rules for building sources it contributes
RF/boards/B-L072Z-LRWAN1/cmsis/arm-std/%.o: ../RF/boards/B-L072Z-LRWAN1/cmsis/arm-std/%.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -x assembler-with-cpp -I"D:\RT-ThreadStudio\workspace\L072" -Xassembler -mimplicit-it=thumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

