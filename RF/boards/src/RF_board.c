/*!
 * \file      board.c
 *
 * \brief     Target board general functions implementation
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
#include "utilities.h"
#include "board-config.h"
#include "sx126x-board.h"
#include "RF_board.h"
#include "LoRaRun.h"
#include "Commissioning.h"
#include "rtc-board.h"
#include "timer.h"
void BoardInitMcu( void )
{
    SX126xSpiInit( );
    SX126xIoInit( );
}

void BoardDeInitMcu( void )
{
    SX126xIoDeInit( );
}
