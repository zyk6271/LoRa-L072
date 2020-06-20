################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/mac/src/LoRaMac.c \
../RF/mac/src/LoRaMacAdr.c \
../RF/mac/src/LoRaMacClassB.c \
../RF/mac/src/LoRaMacCommands.c \
../RF/mac/src/LoRaMacConfirmQueue.c \
../RF/mac/src/LoRaMacCrypto.c \
../RF/mac/src/LoRaMacParser.c \
../RF/mac/src/LoRaMacSerializer.c \
../RF/mac/src/Region.c \
../RF/mac/src/RegionCN470.c \
../RF/mac/src/RegionCommon.c 

OBJS += \
./RF/mac/src/LoRaMac.o \
./RF/mac/src/LoRaMacAdr.o \
./RF/mac/src/LoRaMacClassB.o \
./RF/mac/src/LoRaMacCommands.o \
./RF/mac/src/LoRaMacConfirmQueue.o \
./RF/mac/src/LoRaMacCrypto.o \
./RF/mac/src/LoRaMacParser.o \
./RF/mac/src/LoRaMacSerializer.o \
./RF/mac/src/Region.o \
./RF/mac/src/RegionCN470.o \
./RF/mac/src/RegionCommon.o 

C_DEPS += \
./RF/mac/src/LoRaMac.d \
./RF/mac/src/LoRaMacAdr.d \
./RF/mac/src/LoRaMacClassB.d \
./RF/mac/src/LoRaMacCommands.d \
./RF/mac/src/LoRaMacConfirmQueue.d \
./RF/mac/src/LoRaMacCrypto.d \
./RF/mac/src/LoRaMacParser.d \
./RF/mac/src/LoRaMacSerializer.d \
./RF/mac/src/Region.d \
./RF/mac/src/RegionCN470.d \
./RF/mac/src/RegionCommon.d 


# Each subdirectory must supply rules for building sources it contributes
RF/mac/src/%.o: ../RF/mac/src/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O2 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -DREGION_CN470 -I"D:\RT-ThreadStudio\workspace\LoRa-L072\drivers" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\applications" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\libraries\STM32L0xx_HAL_Driver\Src" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\boards\inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\mac\inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\radio\inc" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\softse" -I"D:\RT-ThreadStudio\workspace\LoRa-L072" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\components\drivers\spi" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\rt-thread\libcpu\arm\cortex-m0" -I"D:\RT-ThreadStudio\workspace\LoRa-L072\RF\application\inc" -include"D:\RT-ThreadStudio\workspace\LoRa-L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

