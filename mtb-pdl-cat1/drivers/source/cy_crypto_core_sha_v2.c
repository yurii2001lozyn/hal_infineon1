/***************************************************************************//**
* \file cy_crypto_core_sha_v2.c
* \version 2.150
*
* \brief
*  This file provides the source code to the API for the SHA method
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

#include "cy_crypto_core_sha_v2.h"

#if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)

#include "cy_crypto_core_hw_v2.h"
#include "cy_crypto_core_mem_v2.h"
#include "cy_syslib.h"

#if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)
/* Functions prototypes */
static cy_en_crypto_status_t Cy_Crypto_Sha3_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest);

static cy_en_crypto_status_t Cy_Crypto_Sha3_Update(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t messageSize);
#endif

static cy_en_crypto_status_t Cy_Crypto_Sha1_Sha2_Update(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t messageSize);

static cy_en_crypto_status_t Cy_Crypto_Sha1_Sha2_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest);


/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Sha_Init
****************************************************************************//**
*
* The function to initialize SHA operation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to a Hash State.
*
* \param mode
* One of these: CY_CRYPTO_SHA256, CY_CRYPTO_SHA1, CY_CRYPTO_SHA256_224,
* CY_CRYPTO_SHA512, CY_CRYPTO_SHA384, CY_CRYPTO_SHA512_224, CY_CRYPTO_SHA512_256
*
* \param shaBuffers
* The pointer to the memory buffers storage
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Sha_Init(CRYPTO_Type *base,
                             cy_stc_crypto_sha_state_t *hashState,
                             cy_en_crypto_sha_mode_t mode,
                             void *shaBuffers)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SUCCESS;

    (void)base; /* Suppress warning */

    /* Initialization vectors for different modes of the SHA algorithm */
    #if (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    static const uint8_t sha1InitHash[] =
    {
       0x67u, 0x45u, 0x23u, 0x01u,
       0xefu, 0xcdu, 0xabu, 0x89u,
       0x98u, 0xbau, 0xdcu, 0xfeu,
       0x10u, 0x32u, 0x54u, 0x76u,
       0xc3u, 0xd2u, 0xe1u, 0xf0u
    };
    #endif /* (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED) */

    #if (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    static const uint8_t sha224InitHash[] =
    {
       0xc1u, 0x05u, 0x9eu, 0xd8u,
       0x36u, 0x7cu, 0xd5u, 0x07u,
       0x30u, 0x70u, 0xddu, 0x17u,
       0xf7u, 0x0eu, 0x59u, 0x39u,
       0xffu, 0xc0u, 0x0bu, 0x31u,
       0x68u, 0x58u, 0x15u, 0x11u,
       0x64u, 0xf9u, 0x8fu, 0xa7u,
       0xbeu, 0xfau, 0x4fu, 0xa4u
    };

    static const uint8_t sha256InitHash[] =
    {
       0x6au, 0x09u, 0xe6u, 0x67u,
       0xbbu, 0x67u, 0xaeu, 0x85u,
       0x3cu, 0x6eu, 0xf3u, 0x72u,
       0xa5u, 0x4fu, 0xf5u, 0x3au,
       0x51u, 0x0eu, 0x52u, 0x7fu,
       0x9bu, 0x05u, 0x68u, 0x8cu,
       0x1fu, 0x83u, 0xd9u, 0xabu,
       0x5bu, 0xe0u, 0xcdu, 0x19u
    };
    #endif /* (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED) */

    #if (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    static const uint8_t sha512_224InitHash[] = {
       0x8cu, 0x3du, 0x37u, 0xc8u, 0x19u, 0x54u, 0x4du, 0xa2u,
       0x73u, 0xe1u, 0x99u, 0x66u, 0x89u, 0xdcu, 0xd4u, 0xd6u,
       0x1du, 0xfau, 0xb7u, 0xaeu, 0x32u, 0xffu, 0x9cu, 0x82u,
       0x67u, 0x9du, 0xd5u, 0x14u, 0x58u, 0x2fu, 0x9fu, 0xcfu,
       0x0fu, 0x6du, 0x2bu, 0x69u, 0x7bu, 0xd4u, 0x4du, 0xa8u,
       0x77u, 0xe3u, 0x6fu, 0x73u, 0x04u, 0xc4u, 0x89u, 0x42u,
       0x3fu, 0x9du, 0x85u, 0xa8u, 0x6au, 0x1du, 0x36u, 0xc8u,
       0x11u, 0x12u, 0xe6u, 0xadu, 0x91u, 0xd6u, 0x92u, 0xa1u
    };

    static const uint8_t sha512_256InitHash[] = {
       0x22u, 0x31u, 0x21u, 0x94u, 0xfcu, 0x2bu, 0xf7u, 0x2cu,
       0x9fu, 0x55u, 0x5fu, 0xa3u, 0xc8u, 0x4cu, 0x64u, 0xc2u,
       0x23u, 0x93u, 0xb8u, 0x6bu, 0x6fu, 0x53u, 0xb1u, 0x51u,
       0x96u, 0x38u, 0x77u, 0x19u, 0x59u, 0x40u, 0xeau, 0xbdu,
       0x96u, 0x28u, 0x3eu, 0xe2u, 0xa8u, 0x8eu, 0xffu, 0xe3u,
       0xbeu, 0x5eu, 0x1eu, 0x25u, 0x53u, 0x86u, 0x39u, 0x92u,
       0x2bu, 0x01u, 0x99u, 0xfcu, 0x2cu, 0x85u, 0xb8u, 0xaau,
       0x0eu, 0xb7u, 0x2du, 0xdcu, 0x81u, 0xc5u, 0x2cu, 0xa2u
    };

    static const uint8_t sha384InitHash[] = {
       0xcbu, 0xbbu, 0x9du, 0x5du, 0xc1u, 0x05u, 0x9eu, 0xd8u,
       0x62u, 0x9au, 0x29u, 0x2au, 0x36u, 0x7cu, 0xd5u, 0x07u,
       0x91u, 0x59u, 0x01u, 0x5au, 0x30u, 0x70u, 0xddu, 0x17u,
       0x15u, 0x2fu, 0xecu, 0xd8u, 0xf7u, 0x0eu, 0x59u, 0x39u,
       0x67u, 0x33u, 0x26u, 0x67u, 0xffu, 0xc0u, 0x0bu, 0x31u,
       0x8eu, 0xb4u, 0x4au, 0x87u, 0x68u, 0x58u, 0x15u, 0x11u,
       0xdbu, 0x0cu, 0x2eu, 0x0du, 0x64u, 0xf9u, 0x8fu, 0xa7u,
       0x47u, 0xb5u, 0x48u, 0x1du, 0xbeu, 0xfau, 0x4fu, 0xa4u
    };

    static const uint8_t sha512InitHash[] = {
       0x6au, 0x09u, 0xe6u, 0x67u, 0xf3u, 0xbcu, 0xc9u, 0x08u,
       0xbbu, 0x67u, 0xaeu, 0x85u, 0x84u, 0xcau, 0xa7u, 0x3bu,
       0x3cu, 0x6eu, 0xf3u, 0x72u, 0xfeu, 0x94u, 0xf8u, 0x2bu,
       0xa5u, 0x4fu, 0xf5u, 0x3au, 0x5fu, 0x1du, 0x36u, 0xf1u,
       0x51u, 0x0eu, 0x52u, 0x7fu, 0xadu, 0xe6u, 0x82u, 0xd1u,
       0x9bu, 0x05u, 0x68u, 0x8cu, 0x2bu, 0x3eu, 0x6cu, 0x1fu,
       0x1fu, 0x83u, 0xd9u, 0xabu, 0xfbu, 0x41u, 0xbdu, 0x6bu,
       0x5bu, 0xe0u, 0xcdu, 0x19u, 0x13u, 0x7eu, 0x21u, 0x79u
    };
    #endif /* (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED) */

    CY_ASSERT_L1((shaBuffers != NULL) && (hashState != NULL));

    switch (mode)
    {
        #if (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
            case CY_CRYPTO_MODE_SHA1:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha1_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha1_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA1_OPC;
                hashState->initialHash    = (const uint8_t*)(sha1InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA1_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA1_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA1_DIGEST_SIZE;
                break;
        #endif /* (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED) */

        #if (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
            case CY_CRYPTO_MODE_SHA256:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha256_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha256_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA2_256_OPC;
                hashState->initialHash    = (const uint8_t*)(sha256InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA256_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA256_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA256_DIGEST_SIZE;
                break;
            case CY_CRYPTO_MODE_SHA224:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha256_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha256_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA2_256_OPC;
                hashState->initialHash    = (const uint8_t*)(sha224InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA256_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA256_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA224_DIGEST_SIZE;
                break;
        #endif /* (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED) */

        #if (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
            case CY_CRYPTO_MODE_SHA512:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA2_512_OPC;
                hashState->initialHash    = (const uint8_t*)(sha512InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_DIGEST_SIZE;
                break;
            case CY_CRYPTO_MODE_SHA384:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA2_512_OPC;
                hashState->initialHash    = (const uint8_t*)(sha384InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA384_DIGEST_SIZE;
                break;
            case CY_CRYPTO_MODE_SHA512_256:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA2_512_OPC;
                hashState->initialHash    = (const uint8_t*)(sha512_256InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_256_DIGEST_SIZE;
                break;
            case CY_CRYPTO_MODE_SHA512_224:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha512_buffers_t*)shaBuffers)->hash;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA2_512_OPC;
                hashState->initialHash    = (const uint8_t*)(sha512_224InitHash);
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_224_DIGEST_SIZE;
                break;
        #endif /* (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED) */

        #if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)
            case CY_CRYPTO_MODE_SHA3_224:
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha3_buffers_t*)shaBuffers)->hash;
                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA3_OPC;
                hashState->blockSize      = CY_CRYPTO_SHA3_224_BLOCK_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA224_DIGEST_SIZE;
                hashState->hashSize       = 0u;
                break;
            case CY_CRYPTO_MODE_SHA3_256:
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha3_buffers_t*)shaBuffers)->hash;
                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA3_OPC;
                hashState->blockSize      = CY_CRYPTO_SHA3_256_BLOCK_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA256_DIGEST_SIZE;
                hashState->hashSize       = 0u;
                break;
            case CY_CRYPTO_MODE_SHA3_384:
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha3_buffers_t*)shaBuffers)->hash;
                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA3_OPC;
                hashState->blockSize      = CY_CRYPTO_SHA3_384_BLOCK_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA384_DIGEST_SIZE;
                hashState->hashSize       = 0u;
                break;
            case CY_CRYPTO_MODE_SHA3_512:
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v2_sha3_buffers_t*)shaBuffers)->hash;
                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V2_SHA3_OPC;
                hashState->blockSize      = CY_CRYPTO_SHA3_512_BLOCK_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_DIGEST_SIZE;
                hashState->hashSize       = 0u;
                break;
        #endif/* (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED) */
            default:
                tmpResult = CY_CRYPTO_BAD_PARAMS;
                break;
    }

    return (tmpResult);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Sha_Start
****************************************************************************//**
*
* Initializes the initial hash vector.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Sha_Start(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;
    uint8_t *hashRemap;
    uint8_t *initialHashRemap;

    if (hashState != NULL)
    {
        hashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->hash);
        initialHashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->initialHash);

        hashState->blockIdx = 0U;
        hashState->messageSize = 0U;

        #if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)
        switch ((cy_en_crypto_sha_mode_t)hashState->mode)
        {
            case CY_CRYPTO_MODE_SHA3_224:
            case CY_CRYPTO_MODE_SHA3_256:
            case CY_CRYPTO_MODE_SHA3_384:
            case CY_CRYPTO_MODE_SHA3_512:
                        Cy_Crypto_Core_V2_MemSet(base, hashRemap, (uint8_t) 0, (uint16_t) CY_CRYPTO_SHA3_STATE_SIZE);
                        tmpResult = CY_CRYPTO_SUCCESS;
                        break;
            default:
                    tmpResult = CY_CRYPTO_BAD_PARAMS;
                    break;
        }
        #endif

        if (hashState->hashSize != 0U)
        {
            Cy_Crypto_Core_V2_MemCpy(base, (void*)hashRemap, (void *)initialHashRemap, (uint16_t)hashState->hashSize);
            tmpResult = CY_CRYPTO_SUCCESS;
        }

    }

    return (tmpResult);
}

#if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)

/*******************************************************************************
* Function Name: Cy_Crypto_Sha3_Update
****************************************************************************//**
*
* Performs the SHA3 update calculation on message.
*
* For CAT1C & CAT1D(CM55) devices when D-Cache is enabled parameter message must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param message
* The pointer to the message whose Hash is being computed.
*
* \param messageSize
* The size of the message whose Hash is being computed.
*
* \return
* \ref cy_en_crypto_status_t
*
*
*******************************************************************************/
static cy_en_crypto_status_t Cy_Crypto_Sha3_Update(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t messageSize)
{

    uint32_t hashBlockIdx  = hashState->blockIdx;
    uint32_t hashBlockSize = hashState->blockSize;

    uint8_t *hashRemap;
    uint8_t *messageRemap;

    hashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->hash);
    messageRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(message);

    /* Load the calculated hash from the context buffer */
    Cy_Crypto_Core_V2_RBClear(base);
    Cy_Crypto_Core_V2_Sync(base);

    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, hashRemap, CY_CRYPTO_SHA3_STATE_SIZE);
    Cy_Crypto_Core_V2_RBXor(base, 0U, 128U);
    Cy_Crypto_Core_V2_RBSwap(base);
    Cy_Crypto_Core_V2_RBXor(base, 0U, 72U);
    Cy_Crypto_Core_V2_RBSwap(base);

    /* Start the message loading */
    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, messageRemap, messageSize);

    /* Processing the fully filled blocks with remaining buffer data */
    while ((hashBlockIdx + messageSize) >= hashBlockSize)
    {
        uint32_t tempBlockSize = hashBlockSize - hashBlockIdx;

        if(hashBlockSize>128U) // This condition is for the SHA3_224 & SHA3_256 where the rate size is more that 1024 bits
        {
            if(hashBlockIdx<=128U)
            {
                Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, 128U-hashBlockIdx);
                Cy_Crypto_Core_V2_RBSwap(base);
                Cy_Crypto_Core_V2_RBXor(base, 0U, hashBlockSize-128U);
                Cy_Crypto_Core_V2_RBSwap(base);
            }
            else
            {
                Cy_Crypto_Core_V2_RBSwap(base);
                Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx - 128U, hashBlockSize-hashBlockIdx);
                Cy_Crypto_Core_V2_RBSwap(base);
            }
        }
        else
        {
            Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, tempBlockSize);
        }

        Cy_Crypto_Core_V2_Run(base, hashState->modeHw);

        messageSize -= tempBlockSize;
        hashBlockIdx = 0U;
    }

    hashState->blockIdx = hashBlockIdx + messageSize;

    /* Load the end of the message (tail that less then block size) to the register buffer */
    if (messageSize != 0U)
    {
        if(hashBlockSize>128U)
        {
            if(messageSize + hashBlockIdx <= 128U)
            {
                Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, messageSize);
                Cy_Crypto_Core_V2_Sync(base);
            }

            else
            {
                if(hashBlockIdx<128U)
                {
                    Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, 128U-hashBlockIdx);
                    Cy_Crypto_Core_V2_RBSwap(base);
                    Cy_Crypto_Core_V2_RBXor(base, 0U, messageSize - 128U);
                    Cy_Crypto_Core_V2_RBSwap(base);
                }
                else
                {
                    Cy_Crypto_Core_V2_RBSwap(base);
                    Cy_Crypto_Core_V2_RBXor(base,  hashBlockIdx % 128U , messageSize);
                    Cy_Crypto_Core_V2_RBSwap(base);
                }
            }
        }
        else
        {
            Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, messageSize);
            Cy_Crypto_Core_V2_Sync(base);
        }
    }

    /* Store the hash state to the context buffer */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, hashRemap, 128);
    Cy_Crypto_Core_V2_RBStore(base, 0U, 128U);
    Cy_Crypto_Core_V2_FFStoreSync(base);

    Cy_Crypto_Core_V2_RBSwap(base);
    Cy_Crypto_Core_V2_Sync(base);

    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, &hashRemap[128u], 72u);
    Cy_Crypto_Core_V2_RBStore(base, 0U, 72U);
    Cy_Crypto_Core_V2_FFStoreSync(base);

    return CY_CRYPTO_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_Crypto_Sha3_Finish
****************************************************************************//**
*
* Completes SHA3 calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param digest
* The pointer to the calculated hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
static cy_en_crypto_status_t Cy_Crypto_Sha3_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;
    uint8_t *hashRemap;
    
    if ((hashState != NULL) && (digest != NULL))
    {
#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        /* Flush the cache */
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t.');
        SCB_InvalidateDCache_by_Addr((volatile void *)hashState->hash,(int32_t)(CY_CRYPTO_SHA_MAX_HASH_SIZE));
#endif  

        uint32_t hashBlockSize   = hashState->blockSize;
        uint32_t hashBlockIdx    = hashState->blockIdx;
        hashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->hash);

        hashState->hash[hashBlockIdx] = hashState->hash[hashBlockIdx] ^ 0x06U;
        hashState->hash[hashBlockSize-1U] = hashState->hash[hashBlockSize-1U] ^ 0x80U;

#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        /* Flush the cache */
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t.');
        SCB_CleanDCache_by_Addr((volatile void *)hashState->hash,(int32_t)(CY_CRYPTO_SHA_MAX_HASH_SIZE));
#endif    
        /* Load the calculated hash state from the context buffer */
        Cy_Crypto_Core_V2_RBClear(base);
        Cy_Crypto_Core_V2_Sync(base);

        Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, hashRemap, CY_CRYPTO_SHA3_STATE_SIZE);
        Cy_Crypto_Core_V2_RBXor(base, 0U, 128U);
        Cy_Crypto_Core_V2_RBSwap(base);

        Cy_Crypto_Core_V2_RBXor(base, 0U, 72U);
        Cy_Crypto_Core_V2_RBSwap(base);
        Cy_Crypto_Core_V2_Sync(base);

        Cy_Crypto_Core_V2_Run(base, hashState->modeHw);
        Cy_Crypto_Core_V2_Sync(base);

        /* Write digest. */
        Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, digest, hashState->digestSize);
        Cy_Crypto_Core_V2_RBStore(base, 0U, hashState->digestSize);
        Cy_Crypto_Core_V2_FFStoreSync(base);

        tmpResult = CY_CRYPTO_SUCCESS;
        
    }
  
    return (tmpResult);
}
#endif

/*******************************************************************************
* Function Name: Cy_Crypto_Sha1_Sha2_Update
****************************************************************************//**
*
* Performs the SHA1/SHA2 update calculation on message.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param message
* The pointer to the message whose Hash is being computed.
*
* \param messageSize
* The size of the message whose Hash is being computed.
*
* \return
* \ref cy_en_crypto_status_t
*
*
*******************************************************************************/
static cy_en_crypto_status_t Cy_Crypto_Sha1_Sha2_Update(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t messageSize)
{

    hashState->messageSize += messageSize;
    uint8_t *hashRemap;
    uint8_t *blockRemap;
    uint8_t *messageRemap;

    hashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->hash);
    blockRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->block);
    messageRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(message);

    uint32_t hashBlockIdx  = hashState->blockIdx;
    uint32_t hashBlockSize = hashState->blockSize;

    /* Load the calculated hash from the context buffer */
    Cy_Crypto_Core_V2_RBClear(base);
    Cy_Crypto_Core_V2_Sync(base);

    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, hashRemap, hashState->hashSize);
    Cy_Crypto_Core_V2_RBXor(base, 0U, hashState->hashSize);
    Cy_Crypto_Core_V2_Sync(base);
    Cy_Crypto_Core_V2_RBSwap(base);

    /* Load the remaining block from the context buffer */
    if (hashBlockIdx != 0U)
    {
        Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, blockRemap, hashBlockIdx);
        Cy_Crypto_Core_V2_RBXor(base, 0U, hashBlockIdx);
        Cy_Crypto_Core_V2_Sync(base);
    }

    /* Start the hash calculating */
    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, messageRemap, messageSize);

    /* Processing the fully filled blocks with remaining buffer data */
    while ((hashBlockIdx + messageSize) >= hashBlockSize)
    {
        uint32_t tempBlockSize = hashBlockSize - hashBlockIdx;

        Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, tempBlockSize);

        Cy_Crypto_Core_V2_Run(base, hashState->modeHw);

        messageSize -= tempBlockSize;

        hashBlockIdx = 0U;
    }

    /* The remaining block will be calculated in the Finish function */
    hashState->blockIdx = hashBlockIdx + messageSize;

    /* Load the end of the message (tail that less then block size) to the register buffer */
    if (messageSize != 0U)
    {
        Cy_Crypto_Core_V2_RBXor(base, hashBlockIdx, messageSize);
        Cy_Crypto_Core_V2_Sync(base);
    }

    /* Save the remaining data to the context buffer */
    if (hashState->blockIdx != 0U)
    {
        Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, blockRemap, hashState->blockIdx);
        Cy_Crypto_Core_V2_RBStore(base, 0U, hashState->blockIdx);
        Cy_Crypto_Core_V2_Sync(base);
    }

    /* Store the calculated hash to the context buffer */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, hashRemap, hashState->hashSize);
    Cy_Crypto_Core_V2_RBSwap(base);
    Cy_Crypto_Core_V2_RBStore(base, 0U, hashState->hashSize);
    Cy_Crypto_Core_V2_Sync(base);
    Cy_Crypto_Core_V2_RBSwap(base);

    return CY_CRYPTO_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_Crypto_Sha1_Sha2_Finish
****************************************************************************//**
*
* Completes SHA1/SHA2 calculation.
*
* For CAT1C & CAT1D(CM55) devices when D-Cache is enabled parameter digest must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param digest
* The pointer to the calculated hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
static cy_en_crypto_status_t Cy_Crypto_Sha1_Sha2_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest)
{
    uint32_t hashBlockSize   = hashState->blockSize;
    uint32_t hashBlockIdx    = hashState->blockIdx;

    uint64_t finalMessageSizeInBits = hashState->messageSize * 8U;
    uint32_t padSize;
    uint8_t *hashRemap;
    uint8_t *blockRemap;

    hashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->hash);
    blockRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->block);
    
    if (CY_CRYPTO_SHA512_BLOCK_SIZE == hashBlockSize)
    {
        padSize = CY_CRYPTO_SHA512_PAD_SIZE; /* Pad size = 112 */
    }
    else
    {
        padSize = CY_CRYPTO_SHA256_PAD_SIZE; /* Pad size = 56 */
    }

    /* Load the calculated hash from the context buffer */
    Cy_Crypto_Core_V2_RBClear(base);
    Cy_Crypto_Core_V2_Sync(base);

    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, hashRemap, hashState->hashSize);
    Cy_Crypto_Core_V2_RBXor(base, 0U, hashState->hashSize);
    Cy_Crypto_Core_V2_Sync(base);
    Cy_Crypto_Core_V2_RBSwap(base);

    /* Load the end of the message (tail that less then block size) to the register buffer */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, blockRemap, hashBlockIdx);
    Cy_Crypto_Core_V2_RBXor(base, 0U, hashBlockIdx);

    /* Sync until XOR operation is completed */
    Cy_Crypto_Core_V2_Sync(base);

    /* Append 1 bit to the end of the message */
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockIdx, 0x80U);

    if (hashBlockIdx >= padSize)
    {
        Cy_Crypto_Core_V2_Run(base, hashState->modeHw);
        Cy_Crypto_Core_V2_Sync(base);
    }

    /* Append message size into last of the block */

    /* In case of u64SizeInByte * 8 > u64Max */

    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 8U, (uint8_t)(finalMessageSizeInBits >> 56U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 7U, (uint8_t)(finalMessageSizeInBits >> 48U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 6U, (uint8_t)(finalMessageSizeInBits >> 40U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 5U, (uint8_t)(finalMessageSizeInBits >> 32U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 4U, (uint8_t)(finalMessageSizeInBits >> 24U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 3U, (uint8_t)(finalMessageSizeInBits >> 16U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 2U, (uint8_t)(finalMessageSizeInBits >> 8U));
    Cy_Crypto_Core_V2_RBSetByte(base, hashBlockSize - 1U, (uint8_t)(finalMessageSizeInBits));

    Cy_Crypto_Core_V2_Run(base, hashState->modeHw);
    Cy_Crypto_Core_V2_Sync(base);

    /* Write digest. */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, digest, hashState->digestSize);
    Cy_Crypto_Core_V2_RBSwap(base);
    Cy_Crypto_Core_V2_RBStore(base, 0U, hashState->digestSize);

    Cy_Crypto_Core_V2_FFStoreSync(base);

    return CY_CRYPTO_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Sha_Update
****************************************************************************//**
*
* Performs the SHA calculation on one message.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param message
* The pointer to the message whose Hash is being computed.
*
* \param messageSize
* The size of the message whose Hash is being computed.
*
* \return
* \ref cy_en_crypto_status_t
*
* \note
* This function can be called several times only with message lengths dividable
* by the block size. Only the last call to the function can process a message with
* a not-dividable size.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Sha_Update(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t messageSize)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;
    uint8_t *messageRemap;

    if(messageSize == 0UL)
    {
        return CY_CRYPTO_SUCCESS;
    }

    if ((hashState != NULL) && (message != NULL))
    {

#if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
        /* Flush the cache */
        SCB_CleanDCache_by_Addr((volatile void *)message,(int32_t)messageSize);
#endif

        messageRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(message);

        if (hashState->blockSize != 0U)
        {

            switch ((cy_en_crypto_sha_mode_t)hashState->mode)
            {

            #if (CPUSS_CRYPTO_SHA1 ==1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
            case CY_CRYPTO_MODE_SHA1:
                tmpResult = Cy_Crypto_Sha1_Sha2_Update(base, hashState, messageRemap, messageSize);
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA256 ==1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
            case CY_CRYPTO_MODE_SHA224:
            case CY_CRYPTO_MODE_SHA256:
                tmpResult = Cy_Crypto_Sha1_Sha2_Update(base, hashState, messageRemap, messageSize);
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA512 ==1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
            case CY_CRYPTO_MODE_SHA384:
            case CY_CRYPTO_MODE_SHA512:
            case CY_CRYPTO_MODE_SHA512_224:
            case CY_CRYPTO_MODE_SHA512_256:
                tmpResult = Cy_Crypto_Sha1_Sha2_Update(base, hashState, messageRemap, messageSize);
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)
            case CY_CRYPTO_MODE_SHA3_224:
            case CY_CRYPTO_MODE_SHA3_256:
            case CY_CRYPTO_MODE_SHA3_384:
            case CY_CRYPTO_MODE_SHA3_512:
                tmpResult = Cy_Crypto_Sha3_Update(base, hashState, messageRemap, messageSize);
                break;
                #endif

            default:
                    tmpResult = CY_CRYPTO_BAD_PARAMS;
                break;
            }
            
        }
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Sha_Finish
****************************************************************************//**
*
* Completes SHA calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param digest
* The pointer to the calculated hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Sha_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;
    uint8_t *digestRemap;

    if ((hashState != NULL) && (digest != NULL))
    {
        digestRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(digest);

        switch ((cy_en_crypto_sha_mode_t)hashState->mode)
        {

            #if (CPUSS_CRYPTO_SHA1 ==1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
            case CY_CRYPTO_MODE_SHA1:
                tmpResult = Cy_Crypto_Sha1_Sha2_Finish(base, hashState, digestRemap);
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA256 ==1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
            case CY_CRYPTO_MODE_SHA224:
            case CY_CRYPTO_MODE_SHA256:
                tmpResult = Cy_Crypto_Sha1_Sha2_Finish(base, hashState, digestRemap);
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA512 ==1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
            case CY_CRYPTO_MODE_SHA384:
            case CY_CRYPTO_MODE_SHA512:
            case CY_CRYPTO_MODE_SHA512_224:
            case CY_CRYPTO_MODE_SHA512_256:
                tmpResult = Cy_Crypto_Sha1_Sha2_Finish(base, hashState, digestRemap);
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)
            case CY_CRYPTO_MODE_SHA3_224:
            case CY_CRYPTO_MODE_SHA3_256:
            case CY_CRYPTO_MODE_SHA3_384:
            case CY_CRYPTO_MODE_SHA3_512:
                tmpResult = Cy_Crypto_Sha3_Finish(base, hashState, digestRemap);
                break;
            #endif

            default:
                    tmpResult = CY_CRYPTO_BAD_PARAMS;
                    break;

        }
    }

    #if (((CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)) || CY_CPU_CORTEX_M55)
    if(tmpResult == CY_CRYPTO_SUCCESS)
    {
        SCB_InvalidateDCache_by_Addr(digest, (int32_t)hashState->digestSize);
    }
    #endif

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Sha_Free
****************************************************************************//**
*
* Clears the used memory buffers.
*
* For CAT1C & CAT1D(CM55) devices when D-Cache is enabled parameter hashState must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \return
* \ref cy_en_crypto_status_t
*
* *******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Sha_Free(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;
    uint8_t *hashRemap;
    uint8_t *blockRemap;
    cy_stc_crypto_sha_state_t *stateRemap;

    if ((NULL != base) && (hashState != NULL))
    {
        hashRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->hash);
        blockRemap = (uint8_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState->block);
        stateRemap = (cy_stc_crypto_sha_state_t *)CY_REMAP_ADDRESS_FOR_CRYPTO(hashState);

        
        /* Clears the context buffers */
        tmpResult = CY_CRYPTO_SUCCESS;

        switch ((cy_en_crypto_sha_mode_t)hashState->mode)
        {

            #if (CPUSS_CRYPTO_SHA1 ==1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
            case CY_CRYPTO_MODE_SHA1:
                if(NULL != blockRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, blockRemap, 0x00U, (uint16_t)hashState->blockSize);
                }
                if(NULL != hashRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, hashRemap,  0x00U, (uint16_t)hashState->hashSize);
                }
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA256 ==1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
            case CY_CRYPTO_MODE_SHA224:
            case CY_CRYPTO_MODE_SHA256:
                if(NULL != blockRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, blockRemap, 0x00U, (uint16_t)hashState->blockSize);
                }
                if(NULL != hashRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, hashRemap,  0x00U, (uint16_t)hashState->hashSize);
                }
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA512 ==1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
            case CY_CRYPTO_MODE_SHA384:
            case CY_CRYPTO_MODE_SHA512:
            case CY_CRYPTO_MODE_SHA512_224:
            case CY_CRYPTO_MODE_SHA512_256:
                if(NULL != blockRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, blockRemap, 0x00U, (uint16_t)hashState->blockSize);
                }
                if(NULL != hashRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, hashRemap,  0x00U, (uint16_t)hashState->hashSize);
                }
                break;
            #endif

            #if (CPUSS_CRYPTO_SHA3 == 1) && defined(CY_CRYPTO_CFG_SHA3_ENABLED)
            case CY_CRYPTO_MODE_SHA3_224:
            case CY_CRYPTO_MODE_SHA3_256:
            case CY_CRYPTO_MODE_SHA3_384:
            case CY_CRYPTO_MODE_SHA3_512:
                if(NULL != hashRemap)
                {
                    Cy_Crypto_Core_V2_MemSet(base, hashRemap,  0x00U, (uint16_t)hashState->hashSize);
                }                break;
            #endif

            default:
                tmpResult = CY_CRYPTO_NOT_SUPPORTED;
                break;

        }

        if(CY_CRYPTO_SUCCESS == tmpResult)
        {
            /* Clears the hash state */
            Cy_Crypto_Core_V2_MemSet(base, (void*)stateRemap, 0x00U, (uint16_t)(sizeof(cy_stc_crypto_sha_state_t) - CY_CRYPTO_DCAHCE_PADDING_SIZE));

            /* Clears the memory buffer. */
            Cy_Crypto_Core_V2_RBClear(base);
            Cy_Crypto_Core_V2_Sync(base);
        }
    }

    return (tmpResult);
}




/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Sha
****************************************************************************//**
*
* Performs the SHA Hash function.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param mode
* \ref cy_en_crypto_sha_mode_t
*
* \param message
* The pointer to a message whose hash value is being computed.
*
* \param messageSize
* The size of a message.
*
* \param digest
* The pointer to the hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Sha(CRYPTO_Type *base,
                                uint8_t const *message,
                                uint32_t messageSize,
                                uint8_t *digest,
                                cy_en_crypto_sha_mode_t mode)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;
    /* Allocate maximal space for the structure which stores the SHA buffers */
    uint8_t shaBuffers_t[CY_CRYPTO_ALIGN_CACHE_LINE(sizeof(cy_stc_crypto_v2_sha_buffers_t)) + CY_CRYPTO_DCAHCE_PADDING_SIZE];
    /* Allocate space for the structure which stores the SHA context */
    uint8_t hashState_t[CY_CRYPTO_ALIGN_CACHE_LINE(sizeof(cy_stc_crypto_sha_state_t)) + CY_CRYPTO_DCAHCE_PADDING_SIZE];

    cy_stc_crypto_v2_sha_buffers_t *shaBuffers = (cy_stc_crypto_v2_sha_buffers_t *)CY_CRYPTO_DCAHCE_ALIGN_ADDRESS(shaBuffers_t);
    cy_stc_crypto_sha_state_t *hashState = (cy_stc_crypto_sha_state_t *)CY_CRYPTO_DCAHCE_ALIGN_ADDRESS(hashState_t);

    Cy_Crypto_Core_V2_MemSet(base, (void*)shaBuffers, 0x00U, (uint16_t)sizeof(cy_stc_crypto_v2_sha_buffers_t));
    Cy_Crypto_Core_V2_MemSet(base, (void*)hashState, 0x00U, (uint16_t)sizeof(cy_stc_crypto_sha_state_t));

    /* No buffers are needed for the Crypto_ver2 IP block. */
    tmpResult = Cy_Crypto_Core_V2_Sha_Init   (base, hashState, mode, shaBuffers);

    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V2_Sha_Start  (base, hashState);
    }
    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V2_Sha_Update (base, hashState, message, messageSize);
    }

    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V2_Sha_Finish (base, hashState, digest);
    }

    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V2_Sha_Free   (base, hashState);
    }

    return (tmpResult);
}


#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
