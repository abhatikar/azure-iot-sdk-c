// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/** @file iothub_client_ll.h
*	@brief	 APIs that allow a user (usually a device) to communicate
*		     with an Azure IoTHub.
*
*	@details IoTHubClient_LL is a module that allows a user (usually a
*			 device) to communicate with an Azure IoTHub. It can send events
*			 and receive messages. At any given moment in time there can only
*			 be at most 1 message callback function.
*
*			 This API surface contains a set of APIs that allows the user to
*			 interact with the lower layer portion of the IoTHubClient. These APIs
*			 contain @c _LL_ in their name, but retain the same functionality like the
*			 @c IoTHubClient_... APIs, with one difference. If the @c _LL_ APIs are
*			 used then the user is responsible for scheduling when the actual work done
*			 by the IoTHubClient happens (when the data is sent/received on/from the wire).
*			 This is useful for constrained devices where spinning a separate thread is
*			 often not desired.
*/

#ifndef IOTHUB_CLIENT_LL_CORE_H
#define IOTHUB_CLIENT_LL_CORE_H

#include "azure_c_shared_utility/macro_utils.h"
#include "azure_c_shared_utility/umock_c_prod.h"

#include "azure_c_shared_utility/agenttime.h"
#include "azure_c_shared_utility/xio.h"
#include "azure_c_shared_utility/doublylinkedlist.h"
#include "iothub_message.h"
#include "iothub_client_common.h"
#include "iothub_transport_ll.h"
#include "iothub_client_authorization.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


//maybe put this in upload to blob specific
#define IOTHUB_CLIENT_FILE_UPLOAD_RESULT_VALUES \
    FILE_UPLOAD_OK, \
    FILE_UPLOAD_ERROR

    DEFINE_ENUM(IOTHUB_CLIENT_FILE_UPLOAD_RESULT, IOTHUB_CLIENT_FILE_UPLOAD_RESULT_VALUES)
    
    typedef void(*IOTHUB_CLIENT_FILE_UPLOAD_CALLBACK)(IOTHUB_CLIENT_FILE_UPLOAD_RESULT result, void* userContextCallback);
    typedef struct IOTHUB_CLIENT_CORE_LL_HANDLE_DATA_TAG* IOTHUB_CLIENT_CORE_LL_HANDLE;

#ifndef DONT_USE_UPLOADTOBLOB

#define BLOCK_SIZE (4*1024*1024)

#define IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_RESULT_VALUES \
    IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_OK, \
    IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_ABORT

    DEFINE_ENUM(IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_RESULT, IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_RESULT_VALUES);

    /**
    *  @brief           Callback invoked by IoTHubClient_UploadMultipleBlocksToBlobAsync requesting the chunks of data to be uploaded.
    *  @param result    The result of the upload of the previous block of data provided by the user (IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_CALLBACK_EX only)
    *  @param data      Next block of data to be uploaded, to be provided by the user when this callback is invoked.
    *  @param size      Size of the data parameter.
    *  @param context   User context provided on the call to IoTHubClient_UploadMultipleBlocksToBlobAsync.
    *  @remarks         If the user wants to abort the upload, the callback should return IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_ABORT
    *                   It should return IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_OK otherwise.
    *                   If a NULL is provided for parameter "data" and/or zero is provided for "size", the user indicates to the client that the complete file has been uploaded.
    *                   In such case this callback will be invoked only once more to indicate the status of the final block upload.
    *                   If result is not FILE_UPLOAD_OK, the download is cancelled and this callback stops being invoked.
    *                   When this callback is called for the last time, no data or size is expected, so data and size are set to NULL
    */
    typedef void(*IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_CALLBACK)(IOTHUB_CLIENT_FILE_UPLOAD_RESULT result, unsigned char const ** data, size_t* size, void* context);
    typedef IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_RESULT(*IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_CALLBACK_EX)(IOTHUB_CLIENT_FILE_UPLOAD_RESULT result, unsigned char const ** data, size_t* size, void* context);
#endif /* DONT_USE_UPLOADTOBLOB */

     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_CORE_LL_HANDLE, IoTHubClientCore_LL_CreateFromConnectionString, const char*, connectionString, IOTHUB_CLIENT_TRANSPORT_PROVIDER, protocol);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_CORE_LL_HANDLE, IoTHubClientCore_LL_Create, const IOTHUB_CLIENT_CONFIG*, config);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_CORE_LL_HANDLE, IoTHubClientCore_LL_CreateWithTransport, const IOTHUB_CLIENT_DEVICE_CONFIG*, config);
     MOCKABLE_FUNCTION(, void, IoTHubClientCore_LL_Destroy, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SendEventAsync, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_MESSAGE_HANDLE, eventMessageHandle, IOTHUB_CLIENT_EVENT_CONFIRMATION_CALLBACK, eventConfirmationCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_GetSendStatus, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_STATUS*, iotHubClientStatus);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetMessageCallback, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_MESSAGE_CALLBACK_ASYNC, messageCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetConnectionStatusCallback, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_CONNECTION_STATUS_CALLBACK, connectionStatusCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetRetryPolicy, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_RETRY_POLICY, retryPolicy, size_t, retryTimeoutLimitInSeconds);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_GetRetryPolicy, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_RETRY_POLICY*, retryPolicy, size_t*, retryTimeoutLimitInSeconds);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_GetLastMessageReceiveTime, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, time_t*, lastMessageReceiveTime);
     MOCKABLE_FUNCTION(, void, IoTHubClientCore_LL_DoWork, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetOption, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, const char*, optionName, const void*, value);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetDeviceTwinCallback, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_DEVICE_TWIN_CALLBACK, deviceTwinCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SendReportedState, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, const unsigned char*, reportedState, size_t, size, IOTHUB_CLIENT_REPORTED_STATE_CALLBACK, reportedStateCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetDeviceMethodCallback, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_DEVICE_METHOD_CALLBACK_ASYNC, deviceMethodCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_SetDeviceMethodCallback_Ex, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, IOTHUB_CLIENT_INBOUND_DEVICE_METHOD_CALLBACK, inboundDeviceMethodCallback, void*, userContextCallback);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_DeviceMethodResponse, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, METHOD_HANDLE, methodId, const unsigned char*, response, size_t, respSize, int, statusCode);


#ifndef DONT_USE_UPLOADTOBLOB
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_UploadToBlob, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, const char*, destinationFileName, const unsigned char*, source, size_t, size);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_UploadMultipleBlocksToBlob, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, const char*, destinationFileName, IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_CALLBACK, getDataCallback, void*, context);
     MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTHubClientCore_LL_UploadMultipleBlocksToBlobEx, IOTHUB_CLIENT_CORE_LL_HANDLE, iotHubClientHandle, const char*, destinationFileName, IOTHUB_CLIENT_FILE_UPLOAD_GET_DATA_CALLBACK_EX, getDataCallbackEx, void*, context);

#endif /*DONT_USE_UPLOADTOBLOB*/

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_CLIENT_LL_H */
