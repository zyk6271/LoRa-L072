################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RF/boards/mcu/saml21/hal/src/hal_atomic.c \
../RF/boards/mcu/saml21/hal/src/hal_delay.c \
../RF/boards/mcu/saml21/hal/src/hal_ext_irq.c \
../RF/boards/mcu/saml21/hal/src/hal_gpio.c \
../RF/boards/mcu/saml21/hal/src/hal_init.c \
../RF/boards/mcu/saml21/hal/src/hal_io.c \
../RF/boards/mcu/saml21/hal/src/hal_sleep.c \
../RF/boards/mcu/saml21/hal/src/hal_spi_m_sync.c \
../RF/boards/mcu/saml21/hal/src/hal_timer.c \
../RF/boards/mcu/saml21/hal/src/hal_usart_sync.c 

OBJS += \
./RF/boards/mcu/saml21/hal/src/hal_atomic.o \
./RF/boards/mcu/saml21/hal/src/hal_delay.o \
./RF/boards/mcu/saml21/hal/src/hal_ext_irq.o \
./RF/boards/mcu/saml21/hal/src/hal_gpio.o \
./RF/boards/mcu/saml21/hal/src/hal_init.o \
./RF/boards/mcu/saml21/hal/src/hal_io.o \
./RF/boards/mcu/saml21/hal/src/hal_sleep.o \
./RF/boards/mcu/saml21/hal/src/hal_spi_m_sync.o \
./RF/boards/mcu/saml21/hal/src/hal_timer.o \
./RF/boards/mcu/saml21/hal/src/hal_usart_sync.o 

C_DEPS += \
./RF/boards/mcu/saml21/hal/src/hal_atomic.d \
./RF/boards/mcu/saml21/hal/src/hal_delay.d \
./RF/boards/mcu/saml21/hal/src/hal_ext_irq.d \
./RF/boards/mcu/saml21/hal/src/hal_gpio.d \
./RF/boards/mcu/saml21/hal/src/hal_init.d \
./RF/boards/mcu/saml21/hal/src/hal_io.d \
./RF/boards/mcu/saml21/hal/src/hal_sleep.d \
./RF/boards/mcu/saml21/hal/src/hal_spi_m_sync.d \
./RF/boards/mcu/saml21/hal/src/hal_timer.d \
./RF/boards/mcu/saml21/hal/src/hal_usart_sync.d 


# Each subdirectory must supply rules for building sources it contributes
RF/boards/mcu/saml21/hal/src/%.o: ../RF/boards/mcu/saml21/hal/src/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"D:\RT-ThreadStudio\workspace\L072\drivers" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\L072\libraries" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Device\ST\STM32L0xx\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio" -I"D:\RT-ThreadStudio\workspace\L072\RF\radio\sx126x" -I"D:\RT-ThreadStudio\workspace\L072\RF" -I"D:\RT-ThreadStudio\workspace\L072" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\L072\rt-thread\libcpu\arm\cortex-m0" -I"D:\RT-ThreadStudio\workspace\L072\libraries\STM32L0xx_HAL_Driver\Inc" -include"D:\RT-ThreadStudio\workspace\L072\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

