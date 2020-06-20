################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/boards/mcu/saml21/hpl/rtc/hpl_rtc.c 

OBJS += \
./RF/boards/mcu/saml21/hpl/rtc/hpl_rtc.o 

C_DEPS += \
./RF/boards/mcu/saml21/hpl/rtc/hpl_rtc.d 


# Each subdirectory must supply rules for building sources it contributes
RF/boards/mcu/saml21/hpl/rtc/%.o: ../RF/boards/mcu/saml21/hpl/rtc/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"D:\RT-ThreadStudio\workspace\L072\drivers" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\L072\libraries" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio\sx126x" -I"D:\RT-ThreadStudio\workspace\L072\RF" -I"D:\RT-ThreadStudio\workspace\L072" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\cortex-m0" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -include"D:\RT-ThreadStudio\workspace\L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

