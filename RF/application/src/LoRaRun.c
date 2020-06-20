#include <rtthread.h>
#include <rtdevice.h>
#include <stdio.h>
#include "utilities.h"
#include "RF_board.h"
#include "LoRaMac.h"
#include "Commissioning.h"
#include "NvmCtxMgmt.h"
#include "string.h"
#include "sx126x.h"
#include "LoRaRun.h"

#ifndef ACTIVE_REGION
#define ACTIVE_REGION LORAMAC_REGION_CN470
#endif

#define APP_TX_DUTYCYCLE                            5000
#define APP_TX_DUTYCYCLE_RND                        1000
#define LORAWAN_DEFAULT_DATARATE                    DR_5
#define LORAWAN_CONFIRMED_MSG_ON                    false
#define LORAWAN_ADR_ON                              false
#define LORAWAN_APP_DATA_MAX_SIZE                   242
#define LORAWAN_APP_PORT                            3

static uint8_t FNwkSIntKey[] = LORAWAN_F_NWK_S_INT_KEY;
static uint8_t SNwkSIntKey[] = LORAWAN_S_NWK_S_INT_KEY;
static uint8_t NwkSEncKey[] = LORAWAN_NWK_S_ENC_KEY;
static uint8_t AppSKey[] = LORAWAN_APP_S_KEY;
uint32_t DevAddr = LORAWAN_DEVICE_ADDRESS;
#if defined(OTAA)
static uint8_t AppKey[] = LORAWAN_APP_KEY;
static uint8_t NwkKey[] = LORAWAN_NWK_KEY;
static uint8_t devEui[] = LORAWAN_DEVICE_EUI;
static uint8_t joinEui[] = LORAWAN_JOIN_EUI;
#endif
static uint8_t AppPort = LORAWAN_APP_PORT;
static uint8_t AppDataSize = 1;
static uint8_t AppDataBuffer[LORAWAN_APP_DATA_MAX_SIZE];
static uint8_t IsTxConfirmed = LORAWAN_CONFIRMED_MSG_ON;
static uint32_t TxDutyCycleTime;
static rt_timer_t TxNextPacketTimer;
static bool NextTx = true;

static enum eDeviceState
{
    DEVICE_STATE_RESTORE,
    DEVICE_STATE_START,
    DEVICE_STATE_JOIN,
    DEVICE_STATE_SEND,
    DEVICE_STATE_CYCLE,
    DEVICE_STATE_RXC,
    DEVICE_STATE_SLEEP
}DeviceState;

struct ComplianceTest_s
{
    bool Running;
    uint8_t State;
    bool IsTxConfirmed;
    uint8_t AppPort;
    uint8_t AppDataSize;
    uint8_t *AppDataBuffer;
    uint16_t DownLinkCounter;
    bool LinkCheck;
    uint8_t DemodMargin;
    uint8_t NbGateways;
}ComplianceTest;

typedef enum
{
    LORAMAC_HANDLER_UNCONFIRMED_MSG = 0,
    LORAMAC_HANDLER_CONFIRMED_MSG = !LORAMAC_HANDLER_UNCONFIRMED_MSG
}LoRaMacHandlerMsgTypes_t;

typedef struct LoRaMacHandlerAppData_s
{
    LoRaMacHandlerMsgTypes_t MsgType;
    uint8_t Port;
    uint8_t BufferSize;
    uint8_t *Buffer;
}LoRaMacHandlerAppData_t;

LoRaMacHandlerAppData_t AppData =
{
    .MsgType = LORAMAC_HANDLER_UNCONFIRMED_MSG,
    .Buffer = NULL,
    .BufferSize = 0,
    .Port = 0
};

/*!
 * LED GPIO pins objects
 */

void PrintHexBuffer( uint8_t *buffer, uint8_t size )
{
    uint8_t newline = 0;

    for( uint8_t i = 0; i < size; i++ )
    {
        if( newline != 0 )
        {
            //printf( "\r\n" );
            newline = 0;
        }

        //printf( "%02X ", buffer[i] );

        if( ( ( i + 1 ) % 16 ) == 0 )
        {
            newline = 1;
        }
    }
    //printf( "\r\n" );
}

static void JoinNetwork( void )
{
    LoRaMacStatus_t status;
    MlmeReq_t mlmeReq;
    mlmeReq.Type = MLME_JOIN;
    mlmeReq.Req.Join.Datarate = LORAWAN_DEFAULT_DATARATE;

    status = LoRaMacMlmeRequest( &mlmeReq );
    if( status == LORAMAC_STATUS_OK )
    {
        //printf( "###### ===== JOINING ==== ######\r\n" );
        DeviceState = DEVICE_STATE_SLEEP;
    }
    else
    {
        DeviceState = DEVICE_STATE_CYCLE;
    }
}

static void PrepareTxFrame( uint8_t port )
{
        AppDataBuffer[0] = 0x01;
        AppDataSize = 1;
}
static void UserPrepareTxFrame( uint8_t port,uint8_t *buffer,uint8_t size )
{
        memset1(AppDataBuffer,0,sizeof(AppDataBuffer));
        memcpy1(AppDataBuffer,buffer,sizeof(AppDataBuffer));
        AppDataSize = size;
}
static bool SendFrame( void )
{
    McpsReq_t mcpsReq;
    LoRaMacTxInfo_t txInfo;

    if( LoRaMacQueryTxPossible( AppDataSize, &txInfo ) != LORAMAC_STATUS_OK )
    {
        mcpsReq.Type = MCPS_UNCONFIRMED;
        mcpsReq.Req.Unconfirmed.fBuffer = NULL;
        mcpsReq.Req.Unconfirmed.fBufferSize = 0;
        mcpsReq.Req.Unconfirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
    }
    else
    {
        if( IsTxConfirmed == false )
        {
            mcpsReq.Type = MCPS_UNCONFIRMED;
            mcpsReq.Req.Unconfirmed.fPort = AppPort;
            mcpsReq.Req.Unconfirmed.fBuffer = AppDataBuffer;
            mcpsReq.Req.Unconfirmed.fBufferSize = AppDataSize;
            mcpsReq.Req.Unconfirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
        }
        else
        {
            mcpsReq.Type = MCPS_CONFIRMED;
            mcpsReq.Req.Confirmed.fPort = AppPort;
            mcpsReq.Req.Confirmed.fBuffer = AppDataBuffer;
            mcpsReq.Req.Confirmed.fBufferSize = AppDataSize;
            mcpsReq.Req.Confirmed.NbTrials = 1;
            mcpsReq.Req.Confirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
        }
    }

    AppData.MsgType = ( mcpsReq.Type == MCPS_CONFIRMED ) ? LORAMAC_HANDLER_CONFIRMED_MSG : LORAMAC_HANDLER_UNCONFIRMED_MSG;
    AppData.Port = mcpsReq.Req.Unconfirmed.fPort;
    AppData.Buffer = mcpsReq.Req.Unconfirmed.fBuffer;
    AppData.BufferSize = mcpsReq.Req.Unconfirmed.fBufferSize;

    LoRaMacStatus_t status;
    status = LoRaMacMcpsRequest( &mcpsReq );

    if( status == LORAMAC_STATUS_OK )
    {
        return false;
    }
    return true;
}
bool DataSend( uint8_t *buffer, uint8_t size)
{
    McpsReq_t mcpsReq;
    LoRaMacTxInfo_t txInfo;
    UserPrepareTxFrame(3,buffer,size);
    if( LoRaMacQueryTxPossible( AppDataSize, &txInfo ) != LORAMAC_STATUS_OK )
    {
        mcpsReq.Type = MCPS_UNCONFIRMED;
        mcpsReq.Req.Unconfirmed.fBuffer = NULL;
        mcpsReq.Req.Unconfirmed.fBufferSize = 0;
        mcpsReq.Req.Unconfirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
    }
    else
    {
        if( IsTxConfirmed == false )
        {
            mcpsReq.Type = MCPS_UNCONFIRMED;
            mcpsReq.Req.Unconfirmed.fPort = AppPort;
            mcpsReq.Req.Unconfirmed.fBuffer = AppDataBuffer;
            mcpsReq.Req.Unconfirmed.fBufferSize = AppDataSize;
            mcpsReq.Req.Unconfirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
        }
        else
        {
            mcpsReq.Type = MCPS_CONFIRMED;
            mcpsReq.Req.Confirmed.fPort = AppPort;
            mcpsReq.Req.Confirmed.fBuffer = AppDataBuffer;
            mcpsReq.Req.Confirmed.fBufferSize = AppDataSize;
            mcpsReq.Req.Confirmed.NbTrials = 3;
            mcpsReq.Req.Confirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
        }
    }

    AppData.MsgType = ( mcpsReq.Type == MCPS_CONFIRMED ) ? LORAMAC_HANDLER_CONFIRMED_MSG : LORAMAC_HANDLER_UNCONFIRMED_MSG;
    AppData.Port = mcpsReq.Req.Unconfirmed.fPort;
    AppData.Buffer = mcpsReq.Req.Unconfirmed.fBuffer;
    AppData.BufferSize = mcpsReq.Req.Unconfirmed.fBufferSize;

    LoRaMacStatus_t status;
    status = LoRaMacMcpsRequest( &mcpsReq );
    if( status == LORAMAC_STATUS_OK )
    {
        return false;
    }
    return true;
}
bool ConfirmedDataSend( uint8_t *buffer, uint8_t size, uint8_t nbtrials)
{
    McpsReq_t mcpsReq;
    LoRaMacTxInfo_t txInfo;

    UserPrepareTxFrame(10,buffer,size);

    if( LoRaMacQueryTxPossible( AppDataSize, &txInfo ) != LORAMAC_STATUS_OK )
    {
        mcpsReq.Type = MCPS_UNCONFIRMED;
        mcpsReq.Req.Unconfirmed.fBuffer = NULL;
        mcpsReq.Req.Unconfirmed.fBufferSize = 0;
        mcpsReq.Req.Unconfirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
    }
    else
    {
                mcpsReq.Type = MCPS_CONFIRMED;
                mcpsReq.Req.Confirmed.fPort = AppPort;
                mcpsReq.Req.Confirmed.fBuffer = AppDataBuffer;
                mcpsReq.Req.Confirmed.fBufferSize = AppDataSize;
                mcpsReq.Req.Confirmed.NbTrials = nbtrials;
                mcpsReq.Req.Confirmed.Datarate = LORAWAN_DEFAULT_DATARATE;
    }

    AppData.MsgType = ( mcpsReq.Type == MCPS_CONFIRMED ) ? LORAMAC_HANDLER_CONFIRMED_MSG : LORAMAC_HANDLER_UNCONFIRMED_MSG;
    AppData.Port = mcpsReq.Req.Unconfirmed.fPort;
    AppData.Buffer = mcpsReq.Req.Unconfirmed.fBuffer;
    AppData.BufferSize = mcpsReq.Req.Unconfirmed.fBufferSize;

    LoRaMacStatus_t status;
    status = LoRaMacMcpsRequest( &mcpsReq );

    if( status == LORAMAC_STATUS_OK )
    {
        return false;
    }
    return true;
}

static void OnTxNextPacketTimerEvent( void* context )
{
    MibRequestConfirm_t mibReq;
    LoRaMacStatus_t status;

    rt_timer_stop( TxNextPacketTimer );

    mibReq.Type = MIB_NETWORK_ACTIVATION;
    status = LoRaMacMibGetRequestConfirm( &mibReq );

    if( status == LORAMAC_STATUS_OK )
    {
        if( mibReq.Param.NetworkActivation == ACTIVATION_TYPE_NONE )
        {
            JoinNetwork( );
        }
        else
        {
            DeviceState = DEVICE_STATE_SEND;
            NextTx = true;
        }
    }
}

static void McpsConfirm( McpsConfirm_t *mcpsConfirm )
{
    if( mcpsConfirm->Status != LORAMAC_EVENT_INFO_STATUS_OK )
    {
    }
    else
    {
        switch( mcpsConfirm->McpsRequest )
        {
            case MCPS_UNCONFIRMED:
            {
                break;
            }
            case MCPS_CONFIRMED:
            {
                break;
            }
            case MCPS_PROPRIETARY:
            {
                break;
            }
            default:
                break;
        }
    }
    MibRequestConfirm_t mibReq;

    mibReq.Type = MIB_DEVICE_CLASS;
    LoRaMacMibGetRequestConfirm( &mibReq );

}
static void McpsIndication( McpsIndication_t *mcpsIndication )
{
    if( mcpsIndication->Status != LORAMAC_EVENT_INFO_STATUS_OK )
    {
        return;
    }

    if( mcpsIndication->FramePending == true )
    {
        OnTxNextPacketTimerEvent( NULL );
    }
    if( ComplianceTest.Running == true )
    {
        ComplianceTest.DownLinkCounter++;
    }

    if( mcpsIndication->RxData == true )
    {
    }

    if( mcpsIndication->BufferSize != 0 )
    {
        rt_thread_mdelay(200);
        DataSend(mcpsIndication->Buffer, mcpsIndication->BufferSize);
        memset1(mcpsIndication->Buffer,0,mcpsIndication->BufferSize);
    }
}

static void MlmeConfirm( MlmeConfirm_t *mlmeConfirm )
{
    if( mlmeConfirm->Status != LORAMAC_EVENT_INFO_STATUS_OK )
    {
    }
    switch( mlmeConfirm->MlmeRequest )
    {
        case MLME_JOIN:
        {
            if( mlmeConfirm->Status == LORAMAC_EVENT_INFO_STATUS_OK )
            {
                MibRequestConfirm_t mibGet;
                //printf( "###### ===== JOINED ==== ######\r\n" );
                //printf( "\r\nOTAA\r\n\r\n" );

                mibGet.Type = MIB_DEV_ADDR;
                LoRaMacMibGetRequestConfirm( &mibGet );
                //printf( "DevAddr     : %08lX\r\n", mibGet.Param.DevAddr );

                //printf( "\n\r\n" );
                mibGet.Type = MIB_CHANNELS_DATARATE;
                LoRaMacMibGetRequestConfirm( &mibGet );
                //printf( "DATA RATE   : DR_%d\r\n", mibGet.Param.ChannelsDatarate );
                //printf( "\r\n" );
                DeviceState = DEVICE_STATE_SEND;
            }
            else
            {
                JoinNetwork( );
            }
            break;
        }
        case MLME_LINK_CHECK:
        {
            if( mlmeConfirm->Status == LORAMAC_EVENT_INFO_STATUS_OK )
            {
                if( ComplianceTest.Running == true )
                {
                    ComplianceTest.LinkCheck = true;
                    ComplianceTest.DemodMargin = mlmeConfirm->DemodMargin;
                    ComplianceTest.NbGateways = mlmeConfirm->NbGateways;
                }
            }
            break;
        }
        default:
            break;
    }
}

static void MlmeIndication( MlmeIndication_t *mlmeIndication )
{
    if( mlmeIndication->Status != LORAMAC_EVENT_INFO_STATUS_BEACON_LOCKED )
    {
    }
    if( mlmeIndication->Status != LORAMAC_EVENT_INFO_STATUS_OK )
    {
    }
    switch( mlmeIndication->MlmeIndication )
    {
        case MLME_SCHEDULE_UPLINK:
        {
            OnTxNextPacketTimerEvent( NULL );
            break;
        }
        default:
            break;
    }
}
static void OnMacProcessNotify( )
{
}
uint8_t buffer[5]={1,2,3,4,5};
void testsend(void)
{
    DataSend(buffer, 5);
}
void LoRaRun( void *parameter)
{
    LoRaMacPrimitives_t macPrimitives;
    LoRaMacCallback_t macCallbacks;
    MibRequestConfirm_t mibReq;

    macPrimitives.MacMcpsConfirm = McpsConfirm;
    macPrimitives.MacMcpsIndication = McpsIndication;
    macPrimitives.MacMlmeConfirm = MlmeConfirm;
    macPrimitives.MacMlmeIndication = MlmeIndication;
    macCallbacks.MacProcessNotify = OnMacProcessNotify;
    macCallbacks.NvmContextChange = NvmCtxMgmtEvent;
    LoRaMacInitialization( &macPrimitives, &macCallbacks, ACTIVE_REGION );

    while( 1 )
    {

        if( Radio.IrqProcess != NULL )
        {
            Radio.IrqProcess( );
        }

        LoRaMacProcess( );

        switch( DeviceState )
        {
            case DEVICE_STATE_RESTORE:
            {
                DeviceState = DEVICE_STATE_START;
                break;
            }

            case DEVICE_STATE_START:
            {
                //TimerInit( &TxNextPacketTimer, OnTxNextPacketTimerEvent );
                TxNextPacketTimer = rt_timer_create("TxNextPacketTimer", OnTxNextPacketTimerEvent,RT_NULL, 10,RT_TIMER_FLAG_PERIODIC);


                mibReq.Type = MIB_DEVICE_CLASS;
                mibReq.Param.Class = CLASS_C;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_NETWORK_ACTIVATION;
                mibReq.Param.NetworkActivation = ACTIVATION_TYPE_ABP;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_PUBLIC_NETWORK;
                mibReq.Param.EnablePublicNetwork = LORAWAN_PUBLIC_NETWORK;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_ADR;
                mibReq.Param.AdrEnable = LORAWAN_ADR_ON;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_SYSTEM_MAX_RX_ERROR;
                mibReq.Param.SystemMaxRxError = 20;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_NET_ID;
                mibReq.Param.NetID = LORAWAN_NETWORK_ID;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_DEV_ADDR;
                mibReq.Param.DevAddr = DevAddr;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_F_NWK_S_INT_KEY;
                mibReq.Param.FNwkSIntKey = FNwkSIntKey;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_S_NWK_S_INT_KEY;
                mibReq.Param.SNwkSIntKey = SNwkSIntKey;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_NWK_S_ENC_KEY;
                mibReq.Param.NwkSEncKey = NwkSEncKey;
                LoRaMacMibSetRequestConfirm( &mibReq );

                mibReq.Type = MIB_APP_S_KEY;
                mibReq.Param.AppSKey = AppSKey;
                LoRaMacMibSetRequestConfirm( &mibReq );


                LoRaMacStart();
                testsend();

                DeviceState = DEVICE_STATE_SLEEP;

                break;
            }
            case DEVICE_STATE_JOIN:
            {
                mibReq.Type = MIB_DEV_EUI;
                LoRaMacMibGetRequestConfirm( &mibReq );

                mibReq.Type = MIB_JOIN_EUI;
                LoRaMacMibGetRequestConfirm( &mibReq );

                mibReq.Type = MIB_NETWORK_ACTIVATION;
                mibReq.Param.NetworkActivation = ACTIVATION_TYPE_ABP;
                LoRaMacMibSetRequestConfirm( &mibReq );

                DeviceState = DEVICE_STATE_SEND;

                break;
            }
            case DEVICE_STATE_SEND:
            {
                if( NextTx == true )
                {
                  PrepareTxFrame( AppPort );
                  NextTx = SendFrame( );
                }
                DeviceState = DEVICE_STATE_SLEEP;
                break;
            }
            case DEVICE_STATE_CYCLE:
            {
                DeviceState = DEVICE_STATE_SLEEP;
                if( ComplianceTest.Running == true )
                {
                        TxDutyCycleTime = 5000; // 5000 ms
                }
                else
                {
                        TxDutyCycleTime = APP_TX_DUTYCYCLE + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
                }
                rt_timer_control( TxNextPacketTimer, RT_TIMER_CTRL_SET_TIME,(void*)&TxDutyCycleTime );
                rt_timer_start( TxNextPacketTimer );
                break;
            }
            case DEVICE_STATE_RXC:
            {
                DeviceState = DEVICE_STATE_SLEEP;
                break;
            }
            case DEVICE_STATE_SLEEP:
            {
                break;
            }
          }
        rt_thread_mdelay(100);
    }
}
static rt_thread_t tid1 = RT_NULL;
void LoRaTaskInit(void)
{
    BoardInitMcu();
    tid1 = rt_thread_create("LoRaTask",LoRaRun, RT_NULL,1024,10, 20);
    if (tid1 != RT_NULL)
    rt_thread_startup(tid1);
}
