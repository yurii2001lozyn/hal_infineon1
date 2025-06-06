/***************************************************************************//**
* \file cy_crypto_core_hmac_v2.c
* \version 2.150
*
* \brief
*  This file provides the source code to the API for the HMAC method
*  in the Crypto block driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2024), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined(CY_IP_MXCRYPTO)

#include "cy_crypto_core_hmac_v2.h"

#if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C)

#include "cy_crypto_core_sha_v2.h"
#include "cy_crypto_core_mem_v2.h"
#include "cy_syslib.h"

/*****************************************************************************
* Cy_Crypto_Core_V2_Hmac_Init
******************************************************************************
*
* The function to initialize the HMAC operation.
*
* For CAT1C & CAT1D(CM55) devices when D-Cache is enabled parameters hmacState and hmacBuffer must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the cy_stc_crypto_hmac_state_t structure that stores all
* internal state for mxcrypto driver.
*
* \param mode
* The hash mode for HMAC.
*
* \param hmacBuffer
* The pointer to the cy_stc_crypto_v2_hmac_buffers_t structure that stores all
* buffers for HMAC operation.
*
* \return
* cy_en_crypto_status_t
*
*******************************************************************************/

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Init(CRYPTO_Type *base, cy_stc_crypto_hmac_state_t *hmacState, cy_en_crypto_sha_mode_t mode, cy_stc_crypto_v2_hmac_buffers_t *hmacBuffer)
{


    /* Input parameters verification */
    if ((NULL == base) || (NULL == hmacState) || (NULL == hmacBuffer))
    {
        return CY_CRYPTO_BAD_PARAMS;
    }

    hmacState->ipad = hmacBuffer->ipad;
    hmacState->opad = hmacBuffer->opad;
    hmacState->m0Key = hmacBuffer->m0Key;
    hmacState->sha_buffer = &hmacBuffer->shaBuffers;


    return Cy_Crypto_Core_V2_Sha_Init(base, &hmacState->hashState, mode, hmacState->sha_buffer);

}



/*******************************************************************************
* Cy_Crypto_Core_V2_Hmac_Start
******************************************************************************
*
* Initializes the initial Hash vector.
*
* For CAT1C & CAT1D(CM55) devices when D-Cache is enabled parameters key & hmacState (m0Key) must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the cy_stc_crypto_hmac_state_t structure that stores all
* internal state for mxcrypto driver.
*
* \param key
* The pointer to the HMAC key.
*
* \param keyLength
* The size of the input key
*
* \return
* cy_en_crypto_status_t
*
*******************************************************************************/

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Start(CRYPTO_Type *base, cy_stc_crypto_hmac_state_t *hmacState,
                                        uint8_t const *key,
                                        uint32_t keyLength
                                        )

{

    uint32_t i = 0uL;
    uint32_t blockSizeTmp;
    uint32_t digestSizeTmp;
    uint8_t *ipadRemap;
    uint8_t *opadRemap;
    uint8_t *m0KeyRemap;
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;
    uint8_t *ipadPtr;
    uint8_t *opadPtr;
    uint8_t *m0KeyPtr;

    /* Input parameters verification */
    if ((NULL == base) || (NULL == hmacState) || ((NULL == key) && (0UL != keyLength)) )
    {
        return CY_CRYPTO_BAD_PARAMS;
    }

    blockSizeTmp   = hmacState->hashState.blockSize;
    digestSizeTmp  = hmacState->hashState.digestSize;
    ipadRemap  = (uint8_t*)CY_REMAP_ADDRESS_FOR_CRYPTO(hmacState->ipad);
    opadRemap  = (uint8_t*)CY_REMAP_ADDRESS_FOR_CRYPTO(hmacState->opad);
    m0KeyRemap = (uint8_t*)CY_REMAP_ADDRESS_FOR_CRYPTO(hmacState->m0Key);

    ipadPtr = hmacState->ipad;
    opadPtr = hmacState->opad;
    m0KeyPtr = hmacState->m0Key;

#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        /* Flush the cache */
        SCB_CleanDCache_by_Addr((volatile void *)key,(int32_t)keyLength);
#endif
    Cy_Crypto_Core_V2_MemSet(base, m0KeyRemap, 0x00u, (uint16_t)blockSizeTmp);
    Cy_Crypto_Core_V2_MemSet(base, ipadRemap, 0x00u, (uint16_t)blockSizeTmp);
    Cy_Crypto_Core_V2_MemSet(base, opadRemap, 0x00u, (uint16_t)blockSizeTmp);

    /* Steps 1-3 according to FIPS 198-1 */
    if (keyLength > blockSizeTmp)
    {
        /* The key is larger than the block size. Do a hash on the key. */
        status = Cy_Crypto_Core_V2_Sha_Start  (base, &hmacState->hashState);

        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Update (base, &hmacState->hashState, key, keyLength);
        }
        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Finish (base, &hmacState->hashState, m0KeyRemap);
        }

        /* Append zeros */
        Cy_Crypto_Core_V2_MemSet(base, (m0KeyRemap + digestSizeTmp), 0x00u, (uint16_t)(blockSizeTmp - digestSizeTmp));
    }
    else if (keyLength < blockSizeTmp)
    {
        /* If the key is shorter than the block, append zeros */
        Cy_Crypto_Core_V2_MemCpy(base, m0KeyRemap, key, (uint16_t)keyLength);
        Cy_Crypto_Core_V2_MemSet(base, m0KeyRemap + keyLength, 0x00u, (uint16_t)(blockSizeTmp - keyLength));
    }
    else
    {
        Cy_Crypto_Core_V2_MemCpy(base, m0KeyRemap, key, (uint16_t)keyLength);
    }
#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
    SCB_InvalidateDCache_by_Addr(hmacState->m0Key, (int32_t)blockSizeTmp);
#endif

    if (CY_CRYPTO_SUCCESS == status)
    {
        /* Steps 4 and 7 according to FIPS 198-1 */
        while (i < blockSizeTmp)
        {
            ipadPtr[i] = CY_CRYPTO_HMAC_IPAD ^ m0KeyPtr[i];
            opadPtr[i] = CY_CRYPTO_HMAC_0PAD ^ m0KeyPtr[i];
            i++;
        }

#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        SCB_CleanDCache_by_Addr((volatile void *)hmacState->ipad,(int32_t)CY_CRYPTO_HMAC_MAX_PAD_SIZE);
        SCB_CleanDCache_by_Addr((volatile void *)hmacState->opad,(int32_t)CY_CRYPTO_HMAC_MAX_PAD_SIZE);
#endif


        /* Step 6 according to FIPS 198-1 */
        status = Cy_Crypto_Core_V2_Sha_Start (base, &hmacState->hashState);

        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Update(base, &hmacState->hashState, ipadRemap, blockSizeTmp);
        }

#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        SCB_InvalidateDCache_by_Addr((volatile void *)hmacState->ipad,(int32_t)CY_CRYPTO_HMAC_MAX_PAD_SIZE);
        SCB_InvalidateDCache_by_Addr((volatile void *)hmacState->opad,(int32_t)CY_CRYPTO_HMAC_MAX_PAD_SIZE);
#endif
    }

    return status;

}


/*******************************************************************************
* Cy_Crypto_Core_V2_Hmac_Update
******************************************************************************
*
* Performs the multipart hmac operation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the cy_stc_crypto_hmac_state_t structure that stores all
* internal state for mxcrypto driver.
*
* \param message
* The pointer to the message.
*
* \param messageSize
* The size of the message
*
* \return
* cy_en_crypto_status_t
*
*******************************************************************************/

 cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Update(CRYPTO_Type *base, cy_stc_crypto_hmac_state_t  *hmacState,
                                   uint8_t const  *message,
                                   uint32_t  messageSize
                                   )
{

    if (0UL == messageSize)
    {
        return CY_CRYPTO_SUCCESS;
    }

    /* Input parameters verification */
    if ((NULL == base) || (NULL == hmacState) || (NULL == message))
    {
        return CY_CRYPTO_BAD_PARAMS;  
    }

    return Cy_Crypto_Core_V2_Sha_Update(base, &hmacState->hashState, message, messageSize);

}



/*******************************************************************************
* Cy_Crypto_Core_V2_Hmac_Finish
******************************************************************************
*
* Finishes the hmac operation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the cy_stc_crypto_hmac_state_t structure that stores all
* internal state for mxcrypto driver.
*
* \param hmac
* The pointer to store the hmac value.
*
* \return
* cy_en_crypto_status_t
*
*******************************************************************************/

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Finish(CRYPTO_Type *base, cy_stc_crypto_hmac_state_t *hmacState,
                                                    uint8_t *hmac)

{
    uint32_t blockSizeTmp;
    uint32_t digestSizeTmp;
    uint8_t *ipadPtrTmp;
    uint8_t *opadPtrTmp;
    cy_en_crypto_status_t status = CY_CRYPTO_BAD_PARAMS;

    /* Input parameters verification */
    if ((NULL == base) || (NULL == hmacState) || (NULL == hmac))
    {
        return status;
    }

    blockSizeTmp  = hmacState->hashState.blockSize;
    digestSizeTmp = hmacState->hashState.digestSize;
    ipadPtrTmp = (uint8_t*)hmacState->ipad;
    opadPtrTmp = (uint8_t*)hmacState->opad;

    status = Cy_Crypto_Core_V2_Sha_Finish(base, &hmacState->hashState, ipadPtrTmp);
        
    /* Here is the ready part of HASH: Hash((Key^ipad)||text) */

    if (CY_CRYPTO_SUCCESS == status)
    {
        /* Steps 8, 9 according to FIPS 198-1 */
        status = Cy_Crypto_Core_V2_Sha_Start(base, &hmacState->hashState);

        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Update(base, &hmacState->hashState, opadPtrTmp, blockSizeTmp);
        }

        /* Append HASH from Step 6 */
        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Update(base, &hmacState->hashState, ipadPtrTmp, digestSizeTmp);
        }

        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Finish(base, &hmacState->hashState, hmac);
        }

        if (CY_CRYPTO_SUCCESS == status)
        {
            status = Cy_Crypto_Core_V2_Sha_Free(base, &hmacState->hashState);
        }
    }
    
    return status;

}


/*******************************************************************************
* Cy_Crypto_Core_V2_Hmac_Free
******************************************************************************
*
* Frees the internally stored buffers in hmac context.
*
* For CAT1C & CAT1D(CM55) devices when D-Cache is enabled parameters hmacState must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the cy_stc_crypto_hmac_state_t structure that stores all
* internal state for mxcrypto driver.
*
*
* \return
* cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Free(CRYPTO_Type *base, cy_stc_crypto_hmac_state_t *hmacState)
{
    /* Input parameters verification */
    if ( (NULL != base) && (NULL != hmacState))
    {
        /* Clear the memory buffer. */

        if (NULL != hmacState->ipad)
        {
            Cy_Crypto_Core_V2_MemSet(base, hmacState->ipad, 0u, CY_CRYPTO_HMAC_MAX_PAD_SIZE);
        }

        if (NULL != hmacState->opad)
        {
            Cy_Crypto_Core_V2_MemSet(base, hmacState->opad, 0u, CY_CRYPTO_HMAC_MAX_PAD_SIZE);
        }

        if (NULL != hmacState->m0Key)
        {
            Cy_Crypto_Core_V2_MemSet(base, hmacState->m0Key, 0u, CY_CRYPTO_SHA_MAX_BLOCK_SIZE);
        }

        Cy_Crypto_Core_V2_MemSet(base, hmacState, 0u, (uint16_t)sizeof(cy_stc_crypto_hmac_state_t));
    #if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        SCB_InvalidateDCache_by_Addr(hmacState->ipad, (int32_t)CY_CRYPTO_HMAC_MAX_PAD_SIZE);
        SCB_InvalidateDCache_by_Addr(hmacState->opad, (int32_t)CY_CRYPTO_HMAC_MAX_PAD_SIZE);
        SCB_InvalidateDCache_by_Addr(hmacState->m0Key, (int32_t)CY_CRYPTO_SHA_MAX_BLOCK_SIZE);
        SCB_InvalidateDCache_by_Addr(hmacState, (int32_t)sizeof(cy_stc_crypto_hmac_state_t));
    #endif

    }


    return CY_CRYPTO_SUCCESS;

}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Hmac
****************************************************************************//**
*
* Performs HMAC calculation.
*
* For CAT1A and CAT1C devices with DCache disabled, hmac must be 4-byte aligned.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmac
* The pointer to the calculated HMAC.
*
* \param message
* The pointer to a message whose hash value is being computed.
*
* \param messageSize
* The size of a message.
*
* \param key
* The pointer to the key.
*
* \param keyLength
* The length of the key.
*
* \param mode
* \ref cy_en_crypto_sha_mode_t
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac(CRYPTO_Type *base,
                                          uint8_t *hmac,
                                          uint8_t const *message,
                                          uint32_t messageSize,
                                          uint8_t const *key,
                                          uint32_t keyLength,
                                          cy_en_crypto_sha_mode_t mode)
{
    cy_en_crypto_status_t status = CY_CRYPTO_BAD_PARAMS;
    uint8_t  hmacState_t[CY_CRYPTO_ALIGN_CACHE_LINE(sizeof(cy_stc_crypto_hmac_state_t)) + CY_CRYPTO_DCAHCE_PADDING_SIZE];
    uint8_t  hmacBuffer_t[CY_CRYPTO_ALIGN_CACHE_LINE(sizeof(cy_stc_crypto_v2_hmac_buffers_t)) + CY_CRYPTO_DCAHCE_PADDING_SIZE];

    cy_stc_crypto_hmac_state_t  *hmacState = (cy_stc_crypto_hmac_state_t *)CY_CRYPTO_DCAHCE_ALIGN_ADDRESS(hmacState_t);
    cy_stc_crypto_v2_hmac_buffers_t *hmacBuffer = (cy_stc_crypto_v2_hmac_buffers_t *)CY_CRYPTO_DCAHCE_ALIGN_ADDRESS(hmacBuffer_t);

    /* Input parameters verification */
    if ((NULL == base) || (NULL == hmac) || ((NULL == message) && (0UL != messageSize))
        ||((NULL == key) && (0UL != keyLength)))
    {
        return status;
    }

    Cy_Crypto_Core_V2_MemSet(base, (void*)hmacState, 0x00U, (uint16_t)sizeof(cy_stc_crypto_hmac_state_t));
    Cy_Crypto_Core_V2_MemSet(base, (void*)hmacBuffer, 0x00U, (uint16_t)sizeof(cy_stc_crypto_v2_hmac_buffers_t));

    status = Cy_Crypto_Core_V2_Hmac_Init(base, hmacState, mode, hmacBuffer);

    if (CY_CRYPTO_SUCCESS == status)
    {
        status = Cy_Crypto_Core_V2_Hmac_Start(base, hmacState, key, keyLength);
    }

    if (CY_CRYPTO_SUCCESS == status)
    {
        status = Cy_Crypto_Core_V2_Hmac_Update(base, hmacState, message, messageSize);
    }

    if (CY_CRYPTO_SUCCESS == status)
    {
        status =  Cy_Crypto_Core_V2_Hmac_Finish(base, hmacState, hmac);
    }

    if (CY_CRYPTO_SUCCESS == status)
    {
        status =  Cy_Crypto_Core_V2_Hmac_Free(base, hmacState);
    }

    return (status);
}

#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
