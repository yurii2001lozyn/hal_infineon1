/*
 * Copyright 2024, Cypress Semiconductor Corporation (an Infineon company)
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file
 *  Provides generic APSTA functionality that chip specific files use
 */

#include "whd_debug.h"
#include "whd_network_if.h"
#include "whd_proto.h"

/******************************************************
 *  * @cond               Constants
 *   ******************************************************/

/******************************************************
 *  *                   Enumerations
 *   ******************************************************/

/******************************************************
**               Function Declarations
*******************************************************/

/******************************************************
 *        Variables Definitions
 *****************************************************/

/******************************************************
*               Function Definitions
******************************************************/
/** Called by WHD to pass received data to the network stack
 *
 *
 *  Packets received from the Wi-Fi network by WHD are forwarded to by calling function ptr which
 *  must be implemented in the network interface. Ethernet headers
 *  are present at the start of these packet buffers.
 *
 *  This function is called asynchronously in the context of the
 *  WHD thread whenever new data has arrived.
 *  Packet buffers are allocated within WHD, and ownership is transferred
 *  to the network stack. The network stack or application is thus
 *  responsible for releasing the packet buffers.
 *  Most packet buffering systems have a pointer to the 'current point' within
 *  the packet buffer. When this function is called, the pointer points
 *  to the start of the Ethernet header. There is other inconsequential data
 *  before the Ethernet header.
 *
 *  It is preferable that the (whd_network_process_ethernet_data)() function simply puts
 *  the received packet on a queue for processing by another thread. This avoids the
 *  WHD thread being unnecessarily tied up which would delay other packets
 *  being transmitted or received.
 *
 *  @param interface : The interface on which the packet was received.
 *  @param buffer    : Handle of the packet which has just been received. Responsibility for
 *                    releasing this buffer is transferred from WHD at this point.
 *
 */
whd_result_t whd_network_process_ethernet_data(whd_interface_t ifp, whd_buffer_t buffer)
{
    whd_driver_t whd_driver = ifp->whd_driver;
    if (whd_driver->network_if->whd_network_process_ethernet_data)
    {
        whd_driver->network_if->whd_network_process_ethernet_data(ifp, buffer);
        return WHD_SUCCESS;
    }
    else
    {
        WPRINT_WHD_INFO( ("Function pointers not provided .\n") );
    }
    return WHD_WLAN_NOFUNCTION;
}

/** Sends a data packet.
 *
 * @param buffer  : The ethernet packet buffer to be sent
 * @param interface : the interface over which to send the packet (AP or STA)
 *
 * @return    WHD result code
 */
whd_result_t whd_network_send_ethernet_data(whd_interface_t ifp, whd_buffer_t buffer)
{
#ifdef COMPONENT_SDIO_HM
    whd_result_t status;
    cy_rtos_get_mutex(&ifp->whd_driver->whd_hm_tx_lock, CY_RTOS_NEVER_TIMEOUT);
    status = whd_proto_tx_queue_data(ifp, buffer);
    cy_rtos_set_mutex(&ifp->whd_driver->whd_hm_tx_lock);
    return status;
#else
    return whd_proto_tx_queue_data(ifp, buffer);
#endif
}
