################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/mac/LoRaMac.c \
../RF/mac/LoRaMacAdr.c \
../RF/mac/LoRaMacClassB.c \
../RF/mac/LoRaMacCommands.c \
../RF/mac/LoRaMacConfirmQueue.c \
../RF/mac/LoRaMacCrypto.c \
../RF/mac/LoRaMacParser.c \
../RF/mac/LoRaMacSerializer.c 

OBJS += \
./RF/mac/LoRaMac.o \
./RF/mac/LoRaMacAdr.o \
./RF/mac/LoRaMacClassB.o \
./RF/mac/LoRaMacCommands.o \
./RF/mac/LoRaMacConfirmQueue.o \
./RF/mac/LoRaMacCrypto.o \
./RF/mac/LoRaMacParser.o \
./RF/mac/LoRaMacSerializer.o 

C_DEPS += \
./RF/mac/LoRaMac.d \
./RF/mac/LoRaMacAdr.d \
./RF/mac/LoRaMacClassB.d \
./RF/mac/LoRaMacCommands.d \
./RF/mac/LoRaMacConfirmQueue.d \
./RF/mac/LoRaMacCrypto.d \
./RF/mac/LoRaMacParser.d \
./RF/mac/LoRaMacSerializer.d 


# Each subdirectory must supply rules for building sources it contributes
RF/mac/%.o: ../RF/mac/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"D:\RT-ThreadStudio\workspace\L072\drivers" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\L072\libraries" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio\sx126x" -I"D:\RT-ThreadStudio\workspace\L072\RF" -I"D:\RT-ThreadStudio\workspace\L072\RF\boards" -I"D:\RT-ThreadStudio\workspace\L072\RF\peripherals\soft-se" -I"D:\RT-ThreadStudio\workspace\L072\RF\system" -I"D:\RT-ThreadStudio\workspace\L072\RF\mac" -I"D:\RT-ThreadStudio\workspace\L072\RF\mac\region" -I"D:\RT-ThreadStudio\workspace\L072\RF\boards\B-L072Z-LRWAN1" -I"D:\RT-ThreadStudio\workspace\L072\applications" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Src" -I"D:\RT-ThreadStudio\workspace\L072" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\cortex-m0" -include"D:\RT-ThreadStudio\workspace\L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

