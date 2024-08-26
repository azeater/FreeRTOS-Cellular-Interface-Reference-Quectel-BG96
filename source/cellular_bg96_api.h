#ifndef CELLULAR_BG96_API_H
#define CELLULAR_BG96_API_H

/* The config header is always included first. */
#include "cellular_config.h"
#include "cellular_config_defaults.h"

/* IoT Cellular data types. */
#include "cellular_types.h"

// TODO: Create an enum instead of defines
#define NO_SSL_CONTEXT_ID    (-1)
#define MQTT_SSL_CONTEXT_ID  (1)
#define HTTPS_SSL_CONTEXT_ID (2)

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


#endif
