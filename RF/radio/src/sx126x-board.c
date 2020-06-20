/*!
 * \file      sx1262mbxcas-board.c
 *
 * \brief     Target board SX1262MBXCAS shield driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_spi.h"
#include <stdlib.h>
#include "utilities.h"
#include "board-config.h"
#include "board.h"
#include "radio.h"
#include "sx126x-board.h"

/*!
 * Antenna switch GPIO pins objects
 */
extern void RadioOnDioIrq( void* context );

#define Spi_Bus_Name "spi1"
#define LoRa_Device_Name "spi10"
#define SPIx SPI1
#define NssGpioPort GPIOA
#define NssGpioPIN GPIO_PIN_4

void SX126xSpiInit( void )
{
    struct rt_spi_device *lora_radio_spi_device;
    rt_hw_spi_device_attach( Spi_Bus_Name, LoRa_Device_Name, NssGpioPort, NssGpioPIN);
    lora_radio_spi_device = (struct rt_spi_device *)rt_device_find(LoRa_Device_Name);

    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0. */
    cfg.max_hz = 8 * 1000000;             /* max 10M */

    rt_spi_configure(lora_radio_spi_device, &cfg);
    rt_spi_take_bus(lora_radio_spi_device);
    rt_spi_release_bus(lora_radio_spi_device);
}
uint16_t SpiInOut( SPI_TypeDef *spi,uint16_t outData )
{
    uint32_t timeout = 32000;//32M,32ms
    while((spi->SR&SPI_SR_TXE) != SPI_SR_TXE && timeout--){};//µÈ´ý·¢ËÍ¼Ä´æÆ÷¿Õ
    spi->DR = outData;
    timeout = 32000;
    while((spi->SR&SPI_SR_RXNE) != SPI_SR_RXNE && timeout--){};//µÈ´ý½ÓÊÕ¼Ä´æÆ÷·Ç¿Õ
    return spi->DR;
}
void SX126xIoInit( void )
{
    rt_pin_mode(RADIO_NSS,PIN_MODE_OUTPUT);
    rt_pin_write(RADIO_NSS,PIN_HIGH);
    rt_pin_mode(RADIO_BUSY,PIN_MODE_INPUT);
    rt_pin_mode(RADIO_DIO_1,PIN_MODE_INPUT);
}

void SX126xIoIrqInit( DioIrqHandler dioIrq )
{
    rt_pin_attach_irq(RADIO_DIO_1,PIN_IRQ_MODE_RISING ,RadioOnDioIrq,RT_NULL);
    rt_pin_irq_enable(RADIO_DIO_1, PIN_IRQ_ENABLE);
}

void SX126xIoDeInit( void )
{
    rt_pin_mode(RADIO_NSS,PIN_MODE_OUTPUT);
    rt_pin_write(RADIO_NSS,PIN_HIGH);
    rt_pin_mode(RADIO_BUSY,PIN_MODE_INPUT);
    rt_pin_mode(RADIO_DIO_1,PIN_MODE_INPUT);
}

void SX126xIoDbgInit( void )
{
#if defined( USE_RADIO_DEBUG )
    GpioInit( &DbgPinTx, RADIO_DBG_PIN_TX, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &DbgPinRx, RADIO_DBG_PIN_RX, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
#endif
}

void SX126xIoTcxoInit( void )
{
    CalibrationParams_t calibParam;
    SX126xSetDio3AsTcxoCtrl( TCXO_CTRL_1_8V, SX126xGetBoardTcxoWakeupTime( ) << 6 ); // convert from ms to SX126x time base
    calibParam.Value = 0x7F;
    SX126xCalibrate( calibParam );
}

uint32_t SX126xGetBoardTcxoWakeupTime( void )
{
    return BOARD_TCXO_WAKEUP_TIME;
}

void SX126xReset( void )
{
    rt_thread_mdelay( 10 );
    rt_pin_mode(RADIO_RESET,PIN_MODE_OUTPUT);
    rt_pin_write(RADIO_RESET,PIN_LOW);
    rt_thread_mdelay( 20 );
    rt_pin_mode(RADIO_RESET,PIN_MODE_INPUT);
    rt_thread_mdelay( 10 );
}

void SX126xWaitOnBusy( void )
{
    while( rt_pin_read( RADIO_BUSY ) == 1 );
}

void SX126xWakeup( void )
{
    CRITICAL_SECTION_BEGIN( );

    rt_pin_write(RADIO_NSS,PIN_LOW);

    SpiInOut( SPIx, RADIO_GET_STATUS );
    SpiInOut( SPIx, 0x00 );

    rt_pin_write(RADIO_NSS,PIN_HIGH);

    // Wait for chip to be ready.
    SX126xWaitOnBusy( );

    CRITICAL_SECTION_END( );
}

void SX126xWriteCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    rt_pin_write(RADIO_NSS,PIN_LOW);

    SpiInOut( SPIx, ( uint8_t )command );

    for( uint16_t i = 0; i < size; i++ )
    {
        SpiInOut( SPIx, buffer[i] );
    }

    rt_pin_write(RADIO_NSS,PIN_HIGH);

    if( command != RADIO_SET_SLEEP )
    {
        SX126xWaitOnBusy( );
    }
}

uint8_t SX126xReadCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    uint8_t status = 0;

    SX126xCheckDeviceReady( );

    rt_pin_write(RADIO_NSS,PIN_LOW);

    SpiInOut( SPIx, ( uint8_t )command );
    status = SpiInOut( SPIx, 0x00 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( SPIx, 0 );
    }

    rt_pin_write(RADIO_NSS,PIN_HIGH);

    SX126xWaitOnBusy( );

    return status;
}

void SX126xWriteRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    rt_pin_write(RADIO_NSS,PIN_LOW);
    
    SpiInOut( SPIx, RADIO_WRITE_REGISTER );
    SpiInOut( SPIx, ( address & 0xFF00 ) >> 8 );
    SpiInOut( SPIx, address & 0x00FF );
    
    for( uint16_t i = 0; i < size; i++ )
    {
        SpiInOut( SPIx, buffer[i] );
    }

    rt_pin_write(RADIO_NSS,PIN_HIGH);

    SX126xWaitOnBusy( );
}

void SX126xWriteRegister( uint16_t address, uint8_t value )
{
    SX126xWriteRegisters( address, &value, 1 );
}

void SX126xReadRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    rt_pin_write(RADIO_NSS,PIN_LOW);

    SpiInOut( SPIx, RADIO_READ_REGISTER );
    SpiInOut( SPIx, ( address & 0xFF00 ) >> 8 );
    SpiInOut( SPIx, address & 0x00FF );
    SpiInOut( SPIx, 0 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( SPIx, 0 );
    }
    rt_pin_write(RADIO_NSS,PIN_HIGH);

    SX126xWaitOnBusy( );
}

uint8_t SX126xReadRegister( uint16_t address )
{
    uint8_t data;
    SX126xReadRegisters( address, &data, 1 );
    return data;
}

void SX126xWriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    rt_pin_write(RADIO_NSS,PIN_LOW);

    SpiInOut( SPIx, RADIO_WRITE_BUFFER );
    SpiInOut( SPIx, offset );
    for( uint16_t i = 0; i < size; i++ )
    {
        SpiInOut( SPIx, buffer[i] );
    }

    rt_pin_write(RADIO_NSS,PIN_HIGH);

    SX126xWaitOnBusy( );
}

void SX126xReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    rt_pin_write(RADIO_NSS,PIN_LOW);

    SpiInOut( SPIx, RADIO_READ_BUFFER );
    SpiInOut( SPIx, offset );
    SpiInOut( SPIx, 0 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( SPIx, 0 );
    }
    rt_pin_write(RADIO_NSS,PIN_HIGH);

    SX126xWaitOnBusy( );
}

void SX126xSetRfTxPower( int8_t power )
{
    SX126xSetTxParams( power, RADIO_RAMP_40_US );
}

uint8_t SX126xGetDeviceId( void )
{
    return SX1262;
}

void SX126xAntSwOn( void )
{
    rt_pin_mode(RADIO_ANT_SWITCH_POWER,PIN_MODE_OUTPUT);
    rt_pin_write(RADIO_ANT_SWITCH_POWER,PIN_HIGH);
}

void SX126xAntSwOff( void )
{
    rt_pin_mode(RADIO_ANT_SWITCH_POWER,PIN_MODE_OUTPUT);
    rt_pin_write(RADIO_ANT_SWITCH_POWER,PIN_LOW);
}

bool SX126xCheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}
