//// Copyright (c) Microsoft. All rights reserved.
//// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
//#include <stdlib.h>
//#include <string.h>
//#include "azure_c_shared_utility/optimize_size.h"
//#include "azure_c_shared_utility/gballoc.h"
//#include "azure_c_shared_utility/string_tokenizer.h"
//#include "azure_c_shared_utility/doublylinkedlist.h"
//#include "azure_c_shared_utility/xlogging.h"
//#include "azure_c_shared_utility/tickcounter.h"
//#include "azure_c_shared_utility/constbuffer.h"
//#include "azure_c_shared_utility/platform.h"
//
//#include "internal/iothub_client_core_ll.h"
//#include "iothub_client_authorization.h"
//#include "iothub_client_ll.h"
//#include "iothub_transport_ll.h"
//#include "iothub_client_private.h"
//#include "iothub_client_options.h"
//#include "iothub_client_version.h"
//#include "iothub_client_diagnostic.h"
//#include <stdint.h>
//
//#ifdef USE_PROV_MODULE
//#include "iothub_client_hsm_ll.h"
//#endif
//
//#ifndef DONT_USE_UPLOADTOBLOB
//#include "iothub_client_ll_uploadtoblob.h"
//#endif
//
//
//IOTHUB_CLIENT_LL_HANDLE IoTHubClient_LL_CreateFromDeviceAuth(const char* iothub_uri, const char* device_id, IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol)
//{
//    return (IOTHUB_CLIENT_LL_HANDLE)IoTHubClientCore_LL_CreateFromDeviceAuth(iothub_uri, device_id, protocol);
//}
//
//IOTHUB_CLIENT_LL_HANDLE IoTHubClient_LL_CreateFromConnectionString(const char* connectionString, IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol)
//{
//    return (IOTHUB_CLIENT_LL_HANDLE)IoTHubClientCore_LL_CreateFromConnectionString(connectionString, protocol);
//}
//
//IOTHUB_CLIENT_LL_HANDLE IoTHubClient_LL_Create(const IOTHUB_CLIENT_CONFIG* config)
//{
//    return (IOTHUB_CLIENT_LL_HANDLE)IoTHubClientCore_LL_Create(config);
//}
//
//IOTHUB_CLIENT_LL_HANDLE IoTHubClient_LL_CreateWithTransport(const IOTHUB_CLIENT_DEVICE_CONFIG * config)
//{
//    return (IOTHUB_CLIENT_LL_HANDLE)IoTHubClientCore_LL_CreateWithTransport(config);
//}
//
//void IoTHubClient_LL_Destroy(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle)
//{
//    IoTHubClientCore_LL_Destroy((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SendEventAsync(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_MESSAGE_HANDLE eventMessageHandle, IOTHUB_CLIENT_EVENT_CONFIRMATION_CALLBACK eventConfirmationCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SendEventAsync((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, eventMessageHandle, eventConfirmationCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetMessageCallback(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_MESSAGE_CALLBACK_ASYNC messageCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SetMessageCallback((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, messageCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetMessageCallback_Ex(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_MESSAGE_CALLBACK_ASYNC_EX messageCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SetMessageCallback_Ex((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, messageCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SendMessageDisposition(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, MESSAGE_CALLBACK_INFO* message_data, IOTHUBMESSAGE_DISPOSITION_RESULT disposition)
//{
//    return IoTHubClientCore_LL_SendMessageDisposition((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, message_data, disposition);
//}
//
//void IoTHubClient_LL_DoWork(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle)
//{
//    IoTHubClientCore_LL_DoWork((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_GetSendStatus(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_STATUS *iotHubClientStatus)
//{
//    return IoTHubClientCore_LL_GetSendStatus((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, iotHubClientStatus);
//}
//
//void IoTHubClient_LL_SendComplete(IOTHUB_CLIENT_LL_HANDLE handle, PDLIST_ENTRY completed, IOTHUB_CLIENT_CONFIRMATION_RESULT result)
//{
//    IoTHubClientCore_LL_SendComplete((IOTHUB_CLIENT_CORE_LL_HANDLE)handle, completed, result);
//}
//
//int IoTHubClient_LL_DeviceMethodComplete(IOTHUB_CLIENT_LL_HANDLE handle, const char* method_name, const unsigned char* payLoad, size_t size, METHOD_HANDLE response_id)
//{
//    return IoTHubClientCore_LL_DeviceMethodComplete((IOTHUB_CLIENT_CORE_LL_HANDLE)handle, method_name, payLoad, size, response_id);
//}
//
//void IoTHubClient_LL_RetrievePropertyComplete(IOTHUB_CLIENT_LL_HANDLE handle, DEVICE_TWIN_UPDATE_STATE update_state, const unsigned char* payLoad, size_t size)
//{
//    IoTHubClientCore_LL_RetrievePropertyComplete((IOTHUB_CLIENT_CORE_LL_HANDLE)handle, update_state, payLoad, size);
//}
//
//void IoTHubClient_LL_ReportedStateComplete(IOTHUB_CLIENT_LL_HANDLE handle, uint32_t item_id, int status_code)
//{
//    IoTHubClientCore_LL_ReportedStateComplete((IOTHUB_CLIENT_CORE_LL_HANDLE)handle, item_id, status_code);
//}
//
//bool IoTHubClient_LL_MessageCallback(IOTHUB_CLIENT_LL_HANDLE handle, MESSAGE_CALLBACK_INFO* messageData)
//{
//    return IoTHubClientCore_LL_MessageCallback((IOTHUB_CLIENT_CORE_LL_HANDLE)handle, messageData);
//}
//
//void IoTHubClient_LL_ConnectionStatusCallBack(IOTHUB_CLIENT_LL_HANDLE handle, IOTHUB_CLIENT_CONNECTION_STATUS status, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason)
//{
//    IoTHubClientCore_LL_ConnectionStatusCallBack((IOTHUB_CLIENT_CORE_LL_HANDLE)handle, status, reason);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetConnectionStatusCallback(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_CONNECTION_STATUS_CALLBACK connectionStatusCallback, void * userContextCallback)
//{
//    return IoTHubClientCore_LL_SetConnectionStatusCallback((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, connectionStatusCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetRetryPolicy(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_RETRY_POLICY retryPolicy, size_t retryTimeoutLimitInSeconds)
//{
//    return IoTHubClientCore_LL_SetRetryPolicy((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, retryPolicy, retryTimeoutLimitInSeconds);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_GetRetryPolicy(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_RETRY_POLICY* retryPolicy, size_t* retryTimeoutLimitInSeconds)
//{
//    return IoTHubClientCore_LL_GetRetryPolicy((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, retryPolicy, retryTimeoutLimitInSeconds);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_GetLastMessageReceiveTime(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, time_t* lastMessageReceiveTime)
//{
//    return IoTHubClientCore_LL_GetLastMessageReceiveTime((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, lastMessageReceiveTime);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetOption(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, const char* optionName, const void* value)
//{
//    return IoTHubClientCore_LL_SetOption((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, optionName, value);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_GetOption(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, const char* optionName, void** value)
//{
//    return IoTHubClientCore_LL_GetOption((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, optionName, value);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetDeviceTwinCallback(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_DEVICE_TWIN_CALLBACK deviceTwinCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SetDeviceTwinCallback((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, deviceTwinCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SendReportedState(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, const unsigned char* reportedState, size_t size, IOTHUB_CLIENT_REPORTED_STATE_CALLBACK reportedStateCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SendReportedState((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, reportedState, size, reportedStateCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetDeviceMethodCallback(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_DEVICE_METHOD_CALLBACK_ASYNC deviceMethodCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SetDeviceMethodCallback((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, deviceMethodCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_SetDeviceMethodCallback_Ex(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, IOTHUB_CLIENT_INBOUND_DEVICE_METHOD_CALLBACK inboundDeviceMethodCallback, void* userContextCallback)
//{
//    return IoTHubClientCore_LL_SetDeviceMethodCallback_Ex((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, inboundDeviceMethodCallback, userContextCallback);
//}
//
//IOTHUB_CLIENT_RESULT IoTHubClient_LL_DeviceMethodResponse(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, METHOD_HANDLE methodId, const unsigned char* response, size_t response_size, int status_response)
//{
//    return IoTHubClientCore_LL_DeviceMethodResponse((IOTHUB_CLIENT_CORE_LL_HANDLE)iotHubClientHandle, methodId, response, response_size, status_response);
//}
