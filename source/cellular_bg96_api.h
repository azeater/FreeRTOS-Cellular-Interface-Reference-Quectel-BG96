#ifndef CELLULAR_BG96_API_H
#define CELLULAR_BG96_API_H

/* The config header is always included first. */
#include "cellular_config.h"
#include "cellular_config_defaults.h"

/* IoT Cellular data types. */
#include "cellular_types.h"

#define BG96_API_NO_SSL_CONTEXT_ID    (-1)
#define BG96_API_MQTT_SSL_CONTEXT_ID  (1)
#define BG96_API_HTTPS_SSL_CONTEXT_ID (2)

typedef struct CellularSocketSslConfig
{
    uint8_t useSsl;
    uint8_t sslContextId;
} CellularSocketSslConfig_t;

/* Upload credential to the file system. Later it can be used to configure the secure socket context. */
CellularError_t Cellular_UploadFileToStorage( CellularHandle_t cellularHandle,
                                              const char* filename,
                                              const char* fileContent,
                                              uint32_t fileSize,
                                              uint32_t* pSentDataLength );

/* Configure the secure socket context. */
CellularError_t Cellular_ConfigureSSLContext( CellularHandle_t cellularHandle,
                                              uint8_t sslContextId,
                                              const char* sslConfigurationParameter,
                                              const char* inputArg,
                                              bool isNumeric );

/* Used to delete credentials from file system */
CellularError_t Cellular_DeleteFileFromStorage( CellularHandle_t cellularHandle,
                                                const char* filename );

/* Used to check if credentials exist on file system */
CellularError_t Cellular_CheckFileExistsInStorage( CellularHandle_t cellularHandle,
                                                   const char* filename,
                                                   bool * fileExists );

//MQTT Modifications

CellularError_t Cellular_MqttConfigureGeneric(CellularHandle_t cellularHandle,
                                              uint8_t mqttContextId,
                                              const char* mqttConfigurationParameter,
                                              const char* inputArg,
                                              bool isNumeric);

CellularError_t Cellular_MqttConfigureSsl(CellularHandle_t cellularHandle,
                                          uint8_t mqttContextId,
                                          bool enable_ssl,
                                          uint8_t sslContextId);

CellularError_t Cellular_MqttConfigureTimeout(CellularHandle_t cellularHandle,
                                              uint8_t mqttContextId,
                                              uint8_t packet_timeout,
                                              uint8_t max_retry_attempts,
                                              bool report_timeout);

CellularError_t Cellular_MqttConfigureWill(CellularHandle_t cellularHandle,
                                           uint8_t mqttContextId,
                                           bool will_flag_required,
                                           uint8_t will_qos,
                                           bool retain_will_message,
                                           const char* will_topic,
                                           const char* will_message);

CellularError_t Cellular_MqttConfigureReceiveMode(CellularHandle_t cellularHandle,
                                                  uint8_t mqttContextId,
                                                  bool message_not_in_urc,
                                                  bool message_length_in_urc);

CellularError_t Cellular_MqttOpen(CellularHandle_t cellularHandle,
                                  uint8_t mqttContextId,
                                  const char* endpoint,
                                  uint32_t port);

CellularError_t Cellular_MqttClose(CellularHandle_t cellularHandle,
                                   uint8_t mqttContextId);

CellularError_t Cellular_MqttConnect(CellularHandle_t cellularHandle,
                                     uint8_t mqttContextId,
                                     const char* clientId);

CellularError_t Cellular_MqttDisconnect(CellularHandle_t cellularHandle,
                                        uint8_t mqttContextId);

CellularError_t Cellular_MqttPublish(CellularHandle_t cellularHandle,
                                     uint8_t mqttContextId,
                                     uint16_t messageId,
                                     uint8_t qos,
                                     bool retain,
                                     const char* topic,
                                     const char* message,
                                     uint32_t messageLength,
                                     uint32_t* sentDataLength);

CellularError_t Cellular_MqttSubscribe(CellularHandle_t cellularHandle,
                                       uint8_t mqttContextId,
                                       uint16_t messageId,
                                       const char* topic,
                                       uint8_t qos);

CellularError_t Cellular_MqttUnsubscribe(CellularHandle_t cellularHandle,
                                         uint8_t mqttContextId,
                                         uint16_t messageId,
                                         const char* topic);

CellularError_t Cellular_MqttReadIncomingPublish( CellularHandle_t cellularHandle,
                                                  uint8_t mqttContextId,
                                                  uint8_t mqttBufferIndex,
                                                  uint8_t * pBuffer,
                                                  uint32_t bufferLength,
                                                  uint32_t * pReceivedDataLength,
                                                  char * topic,
                                                  uint32_t topicBufferLength,
                                                  uint32_t * receivedTopicLength);


#endif
