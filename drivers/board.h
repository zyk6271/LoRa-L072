/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-26     ChenYong     first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32l0xx.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------- UART CONFIG BEGIN --------------------------*/

/** After configuring corresponding UART or UART DMA, you can use it.
  *
  * STEP 1, define macro define related to the serial port opening based on the serial port number
  *                 such as     #define BSP_USING_UATR1
  *
  * STEP 2, according to the corresponding pin of serial port, modify the related serial port information
  *                 such as     #define UART1_TX_PORT            GPIOX   ->   GPIOA
  *                             #define UART1_RX_PORT            GPIOX   ->   GPIOA
  *                             #define UART1_TX_PIN        GPIO_PIN_X   ->   GPIO_PIN_9
  *                             #define UART1_RX_PIN        GPIO_PIN_X   ->   GPIO_PIN_10
  *
  * STEP 3, if you want using SERIAL DMA, you must open it in the RT-Thread Settings.
  *                 RT-Thread Setting -> Components -> Device Drivers -> Serial Device Drivers -> Enable Serial DMA Mode
  *
  * STEP 4, according to serial port number to define serial port tx/rx DMA function in the board.h file
  *                 such as     #define BSP_UART1_RX_USING_DMA
  *
  */

#define BSP_USING_UART5

#if defined(BSP_USING_UART1)
#define UART1_TX_PORT       GPIOA
#define UART1_RX_PORT       GPIOA
#define UART1_TX_PIN        GPIO_PIN_9
#define UART1_RX_PIN        GPIO_PIN_10
#endif
#if defined(BSP_USING_UART2)
#define UART2_TX_PORT       GPIOB
#define UART2_RX_PORT       GPIOB
#define UART2_TX_PIN        GPIO_PIN_3
#define UART2_RX_PIN        GPIO_PIN_4
#endif
#if defined(BSP_USING_UART3)
#define UART3_TX_PORT       GPIOX
#define UART3_RX_PORT       GPIOX
#define UART3_TX_PIN        GPIO_PIN_X
#define UART3_RX_PIN        GPIO_PIN_X
#endif
#if defined(BSP_USING_UART4)
#define UART4_TX_PORT       GPIOX
#define UART4_RX_PORT       GPIOX
#define UART4_TX_PIN        GPIO_PIN_X
#define UART4_RX_PIN        GPIO_PIN_X
#endif
#if defined(BSP_USING_UART5)
#define UART5_TX_PORT       GPIOB
#define UART5_RX_PORT       GPIOB
#define UART5_TX_PIN        GPIO_PIN_3
#define UART5_RX_PIN        GPIO_PIN_4
#endif
#if defined(BSP_USING_UART6)
#define UART6_TX_PORT       GPIOX
#define UART6_RX_PORT       GPIOX
#define UART6_TX_PIN        GPIO_PIN_X
#define UART6_RX_PIN        GPIO_PIN_X
#endif
#if defined(BSP_USING_UART7)
#define UART7_TX_PORT       GPIOX
#define UART7_RX_PORT       GPIOX
#define UART7_TX_PIN        GPIO_PIN_X
#define UART7_RX_PIN        GPIO_PIN_X
#endif
#if defined(BSP_USING_UART8)
#define UART8_TX_PORT       GPIOX
#define UART8_RX_PORT       GPIOX
#define UART8_TX_PIN        GPIO_PIN_X
#define UART8_RX_PIN        GPIO_PIN_X
#endif
#if defined(BSP_USING_LPUART1)
#define LPUART1_TX_PORT     GPIOX
#define LPUART1_RX_PORT     GPIOX
#define LPUART1_TX_PIN      GPIO_PIN_X
#define LPUART1_RX_PIN      GPIO_PIN_X
#endif
/*-------------------------- UART CONFIG END --------------------------*/


/*-------------------------- I2C CONFIG BEGIN --------------------------*/

/** if you want to use i2c bus(soft simulate) you can use the following instructions.
  *
  * STEP 1, open i2c driver framework(soft simulate) support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the i2c bus
  *                 such as     #define BSP_USING_I2C1
  *
  * STEP 3, according to the corresponding pin of i2c port, modify the related i2c port and pin information
  *                 such as     #define BSP_I2C1_SCL_PIN    GET_PIN(port, pin)   ->   GET_PIN(C, 11)
  *                             #define BSP_I2C1_SDA_PIN    GET_PIN(port, pin)   ->   GET_PIN(C, 12)
  */

/*#define BSP_USING_I2C1*/
#ifdef BSP_USING_I2C1
#define BSP_I2C1_SCL_PIN    GET_PIN(port, pin)
#define BSP_I2C1_SDA_PIN    GET_PIN(port, pin)
#endif

/*#define BSP_USING_I2C2*/
#ifdef BSP_USING_I2C2
#define BSP_I2C2_SCL_PIN    GET_PIN(port, pin)
#define BSP_I2C2_SDA_PIN    GET_PIN(port, pin)
#endif

/*-------------------------- I2C CONFIG END --------------------------*/


/*-------------------------- SPI CONFIG BEGIN --------------------------*/

/** if you want to use spi bus you can use the following instructions.
  *
  * STEP 1, open spi driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the spi bus
  *                 such as     #define BSP_USING_SPI1
  *
  * STEP 3, copy your spi init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
  * 
  * STEP 4, modify your stm32xxxx_hal_config.h file to support spi peripherals. define macro related to the peripherals
  *                 such as     #define HAL_SPI_MODULE_ENABLED
  */

#define BSP_USING_SPI1
/*#define BSP_USING_SPI2*/
/*#define BSP_USING_SPI3*/

/*-------------------------- SPI CONFIG END --------------------------*/


/*-------------------------- QSPI CONFIG BEGIN --------------------------*/

/** if you want to use qspi you can use the following instructions.
  *
  * STEP 1, open qspi driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the qspi
  *                 such as     #define BSP_USING_QSPI
  *
  * STEP 3, copy your qspi init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_QSPI_MspInit(QSPI_HandleTypeDef* hqspi)
  * 
  * STEP 4, modify your stm32xxxx_hal_config.h file to support qspi peripherals. define macro related to the peripherals
  *                 such as     #define HAL_QSPI_MODULE_ENABLED
  * 
  */
 
/*#define BSP_USING_QSPI*/

/*-------------------------- QSPI CONFIG END --------------------------*/


/*-------------------------- PWM CONFIG BEGIN --------------------------*/

/** if you want to use pwm you can use the following instructions.
  *
  * STEP 1, open pwm driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the pwm
  *                 such as     #define BSP_USING_PWM1
  *
  * STEP 3, copy your pwm timer init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end if board.c file
  *                 such as     void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)  and 
  *                             void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
  * 
  * STEP 4, modify your stm32xxxx_hal_config.h file to support pwm peripherals. define macro related to the peripherals
  *                 such as     #define HAL_TIM_MODULE_ENABLED
  * 
  */

/*#define BSP_USING_PWM1*/
/*#define BSP_USING_PWM2*/
/*#define BSP_USING_PWM3*/

/*-------------------------- PWM CONFIG END --------------------------*/


/*-------------------------- ADC CONFIG BEGIN --------------------------*/

/** if you want to use adc you can use the following instructions.
  *
  * STEP 1, open adc driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the adc
  *                 such as     #define BSP_USING_ADC1
  *
  * STEP 3, copy your adc init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
  * 
  * STEP 4, modify your stm32xxxx_hal_config.h file to support adc peripherals. define macro related to the peripherals
  *                 such as     #define HAL_ADC_MODULE_ENABLED
  * 
  */

/*#define BSP_USING_ADC1*/
/*#define BSP_USING_ADC2*/
/*#define BSP_USING_ADC3*/

/*-------------------------- ADC CONFIG END --------------------------*/


/*-------------------------- WDT CONFIG BEGIN --------------------------*/

/** if you want to use wdt you can use the following instructions.
  *
  * STEP 1, open wdt driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, modify your stm32xxxx_hal_config.h file to support wdt peripherals. define macro related to the peripherals
  *                 such as     #define HAL_IWDG_MODULE_ENABLED
  * 
  */

/*-------------------------- WDT CONFIG END --------------------------*/


/*-------------------------- HARDWARE TIMER CONFIG BEGIN --------------------------*/

/** if you want to use hardware timer you can use the following instructions.
  *
  * STEP 1, open hwtimer driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the hwtimer
  *                 such as     #define BSP_USING_TIM  and
  *                             #define BSP_USING_TIM1
  *
  * STEP 3, copy your hardwire timer init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
  * 
  * STEP 4, modify your stm32xxxx_hal_config.h file to support hardwere timer peripherals. define macro related to the peripherals
  *                 such as     #define HAL_TIM_MODULE_ENABLED
  * 
  */

/*#define BSP_USING_TIM*/
#ifdef BSP_USING_TIM
/*#define BSP_USING_TIM15*/
/*#define BSP_USING_TIM16*/
/*#define BSP_USING_TIM17*/
#endif

/*-------------------------- HAREWARE TIMER CONFIG END --------------------------*/


/*-------------------------- RTC CONFIG BEGIN --------------------------*/

/** if you want to use rtc(hardware) you can use the following instructions.
  *
  * STEP 1, open rtc driver framework(hardware) support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the rtc
  *                 such as    BSP_USING_ONCHIP_RTC
  * 
  * STEP 3, modify your stm32xxxx_hal_config.h file to support rtc peripherals. define macro related to the peripherals
  *                 such as     #define HAL_RTC_MODULE_ENABLED
  * 
  */
#define BSP_USING_ONCHIP_RTC

/*-------------------------- RTC CONFIG END --------------------------*/


/*-------------------------- SDIO CONFIG BEGIN --------------------------*/

/** if you want to use sdio you can use the following instructions.
  *
  * STEP 1, open sdio driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the sdio
  *                 such as    BSP_USING_SDIO
  * 
  * STEP 3, copy your sdio init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
  * 
  * STEP 4, modify your stm32xxxx_hal_config.h file to support sdio peripherals. define macro related to the peripherals
  *                 such as     #define HAL_SD_MODULE_ENABLED
  * 
  * STEP 5, config your device file system or another applications
  * 
  */

/*#define BSP_USING_SDIO*/

/*-------------------------- SDIO CONFIG END --------------------------*/


/*-------------------------- ETH CONFIG BEGIN --------------------------*/

/** if you want to use eth you can use the following instructions.
  *
  * STEP 1, define macro related to the eth
  *                 such as    BSP_USING_ETH
  * 
  * STEP 2, copy your eth init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end if board.c file
  *                 such as     void HAL_ETH_MspInit(ETH_HandleTypeDef* heth)
  * 
  * STEP 3, modify your stm32xxxx_hal_config.h file to support eth peripherals. define macro related to the peripherals
  *                 such as     #define HAL_ETH_MODULE_ENABLED
  * 
  * STEP 4, config your phy type
  *                 such as     #define PHY_USING_LAN8720A
  *                             #define PHY_USING_DM9161CEP
  *                             #define PHY_USING_DP83848C
  * STEP 5, implement your phy reset function in the end of board.c file
  *                 void phy_reset(void)
  * 
  * STEP 6, config your lwip or other network stack
  * 
  */

/*#define BSP_USING_ETH*/
#ifdef BSP_USING_ETH
/*#define PHY_USING_LAN8720A*/
/*#define PHY_USING_DM9161CEP*/
/*#define PHY_USING_DP83848C*/
#endif
/*-------------------------- ETH CONFIG END --------------------------*/


/*-------------------------- USB HOST CONFIG BEGIN --------------------------*/

/** if you want to use usb host you can use the following instructions.
  *
  * STEP 1, open usb host driver framework support in the RT-Thread Settings file
  * 
  * STEP 2, define macro related to the usb host
  *                 such as    BSP_USING_USBHOST
  * 
  * STEP 3, copy your usb host init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_HCD_MspInit(HCD_HandleTypeDef* hhcd)
  * 
  * STEP 4, config your usb peripheral clock in SystemClock_Config() generated by STM32CubeMX and replace this function in board.c
  * 
  * STEP 5, modify your stm32xxxx_hal_config.h file to support usb host peripherals. define macro related to the peripherals
  *                 such as     #define HAL_HCD_MODULE_ENABLED
  * 
  */

/*#define BSP_USING_USBHOST*/

/*-------------------------- USB HOST CONFIG END --------------------------*/


/*-------------------------- USB DEVICE CONFIG BEGIN --------------------------*/

/** if you want to use usb device you can use the following instructions.
  *
  * STEP 1, open usb device driver framework support in the RT-Thread Settings file
  * 
  * STEP 2 define macro related to the usb device
  *                 such as    BSP_USING_USBDEVICE
  * 
  * STEP 3, copy your usb device init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
  *                 such as     void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
  * 
  * STEP 4, config your usb peripheral clock in SystemClock_Config() generated by STM32CubeMX and replace this function in board.c
  * 
  * STEP 5, modify your stm32xxxx_hal_config.h file to support usb device peripherals. define macro related to the peripherals
  *                 such as     #define HAL_PCD_MODULE_ENABLED
  * 
  */

/*#define BSP_USING_USBDEVICE*/

/*-------------------------- USB DEVICE CONFIG END --------------------------*/


/*-------------------------- ON_CHIP_FLASH CONFIG BEGIN --------------------------*/

/** if you want to use on chip flash you can use the following instructions.
  *
  * STEP 1 define macro related to the on chip flash
  *                 such as    BSP_USING_ON_CHIP_FLASH
  * 
  * STEP 2, modify your stm32xxxx_hal_config.h file to support on chip flash peripherals. define macro related to the peripherals
  *                 such as     #define HAL_FLASH_MODULE_ENABLED
  * 
  */

/*#define BSP_USING_ON_CHIP_FLASH*/

/*-------------------------- ON_CHIP_FLASH CONFIG END --------------------------*/


/*-------------------------- ROM/RAM CONFIG BEGIN --------------------------*/

#define STM32_FLASH_START_ADRESS       ((uint32_t)0x8000000)
#define STM32_FLASH_SIZE               (128)
#define STM32_FLASH_END_ADDRESS        ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE * 1024))

#define STM32_SRAM1_SIZE               (20)
#define STM32_SRAM1_START              (0x20000000)
#define STM32_SRAM1_END                (STM32_SRAM1_START + STM32_SRAM1_SIZE * 1024)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$RW_IRAM1$ZI$Limit;
#define HEAP_BEGIN      ((void *)&Image$RW_IRAM1$ZI$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END                       STM32_SRAM1_END

/*-------------------------- ROM/RAM CONFIG END --------------------------*/

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */

