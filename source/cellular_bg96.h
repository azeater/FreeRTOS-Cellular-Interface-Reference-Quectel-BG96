/*
 * FreeRTOS-Cellular-Interface v1.3.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 */

#ifndef __CELLULAR_BG96_H__
#define __CELLULAR_BG96_H__

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* AT Command timeout for PDN activation */
#define PDN_ACTIVATION_PACKET_REQ_TIMEOUT_MS       ( 150000UL )

/* AT Command timeout for PDN deactivation. */
#define PDN_DEACTIVATION_PACKET_REQ_TIMEOUT_MS     ( 40000UL )

/* AT Command timeout for Socket connection */
#define SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS       ( 150000UL )

#define PACKET_REQ_TIMEOUT_MS                      ( 5000UL )

/* AT Command timeout for Socket disconnection */
#define SOCKET_DISCONNECT_PACKET_REQ_TIMEOUT_MS    ( 12000UL )

#define DATA_SEND_TIMEOUT_MS                       ( 50000UL )
#define DATA_READ_TIMEOUT_MS                       ( 50000UL )

/**
 * @brief DNS query result.
 */
typedef enum cellularDnsQueryResult
{
    CELLULAR_DNS_QUERY_SUCCESS,
    CELLULAR_DNS_QUERY_FAILED,
    CELLULAR_DNS_QUERY_MAX,
    CELLULAR_DNS_QUERY_UNKNOWN
} cellularDnsQueryResult_t;

typedef struct cellularModuleContext cellularModuleContext_t;

/**
 * @brief DNS query URC callback fucntion.
 */
typedef void ( * CellularDnsResultEventCallback_t )( cellularModuleContext_t * pModuleContext,
                                                     char * pDnsResult,
                                                     char * pDnsUsrData );
typedef enum CellularMqttState
{
    MQTTSTATE_ALLOCATED = 0, /**< Socket is created. */
    MQTTSTATE_OPENING,
    MQTTSTATE_OPENED,
    MQTTSTATE_CONNECTING,    /**< Socket is connecting in progress with remote peer. */
    MQTTSTATE_CONNECTED,     /**< Socket is connected. */
    MQTTSTATE_DISCONNECTED,   /**< Socket is disconnected by remote peer or due to network error. */
} CellularMqttState_t;

typedef enum CellulartUrcMqttEvent
{
    CELLULAR_URC_MQTT_PUBLISH = 0,
    CELLULAR_URC_MQTT_SUBSCRIBE,
    CELLULAR_URC_MQTT_UNSUBSCRIBE,
} CellularUrcMqttEvent_t;

typedef struct CellularMqttSocketContext CellularMqttSocketContext_t;

typedef void (* CellularMqttOpenCallback_t )( CellularMqttSocketContext_t * mqttContext, void* context );
typedef void (* CellularMqttCloseCallback_t )( CellularMqttSocketContext_t * mqttContext, void* context );
typedef void (* CellularMqttConnectCallback_t )( CellularMqttSocketContext_t * mqttContext, void* context );
typedef void (* CellularMqttDisconnectCallback_t )( CellularMqttSocketContext_t * mqttContext, void* context );
typedef void (* CellularMqttOutgoingResponseCallback_t )( CellularUrcMqttEvent_t event, uint8_t result,
                                                          CellularMqttSocketContext_t * mqttContext, void* context );
typedef void (* CellularMqttReceiveCallback_t )( char* topic, char* payload, CellularMqttSocketContext_t * mqttContext, void* context );
typedef void (* CellularMqttStateCallback_t )( uint8_t status, CellularMqttSocketContext_t * mqttContext, void* context );

typedef struct CellularMqttSocketContext
{
    CellularHandle_t cellularHandle;
    uint8_t          cellularMqttIndex;
    int8_t           sslIndex;

    CellularMqttState_t mqttState;

    /* Callback functions */
    CellularMqttOpenCallback_t openCallback;
    void* openCallbackContext;
    CellularMqttCloseCallback_t closeCallback;
    void* closeCallbackContext;
    CellularMqttConnectCallback_t connectCallback;
    void* connectCallbackContext;
    CellularMqttDisconnectCallback_t disconnectCallback;
    void* disconnectCallbackContext;
    CellularMqttOutgoingResponseCallback_t outgoingCallback;
    void* outgoingCallbackContext;
    CellularMqttReceiveCallback_t receiveCallback;
    void* receiveCallbackContext;
    CellularMqttStateCallback_t stateCallback;
    void* stateCallbackContext;
} CellularMqttSocketContext_t;

typedef struct cellularModuleContext
{
    /* DNS related variables. */
    PlatformMutex_t dnsQueryMutex; /* DNS query mutex to protect the following data. */
    QueueHandle_t pktDnsQueue;     /* DNS queue to receive the DNS query result. */
    uint8_t dnsResultNumber;       /* DNS query result number. */
    uint8_t dnsIndex;              /* DNS query current index. */
    char * pDnsUsrData;            /* DNS user data to store the result. */
    CellularDnsResultEventCallback_t dnsEventCallback;
    /* Forward declaration to declar the callback function prototype. */
    /* coverity[misra_c_2012_rule_1_1_violation]. */
    CellularMqttSocketContext_t moduleMqttSockets[CELLULAR_NUM_SOCKET_MAX];
} cellularModuleContext_t;

CellularPktStatus_t _Cellular_ParseSimstat( char * pInputStr,
                                            CellularSimCardState_t * pSimState );

CellularError_t Cellular_CreateMqttSocket( CellularContext_t * pContext, int8_t* pMqttIndex);

CellularMqttSocketContext_t * Cellular_GetMqttContext( uint8_t mqttIndex );

void Cellular_DeleteMqttContext( uint8_t mqttIndex );

extern CellularAtParseTokenMap_t CellularUrcHandlerTable[];
extern uint32_t CellularUrcHandlerTableSize;

extern const char * CellularSrcTokenErrorTable[];
extern uint32_t CellularSrcTokenErrorTableSize;

extern const char * CellularSrcTokenSuccessTable[];
extern uint32_t CellularSrcTokenSuccessTableSize;

extern const char * CellularUrcTokenWoPrefixTable[];
extern uint32_t CellularUrcTokenWoPrefixTableSize;

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* ifndef __CELLULAR_BG96_H__ */
