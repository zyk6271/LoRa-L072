################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/boards/B-L072Z-LRWAN1/NvmCtxMgmt.c \
../RF/boards/B-L072Z-LRWAN1/delay-board.c \
../RF/boards/B-L072Z-LRWAN1/eeprom-board.c \
../RF/boards/B-L072Z-LRWAN1/gpio-board.c \
../RF/boards/B-L072Z-LRWAN1/lora-board.c \
../RF/boards/B-L072Z-LRWAN1/lpm-board.c \
../RF/boards/B-L072Z-LRWAN1/rtc-board.c \
../RF/boards/B-L072Z-LRWAN1/spi-board.c 

OBJS += \
./RF/boards/B-L072Z-LRWAN1/NvmCtxMgmt.o \
./RF/boards/B-L072Z-LRWAN1/delay-board.o \
./RF/boards/B-L072Z-LRWAN1/eeprom-board.o \
./RF/boards/B-L072Z-LRWAN1/gpio-board.o \
./RF/boards/B-L072Z-LRWAN1/lora-board.o \
./RF/boards/B-L072Z-LRWAN1/lpm-board.o \
./RF/boards/B-L072Z-LRWAN1/rtc-board.o \
./RF/boards/B-L072Z-LRWAN1/spi-board.o 

C_DEPS += \
./RF/boards/B-L072Z-LRWAN1/NvmCtxMgmt.d \
./RF/boards/B-L072Z-LRWAN1/delay-board.d \
./RF/boards/B-L072Z-LRWAN1/eeprom-board.d \
./RF/boards/B-L072Z-LRWAN1/gpio-board.d \
./RF/boards/B-L072Z-LRWAN1/lora-board.d \
./RF/boards/B-L072Z-LRWAN1/lpm-board.d \
./RF/boards/B-L072Z-LRWAN1/rtc-board.d \
./RF/boards/B-L072Z-LRWAN1/spi-board.d 


# Each subdirectory must supply rules for building sources it contributes
RF/boards/B-L072Z-LRWAN1/%.o: ../RF/boards/B-L072Z-LRWAN1/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"D:\RT-ThreadStudio\workspace\L072\drivers" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\L072\libraries" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio\sx126x" -I"D:\RT-ThreadStudio\workspace\L072\RF" -I"D:\RT-ThreadStudio\workspace\L072\RF\boards" -I"D:\RT-ThreadStudio\workspace\L072\RF\peripherals\soft-se" -I"D:\RT-ThreadStudio\workspace\L072\RF\system" -I"D:\RT-ThreadStudio\workspace\L072\RF\mac" -I"D:\RT-ThreadStudio\workspace\L072\RF\mac\region" -I"D:\RT-ThreadStudio\workspace\L072\RF\boards\B-L072Z-LRWAN1" -I"D:\RT-ThreadStudio\workspace\L072\applications" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Src" -I"D:\RT-ThreadStudio\workspace\L072" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\cortex-m0" -include"D:\RT-ThreadStudio\workspace\L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

