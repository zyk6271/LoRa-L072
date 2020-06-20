################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/mac/region/Region.c \
../RF/mac/region/RegionCN470.c \
../RF/mac/region/RegionCommon.c 

OBJS += \
./RF/mac/region/Region.o \
./RF/mac/region/RegionCN470.o \
./RF/mac/region/RegionCommon.o 

C_DEPS += \
./RF/mac/region/Region.d \
./RF/mac/region/RegionCN470.d \
./RF/mac/region/RegionCommon.d 


# Each subdirectory must supply rules for building sources it contributes
RF/mac/region/%.o: ../RF/mac/region/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"D:\RT-ThreadStudio\workspace\L072\drivers" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\L072\libraries" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio\sx126x" -I"D:\RT-ThreadStudio\workspace\L072\RF" -I"D:\RT-ThreadStudio\workspace\L072\RF\boards" -I"D:\RT-ThreadStudio\workspace\L072\RF\peripherals\soft-se" -I"D:\RT-ThreadStudio\workspace\L072\RF\system" -I"D:\RT-ThreadStudio\workspace\L072\RF\mac" -I"D:\RT-ThreadStudio\workspace\L072\RF\mac\region" -I"D:\RT-ThreadStudio\workspace\L072\RF\boards\B-L072Z-LRWAN1" -I"D:\RT-ThreadStudio\workspace\L072\applications" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Src" -I"D:\RT-ThreadStudio\workspace\L072" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\cortex-m0" -include"D:\RT-ThreadStudio\workspace\L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

