################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/softse/aes.c \
../RF/softse/cmac.c \
../RF/softse/soft-se.c 

OBJS += \
./RF/softse/aes.o \
./RF/softse/cmac.o \
./RF/softse/soft-se.o 

C_DEPS += \
./RF/softse/aes.d \
./RF/softse/cmac.d \
./RF/softse/soft-se.d 


# Each subdirectory must supply rules for building sources it contributes
RF/softse/%.o: ../RF/softse/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O2 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -DREGION_CN470 -I"D:\RT-ThreadStudio\workspace\LoRa-L072\drivers" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\applications" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\STM32L0xx_HAL_Driver\Src" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\boards\inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\mac\inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\radio\inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\softse" -I"D:\RT-ThreadStudio\workspace\LoRa-L072" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\components\drivers\spi" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\libcpu\arm\cortex-m0" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\application\inc" -include"D:\RT-ThreadStudio\workspace\LoRa-L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

