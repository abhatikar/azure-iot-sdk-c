// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/** @file iothub_client.h
*	@brief Extends the IoTHubCLient_LL module with additional features.
*
*	@details IoTHubClient is a module that extends the IoTHubCLient_LL
*			 module with 2 features:
*				- scheduling the work for the IoTHubCLient from a
*				  thread, so that the user does not need to create their
*				  own thread
*				- thread-safe APIs
*/

#ifndef IOTHUB_CLIENT_H
#define IOTHUB_CLIENT_H

#ifndef IOTHUB_CLIENT_INSTANCE_TYPE
typedef struct IOTHUB_CLIENT_INSTANCE_TAG* IOTHUB_CLIENT_HANDLE;
#define IOTHUB_CLIENT_INSTANCE_TYPE
#endif // IOTHUB_CLIENT_INSTANCE

#include "iothubtransport.h"
#include <stddef.h>
#include <stdint.h>

#include "iothub_client_ll.h"
#include "azure_c_shared_utility/umock_c_prod.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief	Creates a IoT Hub client for communication with an existing
    * 			IoT Hub using the specified connection string parameter.
    *
    * @param	connectionString	Pointer to a character string
    * @param	protocol			Function pointer for protocol implementation
    *
    *			Sample connection string:
    *				<blockquote>
    *					<pre>HostName=[IoT Hub name goes here].[IoT Hub suffix goes here, e.g., private.azure-devices-int.net];DeviceId=[Device ID goes here];SharedAccessKey=[Device key goes here];</pre>
    *                   <pre>HostName=[IoT Hub name goes here].[IoT Hub suffix goes here, e.g., private.azure-devices-int.net];DeviceId=[Device ID goes here];SharedAccessSignature=SharedAccessSignature sr=[IoT Hub name goes here].[IoT Hub suffix goes here, e.g., private.azure-devices-int.net]/devices/[Device ID goes here]&sig=[SAS Token goes here]&se=[Expiry Time goes here];</pre>
    *				</blockquote>
    *
    * @return	A non-NULL @c IOTHUB_CLIENT_HANDLE value that is used when
    * 			invoking other functions for IoT Hub client and @c NULL on failure.
    */
    MOCKABLE_FUNCTION(, IOTHUB_CLIENT_HANDLE, IoTHubClientCore_CreateFromConnectionString, const char*, connectionString, IOTHUB_CLIENT_TRANSPORT_PROVIDER, protocol);