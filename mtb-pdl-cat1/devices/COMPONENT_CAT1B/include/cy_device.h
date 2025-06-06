/***************************************************************************//**
* \file cy_device.h
* \version 2.0
*
* This file specifies the structure for core and peripheral block HW base
* addresses, versions, and parameters.
*
********************************************************************************/
#ifndef CY_DEVICE_H_
#define CY_DEVICE_H_

#include <stdint.h>
#include <stddef.h>

#include "cy_utils.h"

#ifndef PSC3_UUT
#include "cy_device_headers.h"
#endif

#include "startup_cat1b.h"


CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.6', 1, \
'Checked manually. The definition is a part of linker script.')

#ifdef _GPIO_CYW20829_56_QFN_H_
#define _GPIO_CYW20829B0_56_QFN_H_
#endif

#ifdef _GPIO_CYW20829_40_QFN_H_
#define _GPIO_CYW20829B0_40_QFN_H_
#endif

/* Device descriptor type */
typedef struct
{
    /* Base HW addresses */
    uint32_t hsiomBase;
    uint32_t gpioBase;

    /* IP block versions: [7:4] major, [3:0] minor */
    uint8_t  dwVersion;

    /* Parameters */
    uint8_t  cpussDw0ChNr;
    uint8_t  cpussDw1ChNr;
    uint8_t  epMonitorNr;

    /* Peripheral register offsets */

   /* DW registers */
    uint16_t dwChOffset;
    uint16_t dwChSize;
    uint8_t  dwChCtlPrioPos;
    uint8_t  dwChCtlPreemptablePos;
    uint8_t  dwStatusChIdxPos;
    uint32_t dwStatusChIdxMsk;

    uint8_t  tcpwmCC1Present;
    uint8_t  tcpwmAMCPresent;
    uint8_t  tcpwmSMCPrecent;

} cy_stc_device_t;

/* Pointer to device configuration structure */
#define CY_DEVICE_CFG                   (&cy_deviceIpBlockCfg)


/*******************************************************************************
*                   Global Variables
*******************************************************************************/

extern const cy_stc_device_t   cy_deviceIpBlockCfg;
extern const cy_stc_device_t* cy_device;

/*******************************************************************************
*                   Global Extern Functions
*******************************************************************************/

/*******************************************************************************
*               Macro Definitions
*******************************************************************************/
#if (__SAUREGION_PRESENT==1)
  #define SECURE_ALIAS_OFFSET                   (0x10000000UL)
  #ifdef CY_PDL_TZ_ENABLED
    #define GET_ALIAS_ADDRESS(addr)             ((uint32_t)(((uint32_t)(addr)) | SECURE_ALIAS_OFFSET))
  #else
    #define GET_ALIAS_ADDRESS(addr)             ((uint32_t)(((uint32_t)(addr)) & ~SECURE_ALIAS_OFFSET))
  #endif
  #define GET_NSALIAS_ADDRESS(addr)             ((uint32_t)((uint32_t)(addr) & ~(SECURE_ALIAS_OFFSET)))
#else
  #define GET_ALIAS_ADDRESS(addr)               ((uint32_t)(addr))
  #define GET_NSALIAS_ADDRESS(addr)             ((uint32_t)(addr))
#endif /* (__SAUREGION_PRESENT==1) */


#if defined(CY_DEVICE_PSC3)
    #ifndef NORMAL_PROVISIONED_LCS
    #define CM33_NS_PC_VALUE            (1u)
    #define CM33_S_PC_VALUE             (0u)
    #else
    #define CM33_NS_PC_VALUE            (3u)
    #define CM33_S_PC_VALUE             (2u)
    #endif
#endif

/* For BWC with applications that expect SRAM0 instead of SRAM */
#if defined (CY_DEVICE_CYW20829) || defined (CY_DEVICE_PSC3)
#define CY_SRAM0_BASE                   CY_SRAM_BASE
#define CY_SRAM0_CBUS_BASE              CY_SRAM_CBUS_BASE
#define CY_SRAM0_SIZE                   CY_SRAM_SIZE
#define CY_SRAM0_NS_SBUS_BASE           CY_SRAM_NS_SBUS_BASE
#define CY_SRAM0_NS_CBUS_BASE           CY_SRAM_NS_CBUS_BASE
#define CY_SRAM0_S_SBUS_BASE            CY_SRAM_S_SBUS_BASE
#define CY_SRAM0_S_CBUS_BASE            CY_SRAM_S_CBUS_BASE
#endif

/*******************************************************************************
*                   Function Prototypes
*******************************************************************************/

void Cy_PDL_Init(const cy_stc_device_t * device);

/*******************************************************************************
*               Register Access Helper Macros
*******************************************************************************/
#define CY_DEVICE_CAT1B                /* Device Category */
/*******************************************************************************
*               SDHC
*******************************************************************************/
#define SDHC_WRAP_CTL(base)                     (((SDHC_Type *)(base))->WRAP.CTL)
#define SDHC_CORE_SDMASA_R(base)                (((SDHC_Type *)(base))->CORE.SDMASA_R)
#define SDHC_CORE_BLOCKSIZE_R(base)             (((SDHC_Type *)(base))->CORE.BLOCKSIZE_R)
#define SDHC_CORE_BLOCKCOUNT_R(base)            (((SDHC_Type *)(base))->CORE.BLOCKCOUNT_R)
#define SDHC_CORE_ARGUMENT_R(base)              (((SDHC_Type *)(base))->CORE.ARGUMENT_R)
#define SDHC_CORE_XFER_MODE_R(base)             (((SDHC_Type *)(base))->CORE.XFER_MODE_R)
#define SDHC_CORE_CMD_R(base)                   (((SDHC_Type *)(base))->CORE.CMD_R)
#define SDHC_CORE_RESP01_R(base)                (((SDHC_Type *)(base))->CORE.RESP01_R)
#define SDHC_CORE_RESP23_R(base)                (((SDHC_Type *)(base))->CORE.RESP23_R)
#define SDHC_CORE_RESP45_R(base)                (((SDHC_Type *)(base))->CORE.RESP45_R)
#define SDHC_CORE_RESP67_R(base)                (((SDHC_Type *)(base))->CORE.RESP67_R)
#define SDHC_CORE_BUF_DATA_R(base)              (((SDHC_Type *)(base))->CORE.BUF_DATA_R)
#define SDHC_CORE_PSTATE_REG(base)              (((SDHC_Type *)(base))->CORE.PSTATE_REG)
#define SDHC_CORE_HOST_CTRL1_R(base)            (((SDHC_Type *)(base))->CORE.HOST_CTRL1_R)
#define SDHC_CORE_PWR_CTRL_R(base)              (((SDHC_Type *)(base))->CORE.PWR_CTRL_R)
#define SDHC_CORE_BGAP_CTRL_R(base)             (((SDHC_Type *)(base))->CORE.BGAP_CTRL_R)
#define SDHC_CORE_WUP_CTRL_R(base)              (((SDHC_Type *)(base))->CORE.WUP_CTRL_R)
#define SDHC_CORE_CLK_CTRL_R(base)              (((SDHC_Type *)(base))->CORE.CLK_CTRL_R)
#define SDHC_CORE_TOUT_CTRL_R(base)             (((SDHC_Type *)(base))->CORE.TOUT_CTRL_R)
#define SDHC_CORE_SW_RST_R(base)                (((SDHC_Type *)(base))->CORE.SW_RST_R)
#define SDHC_CORE_NORMAL_INT_STAT_R(base)       (((SDHC_Type *)(base))->CORE.NORMAL_INT_STAT_R)
#define SDHC_CORE_ERROR_INT_STAT_R(base)        (((SDHC_Type *)(base))->CORE.ERROR_INT_STAT_R)
#define SDHC_CORE_NORMAL_INT_STAT_EN_R(base)    (((SDHC_Type *)(base))->CORE.NORMAL_INT_STAT_EN_R)
#define SDHC_CORE_ERROR_INT_STAT_EN_R(base)     (((SDHC_Type *)(base))->CORE.ERROR_INT_STAT_EN_R)
#define SDHC_CORE_NORMAL_INT_SIGNAL_EN_R(base)  (((SDHC_Type *)(base))->CORE.NORMAL_INT_SIGNAL_EN_R)
#define SDHC_CORE_ERROR_INT_SIGNAL_EN_R(base)   (((SDHC_Type *)(base))->CORE.ERROR_INT_SIGNAL_EN_R)
#define SDHC_CORE_AUTO_CMD_STAT_R(base)         (((SDHC_Type *)(base))->CORE.AUTO_CMD_STAT_R)
#define SDHC_CORE_HOST_CTRL2_R(base)            (((SDHC_Type *)(base))->CORE.HOST_CTRL2_R)
#define SDHC_CORE_CAPABILITIES1_R(base)         (((SDHC_Type *)(base))->CORE.CAPABILITIES1_R)
#define SDHC_CORE_CAPABILITIES2_R(base)         (((SDHC_Type *)(base))->CORE.CAPABILITIES2_R)
#define SDHC_CORE_CURR_CAPABILITIES1_R(base)    (((SDHC_Type *)(base))->CORE.CURR_CAPABILITIES1_R)
#define SDHC_CORE_CURR_CAPABILITIES2_R(base)    (((SDHC_Type *)(base))->CORE.CURR_CAPABILITIES2_R)
#define SDHC_CORE_ADMA_ERR_STAT_R(base)         (((SDHC_Type *)(base))->CORE.ADMA_ERR_STAT_R)
#define SDHC_CORE_ADMA_SA_LOW_R(base)           (((SDHC_Type *)(base))->CORE.ADMA_SA_LOW_R)
#define SDHC_CORE_ADMA_ID_LOW_R(base)           (((SDHC_Type *)(base))->CORE.ADMA_ID_LOW_R)
#define SDHC_CORE_EMMC_CTRL_R(base)             (((SDHC_Type *)(base))->CORE.EMMC_CTRL_R)
#define SDHC_CORE_GP_OUT_R(base)                (((SDHC_Type *)(base))->CORE.GP_OUT_R)

/*******************************************************************************
*                SMARTIO
*******************************************************************************/

#define SMARTIO_PRT_CTL(base)               (((SMARTIO_PRT_Type *)(base))->CTL)
#define SMARTIO_PRT_SYNC_CTL(base)          (((SMARTIO_PRT_Type *)(base))->SYNC_CTL)
#define SMARTIO_PRT_LUT_SEL(base, idx)      (((SMARTIO_PRT_Type *)(base))->LUT_SEL[idx])
#define SMARTIO_PRT_LUT_CTL(base, idx)      (((SMARTIO_PRT_Type *)(base))->LUT_CTL[idx])
#define SMARTIO_PRT_DU_SEL(base)            (((SMARTIO_PRT_Type *)(base))->DU_SEL)
#define SMARTIO_PRT_DU_CTL(base)            (((SMARTIO_PRT_Type *)(base))->DU_CTL)
#define SMARTIO_PRT_DATA(base)              (((SMARTIO_PRT_Type *)(base))->DATA)


/*******************************************************************************
*                SMIF
*******************************************************************************/
#if ((defined(CY_IP_MXSMIF_VERSION)) && (CY_IP_MXSMIF_VERSION>=3))
/* For backward compatibility of API, use first crypto device as default device */
#define SMIF_CRYPTO_CMD(base)            (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_CMD)
#define SMIF_CRYPTO_ADDR(base)           (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_ADDR)
#define SMIF_CRYPTO_MASK(base)           (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_MASK)
#define SMIF_CRYPTO_SUBREGION(base)      (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_SUBREGION)
#define SMIF_CRYPTO_INPUT0(base)         (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_INPUT0)
#define SMIF_CRYPTO_INPUT1(base)         (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_INPUT1)
#define SMIF_CRYPTO_INPUT2(base)         (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_INPUT2)
#define SMIF_CRYPTO_INPUT3(base)         (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_INPUT3)
#define SMIF_CRYPTO_KEY0(base)           (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_KEY0)
#define SMIF_CRYPTO_KEY1(base)           (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_KEY1)
#define SMIF_CRYPTO_KEY2(base)           (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_KEY2)
#define SMIF_CRYPTO_KEY3(base)           (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_KEY3)
#define SMIF_CRYPTO_OUTPUT0(base)        (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_OUTPUT0)
#define SMIF_CRYPTO_OUTPUT1(base)        (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_OUTPUT1)
#define SMIF_CRYPTO_OUTPUT2(base)        (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_OUTPUT2)
#define SMIF_CRYPTO_OUTPUT3(base)        (((SMIF_Type*) base)->SMIF_CRYPTO_BLOCK[0].CRYPTO_OUTPUT3)
#else
#define SMIF_CRYPTO_CMD(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_CMD)
#define SMIF_CRYPTO_ADDR(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_ADDR)
#define SMIF_CRYPTO_MASK(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_MASK)
#define SMIF_CRYPTO_SUBREGION(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_SUBREGION)
#define SMIF_CRYPTO_INPUT0(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_INPUT0)
#define SMIF_CRYPTO_INPUT1(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_INPUT1)
#define SMIF_CRYPTO_INPUT2(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_INPUT2)
#define SMIF_CRYPTO_INPUT3(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_INPUT3)
#define SMIF_CRYPTO_KEY0(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_KEY0)
#define SMIF_CRYPTO_KEY1(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_KEY1)
#define SMIF_CRYPTO_KEY2(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_KEY2)
#define SMIF_CRYPTO_KEY3(base)            (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_KEY3)
#define SMIF_CRYPTO_OUTPUT0(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_OUTPUT0)
#define SMIF_CRYPTO_OUTPUT1(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_OUTPUT1)
#define SMIF_CRYPTO_OUTPUT2(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_OUTPUT2)
#define SMIF_CRYPTO_OUTPUT3(base)        (((SMIF_SMIF_CRYPTO_Type *)(base))->CRYPTO_OUTPUT3)
#endif

#define SMIF_CRYPTO_IDX(base, deviceIndex)                 (((SMIF_Type *)(base))->SMIF_CRYPTO_BLOCK[deviceIndex])

#define SMIF_CRYPTO_IDX_CMD(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_CMD)
#define SMIF_CRYPTO_IDX_ADDR(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_ADDR)
#define SMIF_CRYPTO_IDX_MASK(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_MASK)
#define SMIF_CRYPTO_IDX_SUBREGION(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_SUBREGION)
#define SMIF_CRYPTO_IDX_INPUT0(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_INPUT0)
#define SMIF_CRYPTO_IDX_INPUT1(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_INPUT1)
#define SMIF_CRYPTO_IDX_INPUT2(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_INPUT2)
#define SMIF_CRYPTO_IDX_INPUT3(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_INPUT3)
#define SMIF_CRYPTO_IDX_KEY0(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_KEY0)
#define SMIF_CRYPTO_IDX_KEY1(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_KEY1)
#define SMIF_CRYPTO_IDX_KEY2(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_KEY2)
#define SMIF_CRYPTO_IDX_KEY3(base, deviceIndex)        (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_KEY3)
#define SMIF_CRYPTO_IDX_OUTPUT0(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_OUTPUT0)
#define SMIF_CRYPTO_IDX_OUTPUT1(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_OUTPUT1)
#define SMIF_CRYPTO_IDX_OUTPUT2(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_OUTPUT2)
#define SMIF_CRYPTO_IDX_OUTPUT3(base, deviceIndex)    (SMIF_CRYPTO_IDX(base, deviceIndex).CRYPTO_OUTPUT3)


#define SMIF_DEVICE_CTL(base)               (((SMIF_DEVICE_Type *)(base))->CTL)
#define SMIF_DEVICE_ADDR(base)              (((SMIF_DEVICE_Type *)(base))->ADDR)
#define SMIF_DEVICE_ADDR_CTL(base)          (((SMIF_DEVICE_Type *)(base))->ADDR_CTL)
#define SMIF_DEVICE_MASK(base)              (((SMIF_DEVICE_Type *)(base))->MASK)
#define SMIF_DEVICE_RD_CMD_CTL(base)        (((SMIF_DEVICE_Type *)(base))->RD_CMD_CTL)
#define SMIF_DEVICE_RD_ADDR_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_ADDR_CTL)
#define SMIF_DEVICE_RD_MODE_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_MODE_CTL)
#define SMIF_DEVICE_RD_DUMMY_CTL(base)      (((SMIF_DEVICE_Type *)(base))->RD_DUMMY_CTL)
#define SMIF_DEVICE_RD_DATA_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_DATA_CTL)
#define SMIF_DEVICE_RD_BOUND_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_BOUND_CTL)
#define SMIF_DEVICE_WR_CMD_CTL(base)        (((SMIF_DEVICE_Type *)(base))->WR_CMD_CTL)
#define SMIF_DEVICE_WR_ADDR_CTL(base)       (((SMIF_DEVICE_Type *)(base))->WR_ADDR_CTL)
#define SMIF_DEVICE_WR_MODE_CTL(base)       (((SMIF_DEVICE_Type *)(base))->WR_MODE_CTL)
#define SMIF_DEVICE_WR_DUMMY_CTL(base)      (((SMIF_DEVICE_Type *)(base))->WR_DUMMY_CTL)
#define SMIF_DEVICE_WR_DATA_CTL(base)       (((SMIF_DEVICE_Type *)(base))->WR_DATA_CTL)

#define SMIF_DEVICE_IDX(base, deviceIndex)                 (((SMIF_Type *)(base))->DEVICE[deviceIndex])

#define SMIF_DEVICE_IDX_CTL(base, deviceIndex)             (SMIF_DEVICE_IDX(base, deviceIndex).CTL)
#define SMIF_DEVICE_IDX_ADDR(base, deviceIndex)            (SMIF_DEVICE_IDX(base, deviceIndex).ADDR)
#define SMIF_DEVICE_IDX_ADDR_CTL(base, deviceIndex)        (SMIF_DEVICE_IDX(base, deviceIndex).ADDR_CTL)
#define SMIF_DEVICE_IDX_MASK(base, deviceIndex)            (SMIF_DEVICE_IDX(base, deviceIndex).MASK)
#define SMIF_DEVICE_IDX_RD_CMD_CTL(base, deviceIndex)      (SMIF_DEVICE_IDX(base, deviceIndex).RD_CMD_CTL)
#define SMIF_DEVICE_IDX_RD_ADDR_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_ADDR_CTL)
#define SMIF_DEVICE_IDX_RD_MODE_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_MODE_CTL)
#define SMIF_DEVICE_IDX_RD_DUMMY_CTL(base, deviceIndex)    (SMIF_DEVICE_IDX(base, deviceIndex).RD_DUMMY_CTL)
#define SMIF_DEVICE_IDX_RD_DATA_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_DATA_CTL)
#define SMIF_DEVICE_IDX_WR_CMD_CTL(base, deviceIndex)      (SMIF_DEVICE_IDX(base, deviceIndex).WR_CMD_CTL)
#define SMIF_DEVICE_IDX_WR_ADDR_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_ADDR_CTL)
#define SMIF_DEVICE_IDX_WR_MODE_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_MODE_CTL)
#define SMIF_DEVICE_IDX_WR_DUMMY_CTL(base, deviceIndex)    (SMIF_DEVICE_IDX(base, deviceIndex).WR_DUMMY_CTL)
#define SMIF_DEVICE_IDX_WR_DATA_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_DATA_CTL)

#define SMIF_CTL(base)                        (((SMIF_Type *)(base))->CTL)
#define SMIF_STATUS(base)                    (((SMIF_Type *)(base))->STATUS)
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0(base)    (((SMIF_Type *)(base))->INT_CLOCK_DELAY_TAP_SEL0)
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1(base)    (((SMIF_Type *)(base))->INT_CLOCK_DELAY_TAP_SEL1)
#define SMIF_DL_CTL(base)                    (((SMIF_Type *)(base))->DL_CTL)
#define SMIF_DL_STATUS0(base)                (((SMIF_Type *)(base))->DL_STATUS0)
#define SMIF_DL_STATUS1(base)                (((SMIF_Type *)(base))->DL_STATUS1)
#define SMIF_TX_CMD_FIFO_STATUS(base)        (((SMIF_Type *)(base))->TX_CMD_FIFO_STATUS)
#define SMIF_TX_CMD_MMIO_FIFO_STATUS(base)    (((SMIF_Type *)(base))->TX_CMD_MMIO_FIFO_STATUS)
#define SMIF_TX_CMD_MMIO_FIFO_WR(base)        (((SMIF_Type *)(base))->TX_CMD_MMIO_FIFO_WR)
#define SMIF_TX_DATA_MMIO_FIFO_CTL(base)    (((SMIF_Type *)(base))->TX_DATA_MMIO_FIFO_CTL)
#define SMIF_TX_DATA_FIFO_STATUS(base)        (((SMIF_Type *)(base))->TX_DATA_FIFO_STATUS)
#define SMIF_TX_DATA_MMIO_FIFO_STATUS(base)    (((SMIF_Type *)(base))->TX_DATA_MMIO_FIFO_STATUS)
#define SMIF_TX_DATA_MMIO_FIFO_WR1(base)    (((SMIF_Type *)(base))->TX_DATA_MMIO_FIFO_WR1)
#define SMIF_TX_DATA_MMIO_FIFO_WR2(base)    (((SMIF_Type *)(base))->TX_DATA_MMIO_FIFO_WR2)
#define SMIF_TX_DATA_MMIO_FIFO_WR4(base)    (((SMIF_Type *)(base))->TX_DATA_MMIO_FIFO_WR4)
#define SMIF_TX_DATA_MMIO_FIFO_WR1ODD(base)    (((SMIF_Type *)(base))->TX_DATA_MMIO_FIFO_WR1ODD)
#define SMIF_RX_DATA_MMIO_FIFO_CTL(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_CTL)
#define SMIF_RX_DATA_MMIO_FIFO_STATUS(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_STATUS)
#define SMIF_RX_DATA_FIFO_STATUS(base)        (((SMIF_Type *)(base))->RX_DATA_FIFO_STATUS)
#define SMIF_RX_DATA_MMIO_FIFO_RD1(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD1)
#define SMIF_RX_DATA_MMIO_FIFO_RD2(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD2)
#define SMIF_RX_DATA_MMIO_FIFO_RD4(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD4)
#define SMIF_RX_DATA_MMIO_FIFO_RD1_SILENT(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD1_SILENT)
#define SMIF_SLOW_CA_CTL(base)                   (((SMIF_Type *)(base))->SLOW_CA_CTL)
#define SMIF_SLOW_CA_CMD(base)                (((SMIF_Type *)(base))->SLOW_CA_CMD)
#define SMIF_FAST_CA_CTL(base)                (((SMIF_Type *)(base))->FAST_CA_CTL)
#define SMIF_FAST_CA_CMD(base)                (((SMIF_Type *)(base))->FAST_CA_CMD)
#define SMIF_CRC_CMD(base)                    (((SMIF_Type *)(base))->CRC_CMD)
#define SMIF_CRC_INPUT0(base)                (((SMIF_Type *)(base))->CRC_INPUT0)
#define SMIF_CRC_INPUT1(base)                (((SMIF_Type *)(base))->CRC_INPUT1)
#define SMIF_CRC_OUTPUT(base)                (((SMIF_Type *)(base))->CRC_OUTPUT)
#define SMIF_INTR(base)                        (((SMIF_Type *)(base))->INTR)
#define SMIF_INTR_SET(base)                    (((SMIF_Type *)(base))->INTR_SET)
#define SMIF_INTR_MASK(base)                (((SMIF_Type *)(base))->INTR_MASK)
#define SMIF_INTR_MASKED(base)                (((SMIF_Type *)(base))->INTR_MASKED)

/*******************************************************************************
*                DW
*******************************************************************************/


#define CY_DW                               (0UL)
#define CY_DW_CRC                           (1UL)
#define CY_DW0_BASE                         DW0
#define CY_DW1_BASE                         DW1
#define CY_DW0_CH_NR                        CPUSS_DW0_CH_NR
#define CY_DW1_CH_NR                        CPUSS_DW1_CH_NR

#define CY_DW_CH_CTL_PRIO_Pos               ((uint32_t)(DW_CH_STRUCT_CH_CTL_PRIO_Pos))
#define CY_DW_CH_CTL_PRIO_Msk               ((uint32_t)(0x3UL << CY_DW_CH_CTL_PRIO_Pos))
#define CY_DW_CH_CTL_PREEMPTABLE_Pos        ((uint32_t)(DW_CH_STRUCT_CH_CTL_PREEMPTABLE_Pos))
#define CY_DW_CH_CTL_PREEMPTABLE_Msk        ((uint32_t)(0x1UL << CY_DW_CH_CTL_PREEMPTABLE_Pos))
#define CY_DW_STATUS_CH_IDX_Pos             ((uint32_t)(DW_STATUS_CH_IDX_Pos))
#define CY_DW_STATUS_CH_IDX_Msk             (DW_STATUS_CH_IDX_Msk)

#define DW_CTL(base)                        (((DW_Type*)(base))->CTL)
#define DW_STATUS(base)                     (((DW_Type const*)(base))->STATUS)
#define DW_DESCR_SRC(base)                  (((DW_Type*)(base))->ACT_DESCR_SRC)
#define DW_DESCR_DST(base)                  (((DW_Type*)(base))->ACT_DESCR_DST)

#define DW_CRC_CTL(base)                    (((DW_Type*)(base))->CRC_CTL)
#define DW_CRC_DATA_CTL(base)               (((DW_Type*)(base))->CRC_DATA_CTL)
#define DW_CRC_REM_CTL(base)                (((DW_Type*)(base))->CRC_REM_CTL)
#define DW_CRC_POL_CTL(base)                (((DW_Type*)(base))->CRC_POL_CTL)
#define DW_CRC_LFSR_CTL(base)               (((DW_Type*)(base))->CRC_LFSR_CTL)

#define DW_CH_OFFSET                        (uint32_t)(offsetof(DW_Type, CH_STRUCT))
#define DW_CH_SIZE                            (uint32_t)(sizeof(DW_CH_STRUCT_Type))

#define DW_CH(base, chan)                    ((DW_CH_STRUCT_Type*)((uint32_t)(base) + DW_CH_OFFSET + (chan * DW_CH_SIZE)))
#define DW_CH_CTL(base, chan)               (DW_CH((base), (chan))->CH_CTL)
#define DW_CH_STATUS(base, chan)            (DW_CH((base), (chan))->CH_STATUS)
#define DW_CH_IDX(base, chan)               (DW_CH((base), (chan))->CH_IDX)
#define DW_CH_CURR_PTR(base, chan)          (DW_CH((base), (chan))->CH_CURR_PTR)

#define DW_CH_INTR(base, chan)              (DW_CH((base), (chan))->INTR)
#define DW_CH_INTR_SET(base, chan)          (DW_CH((base), (chan))->INTR_SET)
#define DW_CH_INTR_MASK(base, chan)         (DW_CH((base), (chan))->INTR_MASK)
#define DW_CH_INTR_MASKED(base, chan)       (DW_CH((base), (chan))->INTR_MASKED)
#define DW_CH_TR_CMD(base, chan)            (DW_CH((base), (chan))->TR_CMD)

#if defined (CY_IP_MXDW)
#define DW_V2_CRC_CTL_DATA_REVERSE_Msk DW_CRC_CTL_DATA_REVERSE_Msk
#define DW_V2_CRC_CTL_REM_REVERSE_Msk DW_CRC_CTL_REM_REVERSE_Msk
#define DW_V2_CRC_DATA_CTL_DATA_XOR_Msk DW_CRC_DATA_CTL_DATA_XOR_Msk
#define DW_V2_CRC_REM_CTL_REM_XOR_Msk DW_CRC_REM_CTL_REM_XOR_Msk
#define DW_V2_CRC_POL_CTL_POLYNOMIAL_Msk DW_CRC_POL_CTL_POLYNOMIAL_Msk
#define DW_V2_CRC_LFSR_CTL_LFSR32_Msk DW_CRC_LFSR_CTL_LFSR32_Msk
#define DW_V2_CRC_CTL_DATA_REVERSE_Pos DW_CRC_CTL_DATA_REVERSE_Pos
#define DW_V2_CRC_CTL_REM_REVERSE_Pos DW_CRC_CTL_REM_REVERSE_Pos
#define DW_V2_CRC_DATA_CTL_DATA_XOR_Pos DW_CRC_DATA_CTL_DATA_XOR_Pos
#define DW_V2_CRC_REM_CTL_REM_XOR_Pos DW_CRC_REM_CTL_REM_XOR_Pos
#define DW_V2_CRC_POL_CTL_POLYNOMIAL_Pos DW_CRC_POL_CTL_POLYNOMIAL_Pos
#define DW_V2_CRC_LFSR_CTL_LFSR32_Pos DW_CRC_LFSR_CTL_LFSR32_Pos
#endif /* CY_IP_MXDW */

/*******************************************************************************
*                DMAC
*******************************************************************************/
#if defined (CY_IP_MXAHBDMAC)
#define CY_DMAC_CH_NR                       (4UL)
#define DMAC_CTL(base)                      (((MXAHBDMAC_Type*)(base))->CTL)
#define DMAC_ACTIVE(base)                   (((MXAHBDMAC_Type const*)(base))->ACTIVE)
#define DMAC_CH(base, chan)                 (&(((MXAHBDMAC_Type*)(base))->CH[(chan)]))
#define DMAC_CH_CTL(base, chan)             (DMAC_CH(base, chan)->CTL)
#define DMAC_CH_IDX(base, chan)             (DMAC_CH(base, chan)->IDX)
#define DMAC_CH_CURR(base, chan)            (DMAC_CH(base, chan)->CURR)
#define DMAC_CH_DESCR_SRC(base, chan)       (DMAC_CH(base, chan)->DESCR_SRC)
#define DMAC_CH_DESCR_DST(base, chan)       (DMAC_CH(base, chan)->DESCR_DST)
#define DMAC_CH_INTR(base, chan)            (DMAC_CH(base, chan)->INTR)
#define DMAC_CH_INTR_SET(base, chan)        (DMAC_CH(base, chan)->INTR_SET)
#define DMAC_CH_INTR_MASK(base, chan)       (DMAC_CH(base, chan)->INTR_MASK)
#define DMAC_CH_INTR_MASKED(base, chan)     (DMAC_CH(base, chan)->INTR_MASKED)

typedef MXAHBDMAC_Type DMAC_Type;
#define DMAC                                    MXAHBDMAC0_BASE

#define DMAC_CH_V2_INTR_COMPLETION_Msk MXAHBDMAC_CH_INTR_COMPLETION_Msk
#define DMAC_CH_V2_INTR_COMPLETION_Pos MXAHBDMAC_CH_INTR_COMPLETION_Pos
#define DMAC_CH_V2_INTR_SRC_BUS_ERROR_Msk MXAHBDMAC_CH_INTR_SRC_BUS_ERROR_Msk
#define DMAC_CH_V2_INTR_SRC_BUS_ERROR_Pos MXAHBDMAC_CH_INTR_SRC_BUS_ERROR_Pos
#define DMAC_CH_V2_INTR_DST_BUS_ERROR_Msk MXAHBDMAC_CH_INTR_DST_BUS_ERROR_Msk
#define DMAC_CH_V2_INTR_DST_BUS_ERROR_Pos MXAHBDMAC_CH_INTR_DST_BUS_ERROR_Pos
#define DMAC_CH_V2_INTR_SRC_MISAL_Msk MXAHBDMAC_CH_INTR_SRC_MISAL_Msk
#define DMAC_CH_V2_INTR_SRC_MISAL_Pos MXAHBDMAC_CH_INTR_SRC_MISAL_Pos
#define DMAC_CH_V2_INTR_DST_MISAL_Msk MXAHBDMAC_CH_INTR_DST_MISAL_Msk
#define DMAC_CH_V2_INTR_DST_MISAL_Pos MXAHBDMAC_CH_INTR_DST_MISAL_Pos
#define DMAC_CH_V2_INTR_CURR_PTR_NULL_Msk MXAHBDMAC_CH_INTR_CURR_PTR_NULL_Msk
#define DMAC_CH_V2_INTR_CURR_PTR_NULL_Pos MXAHBDMAC_CH_INTR_CURR_PTR_NULL_Pos
#define DMAC_CH_V2_INTR_ACTIVE_CH_DISABLED_Msk MXAHBDMAC_CH_INTR_ACTIVE_CH_DISABLED_Msk
#define DMAC_CH_V2_INTR_ACTIVE_CH_DISABLED_Pos MXAHBDMAC_CH_INTR_ACTIVE_CH_DISABLED_Pos
#define DMAC_CH_V2_INTR_DESCR_BUS_ERROR_Msk MXAHBDMAC_CH_INTR_DESCR_BUS_ERROR_Msk
#define DMAC_CH_V2_INTR_DESCR_BUS_ERROR_Pos MXAHBDMAC_CH_INTR_DESCR_BUS_ERROR_Pos
#define DMAC_Type MXAHBDMAC_Type
#define DMAC_V2_CTL_ENABLED_Msk MXAHBDMAC_CTL_ENABLED_Msk
#define DMAC_V2_CTL_ENABLED_Pos MXAHBDMAC_CTL_ENABLED_Pos
#define DMAC_V2_ACTIVE_ACTIVE_Msk MXAHBDMAC_ACTIVE_ACTIVE_Msk
#define DMAC_V2_ACTIVE_ACTIVE_Pos MXAHBDMAC_ACTIVE_ACTIVE_Pos
#define DMAC_CH_V2_DESCR_CTL_INTR_TYPE_Msk MXAHBDMAC_CH_DESCR_CTL_INTR_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_INTR_TYPE_Pos MXAHBDMAC_CH_DESCR_CTL_INTR_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE_Msk MXAHBDMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE_Pos MXAHBDMAC_CH_DESCR_CTL_TR_IN_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE_Msk MXAHBDMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE_Pos MXAHBDMAC_CH_DESCR_CTL_TR_OUT_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_DATA_SIZE_Msk MXAHBDMAC_CH_DESCR_CTL_DATA_SIZE_Msk
#define DMAC_CH_V2_DESCR_CTL_DATA_SIZE_Pos MXAHBDMAC_CH_DESCR_CTL_DATA_SIZE_Pos
#define DMAC_CH_V2_DESCR_CTL_SRC_TRANSFER_SIZE_Msk MXAHBDMAC_CH_DESCR_CTL_SRC_TRANSFER_SIZE_Msk
#define DMAC_CH_V2_DESCR_CTL_SRC_TRANSFER_SIZE_Pos MXAHBDMAC_CH_DESCR_CTL_SRC_TRANSFER_SIZE_Pos
#define DMAC_CH_V2_DESCR_CTL_DST_TRANSFER_SIZE_Msk MXAHBDMAC_CH_DESCR_CTL_DST_TRANSFER_SIZE_Msk
#define DMAC_CH_V2_DESCR_CTL_DST_TRANSFER_SIZE_Pos MXAHBDMAC_CH_DESCR_CTL_DST_TRANSFER_SIZE_Pos
#define DMAC_CH_V2_DESCR_CTL_WAIT_FOR_DEACT_Msk MXAHBDMAC_CH_DESCR_CTL_WAIT_FOR_DEACT_Msk
#define DMAC_CH_V2_DESCR_CTL_WAIT_FOR_DEACT_Pos MXAHBDMAC_CH_DESCR_CTL_WAIT_FOR_DEACT_Pos
#define DMAC_CH_V2_DESCR_CTL_DESCR_TYPE_Msk MXAHBDMAC_CH_DESCR_CTL_DESCR_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_DESCR_TYPE_Pos MXAHBDMAC_CH_DESCR_CTL_DESCR_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_CH_DISABLE_Msk MXAHBDMAC_CH_DESCR_CTL_CH_DISABLE_Msk
#define DMAC_CH_V2_DESCR_CTL_CH_DISABLE_Pos MXAHBDMAC_CH_DESCR_CTL_CH_DISABLE_Pos
#define DMAC_CH_V2_DESCR_X_INCR_SRC_X_Msk MXAHBDMAC_CH_DESCR_X_INCR_SRC_X_Msk
#define DMAC_CH_V2_DESCR_X_INCR_SRC_X_Pos MXAHBDMAC_CH_DESCR_X_INCR_SRC_X_Pos
#define DMAC_CH_V2_DESCR_X_INCR_DST_X_Msk MXAHBDMAC_CH_DESCR_X_INCR_DST_X_Msk
#define DMAC_CH_V2_DESCR_X_INCR_DST_X_Pos MXAHBDMAC_CH_DESCR_X_INCR_DST_X_Pos
#define DMAC_CH_V2_DESCR_Y_SIZE_Y_COUNT_Msk MXAHBDMAC_CH_DESCR_Y_SIZE_Y_COUNT_Msk
#define DMAC_CH_V2_DESCR_Y_SIZE_Y_COUNT_Pos MXAHBDMAC_CH_DESCR_Y_SIZE_Y_COUNT_Pos
#define DMAC_CH_V2_DESCR_Y_INCR_SRC_Y_Msk MXAHBDMAC_CH_DESCR_Y_INCR_SRC_Y_Msk
#define DMAC_CH_V2_DESCR_Y_INCR_SRC_Y_Pos MXAHBDMAC_CH_DESCR_Y_INCR_SRC_Y_Pos
#define DMAC_CH_V2_DESCR_Y_INCR_DST_Y_Msk MXAHBDMAC_CH_DESCR_Y_INCR_DST_Y_Msk
#define DMAC_CH_V2_DESCR_Y_INCR_DST_Y_Pos MXAHBDMAC_CH_DESCR_Y_INCR_DST_Y_Pos
#define DMAC_CH_V2_CTL_ENABLED_Msk MXAHBDMAC_CH_CTL_ENABLED_Msk
#define DMAC_CH_V2_CTL_ENABLED_Pos MXAHBDMAC_CH_CTL_ENABLED_Pos
#define DMAC_CH_V2_CTL_PRIO_Msk MXAHBDMAC_CH_CTL_PRIO_Msk
#define DMAC_CH_V2_CTL_PRIO_Pos MXAHBDMAC_CH_CTL_PRIO_Pos
#define DMAC_CH_V2_IDX_X_Msk MXAHBDMAC_CH_IDX_X_Msk
#define DMAC_CH_V2_IDX_X_Pos MXAHBDMAC_CH_IDX_X_Pos
#define DMAC_CH_V2_IDX_Y_Msk MXAHBDMAC_CH_IDX_Y_Msk
#define DMAC_CH_V2_IDX_Y_Pos MXAHBDMAC_CH_IDX_Y_Pos
#define DMAC_CH_V2_DESCR_CTL_DATA_PREFETCH_Msk MXAHBDMAC_CH_DESCR_CTL_DATA_PREFETCH_Msk
#define DMAC_CH_V2_DESCR_CTL_DATA_PREFETCH_Pos MXAHBDMAC_CH_DESCR_CTL_DATA_PREFETCH_Pos
#define DMAC_CH_V2_CTL_B_Msk MXAHBDMAC_CH_CTL_B_Msk
#define DMAC_CH_V2_CTL_B_Pos MXAHBDMAC_CH_CTL_B_Pos
#define DMAC_CH_V2_DESCR_X_SIZE_X_COUNT_Msk MXAHBDMAC_CH_DESCR_X_SIZE_X_COUNT_Msk
#define DMAC_CH_V2_DESCR_X_SIZE_X_COUNT_Pos MXAHBDMAC_CH_DESCR_X_SIZE_X_COUNT_Pos

#endif

/*******************************************************************************
*                CRYPTOLITE
*******************************************************************************/
#define CY_PLATFORM_REMAP_ADDRESS_CRYPTOLITE(addr)               (Cy_Platform_RemapAddr(addr))


#if defined(CY_DEVICE_PSC3)
#define CY_DUAL_FLASH_S_SBUS_BASE  0x32800000UL
#define CY_DUAL_FLASH_S_SIZE       0x00020000UL
#define CY_DUAL_FLASH_S_CBUS_BASE  0x12800000UL
#define CY_DUAL_FLASH_NS_SBUS_BASE  0x22800000UL
#define CY_DUAL_FLASH_NS_SIZE       0x00020000UL
#define CY_DUAL_FLASH_NS_CBUS_BASE  0x02800000UL

static inline void * Cy_Platform_RemapAddr(const void *addr)
{
  uint32_t remapAddr, offset;

  #if defined(COMPONENT_SECURE_DEVICE)
  /* FLASH Address Secure */
  if (((uint32_t)addr >= CY_FLASH_S_SBUS_BASE) &&
      ((uint32_t)addr < (CY_FLASH_S_SBUS_BASE + CY_FLASH_SIZE)))
  {
    offset = (uint32_t)addr - CY_FLASH_S_SBUS_BASE;
    remapAddr = CY_FLASH_S_CBUS_BASE + offset;
  }
  /* DUAL FLASH Address Secure */
  else if (((uint32_t)addr >= CY_DUAL_FLASH_S_SBUS_BASE) &&
      ((uint32_t)addr < (CY_DUAL_FLASH_S_SBUS_BASE + CY_DUAL_FLASH_S_SIZE)))
  {
    offset = (uint32_t)addr - CY_DUAL_FLASH_S_SBUS_BASE;
    remapAddr = CY_DUAL_FLASH_S_CBUS_BASE + offset;
  }
  /* SFLASH Address Secure */
  else if (((uint32_t)addr >= CY_SFLASH_S_SBUS_BASE) &&
      ((uint32_t)addr < (CY_SFLASH_S_SBUS_BASE + CY_SFLASH_SIZE)))
  {
    offset = (uint32_t)addr - CY_SFLASH_S_SBUS_BASE;
    remapAddr = CY_SFLASH_S_CBUS_BASE + offset;
  }
  /* SRAM Address Secure */
  else if (((uint32_t)addr >= CY_SRAM_S_CBUS_BASE) &&
      ((uint32_t)addr < (CY_SRAM_S_CBUS_BASE + CY_SRAM_SIZE)))
  {
    offset = (uint32_t)addr - CY_SRAM_S_CBUS_BASE;
    remapAddr = CY_SRAM_S_SBUS_BASE + offset;
  }
  #else
  /* FLASH Address Non-Secure */
  if (((uint32_t)addr >= CY_FLASH_NS_SBUS_BASE) &&
      ((uint32_t)addr < (CY_FLASH_NS_SBUS_BASE + CY_FLASH_SIZE)))
  {
    offset = (uint32_t)addr - CY_FLASH_NS_SBUS_BASE;
    remapAddr = CY_FLASH_NS_CBUS_BASE + offset;
  }
  /* DUAL FLASH Address Non-Secure */
  else if (((uint32_t)addr >= CY_DUAL_FLASH_NS_SBUS_BASE) &&
      ((uint32_t)addr < (CY_DUAL_FLASH_NS_SBUS_BASE + CY_DUAL_FLASH_NS_SIZE)))
  {
    offset = (uint32_t)addr - CY_DUAL_FLASH_NS_SBUS_BASE;
    remapAddr = CY_DUAL_FLASH_NS_CBUS_BASE + offset;
  }
  /* SFLASH Address Non-Secure */
  else if (((uint32_t)addr >= CY_SFLASH_NS_SBUS_BASE) &&
      ((uint32_t)addr < (CY_SFLASH_NS_SBUS_BASE + CY_SFLASH_SIZE)))
  {
    offset = (uint32_t)addr - CY_SFLASH_NS_SBUS_BASE;
    remapAddr = CY_SFLASH_NS_CBUS_BASE + offset;
  }
  /* SRAM Address Non-Secure */
  else if (((uint32_t)addr >= CY_SRAM_NS_CBUS_BASE) &&
      ((uint32_t)addr < (CY_SRAM_NS_CBUS_BASE + CY_SRAM_SIZE)))
  {
    offset = (uint32_t)addr - CY_SRAM_NS_CBUS_BASE;
    remapAddr = CY_SRAM_NS_SBUS_BASE + offset;
  }
  #endif
  else
  {
    remapAddr = (uint32_t)addr;
  }
  return (void *)remapAddr;
}
#else
static inline void * Cy_Platform_RemapAddr(const void *addr)
{
  uint32_t remapAddr, offset;

 /* XIP Address*/
  if (((uint32_t)addr >= CY_XIP_NS_CBUS_BASE) &&
      ((uint32_t)addr < (CY_XIP_NS_CBUS_BASE + CY_XIP_SIZE)))
  {
    offset = (uint32_t)addr - CY_XIP_NS_CBUS_BASE;
    remapAddr = CY_XIP_NS_SBUS_BASE + offset;
  }
  /* SRAM Address*/
  else if (((uint32_t)addr >= CY_SRAM_NS_CBUS_BASE) &&
      ((uint32_t)addr < (CY_SRAM_NS_CBUS_BASE + CY_SRAM_SIZE)))
  {
    offset = (uint32_t)addr - CY_SRAM_NS_CBUS_BASE;
    remapAddr = CY_SRAM_NS_SBUS_BASE + offset;
  }
  else
  {
    remapAddr = (uint32_t)addr;
  }
  return (void *)remapAddr;

}





#endif

/*******************************************************************************
*                IOSS
*******************************************************************************/

#define CY_GPIO_BASE                       ((uint32_t)GPIO_BASE)

#define GPIO_SEC_INTR_CAUSE0               ((GPIO)->SEC_INTR_CAUSE0)
#define GPIO_SEC_INTR_CAUSE1               ((GPIO)->SEC_INTR_CAUSE1)
#define GPIO_SEC_INTR_CAUSE2               ((GPIO)->SEC_INTR_CAUSE2)
#define GPIO_SEC_INTR_CAUSE3               ((GPIO)->SEC_INTR_CAUSE3)
#define GPIO_INTR_CAUSE0                   ((GPIO)->INTR_CAUSE0)
#define GPIO_INTR_CAUSE1                   ((GPIO)->INTR_CAUSE1)
#define GPIO_INTR_CAUSE2                   ((GPIO)->INTR_CAUSE2)
#define GPIO_INTR_CAUSE3                   ((GPIO)->INTR_CAUSE3)

#define GPIO_PRT_OUT(base)                 (((GPIO_PRT_Type*)(base))->OUT)
#define GPIO_PRT_OUT_CLR(base)             (((GPIO_PRT_Type*)(base))->OUT_CLR)
#define GPIO_PRT_OUT_SET(base)             (((GPIO_PRT_Type*)(base))->OUT_SET)
#define GPIO_PRT_OUT_INV(base)             (((GPIO_PRT_Type*)(base))->OUT_INV)
#define GPIO_PRT_IN(base)                  (((GPIO_PRT_Type*)(base))->IN)
#define GPIO_PRT_INTR(base)                (((GPIO_PRT_Type*)(base))->INTR)
#define GPIO_PRT_INTR_MASK(base)           (((GPIO_PRT_Type*)(base))->INTR_MASK)
#define GPIO_PRT_INTR_MASKED(base)         (((GPIO_PRT_Type*)(base))->INTR_MASKED)
#define GPIO_PRT_INTR_SET(base)            (((GPIO_PRT_Type*)(base))->INTR_SET)
#define GPIO_PRT_INTR_CFG(base)            (((GPIO_PRT_Type*)(base))->INTR_CFG)
#define GPIO_PRT_CFG(base)                 (((GPIO_PRT_Type*)(base))->CFG)
#define GPIO_PRT_CFG_IN(base)              (((GPIO_PRT_Type*)(base))->CFG_IN)
#define GPIO_PRT_CFG_OUT(base)             (((GPIO_PRT_Type*)(base))->CFG_OUT)
#define GPIO_PRT_CFG_SIO(base)             (((GPIO_PRT_Type*)(base))->CFG_SIO)
#define GPIO_PRT_SLEW_EXT(base)            (((GPIO_PRT_Type*)(base))->CFG_SLEW_EXT)
#define GPIO_PRT_DRIVE_EXT0(base)          (((GPIO_PRT_Type*)(base))->CFG_DRIVE_EXT0)
#define GPIO_PRT_DRIVE_EXT1(base)          (((GPIO_PRT_Type*)(base))->CFG_DRIVE_EXT1)
#define GPIO_PRT_CFG_IN_AUTOLVL(base)      (((GPIO_PRT_Type*)(base))->CFG_IN_AUTOLVL)

#define CY_HSIOM_BASE                      ((uint32_t)HSIOM_BASE)

#define HSIOM_PRT_PORT_SEL0(base)          (((HSIOM_PRT_Type *)(base))->PORT_SEL0)
#define HSIOM_PRT_PORT_SEL1(base)          (((HSIOM_PRT_Type *)(base))->PORT_SEL1)

#if (IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0)
#define CY_HSIOM_SECURE_BASE               ((uint32_t)&HSIOM->SECURE_PRT[0])
#endif /* IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT */


#define HSIOM_SEC_PRT_NONSEC_MASK(base)    (((HSIOM_SECURE_PRT_Type *)(base))->NONSECURE_MASK)


#define HSIOM_AMUX_SPLIT_CTL(switchCtrl)    (((HSIOM_Type *)HSIOM_BASE)->AMUX_SPLIT_CTL[switchCtrl])

/*******************************************************************************
*                SCB
*******************************************************************************/
#define SCB_CTRL(base)                      (((CySCB_Type*) (base))->CTRL)
#define SCB_SPI_CTRL(base)                  (((CySCB_Type*) (base))->SPI_CTRL)
#define SCB_SPI_STATUS(base)                (((CySCB_Type*) (base))->SPI_STATUS)
#define SCB_SPI_TX_CTRL(base)              (((CySCB_Type*) (base))->SPI_TX_CTRL)
#define SCB_SPI_RX_CTRL(base)              (((CySCB_Type*) (base))->SPI_RX_CTRL)
#define SCB_UART_CTRL(base)                 (((CySCB_Type*) (base))->UART_CTRL)
#define SCB_UART_TX_CTRL(base)              (((CySCB_Type*) (base))->UART_TX_CTRL)
#define SCB_UART_RX_CTRL(base)              (((CySCB_Type*) (base))->UART_RX_CTRL)
#define SCB_UART_FLOW_CTRL(base)            (((CySCB_Type*) (base))->UART_FLOW_CTRL)
#define SCB_I2C_CTRL(base)                  (((CySCB_Type*) (base))->I2C_CTRL)
#define SCB_I2C_STATUS(base)                (((CySCB_Type*) (base))->I2C_STATUS)
#define SCB_I2C_M_CMD(base)                 (((CySCB_Type*) (base))->I2C_M_CMD)
#define SCB_I2C_S_CMD(base)                 (((CySCB_Type*) (base))->I2C_S_CMD)
#define SCB_I2C_CFG(base)                   (((CySCB_Type*) (base))->I2C_CFG)
#define SCB_I2C_STRETCH_CTRL(base)          (((CySCB_Type*) (base))->I2C_STRETCH_CTRL)
#define SCB_I2C_STRETCH_STATUS(base)        (((CySCB_Type*) (base))->I2C_STRETCH_STATUS)
#define SCB_TX_CTRL(base)                   (((CySCB_Type*) (base))->TX_CTRL)
#define SCB_TX_FIFO_CTRL(base)              (((CySCB_Type*) (base))->TX_FIFO_CTRL)
#define SCB_TX_FIFO_STATUS(base)            (((CySCB_Type*) (base))->TX_FIFO_STATUS)
#define SCB_TX_FIFO_WR(base)                (((CySCB_Type*) (base))->TX_FIFO_WR)
#define SCB_RX_CTRL(base)                   (((CySCB_Type*) (base))->RX_CTRL)
#define SCB_RX_FIFO_CTRL(base)              (((CySCB_Type*) (base))->RX_FIFO_CTRL)
#define SCB_RX_FIFO_STATUS(base)            (((CySCB_Type*) (base))->RX_FIFO_STATUS)
#define SCB_RX_MATCH(base)                  (((CySCB_Type*) (base))->RX_MATCH)
#define SCB_RX_FIFO_RD(base)                (((CySCB_Type*) (base))->RX_FIFO_RD)
#define SCB_INTR_CAUSE(base)                (((CySCB_Type*) (base))->INTR_CAUSE)
#define SCB_INTR_I2C_EC(base)               (((CySCB_Type*) (base))->INTR_I2C_EC)
#define SCB_INTR_I2C_EC_MASK(base)          (((CySCB_Type*) (base))->INTR_I2C_EC_MASK)
#define SCB_INTR_I2C_EC_MASKED(base)        (((CySCB_Type*) (base))->INTR_I2C_EC_MASKED)
#define SCB_INTR_SPI_EC(base)               (((CySCB_Type*) (base))->INTR_SPI_EC)
#define SCB_INTR_SPI_EC_MASK(base)          (((CySCB_Type*) (base))->INTR_SPI_EC_MASK)
#define SCB_INTR_SPI_EC_MASKED(base)        (((CySCB_Type*) (base))->INTR_SPI_EC_MASKED)
#define SCB_INTR_M(base)                    (((CySCB_Type*) (base))->INTR_M)
#define SCB_INTR_M_SET(base)                (((CySCB_Type*) (base))->INTR_M_SET)
#define SCB_INTR_M_MASK(base)               (((CySCB_Type*) (base))->INTR_M_MASK)
#define SCB_INTR_M_MASKED(base)             (((CySCB_Type*) (base))->INTR_M_MASKED)
#define SCB_INTR_S(base)                    (((CySCB_Type*) (base))->INTR_S)
#define SCB_INTR_S_SET(base)                (((CySCB_Type*) (base))->INTR_S_SET)
#define SCB_INTR_S_MASK(base)               (((CySCB_Type*) (base))->INTR_S_MASK)
#define SCB_INTR_S_MASKED(base)             (((CySCB_Type*) (base))->INTR_S_MASKED)
#define SCB_INTR_TX(base)                   (((CySCB_Type*) (base))->INTR_TX)
#define SCB_INTR_TX_SET(base)               (((CySCB_Type*) (base))->INTR_TX_SET)
#define SCB_INTR_TX_MASK(base)              (((CySCB_Type*) (base))->INTR_TX_MASK)
#define SCB_INTR_TX_MASKED(base)            (((CySCB_Type*) (base))->INTR_TX_MASKED)
#define SCB_INTR_RX(base)                   (((CySCB_Type*) (base))->INTR_RX)
#define SCB_INTR_RX_SET(base)               (((CySCB_Type*) (base))->INTR_RX_SET)
#define SCB_INTR_RX_MASK(base)              (((CySCB_Type*) (base))->INTR_RX_MASK)
#define SCB_INTR_RX_MASKED(base)            (((CySCB_Type*) (base))->INTR_RX_MASKED)

#if(CY_IP_MXSCB_VERSION>=4)
#define SCB_SPI_CTRL_LATE_MISO_SAMPLE_Pos SCB_SPI_CTRL_LATE_SAMPLE_Pos
#define SCB_SPI_CTRL_LATE_MISO_SAMPLE_Msk SCB_SPI_CTRL_LATE_SAMPLE_Msk
#endif


/*******************************************************************************
*                I3C
*******************************************************************************/


#define I3C_CORE_DEVICE_CTRL(base)                         (((I3C_CORE_Type*) (base))->DEVICE_CTRL)
#define I3C_CORE_DEVICE_ADDR(base)                         (((I3C_CORE_Type*) (base))->DEVICE_ADDR)
#define I3C_CORE_HW_CAPABILITY(base)                     (((I3C_CORE_Type*) (base))->HW_CAPABILITY)
#define I3C_CORE_COMMAND_QUEUE_PORT(base)                 (((I3C_CORE_Type*) (base))->COMMAND_QUEUE_PORT)
#define I3C_CORE_RESPONSE_QUEUE_PORT(base)                 (((I3C_CORE_Type*) (base))->RESPONSE_QUEUE_PORT)
#define I3C_CORE_TX_RX_DATA_PORT(base)                     (((I3C_CORE_Type*) (base))->TX_RX_DATA_PORT)
#define I3C_CORE_IBI_QUEUE_STATUS(base)                 (((I3C_CORE_Type*) (base))->IBI_QUEUE_STATUS)
#define I3C_CORE_QUEUE_THLD_CTRL(base)                     (((I3C_CORE_Type*) (base))->QUEUE_THLD_CTRL)
#define I3C_CORE_DATA_BUFFER_THLD_CTRL(base)            (((I3C_CORE_Type*) (base))->DATA_BUFFER_THLD_CTRL)
#define I3C_CORE_IBI_QUEUE_CTRL(base)                    (((I3C_CORE_Type*) (base))->IBI_QUEUE_CTRL)
#define I3C_CORE_IBI_MR_REQ_REJECT(base)                 (((I3C_CORE_Type*) (base))->IBI_MR_REQ_REJECT)
#define I3C_CORE_IBI_SIR_REQ_REJECT(base)               (((I3C_CORE_Type*) (base))->IBI_SIR_REQ_REJECT)
#define I3C_CORE_RESET_CTRL(base)                       (((I3C_CORE_Type*) (base))->RESET_CTRL)
#define I3C_CORE_SLV_EVENT_STATUS(base)                 (((I3C_CORE_Type*) (base))->SLV_EVENT_STATUS)
#define I3C_CORE_INTR_STATUS(base)                      (((I3C_CORE_Type*) (base))->INTR_STATUS)
#define I3C_CORE_INTR_STATUS_EN(base)                   (((I3C_CORE_Type*) (base))->INTR_STATUS_EN)
#define I3C_CORE_INTR_SIGNAL_EN(base)                   (((I3C_CORE_Type*) (base))->INTR_SIGNAL_EN)
#define I3C_CORE_INTR_FORCE(base)                       (((I3C_CORE_Type*) (base))->INTR_FORCE)
#define I3C_CORE_QUEUE_STATUS_LEVEL(base)               (((I3C_CORE_Type*) (base))->QUEUE_STATUS_LEVEL)
#define I3C_CORE_DATA_BUFFER_STATUS_LEVEL(base)         (((I3C_CORE_Type*) (base))->DATA_BUFFER_STATUS_LEVEL)
#define I3C_CORE_PRESENT_STATE(base)                     (((I3C_CORE_Type*) (base))->PRESENT_STATE)
#define I3C_CORE_CCC_DEVICE_STATUS(base)                (((I3C_CORE_Type*) (base))->CCC_DEVICE_STATUS)
#define I3C_CORE_DEVICE_ADDR_TABLE_POINTER(base)        (((I3C_CORE_Type*) (base))->DEVICE_ADDR_TABLE_POINTER)
#define I3C_CORE_DEV_CHAR_TABLE_POINTER(base)           (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE_POINTER)
#define I3C_CORE_VENDOR_SPECIFIC_REG_POINTER(base)      (((I3C_CORE_Type*) (base))->VENDOR_SPECIFIC_REG_POINTER)
#define I3C_CORE_SLV_PID_VALUE(base)                    (((I3C_CORE_Type*) (base))->SLV_PID_VALUE)
#define I3C_CORE_SLV_CHAR_CTRL(base)                    (((I3C_CORE_Type*) (base))->SLV_CHAR_CTRL)
#define I3C_CORE_SLV_MAX_LEN(base)                      (((I3C_CORE_Type*) (base))->SLV_MAX_LEN)
#define I3C_CORE_MAX_READ_TURNAROUND(base)              (((I3C_CORE_Type*) (base))->MAX_READ_TURNAROUND)
#define I3C_CORE_MAX_DATA_SPEED(base)                   (((I3C_CORE_Type*) (base))->MAX_DATA_SPEED)
#define I3C_CORE_SLV_INTR_REQ(base)                      (((I3C_CORE_Type*) (base))->SLV_INTR_REQ)
#define I3C_CORE_DEVICE_CTRL_EXTENDED(base)             (((I3C_CORE_Type*) (base))->DEVICE_CTRL_EXTENDED)
#define I3C_CORE_SCL_I3C_OD_TIMING(base)                (((I3C_CORE_Type*) (base))->SCL_I3C_OD_TIMING)
#define I3C_CORE_SCL_I3C_PP_TIMING(base)                (((I3C_CORE_Type*) (base))->SCL_I3C_PP_TIMING)
#define I3C_CORE_SCL_I2C_FM_TIMING(base)                (((I3C_CORE_Type*) (base))->SCL_I2C_FM_TIMING)
#define I3C_CORE_SCL_I2C_FMP_TIMING(base)               (((I3C_CORE_Type*) (base))->SCL_I2C_FMP_TIMING)
#define I3C_CORE_SCL_EXT_LCNT_TIMING(base)              (((I3C_CORE_Type*) (base))->SCL_EXT_LCNT_TIMING)
#define I3C_CORE_SCL_EXT_TERMN_LCNT_TIMING(base)        (((I3C_CORE_Type*) (base))->SCL_EXT_TERMN_LCNT_TIMING)
#define I3C_CORE_SDA_HOLD_DLY_TIMING(base)              (((I3C_CORE_Type*) (base))->SDA_HOLD_DLY_TIMING)
#define I3C_CORE_BUS_FREE_AVAIL_TIMING(base)            (((I3C_CORE_Type*) (base))->BUS_FREE_AVAIL_TIMING)
#define I3C_CORE_BUS_IDLE_TIMING(base)                   (((I3C_CORE_Type*) (base))->BUS_IDLE_TIMING)
#define I3C_CORE_I3C_VER_ID(base)                       (((I3C_CORE_Type*) (base))->I3C_VER_ID)
#define I3C_CORE_I3C_VER_TYPE(base)                     (((I3C_CORE_Type*) (base))->I3C_VER_TYPE)
#define I3C_CORE_QUEUE_SIZE_CAPABILITY(base)            (((I3C_CORE_Type*) (base))->QUEUE_SIZE_CAPABILITY)
#define I3C_CORE_DEV_CHAR_TABLE1_LOC1(base)                (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE1_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE1_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE1_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE1_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE1_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE1_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE1_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE2_LOC1(base)                (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE2_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE2_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE2_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE2_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE2_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE2_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE2_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE3_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE3_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE3_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE3_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE3_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE3_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE3_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE3_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE4_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE4_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE4_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE4_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE4_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE4_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE4_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE4_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE5_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE5_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE5_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE5_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE5_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE5_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE5_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE5_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE6_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE6_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE6_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE6_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE6_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE6_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE6_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE6_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE7_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE7_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE7_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE7_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE7_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE7_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE7_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE7_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE8_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE8_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE8_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE8_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE8_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE8_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE8_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE8_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE9_LOC1(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE9_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE9_LOC2(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE9_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE9_LOC3(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE9_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE9_LOC4(base)             (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE9_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE10_LOC1(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE10_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE10_LOC2(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE10_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE10_LOC3(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE10_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE10_LOC4(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE10_LOC4)
#define I3C_CORE_DEV_CHAR_TABLE11_LOC1(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE11_LOC1)
#define I3C_CORE_DEV_CHAR_TABLE11_LOC2(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE11_LOC2)
#define I3C_CORE_DEV_CHAR_TABLE11_LOC3(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE11_LOC3)
#define I3C_CORE_DEV_CHAR_TABLE11_LOC4(base)            (((I3C_CORE_Type*) (base))->DEV_CHAR_TABLE11_LOC4)
#define I3C_CORE_DEV_ADDR_TABLE_LOC1(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC1)
#define I3C_CORE_DEV_ADDR_TABLE_LOC2(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC2)
#define I3C_CORE_DEV_ADDR_TABLE_LOC3(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC3)
#define I3C_CORE_DEV_ADDR_TABLE_LOC4(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC4)
#define I3C_CORE_DEV_ADDR_TABLE_LOC5(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC5)
#define I3C_CORE_DEV_ADDR_TABLE_LOC6(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC6)
#define I3C_CORE_DEV_ADDR_TABLE_LOC7(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC7)
#define I3C_CORE_DEV_ADDR_TABLE_LOC8(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC8)
#define I3C_CORE_DEV_ADDR_TABLE_LOC9(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC9)
#define I3C_CORE_DEV_ADDR_TABLE_LOC10(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC10)
#define I3C_CORE_DEV_ADDR_TABLE_LOC11(base)                (((I3C_CORE_Type*) (base))->DEV_ADDR_TABLE_LOC11)

/*******************************************************************************
*                EFUSE
******************************************************************************/

#define EFUSE_CTL(base)                              (((EFUSE_Type *) (base))->CTL)
#define EFUSE_TEST(base)                             (((EFUSE_Type *) (base))->TEST)
#define EFUSE_CMD(base)                              (((EFUSE_Type *) (base))->CMD)
#define EFUSE_CONFIG(base)                           (((EFUSE_Type *) (base))->CONFIG)
#define EFUSE_SEQ_DEFAULT(base)                      (((EFUSE_Type *) (base))->SEQ_DEFAULT)
#define EFUSE_SEQ_READ_CTL_0(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_0)
#define EFUSE_SEQ_READ_CTL_1(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_1)
#define EFUSE_SEQ_READ_CTL_2(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_2)
#define EFUSE_SEQ_READ_CTL_3(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_3)
#define EFUSE_SEQ_READ_CTL_4(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_4)
#define EFUSE_SEQ_READ_CTL_5(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_5)
#define EFUSE_SEQ_READ_CTL_6(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_6)
#define EFUSE_SEQ_READ_CTL_7(base)                   (((EFUSE_Type *) (base))->SEQ_READ_CTL_7)
#define EFUSE_SEQ_PROGRAM_CTL_0(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_0)
#define EFUSE_SEQ_PROGRAM_CTL_1(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_1)
#define EFUSE_SEQ_PROGRAM_CTL_2(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_2)
#define EFUSE_SEQ_PROGRAM_CTL_3(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_3)
#define EFUSE_SEQ_PROGRAM_CTL_4(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_4)
#define EFUSE_SEQ_PROGRAM_CTL_5(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_5)
#define EFUSE_SEQ_PROGRAM_CTL_6(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_6)
#define EFUSE_SEQ_PROGRAM_CTL_7(base)                (((EFUSE_Type *) (base))->SEQ_PROGRAM_CTL_7)
#define EFUSE_BOOTROW(base)                          (((EFUSE_Type *) (base))->BOOTROW)

/*******************************************************************************
*                FAULT
*******************************************************************************/

#define FAULT_CTL(base)                         (((FAULT_STRUCT_Type *)(base))->CTL)
#define FAULT_STATUS(base)                      (((FAULT_STRUCT_Type *)(base))->STATUS)
#define FAULT_DATA(base)                        (((FAULT_STRUCT_Type *)(base))->DATA)
#define FAULT_PENDING0(base)                    (((FAULT_STRUCT_Type *)(base))->PENDING0)
#define FAULT_PENDING1(base)                    (((FAULT_STRUCT_Type *)(base))->PENDING1)
#define FAULT_PENDING2(base)                    (((FAULT_STRUCT_Type *)(base))->PENDING2)
#define FAULT_MASK0(base)                       (((FAULT_STRUCT_Type *)(base))->MASK0)
#define FAULT_MASK1(base)                       (((FAULT_STRUCT_Type *)(base))->MASK1)
#define FAULT_MASK2(base)                       (((FAULT_STRUCT_Type *)(base))->MASK2)
#define FAULT_INTR(base)                        (((FAULT_STRUCT_Type *)(base))->INTR)
#define FAULT_INTR_SET(base)                    (((FAULT_STRUCT_Type *)(base))->INTR_SET)
#define FAULT_INTR_MASK(base)                   (((FAULT_STRUCT_Type *)(base))->INTR_MASK)
#define FAULT_INTR_MASKED(base)                 (((FAULT_STRUCT_Type *)(base))->INTR_MASKED)

#if defined (CY_DEVICE_CYW20829)
/**
  * \brief Instances of Fault data register.
  */
typedef enum
{
    CY_SYSFAULT_MPU_0                =   0,     /* Bus master 0 MPU/SMPU. */
    CY_SYSFAULT_MPU_1                =   1,     /* Bus master 1 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_2                =   2,     /* Bus master 2 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_3                =   3,     /* Bus master 3 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_4                =   4,     /* Bus master 4 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_5                =   5,     /* Bus master 5 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_6                =   6,     /* Bus master 6 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_7                =   7,     /* Bus master 7 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_8                =   8,     /* Bus master 8 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_9                =   9,     /* Bus master 9 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_10               =  10,     /* Bus master 10 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_11               =  11,     /* Bus master 11 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_12               =  12,     /* Bus master 12 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_13               =  13,     /* Bus master 13 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_14               =  14,     /* Bus master 14 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_15               =  15,     /* Bus master 15 MPU. See MPU_0 description. */
    CY_SYSFAULT_CM4_SYS_MPU          =  16,     /* CM4 system bus AHB-Lite interface MPU. See MPU_0 description. */
    CY_SYSFAULT_CM4_CODE_MPU         =  17,     /* CM4 code bus AHB-Lite interface MPU for non flash controller accesses. See MPU_0 description. */
    CM4_CODE_FLASHC_MPU              =  18,     /* CM4 code bus AHB-Lite interface MPU for flash controller accesses. See MPU_0 description. */
    CY_SYSFAULT_MS_PPU_4             =  25,     /* Peripheral interconnect, master interface 4 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_PERI_ECC             =  26,     /* Peripheral interconnect, protection structures SRAM, correctable ECC error: */
    CY_SYSFAULT_PERI_NC_ECC          =  27,     /* Peripheral interconnect, protection structures SRAM, non-correctable ECC error. */
    CY_SYSFAULT_MS_PPU_0             =  28,     /* Peripheral interconnect, master interface 0 PPU. */
    CY_SYSFAULT_MS_PPU_1             =  29,     /* Peripheral interconnect, master interface 1 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_MS_PPU_2             =  30,     /* Peripheral interconnect, master interface 2 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_MS_PPU_3             =  31,     /* Peripheral interconnect, master interface 3 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_GROUP_FAULT_0        =  32,     /* Peripheral group 0 fault detection. */
    CY_SYSFAULT_GROUP_FAULT_1        =  33,     /* Peripheral group 1 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_2        =  34,     /* Peripheral group 2 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_3        =  35,     /* Peripheral group 3 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_4        =  36,     /* Peripheral group 4 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_5        =  37,     /* Peripheral group 5 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_6        =  38,     /* Peripheral group 6 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_7        =  39,     /* Peripheral group 7 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_8        =  40,     /* Peripheral group 8 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_9        =  41,     /* Peripheral group 9 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_10       =  42,     /* Peripheral group 10 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_11       =  43,     /* Peripheral group 11 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_12       =  44,     /* Peripheral group 12 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_13       =  45,     /* Peripheral group 13 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_14       =  46,     /* Peripheral group 14 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_15       =  47,     /* Peripheral group 15 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_FLASHC_MAIN_BUS_ERROR  =  48,   /* Flash controller, main interface, bus error: */
    CY_SYSFAULT_FLASHC_MAIN_C_ECC    =  49,     /* Flash controller, main interface, correctable ECC error: */
    CY_SYSFAULT_FLASHC_MAIN_NC_ECC   =  50,     /* Flash controller, main interface, non-correctable ECC error.  See FLASHC_MAIN_C_ECC description. */
    CY_SYSFAULT_FLASHC_WORK_BUS_ERROR  =  51,   /* Flash controller, work interface, bus error. See FLASHC_MAIN_BUS_ERROR description. */
    CY_SYSFAULT_FLASHC_WORK_C_ECC    =  52,     /* Flash controller, work interface, correctable ECC error: */
    CY_SYSFAULT_FLASHC_WORK_NC_ECC   =  53,     /* Flash controller, work interface, non-correctable ECC error. See FLASHC_WORK_C_ECC description. */
    CY_SYSFAULT_FLASHC_CM0_CA_C_ECC  =  54,     /* Flash controller, CM0+ cache, correctable ECC error: */
    CY_SYSFAULT_FLASHC_CM0_CA_NC_ECC  =  55,    /* Flash controller, CM0+ cache, non-correctable ECC error.  See FLASHC_CM0_CA_C_ECC description. */
    CY_SYSFAULT_FLASHC_CM4_CA_C_ECC  =  56,     /* Flash controller, CM4 cache, correctable ECC error. See FLASHC_CM0_CA_C_ECC description. */
    CY_SYSFAULT_FLASHC_CM4_CA_NC_ECC =  57,     /* Flash controller, CM4 cache, non-correctable ECC error. See FLASHC_CM0_CA_C_ECC description.. */
    CY_SYSFAULT_RAMC0_C_ECC          =  58,     /* System SRAM 0 correctable ECC error: */
    CY_SYSFAULT_RAMC0_NC_ECC         =  59,     /* System SRAM 0 non-correctable ECC error.  See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC1_C_ECC          =  60,     /* System SRAM 1 correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC1_NC_ECC         =  61,     /* System SRAM 1 non-correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC2_C_ECC          =  62,     /* System SRAM 2 correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC2_NC_ECC         =  63,     /* System SRAM 2 non-correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_CRYPTO_C_ECC         =  64,     /* Cryptography SRAM correctable ECC error. */
    CY_SYSFAULT_CRYPTO_NC_ECC        =  65,     /* Cryptography SRAM non-correctable ECC error. See CRYPTO_C_ECC description. */
    CY_SYSFAULT_DW0_C_ECC            =  70,     /* DataWire 0 SRAM 1 correctable ECC error: */
    CY_SYSFAULT_DW0_NC_ECC           =  71,     /* DataWire 0 SRAM 1 non-correctable ECC error. See DW0_C_ECC description. */
    CY_SYSFAULT_DW1_C_ECC            =  72,     /* DataWire 1 SRAM 1 correctable ECC error. See DW0_C_ECC description. */
    CY_SYSFAULT_DW1_NC_ECC           =  73,     /* DataWire 1 SRAM 1 non-correctable ECC error. See DW0_C_ECC description. */
    CY_SYSFAULT_FM_SRAM_C_ECC        =  74,     /* eCT Flash SRAM (for embedded operations) correctable ECC error: */
    CY_SYSFAULT_FM_SRAM_NC_ECC       =  75,     /* eCT Flash SRAM non-correctable ECC error: See FM_SRAM_C_ECC description. */
    CY_SYSFAULT_CAN0_C_ECC           =  80,     /* CAN controller 0 MRAM correctable ECC error: */
    CY_SYSFAULT_CAN0_NC_ECC          =  81,     /* CAN controller 0 MRAM non-correctable ECC error: */
    CY_SYSFAULT_CAN1_C_ECC           =  82,     /* CAN controller 1 MRAM correctable ECC error. See CAN0_C_ECC description. */
    CY_SYSFAULT_CAN1_NC_ECC          =  83,     /* CAN controller 1 MRAM non-correctable ECC error. See CAN0_NC_ECC description. */
    CY_SYSFAULT_CAN2_C_ECC           =  84,     /* CAN controller 2 MRAM correctable ECC error. See CAN0_C_ECC description.. */
    CY_SYSFAULT_CAN2_NC_ECC          =  85,     /* CAN controller 2 MRAM non-correctable ECC error. See CAN0_NC_ECC description. */
    CY_SYSFAULT_SRSS_CSV             =  90,     /* SRSS Clock SuperVisor (CSV) violation detected. Multiple CSV can detect a violation at the same time. */
    CY_SYSFAULT_SRSS_SSV             =  91,     /* SRSS Clock SuperVisor (CSV) violation detected. Multiple CSV can detect a violation at the same time. */
    CY_SYSFAULT_SRSS_MCWDT0          =  92,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #0 violation detected. Multiple counters can detect a violation at the same time. */
    CY_SYSFAULT_SRSS_MCWDT1          =  93,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #1 violation detected. See SRSS_MCWDT0 description. */
    CY_SYSFAULT_SRSS_MCWDT2          =  94,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #2 violation detected. See SRSS_MCWDT0 description. */
    CY_SYSFAULT_SRSS_MCWDT3          =  95,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #3 violation detected. See SRSS_MCWDT0 description. */
    CY_SYSFAULT_NO_FAULT             =  96
} en_sysfault_source_t;
#endif /* defined (CY_DEVICE_CYW20829) */

/*******************************************************************************
*                PROFILE
*******************************************************************************/


#define CY_EP_MONITOR_COUNT                 ((uint32_t)(cy_device->epMonitorNr))
#define CY_EP_CNT_NR                        (8UL)
#define PROFILE_CTL                         (((PROFILE_Type*) PROFILE_BASE)->CTL)
#define PROFILE_STATUS                      (((PROFILE_Type*) PROFILE_BASE)->STATUS)
#define PROFILE_CMD                         (((PROFILE_Type*) PROFILE_BASE)->CMD)
#define PROFILE_INTR                        (((PROFILE_Type*) PROFILE_BASE)->INTR)
#define PROFILE_INTR_MASK                   (((PROFILE_Type*) PROFILE_BASE)->INTR_MASK)
#define PROFILE_INTR_MASKED                 (((PROFILE_Type*) PROFILE_BASE)->INTR_MASKED)
#define PROFILE_CNT_STRUCT                  (((PROFILE_Type*) PROFILE_BASE)->CNT_STRUCT)

/*******************************************************************************
*                SRSS
*******************************************************************************/

#define CY_SRSS_NUM_PLL400M                 0
#define CY_SRSS_PLL400M_PRESENT             0
#if defined (CY_DEVICE_PSC3)
#define CY_SRSS_DPLL_LP_PRESENT             SRSS_NUM_DPLL250
#define SRSS_NUM_DPLL_LP                    SRSS_NUM_DPLL250
#define SRSS_PLL_250M_0_PATH_NUM            (1UL)
#define SRSS_PLL_250M_1_PATH_NUM            (2UL)
#define CY_SYSCLK_HF_MAX_FREQ(hfNum)        (240000000U)
#define CY_MXS40SSRSS_VER_1_2               1UL
#define SRSS_DPLL_LP_FRAC_BIT_COUNT         (24ULL)
#define SRSS_CLK_ROOT_SELECT_ROOT_DIV       SRSS_CLK_ROOT_SELECT_ROOT_DIV_INT
#define PWRMODE_PWR_SELECT                  (((PWRMODE_Type *) PWRMODE)->CLK_SELECT)
#define SRSS_CLK_DPLL_LP_CONFIG(pllNum)     (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG)
#define SRSS_CLK_DPLL_LP_CONFIG2(pllNum)    (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG2)
#define SRSS_CLK_DPLL_LP_CONFIG3(pllNum)    (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG3)
#define SRSS_CLK_DPLL_LP_CONFIG4(pllNum)    (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG4)
#define SRSS_CLK_DPLL_LP_CONFIG5(pllNum)    (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG5)
#define SRSS_CLK_DPLL_LP_CONFIG6(pllNum)    (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG6)
#define SRSS_CLK_DPLL_LP_CONFIG7(pllNum)    (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].CONFIG7)
#define SRSS_CLK_DPLL_LP_STATUS(pllNum)     (((SRSS_Type *) SRSS)->CLK_DPLL_LP[pllNum].STATUS)
#define SRSS_TRIM_RAM_CTL                   (((SRSS_Type*) SRSS)->RAM_TRIM_STRUCT.TRIM_RAM_CTL)
#define SRSS_TRIM_ROM_CTL                   (((SRSS_Type*) SRSS)->RAM_TRIM_STRUCT.TRIM_ROM_CTL)
#define SRSS_PWR_TRIM_PWRSYS_CTL            (*(volatile uint32_t *) 0x422020E0U)
#define SRSS_PWR_TRIM_WAKE_CTL              (*(volatile uint32_t *) 0x422020E8U)
/* SRSS.PWR_TRIM_PWRSYS_CTL */
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM_Pos 0UL
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM_Msk 0x1FUL
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_BOOST_Pos 30UL
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_BOOST_Msk 0xC0000000UL
/* SRSS.PWR_TRIM_WAKE_CTL */
#define SRSS_PWR_TRIM_WAKE_CTL_WAKE_DELAY_Pos   0UL
#define SRSS_PWR_TRIM_WAKE_CTL_WAKE_DELAY_Msk   0xFFUL

#else
#define CY_SRSS_DPLL_LP_PRESENT             0
#define CY_MXS40SSRSS_VER_1_2               0UL
#endif
#define CY_SRSS_NUM_CLKPATH                 SRSS_NUM_CLKPATH
#define CY_SRSS_NUM_PLL                     SRSS_NUM_TOTAL_PLL
#define CY_SRSS_NUM_HFROOT                  SRSS_NUM_HFROOT
#define CY_SRSS_ECO_PRESENT                 SRSS_ECO_PRESENT
#define CY_SRSS_FLL_PRESENT                 SRSS_FLL_PRESENT
#define CY_SRSS_PLL_PRESENT                 SRSS_NUM_TOTAL_PLL
#define CY_SRSS_ALTHF_PRESENT               SRSS_ALTHF_PRESENT

#if defined (CY_IP_MXS28SRSS)
#define CY_SRSS_IHO_PRESENT                 0
#define CY_SRSS_MFO_PRESENT                 0
#endif

#if defined (CY_IP_MXS40SSRSS)
#define CY_SRSS_IHO_PRESENT                 1
#define CY_SRSS_MFO_PRESENT                 1
#define CY_SRSS_PILO_PRESENT                SRSS_S40S_PILO_PRESENT
#define CY_SRSS_ILO_PRESENT                 1
#define CY_SRSS_IMO_PRESENT                 1
#endif


/** HF PATH # used for PERI PCLK */
#define CY_SYSCLK_CLK_PERI_HF_PATH_NUM     1U

/** HF PATH # used for Core */
#define CY_SYSCLK_CLK_CORE_HF_PATH_NUM     0U

/** FLL Max Frequency */
#define  CY_SYSCLK_FLL_MAX_OUTPUT_FREQ     (96000000UL)



/* HF PATH # Max Allowed Frequencies */
#define CY_SYSCLK_MAX_FREQ_HF0             96000000U
#define CY_SYSCLK_MAX_FREQ_HF1             96000000U
#define CY_SYSCLK_MAX_FREQ_HF2             48000000U
#define CY_SYSCLK_MAX_FREQ_HF3             24000000U


#if defined (CY_DEVICE_CYW20829)
#define CY_SYSCLK_HF_MAX_FREQ(hfNum)       (((hfNum) == 0U) ?  (CY_SYSCLK_MAX_FREQ_HF0) : \
                                           (((hfNum) == 1U) ?  (CY_SYSCLK_MAX_FREQ_HF1) : \
                                           (((hfNum) == 2U) ?  (CY_SYSCLK_MAX_FREQ_HF2) : \
                                           (((hfNum) == 3U) ?  (CY_SYSCLK_MAX_FREQ_HF3) : \
                                           (0U)))))
#endif

/* Technology Independant Register set */
#define SRSS_CLK_DSI_SELECT                 (((SRSS_Type *) SRSS)->CLK_DSI_SELECT)
#define SRSS_CLK_OUTPUT_FAST                (((SRSS_Type *) SRSS)->CLK_OUTPUT_FAST)
#define SRSS_CLK_OUTPUT_SLOW                (((SRSS_Type *) SRSS)->CLK_OUTPUT_SLOW)
#define SRSS_CLK_CAL_CNT1                   (((SRSS_Type *) SRSS)->CLK_CAL_CNT1)
#define SRSS_CLK_CAL_CNT2                   (((SRSS_Type *) SRSS)->CLK_CAL_CNT2)
#define SRSS_SRSS_INTR                      (((SRSS_Type *) SRSS)->SRSS_INTR)
#define SRSS_SRSS_INTR_SET                  (((SRSS_Type *) SRSS)->SRSS_INTR_SET)
#define SRSS_SRSS_INTR_MASK                 (((SRSS_Type *) SRSS)->SRSS_INTR_MASK)
#define SRSS_SRSS_INTR_MASKED               (((SRSS_Type *) SRSS)->SRSS_INTR_MASKED)
#define SRSS_SRSS_AINTR                     (((SRSS_Type *) SRSS)->SRSS_AINTR)
#define SRSS_SRSS_AINTR_SET                 (((SRSS_Type *) SRSS)->SRSS_AINTR_SET)
#define SRSS_SRSS_AINTR_MASK                (((SRSS_Type *) SRSS)->SRSS_AINTR_MASK)
#define SRSS_SRSS_AINTR_MASKED              (((SRSS_Type *) SRSS)->SRSS_AINTR_MASKED)
#define SRSS_PWR_CTL                        (((SRSS_Type *) SRSS)->PWR_CTL)
#define SRSS_PWR_CTL2                       (((SRSS_Type *) SRSS)->PWR_CTL2)
#define SRSS_PWR_HIBERNATE                  (((SRSS_Type *) SRSS)->PWR_HIBERNATE)
#define SRSS_PWR_CTL3                       (((SRSS_Type *) SRSS)->PWR_CTL3)
#define SRSS_PWR_STATUS                     (((SRSS_Type *) SRSS)->PWR_STATUS)
#define SRSS_PWR_HIB_DATA                   (((SRSS_Type *) SRSS)->PWR_HIB_DATA)
#define SRSS_CLK_PATH_SELECT                (((SRSS_Type *) SRSS)->CLK_PATH_SELECT)
#define SRSS_CLK_ROOT_SELECT                (((SRSS_Type *) SRSS)->CLK_ROOT_SELECT)
#define SRSS_CLK_DIRECT_SELECT              (((SRSS_Type *) SRSS)->CLK_DIRECT_SELECT)
#define SRSS_CLK_ECO_STATUS                 (((SRSS_Type *) SRSS)->CLK_ECO_STATUS)
#define SRSS_CLK_ILO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_ILO_CONFIG)
#define SRSS_CLK_TRIM_ILO_CTL               (((SRSS_Type *) SRSS)->CLK_TRIM_ILO_CTL)
#define SRSS_CLK_PILO_CONFIG                (((SRSS_Type *) SRSS)->CLK_PILO_CONFIG)
#define SRSS_CLK_ECO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_ECO_CONFIG)
#define SRSS_CLK_ECO_CONFIG2                (((SRSS_Type *) SRSS)->CLK_ECO_CONFIG2)
#define SRSS_CLK_MFO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_MFO_CONFIG)
#define SRSS_CLK_IHO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_IHO_CONFIG)
#define SRSS_CLK_ALTHF_CTL                  (((SRSS_Type *) SRSS)->CLK_ALTHF_CTL)

#if defined (CY_IP_MXS28SRSS)
#define SRSS_CLK_ILO_CONFIG2                (((SRSS_Type *) SRSS)->CLK_ILO_CONFIG2)
#define SRSS_CLK_PILO_CONFIG2               (((SRSS_Type *) SRSS)->CLK_PILO_CONFIG2)
#endif
#define SRSS_CSV_HF                         (((SRSS_Type *) SRSS)->CSV_HF)
#define SRSS_CLK_SELECT                     (((SRSS_Type *) SRSS)->CLK_SELECT)
#define SRSS_CLK_TIMER_CTL                  (((SRSS_Type *) SRSS)->CLK_TIMER_CTL)
#define SRSS_CLK_IMO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_IMO_CONFIG)
#define SRSS_CLK_ECO_PRESCALE               (((SRSS_Type *) SRSS)->CLK_ECO_PRESCALE)
#define SRSS_CLK_MF_SELECT                  (((SRSS_Type *) SRSS)->CLK_MF_SELECT)
#define SRSS_CSV_REF_SEL                    (((SRSS_Type *) SRSS)->CSV_REF_SEL)
#define SRSS_CSV_REF                        (((SRSS_Type *) SRSS)->CSV_REF)
#define SRSS_CSV_LF                         (((SRSS_Type *) SRSS)->CSV_LF)
#define SRSS_CSV_ILO                        (((SRSS_Type *) SRSS)->CSV_ILO)
#define SRSS_RES_CAUSE                      (((SRSS_Type *) SRSS)->RES_CAUSE)
#define SRSS_RES_CAUSE2                     (((SRSS_Type *) SRSS)->RES_CAUSE2)
#define SRSS_RES_CAUSE_EXTEND               (((SRSS_Type *) SRSS)->RES_CAUSE_EXTEND)
#define SRSS_PWR_CBUCK_CTL                  (((SRSS_Type *) SRSS)->PWR_CBUCK_CTL)
#define SRSS_PWR_CBUCK_CTL2                 (((SRSS_Type *) SRSS)->PWR_CBUCK_CTL2)
#define SRSS_PWR_CBUCK_CTL3                 (((SRSS_Type *) SRSS)->PWR_CBUCK_CTL3)
#define SRSS_PWR_CBUCK_STATUS               (((SRSS_Type *) SRSS)->PWR_CBUCK_STATUS)
#define SRSS_PWR_SDR0_CTL                   (((SRSS_Type *) SRSS)->PWR_SDR0_CTL)
#define SRSS_PWR_SDR1_CTL                   (((SRSS_Type *) SRSS)->PWR_SDR1_CTL)
#define SRSS_PWR_HVLDO0_CTL                 (((SRSS_Type *) SRSS)->PWR_HVLDO0_CTL)
#define SRSS_CLK_LP_PLL                     (((SRSS_Type *) SRSS)->CLK_LP_PLL)
#define SRSS_CLK_IHO                        (((SRSS_Type *) SRSS)->CLK_IHO)
#define SRSS_TST_XRES_SECURE                (((SRSS_Type *) SRSS)->TST_XRES_SECURE)
#define SRSS_RES_PXRES_CTL                  (((SRSS_Type *) SRSS)->RES_PXRES_CTL)
#define SRSS_WDT_CTL                        (((SRSS_Type *) SRSS)->WDT_CTL)
#define SRSS_WDT_CNT                        (((SRSS_Type *) SRSS)->WDT_CNT)
#define SRSS_WDT_MATCH                      (((SRSS_Type *) SRSS)->WDT_MATCH)
#if defined (CY_IP_MXS40SSRSS)
#define SRSS_WDT_MATCH2                      (((SRSS_Type *) SRSS)->WDT_MATCH2)
#endif

#if defined (CY_IP_MXS28SRSS)
#define SRSS_CLK_LP_PLL_CONFIG(pllNum)      (((CLK_LP_PLL_Type*) &SRSS->CLK_LP_PLL[pllNum])->PLL28LP_STRUCT.CONFIG)
#define SRSS_CLK_LP_PLL_CONFIG2(pllNum)     (((CLK_LP_PLL_Type*) &SRSS->CLK_LP_PLL[pllNum])->PLL28LP_STRUCT.CONFIG2)
#define SRSS_CLK_LP_PLL_CONFIG3(pllNum)     (((CLK_LP_PLL_Type*) &SRSS->CLK_LP_PLL[pllNum])->PLL28LP_STRUCT.CONFIG3)
#define SRSS_CLK_LP_PLL_CONFIG4(pllNum)     (((CLK_LP_PLL_Type*) &SRSS->CLK_LP_PLL[pllNum])->PLL28LP_STRUCT.CONFIG4)
#define SRSS_CLK_LP_PLL_CONFIG5(pllNum)     (((CLK_LP_PLL_Type*) &SRSS->CLK_LP_PLL[pllNum])->PLL28LP_STRUCT.CONFIG5)
#define SRSS_CLK_LP_PLL_STATUS(pllNum)      (((CLK_LP_PLL_Type*) &SRSS->CLK_LP_PLL[pllNum])->PLL28LP_STRUCT.STATUS)
#endif

#if defined (CY_IP_MXS40SSRSS)
#define SRSS_CLK_FLL_CONFIG                 (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG)
#define SRSS_CLK_FLL_CONFIG2                (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG2)
#define SRSS_CLK_FLL_CONFIG3                (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG3)
#define SRSS_CLK_FLL_CONFIG4                (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG4)
#define SRSS_CLK_FLL_STATUS                 (((SRSS_Type *) SRSS)->CLK_FLL_STATUS)

#define SRSS_PWR_LVD_CTL                    (((SRSS_Type *) SRSS)->PWR_LVD_CTL)
#define SRSS_PWR_LVD_STATUS                 (((SRSS_Type *) SRSS)->PWR_LVD_STATUS)

#define SRSS_PWR_HIB_WAKE_CTL               (((SRSS_Type *) SRSS)->PWR_HIB_WAKE_CTL)
#define SRSS_PWR_HIB_WAKE_CTL2              (((SRSS_Type *) SRSS)->PWR_HIB_WAKE_CTL2)
#define SRSS_PWR_HIB_WAKE_CAUSE             (((SRSS_Type *) SRSS)->PWR_HIB_WAKE_CAUSE)
#define SRSS_RES_SOFT_CTL                   (((SRSS_Type *) SRSS)->RES_SOFT_CTL)
#endif

#if defined (CY_DEVICE_CYW20829)
#define SRSS_TST_DDFT_FAST_CTL_REG          (*(volatile uint32_t *) 0x40201104U)
#define SRSS_TST_DDFT_SLOW_CTL_REG          (*(volatile uint32_t *) 0x40201108U)
#else
#define SRSS_TST_DDFT_FAST_CTL_REG          (*(volatile uint32_t *) 0x42201104U)
#define SRSS_TST_DDFT_SLOW_CTL_REG          (*(volatile uint32_t *) 0x42201108U)
#endif

#define SRSS_TST_DDFT_SLOW_CTL_MASK         (0x00001F1EU)
#define SRSS_TST_DDFT_FAST_CTL_MASK         (62U)

#if defined (CY_IP_MXS40SSRSS)
/* PPU configurations for DEEPSLEEP */
#define CY_SYSTEM_MAIN_PPU_DEEPSLEEP_MODE        PPU_V1_MODE_FULL_RET
#define CY_SYSTEM_CPUSS_PPU_DEEPSLEEP_MODE       PPU_V1_MODE_FULL_RET
#define CY_SYSTEM_SRAM_PPU_DEEPSLEEP_MODE        PPU_V1_MODE_MEM_RET

/* PPU configurations for DEEPSLEEP-RAM */
#define CY_SYSTEM_MAIN_PPU_DEEPSLEEP_RAM_MODE    PPU_V1_MODE_MEM_RET
#define CY_SYSTEM_CPUSS_PPU_DEEPSLEEP_RAM_MODE   PPU_V1_MODE_OFF
#define CY_SYSTEM_SRAM_PPU_DEEPSLEEP_RAM_MODE    PPU_V1_MODE_MEM_RET

/* PPU configurations for DEEPSLEEP-OFF */
#define CY_SYSTEM_MAIN_PPU_DEEPSLEEP_OFF_MODE    PPU_V1_MODE_OFF
#define CY_SYSTEM_CPUSS_PPU_DEEPSLEEP_OFF_MODE   PPU_V1_MODE_OFF
#define CY_SYSTEM_SRAM_PPU_DEEPSLEEP_OFF_MODE    PPU_V1_MODE_OFF

/* System DEEPSLEEP Mode = (PPU_MAIN Mode)*/
#define CY_SYSTEM_DEEPSLEEP_PPU_MODES        ((uint32_t)CY_SYSTEM_MAIN_PPU_DEEPSLEEP_MODE)
#define CY_SYSTEM_DEEPSLEEP_RAM_PPU_MODES    ((uint32_t)CY_SYSTEM_MAIN_PPU_DEEPSLEEP_RAM_MODE)
#define CY_SYSTEM_DEEPSLEEP_OFF_PPU_MODES    ((uint32_t)CY_SYSTEM_MAIN_PPU_DEEPSLEEP_OFF_MODE)
#endif

#define SRSS_CSV_HF_CSV_REF_CTL(hf)             (((SRSS_Type *) SRSS)->CSV_HF_STRUCT.CSV[hf].REF_CTL)
#define SRSS_CSV_HF_CSV_REF_LIMIT(hf)           (((SRSS_Type *) SRSS)->CSV_HF_STRUCT.CSV[hf].REF_LIMIT)
#define SRSS_CSV_HF_CSV_MON_CTL(hf)             (((SRSS_Type *) SRSS)->CSV_HF_STRUCT.CSV[hf].MON_CTL)
#define CSV_HF_CSV_REF_CTL_CSV_STARTUP           CSV_HF_CSV_REF_CTL_STARTUP
#define CSV_HF_CSV_REF_LIMIT_CSV_LOWER           CSV_HF_CSV_REF_LIMIT_LOWER
#define CSV_HF_CSV_REF_LIMIT_CSV_UPPER           CSV_HF_CSV_REF_LIMIT_UPPER
#define CSV_HF_CSV_MON_CTL_CSV_PERIOD            CSV_HF_CSV_MON_CTL_PERIOD

#define SRSS_CSV_LF_CSV_REF_CTL                 (((SRSS_Type *) SRSS)->CSV_LF_STRUCT.CSV.REF_CTL)
#define SRSS_CSV_LF_CSV_REF_LIMIT               (((SRSS_Type *) SRSS)->CSV_LF_STRUCT.CSV.REF_LIMIT)
#define SRSS_CSV_LF_CSV_MON_CTL                 (((SRSS_Type *) SRSS)->CSV_LF_STRUCT.CSV.MON_CTL)
#define CSV_LF_CSV_REF_CTL_CSV_STARTUP           CSV_LF_CSV_REF_CTL_STARTUP
#define CSV_LF_CSV_REF_LIMIT_CSV_LOWER           CSV_LF_CSV_REF_LIMIT_LOWER
#define CSV_LF_CSV_REF_LIMIT_CSV_UPPER           CSV_LF_CSV_REF_LIMIT_UPPER
#define CSV_LF_CSV_MON_CTL_CSV_PERIOD            CSV_LF_CSV_MON_CTL_PERIOD

#define SRSS_BOOT_ENTRY                         (((SRSS_Type *) SRSS)->BOOT_ENTRY)

/*******************************************************************************
*                PERI
*******************************************************************************/
/*******************************************************************************
*                PERI PCLK
*******************************************************************************/

#define PERI_INSTANCE_COUNT                    (1U)

#ifndef PERI0_PCLK_GROUP_NR
#define PERI0_PCLK_GROUP_NR     PERI_PCLK_GROUP_NR
#endif

#ifndef PERI1_PCLK_GROUP_NR
#define PERI1_PCLK_GROUP_NR     (0U)
#endif


#ifndef PERI_PCLK0_BASE
#define PERI_PCLK0_BASE     PERI_PCLK_BASE
#endif

#ifndef PERI_PCLK1_BASE
#define PERI_PCLK1_BASE     0U
#endif

#if (PERI_INSTANCE_COUNT == 1U)
#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT 0U


#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT 0U


#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT 0U

#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT 0U

#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT 0U

#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT 0U


#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT 0U

#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT 0U

#endif

#define PERI_PCLK_PERI_NUM_Msk                 (0x000000FFU)
#define PERI_PCLK_GR_NUM_Msk                   (0x0000FF00U)
#define PERI_PCLK_GR_NUM_Pos                   (8U)
#define PERI_PCLK_PERIPHERAL_GROUP_NUM         (1UL << PERI_PCLK_GR_NUM_Pos)
#define PERI_PCLK_INST_NUM_Msk                 (0x00FF0000U)
#define PERI_PCLK_INST_NUM_Pos                 (16U)

#define PERI_PCLK_GR_NUM(instNum)              (((instNum) == 0U)? PERI0_PCLK_GROUP_NR : PERI1_PCLK_GROUP_NR)

#define PERI_PCLK1_OFFSET                      (PERI_PCLK1_BASE - PERI_PCLK0_BASE)
#define PERI_PCLK_REG_BASE(instNum)            ((PERI_PCLK_Type*)(PERI_PCLK0_BASE + ((instNum) * PERI_PCLK1_OFFSET)))

#define PERI_DIV_8_CTL(instNum, grNum, divNum)                   ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_8_CTL[divNum]
#define PERI_DIV_16_CTL(instNum, grNum, divNum)                  ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_16_CTL[divNum]
#define PERI_DIV_16_5_CTL(instNum, grNum, divNum)                ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_16_5_CTL[divNum]
#define PERI_DIV_24_5_CTL(instNum, grNum, divNum)                ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_24_5_CTL[divNum]
#define PERI_CLOCK_CTL(instNum, grNum, periNum)                  ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->CLOCK_CTL[periNum]
#define PERI_DIV_CMD(instNum, grNum)                             ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_CMD

#define PERI_PCLK_GR_DIV_8_NR(instNum, grNum)     (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT) |      \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT) << 8U)         |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT) << 16U)        |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT)) |        \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT) |      \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

#define PERI_PCLK_GR_DIV_16_NR(instNum, grNum)    (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT) |      \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT) << 8U)         |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT) << 16U)        |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT)) |         \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT) |       \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

#define PERI_PCLK_GR_DIV_16_5_NR(instNum, grNum)  (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT) |          \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT) << 16U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT)) |         \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT) |       \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

#define PERI_PCLK_GR_DIV_24_5_NR(instNum, grNum)  (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT) |      \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT) << 8U)         |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT) << 16U)        |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT)) |         \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT) |       \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

/* PERI_PCLK_GR.DIV_CMD */
#define CY_PERI_DIV_CMD_DIV_SEL_Pos             PERI_PCLK_GR_DIV_CMD_DIV_SEL_Pos
#define CY_PERI_DIV_CMD_DIV_SEL_Msk             PERI_PCLK_GR_DIV_CMD_DIV_SEL_Msk
#define CY_PERI_DIV_CMD_TYPE_SEL_Pos            PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Pos
#define CY_PERI_DIV_CMD_TYPE_SEL_Msk            PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Msk
#define CY_PERI_DIV_CMD_PA_DIV_SEL_Pos          PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Pos
#define CY_PERI_DIV_CMD_PA_DIV_SEL_Msk          PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Msk
#define CY_PERI_DIV_CMD_PA_TYPE_SEL_Pos         PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Pos
#define CY_PERI_DIV_CMD_PA_TYPE_SEL_Msk         PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Msk
#define CY_PERI_DIV_CMD_DISABLE_Pos             PERI_PCLK_GR_DIV_CMD_DISABLE_Pos
#define CY_PERI_DIV_CMD_DISABLE_Msk             PERI_PCLK_GR_DIV_CMD_DISABLE_Msk
#define CY_PERI_DIV_CMD_ENABLE_Pos              PERI_PCLK_GR_DIV_CMD_ENABLE_Pos
#define CY_PERI_DIV_CMD_ENABLE_Msk              PERI_PCLK_GR_DIV_CMD_ENABLE_Msk


#define PERI_DIV_CMD_DIV_SEL_Pos                PERI_PCLK_GR_DIV_CMD_DIV_SEL_Pos
#define PERI_DIV_CMD_DIV_SEL_Msk                PERI_PCLK_GR_DIV_CMD_DIV_SEL_Msk
#define PERI_DIV_CMD_TYPE_SEL_Pos               PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Pos
#define PERI_DIV_CMD_TYPE_SEL_Msk               PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Msk
#define PERI_DIV_CMD_PA_DIV_SEL_Pos             PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Pos
#define PERI_DIV_CMD_PA_DIV_SEL_Msk             PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Msk
#define PERI_DIV_CMD_PA_TYPE_SEL_Pos            PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Pos
#define PERI_DIV_CMD_PA_TYPE_SEL_Msk            PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Msk
#define PERI_DIV_CMD_DISABLE_Pos                PERI_PCLK_GR_DIV_CMD_DISABLE_Pos
#define PERI_DIV_CMD_DISABLE_Msk                PERI_PCLK_GR_DIV_CMD_DISABLE_Msk
#define PERI_DIV_CMD_ENABLE_Pos                 PERI_PCLK_GR_DIV_CMD_ENABLE_Pos
#define PERI_DIV_CMD_ENABLE_Msk                 PERI_PCLK_GR_DIV_CMD_ENABLE_Msk

/* PERI_PCLK_GR.CLOCK_CTL */
#define CY_PERI_CLOCK_CTL_DIV_SEL_Pos           PERI_PCLK_GR_CLOCK_CTL_DIV_SEL_Pos
#define CY_PERI_CLOCK_CTL_DIV_SEL_Msk           PERI_PCLK_GR_CLOCK_CTL_DIV_SEL_Msk
#define CY_PERI_CLOCK_CTL_TYPE_SEL_Pos          PERI_PCLK_GR_CLOCK_CTL_TYPE_SEL_Pos
#define CY_PERI_CLOCK_CTL_TYPE_SEL_Msk          PERI_PCLK_GR_CLOCK_CTL_TYPE_SEL_Msk
/* PERI.DIV_8_CTL */
#define PERI_DIV_8_CTL_EN_Pos                   PERI_PCLK_GR_DIV_8_CTL_EN_Pos
#define PERI_DIV_8_CTL_EN_Msk                   PERI_PCLK_GR_DIV_8_CTL_EN_Msk
#define PERI_DIV_8_CTL_INT8_DIV_Pos             PERI_PCLK_GR_DIV_8_CTL_INT8_DIV_Pos
#define PERI_DIV_8_CTL_INT8_DIV_Msk             PERI_PCLK_GR_DIV_8_CTL_INT8_DIV_Msk
/* PERI.DIV_16_CTL */
#define PERI_DIV_16_CTL_EN_Pos                  PERI_PCLK_GR_DIV_16_CTL_EN_Pos
#define PERI_DIV_16_CTL_EN_Msk                  PERI_PCLK_GR_DIV_16_CTL_EN_Msk
#define PERI_DIV_16_CTL_INT16_DIV_Pos           PERI_PCLK_GR_DIV_16_CTL_INT16_DIV_Pos
#define PERI_DIV_16_CTL_INT16_DIV_Msk           PERI_PCLK_GR_DIV_16_CTL_INT16_DIV_Msk
/* PERI.DIV_16_5_CTL */
#define PERI_DIV_16_5_CTL_EN_Pos                PERI_PCLK_GR_DIV_16_5_CTL_EN_Pos
#define PERI_DIV_16_5_CTL_EN_Msk                PERI_PCLK_GR_DIV_16_5_CTL_EN_Msk
#define PERI_DIV_16_5_CTL_FRAC5_DIV_Pos         PERI_PCLK_GR_DIV_16_5_CTL_FRAC5_DIV_Pos
#define PERI_DIV_16_5_CTL_FRAC5_DIV_Msk         PERI_PCLK_GR_DIV_16_5_CTL_FRAC5_DIV_Msk
#define PERI_DIV_16_5_CTL_INT16_DIV_Pos         PERI_PCLK_GR_DIV_16_5_CTL_INT16_DIV_Pos
#define PERI_DIV_16_5_CTL_INT16_DIV_Msk         PERI_PCLK_GR_DIV_16_5_CTL_INT16_DIV_Msk
/* PERI.DIV_24_5_CTL */
#define PERI_DIV_24_5_CTL_EN_Pos                PERI_PCLK_GR_DIV_24_5_CTL_EN_Pos
#define PERI_DIV_24_5_CTL_EN_Msk                PERI_PCLK_GR_DIV_24_5_CTL_EN_Msk
#define PERI_DIV_24_5_CTL_FRAC5_DIV_Pos         PERI_PCLK_GR_DIV_24_5_CTL_FRAC5_DIV_Pos
#define PERI_DIV_24_5_CTL_FRAC5_DIV_Msk         PERI_PCLK_GR_DIV_24_5_CTL_FRAC5_DIV_Msk
#define PERI_DIV_24_5_CTL_INT24_DIV_Pos         PERI_PCLK_GR_DIV_24_5_CTL_INT24_DIV_Pos
#define PERI_DIV_24_5_CTL_INT24_DIV_Msk         PERI_PCLK_GR_DIV_24_5_CTL_INT24_DIV_Msk

/*******************************************************************************
*                PERI-GROUP
*******************************************************************************/
#if defined (CY_DEVICE_PSC3)
#define CY_PERI_GROUP_NR                        6
#else
#define CY_PERI_GROUP_NR                        4
#define CY_PERI_BLESS_GROUP_NR                  3
#endif /* CY_DEVICE_PSC3 */

#ifndef PERI0_BASE
#define PERI0_BASE PERI_BASE
#endif

#ifndef PERI1_BASE
#define PERI1_BASE 0U
#endif


#define PERI_GR_OFFSET                      (PERI1_BASE - PERI0_BASE)
#define PERI_GR_REG_BASE(instNum)           ((PERI_Type*)(PERI0_BASE + ((instNum) * PERI_GR_OFFSET)))

#define PERI_GR_INST_NUM_Msk                 (0x0000FF00U)
#define PERI_GR_INST_NUM_Pos                 (8U)


#define PERI_GR_CLOCK_CTL(instNum, grNum)   ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->CLOCK_CTL
#define PERI_GR_SL_CTL(instNum, grNum)      ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->SL_CTL
#define PERI_GR_SL_CTL2(instNum, grNum)     ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->SL_CTL2
#define PERI_GR_SL_CTL3(instNum, grNum)     ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->SL_CTL3

/*******************************************************************************
*                PERI-TR
*******************************************************************************/

#define PERI_TR_CMD                         (((PERI_Type*) (PERI_BASE))->TR_CMD)
#define PERI_TR_GR_TR_CTL(group, trCtl)     (*(volatile uint32_t*) ((uint32_t)PERI_BASE+ (uint32_t)offsetof(PERI_Type,TR_GR) + \
                                            ((group) * (uint32_t)sizeof(PERI_TR_GR_Type)) + \
                                            ((trCtl) * (uint32_t)sizeof(uint32_t))))

#if defined (CY_IP_MXSPERI)
#define PERI_TR_GR_TR_OUT_CTL_TR_SEL_Msk PERI_TR_GR_TR_CTL_TR_SEL_Msk
#define PERI_TR_GR_TR_OUT_CTL_TR_SEL_Pos PERI_TR_GR_TR_CTL_TR_SEL_Pos
#define CY_PERI_TR_CTL_SEL_Msk PERI_TR_GR_TR_CTL_TR_SEL_Msk
#define CY_PERI_TR_CTL_SEL_Pos PERI_TR_GR_TR_CTL_TR_SEL_Pos
#define PERI_V2_TR_CMD_OUT_SEL_Msk PERI_TR_CMD_OUT_SEL_Msk
#define PERI_V2_TR_CMD_OUT_SEL_Pos PERI_TR_CMD_OUT_SEL_Pos
#define PERI_V2_TR_CMD_GROUP_SEL_Msk PERI_TR_CMD_GROUP_SEL_Msk
#define PERI_V2_TR_CMD_GROUP_SEL_Pos PERI_TR_CMD_GROUP_SEL_Pos
#define CY_PERI_TR_CMD_GROUP_SEL_Msk PERI_TR_CMD_GROUP_SEL_Msk
#define CY_PERI_TR_CMD_GROUP_SEL_Pos PERI_TR_CMD_GROUP_SEL_Pos
#define CY_PERI_TR_CTL_SEL PERI_TR_GR_TR_CTL_TR_SEL
#define PERI_TR_GR_TR_OUT_CTL_TR_INV_Msk PERI_TR_GR_TR_CTL_TR_INV_Msk
#define PERI_TR_GR_TR_OUT_CTL_TR_INV_Pos PERI_TR_GR_TR_CTL_TR_INV_Pos
#define PERI_TR_GR_TR_OUT_CTL_TR_EDGE_Msk PERI_TR_GR_TR_CTL_TR_EDGE_Msk
#define PERI_TR_GR_TR_OUT_CTL_TR_EDGE_Pos PERI_TR_GR_TR_CTL_TR_EDGE_Pos
#define PERI_V2_TR_CMD_TR_EDGE_Msk PERI_TR_CMD_TR_EDGE_Msk
#define PERI_V2_TR_CMD_TR_EDGE_Pos PERI_TR_CMD_TR_EDGE_Pos
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV_Msk PERI_TR_1TO1_GR_TR_CTL_TR_INV_Msk
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV_Pos PERI_TR_1TO1_GR_TR_CTL_TR_INV_Pos
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE_Msk PERI_TR_1TO1_GR_TR_CTL_TR_EDGE_Msk
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE_Pos PERI_TR_1TO1_GR_TR_CTL_TR_EDGE_Pos
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_SEL_Msk PERI_TR_1TO1_GR_TR_CTL_TR_SEL_Msk
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_SEL_Pos PERI_TR_1TO1_GR_TR_CTL_TR_SEL_Pos
#define PERI_TR_GR_V2_TR_CTL_DBG_FREEZE_EN_Msk PERI_TR_GR_TR_CTL_DBG_FREEZE_EN_Msk
#define PERI_TR_GR_V2_TR_CTL_DBG_FREEZE_EN_Pos PERI_TR_GR_TR_CTL_DBG_FREEZE_EN_Pos
#define CY_PERI_V1 0U
#define PERI_TR_CMD_COUNT_Pos 0UL
#define PERI_TR_CMD_COUNT_Msk 0UL
#endif /* CY_IP_MXSPERI */

/* CLK_HF* to PERI PCLK Group Mapping */
#define PERI0_PCLK_GR_NUM_0_CLK_HF_NUM              (0U)
#define PERI0_PCLK_GR_NUM_1_CLK_HF_NUM              (1U)
#define PERI0_PCLK_GR_NUM_2_CLK_HF_NUM              (0U)
#define PERI0_PCLK_GR_NUM_3_CLK_HF_NUM              (1U)
#define PERI0_PCLK_GR_NUM_4_CLK_HF_NUM              (2U)
#define PERI0_PCLK_GR_NUM_5_CLK_HF_NUM              (3U)
#if defined (CY_DEVICE_PSC3)
#define PERI0_PCLK_GR_NUM_6_CLK_HF_NUM              (4U)
#else
#define PERI0_PCLK_GR_NUM_6_CLK_HF_NUM              (1U)
#endif


#if defined (CY_IP_MXS40SSRSS)
#if defined (CY_DEVICE_PSC3)
#define CY_SYSPM_BOOTROM_ENTRYPOINT_ADDR        ((uint32_t)&(SRSS_BOOT_ENTRY)) /* Boot ROM will check this address for locating the entry point after Warm Boot */
#else
#define CY_SYSPM_BOOTROM_ENTRYPOINT_ADDR        ((uint32_t)(&BACKUP_BREG_SET1[0])) /* Boot ROM will check this address for locating the entry point after Warm Boot */
#endif /* defined (CY_DEVICE_PSC3) */
#define CY_SYSPM_BOOTROM_DSRAM_DBG_ENABLE_MASK 0x00000001U
#endif
#if defined (CY_DEVICE_CYW20829)
#define ENABLE_MEM_VOLTAGE_TRIMS
#endif


/*******************************************************************************
*                MXCM33
*******************************************************************************/
#define MXCM33_CM33_NMI_CTL(nmi)              (((volatile uint32_t *) (MXCM33->CM33_NMI_CTL))[(nmi)])

/*******************************************************************************
*                MCWDT
*******************************************************************************/

#define MCWDT_CNTLOW(base)      (((MCWDT_STRUCT_Type *)(base))->MCWDT_CNTLOW)
#define MCWDT_CNTHIGH(base)     (((MCWDT_STRUCT_Type *)(base))->MCWDT_CNTHIGH)
#define MCWDT_MATCH(base)       (((MCWDT_STRUCT_Type *)(base))->MCWDT_MATCH)
#define MCWDT_CONFIG(base)      (((MCWDT_STRUCT_Type *)(base))->MCWDT_CONFIG)
#define MCWDT_CTL(base)         (((MCWDT_STRUCT_Type *)(base))->MCWDT_CTL)
#define MCWDT_INTR(base)        (((MCWDT_STRUCT_Type *)(base))->MCWDT_INTR)
#define MCWDT_INTR_SET(base)    (((MCWDT_STRUCT_Type *)(base))->MCWDT_INTR_SET)
#define MCWDT_INTR_MASK(base)   (((MCWDT_STRUCT_Type *)(base))->MCWDT_INTR_MASK)
#define MCWDT_INTR_MASKED(base) (((MCWDT_STRUCT_Type *)(base))->MCWDT_INTR_MASKED)
#define MCWDT_LOCK(base)        (((MCWDT_STRUCT_Type *)(base))->MCWDT_LOCK)
#define MCWDT_LOWER_LIMIT(base) (((MCWDT_STRUCT_Type *)(base))->MCWDT_LOWER_LIMIT)

#if defined (CY_DEVICE_PSC3)
/*******************************************************************************
*                SFLASH
*******************************************************************************/
#define SFLASH_CPUSS_TRIM_ROM_CTL_LP        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_LP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_LP        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_LP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_MF        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_MF)
#define SFLASH_CPUSS_TRIM_RAM_CTL_MF        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_MF)
#define SFLASH_CPUSS_TRIM_ROM_CTL_OD        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_OD)
#define SFLASH_CPUSS_TRIM_RAM_CTL_OD        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_OD)
#define SFLASH_CPUSS_TRIM_ROM_CTL_ULP       (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_ULP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_ULP       (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_ULP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_LP   (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_HALF_LP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_LP   (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_HALF_LP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_MF   (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_HALF_MF)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_MF   (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_HALF_MF)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_OD   (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_HALF_OD)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_OD   (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_HALF_OD)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_ULP  (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_ROM_CTL_HALF_ULP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_ULP  (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->CPUSS_TRIM_RAM_CTL_HALF_ULP)

#define SFLASH_LDO_0P9V_TRIM                (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->LDO_0P9V_TRIM)
#define SFLASH_LDO_1P0V_TRIM                (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->LDO_1P0V_TRIM)
#define SFLASH_LDO_1P1V_TRIM                (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->LDO_1P1V_TRIM)
#define SFLASH_LDO_1P2V_TRIM                (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->LDO_1P2V_TRIM)
#define SFLASH_PWR_TRIM_WAKE_CTL            (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->PWR_TRIM_WAKE_CTL)

#define SFLASH_DIE_YEAR                     (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_YEAR)
#define SFLASH_DIE_MINOR                    (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_MINOR)
#define SFLASH_DIE_SORT                     (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_SORT)
#define SFLASH_DIE_Y                        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_Y)
#define SFLASH_DIE_X                        (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_X)
#define SFLASH_DIE_WAFER                    (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_WAFER)
#define SFLASH_DIE_LOT(val)                 (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->DIE_LOT[(val)])

#define SFLASH_SAR_CALOFFST_0_N40C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_0_N40C)
#define SFLASH_SAR_CALOFFST_1_N40C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_1_N40C)
#define SFLASH_SAR_CALOFFST_2_N40C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_2_N40C)
#define SFLASH_SAR_CALOFFST_3_N40C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_3_N40C)
#define SFLASH_SAR_CALOFFST_0_125C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_0_125C)
#define SFLASH_SAR_CALOFFST_1_125C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_1_125C)
#define SFLASH_SAR_CALOFFST_2_125C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_2_125C)
#define SFLASH_SAR_CALOFFST_3_125C          (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_3_125C)
#define SFLASH_SAR_CALOFFST_0_25C           (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_0_25C)
#define SFLASH_SAR_CALOFFST_1_25C           (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_1_25C)
#define SFLASH_SAR_CALOFFST_2_25C           (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_2_25C)
#define SFLASH_SAR_CALOFFST_3_25C           (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALOFFST_3_25C)
#define SFLASH_SAR_CALREFPT                 (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALREFPT)
#define SFLASH_SAR_TEMP_COEF_A              (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_TEMP_COEF_A)
#define SFLASH_SAR_TEMP_COEF_B              (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_TEMP_COEF_B)
#define SFLASH_SAR_TEMP_COEF_C              (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_TEMP_COEF_C)
#define SFLASH_SAR_TEMP_COEF_D              (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_TEMP_COEF_D)
#define SFLASH_SAR_CAL_LIN_TABLE(val)       (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CAL_LIN_TABLE[(val)])
#define SFLASH_SAR_CALGAINC                 (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALGAINC)
#define SFLASH_SAR_CALGAINF                 (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_CALGAINF)
#define SFLASH_SAR_INFRA_TRIM_TABLE         (((SFLASH_Type *) CY_SFLASH_NS_SBUS_BASE)->SAR_INFRA_TRIM_TABLE)
#endif

/*******************************************************************************
*                CPUSS
*******************************************************************************/
#define CPUSS_SYSTICK_NS_CTL                (((CPUSS_Type*) CPUSS_BASE)->SYSTICK_NS_CTL)
#define CPUSS_SYSTICK_S_CTL                 (((CPUSS_Type*) CPUSS_BASE)->SYSTICK_S_CTL)
#if defined (CY_DEVICE_CYW20829)
#define CPUSS_TRIM_RAM_CTL                  (((CPUSS_Type*) CPUSS_BASE)->TRIM_RAM_CTL)
#define CPUSS_TRIM_ROM_CTL                  (((CPUSS_Type*) CPUSS_BASE)->TRIM_ROM_CTL)
#endif
#define CPUSS_PRODUCT_ID                    (((CPUSS_Type*) CPUSS_BASE)->PRODUCT_ID)


/* ARM core registers */
#define SYSTICK_CTRL                        (((SysTick_Type *)SysTick)->CTRL)
#define SYSTICK_LOAD                        (((SysTick_Type *)SysTick)->LOAD)
#define SYSTICK_VAL                         (((SysTick_Type *)SysTick)->VAL)
#define SYSTICK_NS_CTRL                     (((SysTick_Type *)SysTick_NS)->CTRL)
#define SYSTICK_NS_LOAD                     (((SysTick_Type *)SysTick_NS)->LOAD)
#define SYSTICK_NS_VAL                      (((SysTick_Type *)SysTick_NS)->VAL)
#define SCB_SCR                             (((SCB_Type *)SCB)->SCR)

#define SCS_CPPWR                           (((SCnSCB_Type *)SCnSCB)->CPPWR)
#define SCS_ENABLE_CPPWR_SU10_SU11          (0xFUL << 20u)
#define SCS_CPPWR_SU10_Msk                  (0x100000U)

#define SCB_ENABLE_CPACR_CP10_CP11          (0xFUL << 20u)
#define SCB_CPACR                           (((SCB_Type *)SCB)->CPACR)

#if defined (CY_DEVICE_CYW20829)
#define CY_UNIQE_DEVICE_ID_PRESENT_SFLASH      0u
#else
#define CY_UNIQE_DEVICE_ID_PRESENT_SFLASH      1u
#endif


/*******************************************************************************
*                LPCOMP
*******************************************************************************/

#define LPCOMP_CMP0_CTRL(base)              (((LPCOMP_Type *)(base))->CMP0_CTRL)
#define LPCOMP_CMP1_CTRL(base)              (((LPCOMP_Type *)(base))->CMP1_CTRL)
#define LPCOMP_CMP0_SW_CLEAR(base)          (((LPCOMP_Type *)(base))->CMP0_SW_CLEAR)
#define LPCOMP_CMP1_SW_CLEAR(base)          (((LPCOMP_Type *)(base))->CMP1_SW_CLEAR)
#define LPCOMP_CMP0_SW(base)                (((LPCOMP_Type *)(base))->CMP0_SW)
#define LPCOMP_CMP1_SW(base)                (((LPCOMP_Type *)(base))->CMP1_SW)
#define LPCOMP_STATUS(base)                 (((LPCOMP_Type *)(base))->STATUS)
#define LPCOMP_CONFIG(base)                 (((LPCOMP_Type *)(base))->CONFIG)
#define LPCOMP_INTR(base)                   (((LPCOMP_Type *)(base))->INTR)
#define LPCOMP_INTR_SET(base)               (((LPCOMP_Type *)(base))->INTR_SET)
#define LPCOMP_INTR_MASK(base)              (((LPCOMP_Type *)(base))->INTR_MASK)
#define LPCOMP_INTR_MASKED(base)            (((LPCOMP_Type *)(base))->INTR_MASKED)


/*******************************************************************************
*                TCPWM
*******************************************************************************/

#if defined CY_IP_MXS40TCPWM
/* CY_IP_MXS40TCPWM is nothing but the CY_IP_MXTCPWM version 3. In PSOC C3 it is called CY_IP_MXS40TCPWM */
#define CY_IP_MXTCPWM                   1u
#define CY_IP_MXTCPWM_VERSION           3u
#endif /* defined CY_IP_MXS40TCPWM */

#define TCPWM_CTRL_SET(base)                (((TCPWM_Type *)(base))->CTRL_SET)
#define TCPWM_CTRL_CLR(base)                (((TCPWM_Type *)(base))->CTRL_CLR)
#define TCPWM_CMD_START(base)               (((TCPWM_Type *)(base))->CMD_START)
#define TCPWM_CMD_RELOAD(base)              (((TCPWM_Type *)(base))->CMD_RELOAD)
#define TCPWM_CMD_STOP(base)                (((TCPWM_Type *)(base))->CMD_STOP)
#define TCPWM_CMD_CAPTURE(base)             (((TCPWM_Type *)(base))->CMD_CAPTURE)

#define TCPWM_CNT_CTRL(base, cntNum)         (((TCPWM_Type *)(base))->CNT[cntNum].CTRL)
#define TCPWM_CNT_CC(base, cntNum)           (((TCPWM_Type *)(base))->CNT[cntNum].CC)
#define TCPWM_CNT_CC_BUFF(base, cntNum)      (((TCPWM_Type *)(base))->CNT[cntNum].CC_BUFF)
#define TCPWM_CNT_COUNTER(base, cntNum)      (((TCPWM_Type *)(base))->CNT[cntNum].COUNTER)
#define TCPWM_CNT_PERIOD(base, cntNum)       (((TCPWM_Type *)(base))->CNT[cntNum].PERIOD)
#define TCPWM_CNT_PERIOD_BUFF(base, cntNum)  (((TCPWM_Type *)(base))->CNT[cntNum].PERIOD_BUFF)
#define TCPWM_CNT_STATUS(base, cntNum)       (((TCPWM_Type *)(base))->CNT[cntNum].STATUS)
#define TCPWM_CNT_INTR(base, cntNum)         (((TCPWM_Type *)(base))->CNT[cntNum].INTR)
#define TCPWM_CNT_INTR_SET(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].INTR_SET)
#define TCPWM_CNT_INTR_MASK(base, cntNum)    (((TCPWM_Type *)(base))->CNT[cntNum].INTR_MASK)
#define TCPWM_CNT_INTR_MASKED(base, cntNum)  (((TCPWM_Type *)(base))->CNT[cntNum].INTR_MASKED)
#define TCPWM_CNT_TR_CTRL0(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].TR_CTRL0)
#define TCPWM_CNT_TR_CTRL1(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].TR_CTRL1)
#define TCPWM_CNT_TR_CTRL2(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].TR_CTRL2)

#if defined(CY_DEVICE_PSC3)
#define CY_SYSTEM_TCPWM_DISABLE_ADDR        (0x52a90800UL)
#endif

#if defined (CY_DEVICE_CYW20829)
#define TCPWM_GRP_CC1_PRESENT_STATUS (TCPWM_GRP_NR0_CNT_GRP_CC1_PRESENT | TCPWM_GRP_NR1_CNT_GRP_CC1_PRESENT << 1)
#define TCPWM_GRP_AMC_PRESENT_STATUS (TCPWM_GRP_NR0_CNT_GRP_AMC_PRESENT | TCPWM_GRP_NR1_CNT_GRP_AMC_PRESENT << 1)
#define TCPWM_GRP_SMC_PRESENT_STATUS (TCPWM_GRP_NR0_CNT_GRP_SMC_PRESENT | TCPWM_GRP_NR1_CNT_GRP_SMC_PRESENT << 1)
#else
#define TCPWM_GRP_CC1_PRESENT_STATUS (TCPWM_GRP_NR0_CNT_GRP_CC1_PRESENT | TCPWM_GRP_NR1_CNT_GRP_CC1_PRESENT << 1 | TCPWM_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)
#define TCPWM_GRP_AMC_PRESENT_STATUS (TCPWM_GRP_NR0_CNT_GRP_AMC_PRESENT | TCPWM_GRP_NR1_CNT_GRP_AMC_PRESENT << 1 | TCPWM_GRP_NR2_CNT_GRP_AMC_PRESENT << 2)
#define TCPWM_GRP_SMC_PRESENT_STATUS (TCPWM_GRP_NR0_CNT_GRP_SMC_PRESENT | TCPWM_GRP_NR1_CNT_GRP_SMC_PRESENT << 1 | TCPWM_GRP_NR2_CNT_GRP_SMC_PRESENT << 2)
#endif

#define TCPWM_GRP_CC1(base, grp) ((bool)((TCPWM_GRP_CC1_PRESENT_STATUS >> (grp)) & 0x01U))
#define TCPWM_GRP_AMC(base, grp) ((bool)((TCPWM_GRP_AMC_PRESENT_STATUS >> (grp)) & 0x01U))
#define TCPWM_GRP_SMC(base, grp) ((bool)((TCPWM_GRP_SMC_PRESENT_STATUS >> (grp)) & 0x01U))

#define TCPWM_GRP_CNT_GET_GRP(cntNum)        ((cntNum )/ 256U)

#define TCPWM_GRP_CNT_CTRL(base, grp, cntNum)           (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CTRL)
#define TCPWM_GRP_CNT_STATUS(base, grp, cntNum)         (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].STATUS)
#define TCPWM_GRP_CNT_COUNTER(base, grp, cntNum)        (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].COUNTER)
#define TCPWM_GRP_CNT_CC0(base, grp, cntNum)            (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC0)
#define TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC0_BUFF)
#define TCPWM_GRP_CNT_CC1(base, grp, cntNum)            (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC1)
#define TCPWM_GRP_CNT_CC1_BUFF(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC1_BUFF)
#define TCPWM_GRP_CNT_PERIOD(base, grp, cntNum)         (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PERIOD)
#define TCPWM_GRP_CNT_PERIOD_BUFF(base, grp, cntNum)    (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PERIOD_BUFF)
#define TCPWM_GRP_CNT_LINE_SEL(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LINE_SEL)
#define TCPWM_GRP_CNT_LINE_SEL_BUFF(base, grp, cntNum)  (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LINE_SEL_BUFF)
#define TCPWM_GRP_CNT_DT(base, grp, cntNum)             (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].DT)
#define TCPWM_GRP_CNT_TR_CMD(base, grp, cntNum)         (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_CMD)
#define TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_SEL0)
#define TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_SEL1)
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_EDGE_SEL)
#define TCPWM_GRP_CNT_TR_PWM_CTRL(base, grp, cntNum)    (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_PWM_CTRL)
#define TCPWM_GRP_CNT_TR_OUT_SEL(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_OUT_SEL)
#define TCPWM_GRP_CNT_INTR(base, grp, cntNum)           (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR)
#define TCPWM_GRP_CNT_INTR_SET(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_SET)
#define TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum)      (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_MASK)
#define TCPWM_GRP_CNT_INTR_MASKED(base, grp, cntNum)    (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_MASKED)

#if (CY_IP_MXTCPWM_VERSION >= 2U)
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC0_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC0_Msk
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC1_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC1_Msk
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_PERIOD_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_PERIOD_Msk
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_LINE_SEL_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_LINE_SEL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_LINE_SEL_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_LINE_SEL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_UP_EN_Pos TCPWM_GRP_CNT_CTRL_CC0_MATCH_UP_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_UP_EN_Msk TCPWM_GRP_CNT_CTRL_CC0_MATCH_UP_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_DOWN_EN_Pos TCPWM_GRP_CNT_CTRL_CC0_MATCH_DOWN_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_DOWN_EN_Msk TCPWM_GRP_CNT_CTRL_CC0_MATCH_DOWN_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_UP_EN_Pos TCPWM_GRP_CNT_CTRL_CC1_MATCH_UP_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_UP_EN_Msk TCPWM_GRP_CNT_CTRL_CC1_MATCH_UP_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_DOWN_EN_Pos TCPWM_GRP_CNT_CTRL_CC1_MATCH_DOWN_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_DOWN_EN_Msk TCPWM_GRP_CNT_CTRL_CC1_MATCH_DOWN_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_IMM_KILL_Pos  TCPWM_GRP_CNT_CTRL_PWM_IMM_KILL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_IMM_KILL_Msk  TCPWM_GRP_CNT_CTRL_PWM_IMM_KILL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_STOP_ON_KILL_Pos TCPWM_GRP_CNT_CTRL_PWM_STOP_ON_KILL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_STOP_ON_KILL_Msk TCPWM_GRP_CNT_CTRL_PWM_STOP_ON_KILL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_SYNC_KILL_Pos TCPWM_GRP_CNT_CTRL_PWM_SYNC_KILL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_SYNC_KILL_Msk TCPWM_GRP_CNT_CTRL_PWM_SYNC_KILL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_DISABLE_MODE_Pos TCPWM_GRP_CNT_CTRL_PWM_DISABLE_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_DISABLE_MODE_Msk TCPWM_GRP_CNT_CTRL_PWM_DISABLE_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_UP_DOWN_MODE_Pos  TCPWM_GRP_CNT_CTRL_UP_DOWN_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_UP_DOWN_MODE_Msk  TCPWM_GRP_CNT_CTRL_UP_DOWN_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_ONE_SHOT_Pos      TCPWM_GRP_CNT_CTRL_ONE_SHOT_Pos
#define TCPWM_GRP_CNT_V2_CTRL_ONE_SHOT_Msk      TCPWM_GRP_CNT_CTRL_ONE_SHOT_Msk
#define TCPWM_GRP_CNT_V2_CTRL_QUAD_ENCODING_MODE_Pos TCPWM_GRP_CNT_CTRL_QUAD_ENCODING_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_QUAD_ENCODING_MODE_Msk TCPWM_GRP_CNT_CTRL_QUAD_ENCODING_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_MODE_Pos          TCPWM_GRP_CNT_CTRL_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_MODE_Msk          TCPWM_GRP_CNT_CTRL_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_DBG_FREEZE_EN_Pos TCPWM_GRP_CNT_CTRL_DBG_FREEZE_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_DBG_FREEZE_EN_Msk TCPWM_GRP_CNT_CTRL_DBG_FREEZE_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_ENABLED_Pos       TCPWM_GRP_CNT_CTRL_ENABLED_Pos
#define TCPWM_GRP_CNT_V2_CTRL_ENABLED_Msk       TCPWM_GRP_CNT_CTRL_ENABLED_Msk
/* TCPWM_GRP_CNT.STATUS */
#define TCPWM_GRP_CNT_V2_STATUS_DOWN_Pos        TCPWM_GRP_CNT_STATUS_DOWN_Pos
#define TCPWM_GRP_CNT_V2_STATUS_DOWN_Msk        TCPWM_GRP_CNT_STATUS_DOWN_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE0_Pos TCPWM_GRP_CNT_STATUS_TR_CAPTURE0_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE0_Msk TCPWM_GRP_CNT_STATUS_TR_CAPTURE0_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_COUNT_Pos    TCPWM_GRP_CNT_STATUS_TR_COUNT_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_COUNT_Msk    TCPWM_GRP_CNT_STATUS_TR_COUNT_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_RELOAD_Pos   TCPWM_GRP_CNT_STATUS_TR_RELOAD_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_RELOAD_Msk   TCPWM_GRP_CNT_STATUS_TR_RELOAD_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_STOP_Pos     TCPWM_GRP_CNT_STATUS_TR_STOP_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_STOP_Msk     TCPWM_GRP_CNT_STATUS_TR_STOP_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_START_Pos    TCPWM_GRP_CNT_STATUS_TR_START_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_START_Msk    TCPWM_GRP_CNT_STATUS_TR_START_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE1_Pos TCPWM_GRP_CNT_STATUS_TR_CAPTURE1_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE1_Msk TCPWM_GRP_CNT_STATUS_TR_CAPTURE1_Msk
#define TCPWM_GRP_CNT_V2_STATUS_LINE_OUT_Pos    TCPWM_GRP_CNT_STATUS_LINE_OUT_Pos
#define TCPWM_GRP_CNT_V2_STATUS_LINE_OUT_Msk    TCPWM_GRP_CNT_STATUS_LINE_OUT_Msk
#define TCPWM_GRP_CNT_V2_STATUS_LINE_COMPL_OUT_Pos TCPWM_GRP_CNT_STATUS_LINE_COMPL_OUT_Pos
#define TCPWM_GRP_CNT_V2_STATUS_LINE_COMPL_OUT_Msk TCPWM_GRP_CNT_STATUS_LINE_COMPL_OUT_Msk
#define TCPWM_GRP_CNT_V2_STATUS_RUNNING_Pos     TCPWM_GRP_CNT_STATUS_RUNNING_Pos
#define TCPWM_GRP_CNT_V2_STATUS_RUNNING_Msk     TCPWM_GRP_CNT_STATUS_RUNNING_Msk
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_L_Pos    TCPWM_GRP_CNT_STATUS_DT_CNT_L_Pos
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_L_Msk    TCPWM_GRP_CNT_STATUS_DT_CNT_L_Msk
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_H_Pos    TCPWM_GRP_CNT_STATUS_DT_CNT_H_Pos
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_H_Msk    TCPWM_GRP_CNT_STATUS_DT_CNT_H_Msk
/* TCPWM_GRP_CNT.COUNTER */
#define TCPWM_GRP_CNT_V2_COUNTER_COUNTER_Pos    TCPWM_GRP_CNT_COUNTER_COUNTER_Pos
#define TCPWM_GRP_CNT_V2_COUNTER_COUNTER_Msk    TCPWM_GRP_CNT_COUNTER_COUNTER_Msk
/* TCPWM_GRP_CNT.CC0 */
#define TCPWM_GRP_CNT_V2_CC0_CC_Pos             TCPWM_GRP_CNT_CC0_CC_Pos
#define TCPWM_GRP_CNT_V2_CC0_CC_Msk             TCPWM_GRP_CNT_CC0_CC_Msk
/* TCPWM_GRP_CNT.CC0_BUFF */
#define TCPWM_GRP_CNT_V2_CC0_BUFF_CC_Pos        TCPWM_GRP_CNT_CC0_BUFF_CC_Pos
#define TCPWM_GRP_CNT_V2_CC0_BUFF_CC_Msk        TCPWM_GRP_CNT_CC0_BUFF_CC_Msk
/* TCPWM_GRP_CNT.CC1 */
#define TCPWM_GRP_CNT_V2_CC1_CC_Pos             TCPWM_GRP_CNT_CC1_CC_Pos
#define TCPWM_GRP_CNT_V2_CC1_CC_Msk             TCPWM_GRP_CNT_CC1_CC_Msk
/* TCPWM_GRP_CNT.CC1_BUFF */
#define TCPWM_GRP_CNT_V2_CC1_BUFF_CC_Pos        TCPWM_GRP_CNT_CC1_BUFF_CC_Pos
#define TCPWM_GRP_CNT_V2_CC1_BUFF_CC_Msk        TCPWM_GRP_CNT_CC1_BUFF_CC_Msk
/* TCPWM_GRP_CNT.PERIOD */
#define TCPWM_GRP_CNT_V2_PERIOD_PERIOD_Pos      TCPWM_GRP_CNT_PERIOD_PERIOD_Pos
#define TCPWM_GRP_CNT_V2_PERIOD_PERIOD_Msk      TCPWM_GRP_CNT_PERIOD_PERIOD_Msk
/* TCPWM_GRP_CNT.PERIOD_BUFF */
#define TCPWM_GRP_CNT_V2_PERIOD_BUFF_PERIOD_Pos TCPWM_GRP_CNT_PERIOD_BUFF_PERIOD_Pos
#define TCPWM_GRP_CNT_V2_PERIOD_BUFF_PERIOD_Msk TCPWM_GRP_CNT_PERIOD_BUFF_PERIOD_Msk
/* TCPWM_GRP_CNT.LINE_SEL */
#define TCPWM_GRP_CNT_V2_LINE_SEL_OUT_SEL_Pos   TCPWM_GRP_CNT_LINE_SEL_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_OUT_SEL_Msk   TCPWM_GRP_CNT_LINE_SEL_OUT_SEL_Msk
#define TCPWM_GRP_CNT_V2_LINE_SEL_COMPL_OUT_SEL_Pos TCPWM_GRP_CNT_LINE_SEL_COMPL_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_COMPL_OUT_SEL_Msk TCPWM_GRP_CNT_LINE_SEL_COMPL_OUT_SEL_Msk
/* TCPWM_GRP_CNT.LINE_SEL_BUFF */
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_OUT_SEL_Pos TCPWM_GRP_CNT_LINE_SEL_BUFF_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_OUT_SEL_Msk TCPWM_GRP_CNT_LINE_SEL_BUFF_OUT_SEL_Msk
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_COMPL_OUT_SEL_Pos TCPWM_GRP_CNT_LINE_SEL_BUFF_COMPL_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_COMPL_OUT_SEL_Msk TCPWM_GRP_CNT_LINE_SEL_BUFF_COMPL_OUT_SEL_Msk
/* TCPWM_GRP_CNT.DT */
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L_Pos   TCPWM_GRP_CNT_DT_DT_LINE_OUT_L_Pos
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L_Msk   TCPWM_GRP_CNT_DT_DT_LINE_OUT_L_Msk
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_H_Pos   TCPWM_GRP_CNT_DT_DT_LINE_OUT_H_Pos
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_H_Msk   TCPWM_GRP_CNT_DT_DT_LINE_OUT_H_Msk
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_COMPL_OUT_Pos TCPWM_GRP_CNT_DT_DT_LINE_COMPL_OUT_Pos
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_COMPL_OUT_Msk TCPWM_GRP_CNT_DT_DT_LINE_COMPL_OUT_Msk
/* TCPWM_GRP_CNT.TR_CMD */
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE0_Pos    TCPWM_GRP_CNT_TR_CMD_CAPTURE0_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE0_Msk    TCPWM_GRP_CNT_TR_CMD_CAPTURE0_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_RELOAD_Pos      TCPWM_GRP_CNT_TR_CMD_RELOAD_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_RELOAD_Msk      TCPWM_GRP_CNT_TR_CMD_RELOAD_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_STOP_Pos        TCPWM_GRP_CNT_TR_CMD_STOP_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_STOP_Msk        TCPWM_GRP_CNT_TR_CMD_STOP_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_START_Pos       TCPWM_GRP_CNT_TR_CMD_START_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_START_Msk       TCPWM_GRP_CNT_TR_CMD_START_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE1_Pos    TCPWM_GRP_CNT_TR_CMD_CAPTURE1_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE1_Msk    TCPWM_GRP_CNT_TR_CMD_CAPTURE1_Msk
/* TCPWM_GRP_CNT.TR_IN_SEL0 */
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_CAPTURE0_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_CAPTURE0_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_COUNT_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_COUNT_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_RELOAD_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_RELOAD_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_STOP_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_STOP_SEL_Msk
/* TCPWM_GRP_CNT.TR_IN_SEL1 */
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL1_START_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL1_START_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL1_CAPTURE1_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL1_CAPTURE1_SEL_Msk
/* TCPWM_GRP_CNT.TR_IN_EDGE_SEL */
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_COUNT_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_COUNT_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_RELOAD_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_STOP_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_STOP_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_START_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_START_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Msk
/* TCPWM_GRP_CNT.TR_PWM_CTRL */
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_CC0_MATCH_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_CC0_MATCH_MODE_Msk
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_OVERFLOW_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_OVERFLOW_MODE_Msk
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_UNDERFLOW_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_UNDERFLOW_MODE_Msk
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_CC1_MATCH_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_CC1_MATCH_MODE_Msk
/* TCPWM_GRP_CNT.TR_OUT_SEL */
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0_Pos    TCPWM_GRP_CNT_TR_OUT_SEL_OUT0_Pos
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0_Msk    TCPWM_GRP_CNT_TR_OUT_SEL_OUT0_Msk
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1_Pos    TCPWM_GRP_CNT_TR_OUT_SEL_OUT1_Pos
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1_Msk    TCPWM_GRP_CNT_TR_OUT_SEL_OUT1_Msk
/* TCPWM_GRP_CNT.INTR */
#define TCPWM_GRP_CNT_V2_INTR_TC_Pos            TCPWM_GRP_CNT_INTR_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_TC_Msk            TCPWM_GRP_CNT_INTR_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_CC0_MATCH_Pos     TCPWM_GRP_CNT_INTR_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_CC0_MATCH_Msk     TCPWM_GRP_CNT_INTR_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_CC1_MATCH_Pos     TCPWM_GRP_CNT_INTR_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_CC1_MATCH_Msk     TCPWM_GRP_CNT_INTR_CC1_MATCH_Msk
/* TCPWM_GRP_CNT.INTR_SET */
#define TCPWM_GRP_CNT_V2_INTR_SET_TC_Pos        TCPWM_GRP_CNT_INTR_SET_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_SET_TC_Msk        TCPWM_GRP_CNT_INTR_SET_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_SET_CC0_MATCH_Pos TCPWM_GRP_CNT_INTR_SET_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_SET_CC0_MATCH_Msk TCPWM_GRP_CNT_INTR_SET_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_SET_CC1_MATCH_Pos TCPWM_GRP_CNT_INTR_SET_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_SET_CC1_MATCH_Msk TCPWM_GRP_CNT_INTR_SET_CC1_MATCH_Msk
/* TCPWM_GRP_CNT.INTR_MASK */
#define TCPWM_GRP_CNT_V2_INTR_MASK_TC_Pos       TCPWM_GRP_CNT_INTR_MASK_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASK_TC_Msk       TCPWM_GRP_CNT_INTR_MASK_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC0_MATCH_Pos TCPWM_GRP_CNT_INTR_MASK_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC0_MATCH_Msk TCPWM_GRP_CNT_INTR_MASK_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC1_MATCH_Pos TCPWM_GRP_CNT_INTR_MASK_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC1_MATCH_Msk TCPWM_GRP_CNT_INTR_MASK_CC1_MATCH_Msk
/* TCPWM_GRP_CNT.INTR_MASKED */
#define TCPWM_GRP_CNT_V2_INTR_MASKED_TC_Pos     TCPWM_GRP_CNT_INTR_MASKED_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASKED_TC_Msk     TCPWM_GRP_CNT_INTR_MASKED_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC0_MATCH_Pos TCPWM_GRP_CNT_INTR_MASKED_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC0_MATCH_Msk TCPWM_GRP_CNT_INTR_MASKED_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC1_MATCH_Pos TCPWM_GRP_CNT_INTR_MASKED_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC1_MATCH_Msk TCPWM_GRP_CNT_INTR_MASKED_CC1_MATCH_Msk

/* For backward compatibility, we set TCPWM_CNT_STATUS_RUNNING_Pos with TCPWM_GRP_CNT_V2_STATUS_RUNNING
we need to define this for version 2 only. */
#define TCPWM_CNT_STATUS_RUNNING_Pos 31UL
#endif

#if (CY_IP_MXTCPWM_VERSION >= 3U)
#define TCPWM_GRP_CNT_V3_CTRL_SWAP_ENABLED_Pos   TCPWM_GRP_CNT_CTRL_SWAP_ENABLE_Pos
#define TCPWM_GRP_CNT_V3_CTRL_SWAP_ENABLED_Msk   TCPWM_GRP_CNT_CTRL_SWAP_ENABLE_Msk
#define TCPWM_GRP_CNT_V3_CTRL_DITHEREN_Pos       TCPWM_GRP_CNT_CTRL_DITHEREN_Pos
#define TCPWM_GRP_CNT_V3_CTRL_DITHEREN_Msk       TCPWM_GRP_CNT_CTRL_DITHEREN_Msk

#define TCPWM_GRP_CNT_V3_LFSR_PLFSR_Pos          TCPWM_GRP_CNT_LFSR_PLFSR_Pos
#define TCPWM_GRP_CNT_V3_LFSR_PLFSR_Msk          TCPWM_GRP_CNT_LFSR_PLFSR_Msk
#define TCPWM_GRP_CNT_V3_LFSR_DLFSR_Pos          TCPWM_GRP_CNT_LFSR_DLFSR_Pos
#define TCPWM_GRP_CNT_V3_LFSR_DLFSR_Msk          TCPWM_GRP_CNT_LFSR_DLFSR_Msk
#define TCPWM_GRP_CNT_V3_LFSR_LIMITER_Pos        TCPWM_GRP_CNT_LFSR_LIMITER_Pos
#define TCPWM_GRP_CNT_V3_LFSR_LIMITER_Msk        TCPWM_GRP_CNT_LFSR_LIMITER_Msk

#define TCPWM_GRP_CNT_V3_ONE_GF_GF_DEPTH_Pos     TCPWM_GRP_CNT_ONE_GF_GF_DEPTH_Pos
#define TCPWM_GRP_CNT_V3_ONE_GF_GF_DEPTH_Msk     TCPWM_GRP_CNT_ONE_GF_GF_DEPTH_Msk
#define TCPWM_GRP_CNT_V3_ONE_GF_GFPS_DIV_Pos     TCPWM_GRP_CNT_ONE_GF_GFPS_DIV_Pos
#define TCPWM_GRP_CNT_V3_ONE_GF_GFPS_DIV_Msk     TCPWM_GRP_CNT_ONE_GF_GFPS_DIV_Msk

#define GRP0_DITHERING TCPWM_GRP_NR0_CNT_GRP_DITHERING_PRESENT
#define GRP1_DITHERING TCPWM_GRP_NR1_CNT_GRP_DITHERING_PRESENT
#define GRP2_DITHERING TCPWM_GRP_NR2_CNT_GRP_DITHERING_PRESENT
#define TCPWM_GRP_DITHERING_PRESENT(grp) (((grp) == 0U)? GRP0_DITHERING : (((grp) == 1U)? GRP1_DITHERING : GRP2_DITHERING))

#define GRP0_HRPWM TCPWM_GRP_NR0_CNT_GRP_HRPWM_PRESENT
#define GRP1_HRPWM TCPWM_GRP_NR1_CNT_GRP_HRPWM_PRESENT
#define GRP2_HRPWM TCPWM_GRP_NR2_CNT_GRP_HRPWM_PRESENT
#define TCPWM_GRP_HRPWM_PRESENT(grp) (((grp) == 0U)? GRP0_HRPWM : (((grp) == 1U)? GRP1_HRPWM : GRP2_HRPWM))

#define GRP0_DATA_IN_CC_PRESENT TCPWM_GRP_NR0_CNT_GRP_DATA_IN_CC_PRESENT
#define GRP1_DATA_IN_CC_PRESENT TCPWM_GRP_NR1_CNT_GRP_DATA_IN_CC_PRESENT
#define GRP2_DATA_IN_CC_PRESENT TCPWM_GRP_NR2_CNT_GRP_DATA_IN_CC_PRESENT
#define TCPWM_DATA_IN_CC_PRESENT(grp) (((grp) == 0U)? GRP0_DATA_IN_CC_PRESENT : (((grp) == 1U)? GRP1_DATA_IN_CC_PRESENT : GRP2_DATA_IN_CC_PRESENT))

#define TCPWM_GRP_CNT_LFSR(base, grp, cntNum)        (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LFSR)
#define TCPWM_GRP_CNT_ONE_GF(base, grp, cntNum, onetoone_gf)      (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].ONE_GF[onetoone_gf])
#define TCPWM_GF_FOR_GROUP_TRIGGER(base, gfNum)      (((TCPWM_Type *)(base))->TR_ALL_GF.ALL_GF[((gfNum) % 254U)])
#define TCPWM_GRP_CNT_HRPWM_CTRL(base, grp, cntNum)  (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].HRPWM_CTRL)
#define TCPWM_GRP_CNT_DT_BUFF(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].DT_BUFF)
#define TCPWM_GRP_CNT_PS(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PS)
/* MOTIF */

#define TCPWM_MOTIF_PCONF(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PCONF)
#define TCPWM_MOTIF_PSUS(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PSUS)
#define TCPWM_MOTIF_PRUNS(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PRUNS)
#define TCPWM_MOTIF_PRUN(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PRUN)
#define TCPWM_MOTIF_MDR(base)                 (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MDR)
#define TCPWM_MOTIF_HIST(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->HIST)
#define TCPWM_MOTIF_HMEC(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->HMEC)
#define TCPWM_MOTIF_HALP(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->HALP)
#define TCPWM_MOTIF_HALPS(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->HALPS)
#define TCPWM_MOTIF_HOSC(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->HOSC)
#define TCPWM_MOTIF_MCM(base)                 (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCM)
#define TCPWM_MOTIF_MCSM(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCSM)
#define TCPWM_MOTIF_MCMS(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCMS)
#define TCPWM_MOTIF_MCMC(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCMC)
#define TCPWM_MOTIF_MCMF(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCMF)
#define TCPWM_MOTIF_MCPF(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCPF)
#define TCPWM_MOTIF_MOSC(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MOSC)
#define TCPWM_MOTIF_QDC(base)                 (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->QDC)
#define TCPWM_MOTIF_QOSC(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->QOSC)
#define TCPWM_MOTIF_MCMEC(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCMEC)
#define TCPWM_MOTIF_PFLG(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PFLG)
#define TCPWM_MOTIF_PFLGE(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PFLGE)
#define TCPWM_MOTIF_SPFLG(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->SPFLG)
#define TCPWM_MOTIF_RPFLG(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->RPFLG)
#define TCPWM_MOTIF_MCSM1(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCSM1)
#define TCPWM_MOTIF_MCSM2(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCSM2)
#define TCPWM_MOTIF_MCSM3(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCSM3)
#define TCPWM_MOTIF_MCSM4(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCSM4)
#define TCPWM_MOTIF_MCSM5(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->MCSM5)
#define TCPWM_MOTIF_CLUT(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->CLUT)
#define TCPWM_MOTIF_SLUT(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->SLUT)
#define TCPWM_MOTIF_PDBG(base)                (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PDBG)
#define TCPWM_MOTIF_PLP0S(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PLP0S)
#define TCPWM_MOTIF_PLP1S(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PLP1S)
#define TCPWM_MOTIF_PLP2S(base)               (((TCPWM_MOTIF_GRP_MOTIF_Type *)(base))->PLP2S)

#ifndef TCPWM_TR_ONE_CNT_NR
#define TCPWM_TR_ONE_CNT_NR TCPWM_CNT_TR_ONE_CNT_NR
#endif
#endif /* CY_IP_MXTCPWM_VERSION >= 3U */
/*******************************************************************************
*               TDM
*******************************************************************************/

#define TDM_STRUCT_Type                                TDM_TDM_STRUCT_Type
#define TDM_TX_STRUCT_Type                            TDM_TDM_STRUCT_TDM_TX_STRUCT_Type
#define TDM_RX_STRUCT_Type                            TDM_TDM_STRUCT_TDM_RX_STRUCT_Type
#define TDM_STRUCT0                                 TDM0_TDM_STRUCT0
#define TDM_STRUCT1                                 TDM0_TDM_STRUCT1
#define TDM_STRUCT0_TX                                TDM0_TDM_STRUCT0_TDM_TX_STRUCT
#define TDM_STRUCT1_TX                                TDM0_TDM_STRUCT1_TDM_TX_STRUCT
#define TDM_STRUCT0_RX                                TDM0_TDM_STRUCT0_TDM_RX_STRUCT
#define TDM_STRUCT1_RX                                TDM0_TDM_STRUCT1_TDM_RX_STRUCT
#define TDM_STRUCT_TX_CTL(base)                     (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_CTL)
#define TDM_STRUCT_TX_IF_CTL(base)                     (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_IF_CTL)
#define TDM_STRUCT_TX_CH_CTL(base)                     (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_CH_CTL)
#define TDM_STRUCT_TX_TEST_CTL(base)                 (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_TEST_CTL)
#define TDM_STRUCT_TX_ROUTE_CTL(base)                 (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_ROUTE_CTL)
#define TDM_STRUCT_TX_FIFO_CTL(base)                 (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_FIFO_CTL)
#define TDM_STRUCT_TX_FIFO_STATUS(base)             (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_FIFO_STATUS)
#define TDM_STRUCT_TX_FIFO_WR(base)                 (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->TX_FIFO_WR)
#define TDM_STRUCT_TX_INTR_TX(base)                 (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->INTR_TX)
#define TDM_STRUCT_TX_INTR_TX_SET(base)             (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->INTR_TX_SET)
#define TDM_STRUCT_TX_INTR_TX_MASK(base)             (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->INTR_TX_MASK)
#define TDM_STRUCT_TX_INTR_TX_MASKED(base)             (((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type *)(base))->INTR_TX_MASKED)

#define TDM_STRUCT_RX_CTL(base)                     (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_CTL)
#define TDM_STRUCT_RX_IF_CTL(base)                     (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_IF_CTL)
#define TDM_STRUCT_RX_CH_CTL(base)                     (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_CH_CTL)
#define TDM_STRUCT_RX_TEST_CTL(base)                 (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_TEST_CTL)
#define TDM_STRUCT_RX_ROUTE_CTL(base)                 (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_ROUTE_CTL)
#define TDM_STRUCT_RX_FIFO_CTL(base)                 (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_FIFO_CTL)
#define TDM_STRUCT_RX_FIFO_STATUS(base)             (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_FIFO_STATUS)
#define TDM_STRUCT_RX_FIFO_RD(base)                 (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_FIFO_RD)
#define TDM_STRUCT_RX_FIFO_RD_SILENT(base)             (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->RX_FIFO_RD_SILENT)
#define TDM_STRUCT_RX_INTR_RX(base)                 (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->INTR_RX)
#define TDM_STRUCT_RX_INTR_RX_SET(base)             (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->INTR_RX_SET)
#define TDM_STRUCT_RX_INTR_RX_MASK(base)             (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->INTR_RX_MASK)
#define TDM_STRUCT_RX_INTR_RX_MASKED(base)             (((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type *)(base))->INTR_RX_MASKED)


/*******************************************************************************
*                PDM
*******************************************************************************/

#define PDM_PCM_CTL(base)                               (((PDM_Type*)(base))->CTL)
#define PDM_PCM_CTL_CLR(base)                           (((PDM_Type*)(base))->CTL_CLR)
#define PDM_PCM_CTL_SET(base)                           (((PDM_Type*)(base))->CTL_SET)
#define PDM_PCM_CLOCK_CTL(base)                           (((PDM_Type*)(base))->CLOCK_CTL)
#define PDM_PCM_ROUTE_CTL(base)                           (((PDM_Type*)(base))->ROUTE_CTL)
#define PDM_PCM_TEST_CTL(base)                           (((PDM_Type*)(base))->TEST_CTL)
#define PDM_PCM_FIR0_COEFF0(base)                       (((PDM_Type*)(base))->FIR0_COEFF0)
#define PDM_PCM_FIR0_COEFF1(base)                       (((PDM_Type*)(base))->FIR0_COEFF1)
#define PDM_PCM_FIR0_COEFF2(base)                       (((PDM_Type*)(base))->FIR0_COEFF2)
#define PDM_PCM_FIR0_COEFF3(base)                       (((PDM_Type*)(base))->FIR0_COEFF3)
#define PDM_PCM_FIR0_COEFF4(base)                       (((PDM_Type*)(base))->FIR0_COEFF4)
#define PDM_PCM_FIR0_COEFF5(base)                       (((PDM_Type*)(base))->FIR0_COEFF5)
#define PDM_PCM_FIR0_COEFF6(base)                       (((PDM_Type*)(base))->FIR0_COEFF6)
#define PDM_PCM_FIR0_COEFF7(base)                       (((PDM_Type*)(base))->FIR0_COEFF7)

#define PDM_PCM_FIR1_COEFF0(base)                       (((PDM_Type*)(base))->FIR1_COEFF0)
#define PDM_PCM_FIR1_COEFF1(base)                       (((PDM_Type*)(base))->FIR1_COEFF1)
#define PDM_PCM_FIR1_COEFF2(base)                       (((PDM_Type*)(base))->FIR1_COEFF2)
#define PDM_PCM_FIR1_COEFF3(base)                       (((PDM_Type*)(base))->FIR1_COEFF3)
#define PDM_PCM_FIR1_COEFF4(base)                       (((PDM_Type*)(base))->FIR1_COEFF4)
#define PDM_PCM_FIR1_COEFF5(base)                       (((PDM_Type*)(base))->FIR1_COEFF5)
#define PDM_PCM_FIR1_COEFF6(base)                       (((PDM_Type*)(base))->FIR1_COEFF6)
#define PDM_PCM_FIR1_COEFF7(base)                       (((PDM_Type*)(base))->FIR1_COEFF7)
#define PDM_PCM_FIR1_COEFF8(base)                       (((PDM_Type*)(base))->FIR1_COEFF8)
#define PDM_PCM_FIR1_COEFF9(base)                       (((PDM_Type*)(base))->FIR1_COEFF9)
#define PDM_PCM_FIR1_COEFF10(base)                       (((PDM_Type*)(base))->FIR1_COEFF10)
#define PDM_PCM_FIR1_COEFF11(base)                       (((PDM_Type*)(base))->FIR1_COEFF11)
#define PDM_PCM_FIR1_COEFF12(base)                       (((PDM_Type*)(base))->FIR1_COEFF12)
#define PDM_PCM_FIR1_COEFF13(base)                       (((PDM_Type*)(base))->FIR1_COEFF13)


#define PDM_PCM_CH_CTL(base, chnum)                   (((PDM_Type*)(base))->CH[chnum].CTL)
#define PDM_PCM_CH_IF_CTL(base, chnum)                   (((PDM_Type*)(base))->CH[chnum].IF_CTL)
#define PDM_PCM_CH_CIC_CTL(base, chnum)               (((PDM_Type*)(base))->CH[chnum].CIC_CTL)
#define PDM_PCM_CH_FIR0_CTL(base, chnum)              (((PDM_Type*)(base))->CH[chnum].FIR0_CTL)
#define PDM_PCM_CH_FIR1_CTL(base, chnum)              (((PDM_Type*)(base))->CH[chnum].FIR1_CTL)
#define PDM_PCM_CH_DC_BLOCK_CTL(base, chnum)          (((PDM_Type*)(base))->CH[chnum].DC_BLOCK_CTL)
#define PDM_PCM_INTR_RX_MASK(base, chnum)             (((PDM_Type*)(base))->CH[chnum].INTR_RX_MASK)
#define PDM_PCM_INTR_RX_MASKED(base, chnum)           (((PDM_Type*)(base))->CH[chnum].INTR_RX_MASKED)
#define PDM_PCM_INTR_RX(base, chnum)                  (((PDM_Type*)(base))->CH[chnum].INTR_RX)
#define PDM_PCM_INTR_RX_SET(base, chnum)              (((PDM_Type*)(base))->CH[chnum].INTR_RX_SET)
#define PDM_PCM_RX_FIFO_STATUS(base, chnum)              (((PDM_Type*)(base))->CH[chnum].RX_FIFO_STATUS)
#define PDM_PCM_RX_FIFO_CTL(base, chnum)                 (((PDM_Type*)(base))->CH[chnum].RX_FIFO_CTL)
#define PDM_PCM_RX_FIFO_RD(base, chnum)                  (((PDM_Type*)(base))->CH[chnum].RX_FIFO_RD)
#define PDM_PCM_RX_FIFO_RD_SILENT(base, chnum)           (((PDM_Type*)(base))->CH[chnum].RX_FIFO_RD_SILENT)


/*******************************************************************************
*                BACKUP
*******************************************************************************/

#if defined (CY_IP_MXS28SRSS)
#define BACKUP_RTC_RW                       (((BACKUP_Type *) BACKUP)->RTC_RW)
#define BACKUP_CAL_CTL                      (((BACKUP_Type *) BACKUP)->CAL_CTL)
#define BACKUP_STATUS                       (((BACKUP_Type *) BACKUP)->STATUS)
#define BACKUP_RTC_TIME                     (((BACKUP_Type *) BACKUP)->RTC_TIME)
#define BACKUP_RTC_DATE                     (((BACKUP_Type *) BACKUP)->RTC_DATE)
#define BACKUP_ALM1_TIME                    (((BACKUP_Type *) BACKUP)->ALM1_TIME)
#define BACKUP_ALM1_DATE                    (((BACKUP_Type *) BACKUP)->ALM1_DATE)
#define BACKUP_ALM2_TIME                    (((BACKUP_Type *) BACKUP)->ALM2_TIME)
#define BACKUP_ALM2_DATE                    (((BACKUP_Type *) BACKUP)->ALM2_DATE)
#define BACKUP_INTR                         (((BACKUP_Type *) BACKUP)->INTR)
#define BACKUP_INTR_SET                     (((BACKUP_Type *) BACKUP)->INTR_SET)
#define BACKUP_INTR_MASK                    (((BACKUP_Type *) BACKUP)->INTR_MASK)
#define BACKUP_INTR_MASKED                  (((BACKUP_Type *) BACKUP)->INTR_MASKED)
#define BACKUP_RESET                        (((BACKUP_Type *) BACKUP)->RESET)
#define BACKUP_CTL                          (((BACKUP_Type *) BACKUP)->CTL)
#define BACKUP_WCO_CTL                      (((BACKUP_Type *) BACKUP)->WCO_CTL)
#define BACKUP_WCO_STATUS                   (((BACKUP_Type *) BACKUP)->WCO_STATUS)
#define BACKUP_LFWL_CTL                     (((BACKUP_Type *) BACKUP)->LFWL_CTL)
#define BACKUP_BREG                         (((BACKUP_Type *) BACKUP)->BREG)
#endif

#if defined (CY_IP_MXS40SSRSS)
#define BACKUP_CTL                          (((BACKUP_Type *) BACKUP)->CTL)
#define BACKUP_RTC_RW                       (((BACKUP_Type *) BACKUP)->RTC_RW)
#define BACKUP_CAL_CTL                      (((BACKUP_Type *) BACKUP)->CAL_CTL)
#define BACKUP_STATUS                       (((BACKUP_Type *) BACKUP)->STATUS)
#define BACKUP_RTC_TIME                     (((BACKUP_Type *) BACKUP)->RTC_TIME)
#define BACKUP_RTC_DATE                     (((BACKUP_Type *) BACKUP)->RTC_DATE)
#define BACKUP_ALM1_TIME                    (((BACKUP_Type *) BACKUP)->ALM1_TIME)
#define BACKUP_ALM1_DATE                    (((BACKUP_Type *) BACKUP)->ALM1_DATE)
#define BACKUP_ALM2_TIME                    (((BACKUP_Type *) BACKUP)->ALM2_TIME)
#define BACKUP_ALM2_DATE                    (((BACKUP_Type *) BACKUP)->ALM2_DATE)
#define BACKUP_INTR                         (((BACKUP_Type *) BACKUP)->INTR)
#define BACKUP_INTR_SET                     (((BACKUP_Type *) BACKUP)->INTR_SET)
#define BACKUP_INTR_MASK                    (((BACKUP_Type *) BACKUP)->INTR_MASK)
#define BACKUP_INTR_MASKED                  (((BACKUP_Type *) BACKUP)->INTR_MASKED)
#define BACKUP_PMIC_CTL                     (((BACKUP_Type *) BACKUP)->PMIC_CTL)
#define BACKUP_RESET                        (((BACKUP_Type *) BACKUP)->RESET)
#define BACKUP_LPECO_CTL                    (((BACKUP_Type *) BACKUP)->LPECO_CTL)
#define BACKUP_LPECO_PRESCALE               (((BACKUP_Type *) BACKUP)->LPECO_PRESCALE)
#define BACKUP_LPECO_STATUS                 (((BACKUP_Type *) BACKUP)->LPECO_STATUS)
#define BACKUP_WCO_STATUS                   (((BACKUP_Type *) BACKUP)->WCO_STATUS)
#define BACKUP_BREG_SET0                    (((BACKUP_Type *) BACKUP)->BREG_SET0)
#define BACKUP_BREG_SET1                    (((BACKUP_Type *) BACKUP)->BREG_SET1)
#define BACKUP_BREG_SET2                    (((BACKUP_Type *) BACKUP)->BREG_SET2)
#define BACKUP_BREG_SET3                    (((BACKUP_Type *) BACKUP)->BREG_SET3)


#define CY_SRSS_BACKUP_NUM_BREG             (SRSS_BACKUP_NUM_BREG0 + SRSS_BACKUP_NUM_BREG1 + SRSS_BACKUP_NUM_BREG2 + SRSS_BACKUP_NUM_BREG3)
#define CY_SRSS_BACKUP_BREG0_START_POS      (0UL)
#define CY_SRSS_BACKUP_BREG1_START_POS      (SRSS_BACKUP_NUM_BREG0)
#define CY_SRSS_BACKUP_BREG2_START_POS      (SRSS_BACKUP_NUM_BREG0 + SRSS_BACKUP_NUM_BREG1)
#define CY_SRSS_BACKUP_BREG3_START_POS      (SRSS_BACKUP_NUM_BREG0 + SRSS_BACKUP_NUM_BREG1 + SRSS_BACKUP_NUM_BREG2)

#endif


/*******************************************************************************
*                CANFD
*******************************************************************************/

#define CANFD_CTL(base)                           (((CANFD_Type *)(base))->CTL)
#define CANFD_STATUS(base)                        (((CANFD_Type *)(base))->STATUS)
#define CANFD_NBTP(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.NBTP)
#define CANFD_IR(base, chan)                      (((CANFD_Type *)(base))->CH[chan].M_TTCAN.IR)
#define CANFD_IE(base, chan)                      (((CANFD_Type *)(base))->CH[chan].M_TTCAN.IE)
#define CANFD_ILS(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.ILS)
#define CANFD_ILE(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.ILE)
#define CANFD_CCCR(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.CCCR)
#define CANFD_SIDFC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.SIDFC)
#define CANFD_XIDFC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.XIDFC)
#define CANFD_XIDAM(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.XIDAM)
#define CANFD_RXESC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXESC)
#define CANFD_RXF0C(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF0C)
#define CANFD_RXF1C(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF1C)
#define CANFD_RXFTOP_CTL(base, chan)              (((CANFD_Type *)(base))->CH[chan].RXFTOP_CTL)
#define CANFD_RXBC(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXBC)
#define CANFD_TXESC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXESC)
#define CANFD_TXEFC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXEFC)
#define CANFD_TXBC(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBC)
#define CANFD_DBTP(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.DBTP)
#define CANFD_TDCR(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TDCR)
#define CANFD_GFC(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.GFC)
#define CANFD_TXBRP(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBRP)
#define CANFD_TXBAR(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBAR)
#define CANFD_TXBCR(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBCR)
#define CANFD_TXBTO(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBTO)
#define CANFD_TXBCF(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBCF)
#define CANFD_TXBTIE(base, chan)                  (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBTIE)
#define CANFD_TXBCIE(base, chan)                  (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBCIE)
#define CANFD_NDAT1(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.NDAT1)
#define CANFD_NDAT2(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.NDAT2)
#define CANFD_RXF0S(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF0S)
#define CANFD_RXFTOP0_DATA(base, chan)            (((CANFD_Type *)(base))->CH[chan].RXFTOP0_DATA)
#define CANFD_RXFTOP1_DATA(base, chan)            (((CANFD_Type *)(base))->CH[chan].RXFTOP1_DATA)
#define CANFD_RXF0A(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF0A)
#define CANFD_RXF1S(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF1S)
#define CANFD_RXF1A(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF1A)
#define CANFD_PSR(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.PSR)
#define CANFD_TEST(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TEST)
#define CANFD_CREL(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.CREL)

#define CY_CANFD_CHANNELS_NUM                     (0x1UL)

/*******************************************************************************
*                MXOTPC
*******************************************************************************/
#define CY_MXOTPC_BASE                      (uint32_t)GET_ALIAS_ADDRESS(MXOTPC)

#define MXOTPC_CTL                          (((MXOTPC_Type *) CY_MXOTPC_BASE)->CTL)
#define MXOTPC_OTP_STATUS                   (((MXOTPC_Type *) CY_MXOTPC_BASE)->OTP_STATUS)
#define MXOTPC_OTP_CTL                      (((MXOTPC_Type *) CY_MXOTPC_BASE)->OTP_CTL)
#define MXOTPC_OTP_CMD                      (((MXOTPC_Type *) CY_MXOTPC_BASE)->OTP_CMD)
#define MXOTPC_LAYOUT                       (((MXOTPC_Type *) CY_MXOTPC_BASE)->LAYOUT)
#define MXOTPC_LAYOUT_EXT                   (((MXOTPC_Type *) CY_MXOTPC_BASE)->LAYOUT_EXT)
#define MXOTPC_OTP_PROGDATA                 (((MXOTPC_Type *) CY_MXOTPC_BASE)->OTP_PROGDATA)
#define MXOTPC_FOUT_ECC_STATUS              (((MXOTPC_Type *) CY_MXOTPC_BASE)->FOUT_ECC_STATUS)
#define MXOTPC_ECC_STATUS                   (((MXOTPC_Type *) CY_MXOTPC_BASE)->ECC_STATUS)
#define MXOTPC_CC312_ECC_STATUS             (((MXOTPC_Type *) CY_MXOTPC_BASE)->CC312_ECC_STATUS)
#define MXOTPC_CC312_ERROR_LOG              (((MXOTPC_Type *) CY_MXOTPC_BASE)->CC312_ERROR_LOG)
#define MXOTPC_CC312_CMD_SEL_LO             (((MXOTPC_Type *) CY_MXOTPC_BASE)->CC312_CMD_SEL_LO)
#define MXOTPC_CC312_CMD_SEL_HI             (((MXOTPC_Type *) CY_MXOTPC_BASE)->CC312_CMD_SEL_HI)
#define MXOTPC_LAYOUT_EXT1                  (((MXOTPC_Type *) CY_MXOTPC_BASE)->LAYOUT_EXT1)
#define MXOTPC_LAYOUT_EXT2                  (((MXOTPC_Type *) CY_MXOTPC_BASE)->LAYOUT_EXT2)
#define MXOTPC_LAYOUT_EXT3                  (((MXOTPC_Type *) CY_MXOTPC_BASE)->LAYOUT_EXT3)
#define MXOTPC_LAYOUT_EXT4                  (((MXOTPC_Type *) CY_MXOTPC_BASE)->LAYOUT_EXT4)
#define MXOTPC_CPU_PROG_CMD                 (((MXOTPC_Type *) CY_MXOTPC_BASE)->CPU_PROG_CMD)
#define MXOTPC_BOOTROW                      (((MXOTPC_Type *) CY_MXOTPC_BASE)->BOOTROW)
#define MXOTPC_CC312_RGN_LOCK_CTL           (((MXOTPC_Type *) CY_MXOTPC_BASE)->CC312_RGN_LOCK_CTL)
#define MXOTPC_ERR_RESP_CTL                 (((MXOTPC_Type *) CY_MXOTPC_BASE)->ERR_RESP_CTL)
#define MXOTPC_INTR_OTPC                    (((MXOTPC_Type *) CY_MXOTPC_BASE)->INTR_OTPC)
#define MXOTPC_INTR_OTPC_SET                (((MXOTPC_Type *) CY_MXOTPC_BASE)->INTR_OTPC_SET)
#define MXOTPC_INTR_OTPC_MASK               (((MXOTPC_Type *) CY_MXOTPC_BASE)->INTR_OTPC_MASK)
#define MXOTPC_INTR_OTPC_MASKED             (((MXOTPC_Type *) CY_MXOTPC_BASE)->INTR_OTPC_MASKED)
#define MXOTPC_CPU_ERROR_LOG                (((MXOTPC_Type *) CY_MXOTPC_BASE)->CPU_ERROR_LOG)

#define MXOTPC_BOOT_ROW_FOUT_ECC_DED_STATUS_Msk    0x00070000UL

/*******************************************************************************
*                MXSDIODEV
*******************************************************************************/

#define MXSDIO_CORECONTROL(base)         (((MXSDIO_Type *)(base))->CORECONTROL)
#define MXSDIO_CORESTATUS(base)              (((MXSDIO_Type *)(base))->CORESTATUS)
#define MXSDIO_BISTSTATUS(base)              (((MXSDIO_Type *)(base))->BISTSTATUS)
#define MXSDIO_INTSTATUS(base)               (((MXSDIO_Type *)(base))->INTSTATUS)
#define MXSDIO_INTHOSTMASK(base)             (((MXSDIO_Type *)(base))->INTHOSTMASK)
#define MXSDIO_INTSBMASK(base)               (((MXSDIO_Type *)(base))->INTSBMASK)
#define MXSDIO_SBINTSTATUS(base)             (((MXSDIO_Type *)(base))->SBINTSTATUS)
#define MXSDIO_SBINTMASK(base)               (((MXSDIO_Type *)(base))->SBINTMASK)
#define MXSDIO_SDIOFUNCINTMASK(base)         (((MXSDIO_Type *)(base))->SDIOFUNCINTMASK)
#define MXSDIO_TOSBMAILBOX(base)             (((MXSDIO_Type *)(base))->TOSBMAILBOX)
#define MXSDIO_TOHOSTMAILBOX(base)           (((MXSDIO_Type *)(base))->TOHOSTMAILBOX)
#define MXSDIO_TOSBMAILDATA(base)            (((MXSDIO_Type *)(base))->TOSBMAILDATA)
#define MXSDIO_TOHOSTMAILDATA(base)          (((MXSDIO_Type *)(base))->TOHOSTMAILDATA)
#define MXSDIO_SDIOACCESS(base)              (((MXSDIO_Type *)(base))->SDIOACCESS)
#define MXSDIO_UNUSEDINTFCTRL(base)          (((MXSDIO_Type *)(base))->UNUSEDINTFCTRL)
#define MXSDIO_INTRCVLAZY(base)              (((MXSDIO_Type *)(base))->INTRCVLAZY)
#define MXSDIO_CMD52RDCOUNT(base)            (((MXSDIO_Type *)(base))->CMD52RDCOUNT)
#define MXSDIO_CMD52WRCOUNT(base)            (((MXSDIO_Type *)(base))->CMD52WRCOUNT)
#define MXSDIO_CMD53RDCOUNT(base)            (((MXSDIO_Type *)(base))->CMD53RDCOUNT)
#define MXSDIO_CMD53WRCOUNT(base)            (((MXSDIO_Type *)(base))->CMD53WRCOUNT)
#define MXSDIO_ABORTCOUNT(base)              (((MXSDIO_Type *)(base))->ABORTCOUNT)
#define MXSDIO_CRCERRORCOUNT(base)           (((MXSDIO_Type *)(base))->CRCERRORCOUNT)
#define MXSDIO_RDOUTOFSYNCCOUNT(base)        (((MXSDIO_Type *)(base))->RDOUTOFSYNCCOUNT)
#define MXSDIO_WROUTOFSYNCCOUNT(base)        (((MXSDIO_Type *)(base))->WROUTOFSYNCCOUNT)
#define MXSDIO_WRITEBUSYCOUNT(base)          (((MXSDIO_Type *)(base))->WRITEBUSYCOUNT)
#define MXSDIO_READWAITCOUNT(base)         (((MXSDIO_Type *)(base))->READWAITCOUNT)
#define MXSDIO_RDTERMCOUNT(base)             (((MXSDIO_Type *)(base))->RDTERMCOUNT)
#define MXSDIO_WRTERMCOUNT(base)             (((MXSDIO_Type *)(base))->WRTERMCOUNT)
#define MXSDIO_CLOCKCTRLSTATUS(base)         (((MXSDIO_Type *)(base))->CLOCKCTRLSTATUS)
#define MXSDIO_WORKARND(base)                (((MXSDIO_Type *)(base))->WORKARND)
#define MXSDIO_PWRCTRL(base)                 (((MXSDIO_Type *)(base))->PWRCTRL)
#define MXSDIO_XMTCONTROL(base)              (((MXSDIO_Type *)(base))->XMTCONTROL)
#define MXSDIO_XMTPTR(base)                  (((MXSDIO_Type *)(base))->XMTPTR)
#define MXSDIO_XMTADDRESSLOW(base)           (((MXSDIO_Type *)(base))->XMTADDRESSLOW)
#define MXSDIO_XMTADDRESSHI(base)            (((MXSDIO_Type *)(base))->XMTADDRESSHI)
#define MXSDIO_XMTSTATUS0(base)              (((MXSDIO_Type *)(base))->XMTSTATUS0)
#define MXSDIO_XMTSTATUS1(base)              (((MXSDIO_Type *)(base))->XMTSTATUS1)
#define MXSDIO_RCVCONTROL(base)              (((MXSDIO_Type *)(base))->RCVCONTROL)
#define MXSDIO_RCVPTR(base)                  (((MXSDIO_Type *)(base))->RCVPTR)
#define MXSDIO_RCVADDRESSLOW(base)           (((MXSDIO_Type *)(base))->RCVADDRESSLOW)
#define MXSDIO_RCVADDRESSHI(base)            (((MXSDIO_Type *)(base))->RCVADDRESSHI)
#define MXSDIO_RCVSTATUS0(base)              (((MXSDIO_Type *)(base))->RCVSTATUS0)
#define MXSDIO_RCVSTATUS1(base)              (((MXSDIO_Type *)(base))->RCVSTATUS1)
#define MXSDIO_FIFOADDRESS(base)             (((MXSDIO_Type *)(base))->FIFOADDRESS)
#define MXSDIO_FIFODATAL(base)               (((MXSDIO_Type *)(base))->FIFODATAL)
#define MXSDIO_FIFODATAH(base)               (((MXSDIO_Type *)(base))->FIFODATAH)
#define MXSDIO_SDIOCLKRESETCTRLREG(base)     (((MXSDIO_Type *)(base))->SDIOCLKRESETCTRLREG)
#define MXSDIO_OTPSTATUSSHADOWREG(base)      (((MXSDIO_Type *)(base))->OTPSTATUSSHADOWREG)
#define MXSDIO_OTPLAYOUTSHADOWREG(base)      (((MXSDIO_Type *)(base))->OTPLAYOUTSHADOWREG)
#define MXSDIO_OTPSHADOWREG1(base)           (((MXSDIO_Type *)(base))->OTPSHADOWREG1)
#define MXSDIO_OTPSHADOWREG2(base)           (((MXSDIO_Type *)(base))->OTPSHADOWREG2)
#define MXSDIO_OTPSHADOWREG3(base)           (((MXSDIO_Type *)(base))->OTPSHADOWREG3)

/******************************************************************************
*                MXETH
*******************************************************************************/
#define ETH_CTL(base)                       (((ETH_Type*)(base))->CTL)
#define ETH_TX_Q_PTR(base)                  (((ETH_Type*)(base))->TRANSMIT_Q_PTR)
#define ETH_TX_Q1_PTR(base)                 (((ETH_Type*)(base))->TRANSMIT_Q1_PTR)
#define ETH_TX_Q2_PTR(base)                 (((ETH_Type*)(base))->TRANSMIT_Q2_PTR)
#define ETH_RX_Q_PTR(base)                  (((ETH_Type*)(base))->RECEIVE_Q_PTR)
#define ETH_RX_Q1_PTR(base)                 (((ETH_Type*)(base))->RECEIVE_Q1_PTR)
#define ETH_RX_Q2_PTR(base)                 (((ETH_Type*)(base))->RECEIVE_Q2_PTR)

/*******************************************************************************
*                PPU
*******************************************************************************/
#define CY_PPU_MAIN_BASE                             ((uint32_t)PWRMODE_PPU_MAIN)
#define CY_PPU_CPUSS_BASE                            ((uint32_t)CPUSS_PPU_BASE)
#define CY_PPU_SRAM_BASE                             ((uint32_t)RAMC_PPU0_BASE)

/*******************************************************************************
*                PDCM
*******************************************************************************/

#define CY_PDCM_PD_SENSE(pd_id)                        (((PWRMODE_PD_Type*) &PWRMODE->PD[pd_id])->PD_SENSE)
#define CY_PDCM_PD_SPT(pd_id)                          (((PWRMODE_PD_Type*) &PWRMODE->PD[pd_id])->PD_SPT)

/*******************************************************************************
*                IPC
*******************************************************************************/

#define REG_IPC_STRUCT_ACQUIRE(base)           (((IPC_STRUCT_Type*)(base))->ACQUIRE)
#define REG_IPC_STRUCT_RELEASE(base)           (((IPC_STRUCT_Type*)(base))->RELEASE)
#define REG_IPC_STRUCT_NOTIFY(base)            (((IPC_STRUCT_Type*)(base))->NOTIFY)
#define REG_IPC_STRUCT_DATA(base)              (((IPC_STRUCT_Type*)(base))->DATA0)
#define REG_IPC_STRUCT_DATA1(base)             (((IPC_STRUCT_Type*)(base))->DATA1)
#define REG_IPC_STRUCT_LOCK_STATUS(base)       (*(volatile uint32_t*)((uint32_t)(base) + offsetof(IPC_STRUCT_Type, LOCK_STATUS)))

#define REG_IPC_INTR_STRUCT_INTR(base)         (((IPC_INTR_STRUCT_Type*)(base))->INTR)
#define REG_IPC_INTR_STRUCT_INTR_SET(base)     (((IPC_INTR_STRUCT_Type*)(base))->INTR_SET)
#define REG_IPC_INTR_STRUCT_INTR_MASK(base)    (((IPC_INTR_STRUCT_Type*)(base))->INTR_MASK)
#define REG_IPC_INTR_STRUCT_INTR_MASKED(base)  (((IPC_INTR_STRUCT_Type*)(base))->INTR_MASKED)

#ifdef BTSS
#define CY_IPC_STRUCT_PTR(ipcIndex)            ((IPC_STRUCT_Type*)((void *)(((uint8_t*)&(BTSS_DATA_RAM_IPC->MXIPC_0_ACQUIRE)) + (sizeof(IPC_STRUCT_Type) * (ipcIndex)))))
#define CY_IPC_INTR_STRUCT_PTR(ipcIntrIndex)   ((IPC_INTR_STRUCT_Type *)((void*)(((uint8_t*)&(BTSS_DATA_RAM_IPC->MXIPC_INTR_0)) + (sizeof(IPC_INTR_STRUCT_Type) * (ipcIntrIndex)))))
#else
#define CY_IPC_STRUCT_PTR(ipcIndex)            ((IPC_STRUCT_Type*)(IPC_BASE + (sizeof(IPC_STRUCT_Type) * (ipcIndex))))
#define CY_IPC_INTR_STRUCT_PTR(ipcIntrIndex)   (&(((IPC_Type *)IPC_BASE)->INTR_STRUCT[ipcIntrIndex]))
#endif

#define CY_IPC_STRUCT_PTR_FOR_IP(ipcIndex, base)            ((IPC_STRUCT_Type*)((uint32_t)(base) + (sizeof(IPC_STRUCT_Type) * (ipcIndex))))
#define CY_IPC_INTR_STRUCT_PTR_FOR_IP(ipcIntrIndex, base)   (&(((IPC_Type *)base)->INTR_STRUCT[ipcIntrIndex]))

#define CY_IPC_INSTANCES                       (1U)
#define CY_IPC_CHANNELS                        ((uint32_t)CPUSS_IPC_NR)
#define CY_IPC_INTERRUPTS                      ((uint32_t)CPUSS_IPC_IRQ_NR)
#define CY_IPC_CHANNELS_PER_INSTANCE           CY_IPC_CHANNELS
#define CY_IPC_INTERRUPTS_PER_INSTANCE         CY_IPC_INTERRUPTS

/* ipcChannel comprises of total number of channels present in all IPC IP instances */
#define CY_IPC_PIPE_CHANNEL_NUMBER_WITHIN_INSTANCE(ipcChannel)  (((ipcChannel)%CY_IPC_CHANNELS_PER_INSTANCE))
#define CY_IPC_PIPE_INTR_NUMBER_WITHIN_INSTANCE(ipcIntr)        (((ipcIntr)%CY_IPC_INTERRUPTS_PER_INSTANCE))

#define CY_IPC_CH_MASK(chIndex)         (0x1u << chIndex)
#define CY_IPC_INTR_MASK(intrIndex)     (0x1u << intrIndex)
#define CY_IPC_INTR_MUX(intrIndex)      (cpuss_interrupts_ipc_dpslp_0_IRQn + intrIndex)
#define cpuss_interrupts_ipc_0_IRQn cpuss_interrupts_ipc_dpslp_0_IRQn
#define cpuss_interrupts_ipc_1_IRQn cpuss_interrupts_ipc_dpslp_1_IRQn

#if defined (CY_DEVICE_PSC3)
/* Reserve Channels are Interrupts for CM33-S and Cm33-NS */
#define CM33_S_IPC_CH_NUM                 (0x0u)
#define CM33_S_IPC_CH_MASK                (CY_IPC_CH_MASK(CM33_S_IPC_CH_NUM))
#define CM33_S_IPC_INTR_NUM               (0x0u)
#define CM33_S_IPC_INTR_MASK              (CY_IPC_INTR_MASK(CM33_S_IPC_INTR_NUM))
#define CM33_S_IPC_INTR_MUX               (CY_IPC_INTR_MUX(CM33_S_IPC_INTR_NUM))

/* user IPC channel */
#define CY_IPC_CHAN_USER                  (CM33_S_IPC_CH_NUM + 1u)
/* user IPC interrupt */
#define CY_IPC_INTR_USER                  (CM33_S_IPC_INTR_NUM + 1u)

#endif

/*******************************************************************************
*                LIN
*******************************************************************************/
#if defined (CY_IP_MXLIN)
#define LIN0_CH1                                ((LIN_CH_Type*) &LIN0->CH[1])
#define LIN0_CH2                                ((LIN_CH_Type*) &LIN0->CH[2])
#define LIN0_CH3                                ((LIN_CH_Type*) &LIN0->CH[3])
#define LIN0_CH4                                ((LIN_CH_Type*) &LIN0->CH[4])
#define LIN0_CH5                                ((LIN_CH_Type*) &LIN0->CH[5])
#define LIN0_CH6                                ((LIN_CH_Type*) &LIN0->CH[6])
#define LIN0_CH7                                ((LIN_CH_Type*) &LIN0->CH[7])
#define LIN0_CH8                                ((LIN_CH_Type*) &LIN0->CH[8])
#define LIN0_CH9                                ((LIN_CH_Type*) &LIN0->CH[9])
#define LIN0_CH10                               ((LIN_CH_Type*) &LIN0->CH[10])
#define LIN0_CH11                               ((LIN_CH_Type*) &LIN0->CH[11])
#define LIN0_CH12                               ((LIN_CH_Type*) &LIN0->CH[12])
#define LIN0_CH13                               ((LIN_CH_Type*) &LIN0->CH[13])
#define LIN0_CH14                               ((LIN_CH_Type*) &LIN0->CH[14])
#define LIN0_CH15                               ((LIN_CH_Type*) &LIN0->CH[15])
#define LIN0_CH16                               ((LIN_CH_Type*) &LIN0->CH[16])
#define LIN0_CH17                               ((LIN_CH_Type*) &LIN0->CH[17])
#define LIN0_CH18                               ((LIN_CH_Type*) &LIN0->CH[18])
#define LIN0_CH19                               ((LIN_CH_Type*) &LIN0->CH[19])
#define LIN0_CH20                               ((LIN_CH_Type*) &LIN0->CH[20])
#define LIN0_CH21                               ((LIN_CH_Type*) &LIN0->CH[21])
#define LIN0_CH22                               ((LIN_CH_Type*) &LIN0->CH[22])
#define LIN0_CH23                               ((LIN_CH_Type*) &LIN0->CH[23])
#define LIN0_CH24                               ((LIN_CH_Type*) &LIN0->CH[24])
#define LIN0_CH25                               ((LIN_CH_Type*) &LIN0->CH[25])
#define LIN0_CH26                               ((LIN_CH_Type*) &LIN0->CH[26])
#define LIN0_CH27                               ((LIN_CH_Type*) &LIN0->CH[27])
#define LIN0_CH28                               ((LIN_CH_Type*) &LIN0->CH[28])
#define LIN0_CH29                               ((LIN_CH_Type*) &LIN0->CH[29])
#define LIN0_CH30                               ((LIN_CH_Type*) &LIN0->CH[30])
#define LIN0_CH31                               ((LIN_CH_Type*) &LIN0->CH[31])

#define LIN_CH_CTL0(base)                       (((LIN_CH_Type *)(base))->CTL0)
#define LIN_CH_CTL1(base)                       (((LIN_CH_Type *)(base))->CTL1)
#define LIN_CH_STATUS(base)                     (((LIN_CH_Type *)(base))->STATUS)
#define LIN_CH_CMD(base)                        (((LIN_CH_Type *)(base))->CMD)
#define LIN_CH_TX_RX_STATUS(base)               (((LIN_CH_Type *)(base))->TX_RX_STATUS)
#define LIN_CH_PID_CHECKSUM(base)               (((LIN_CH_Type *)(base))->PID_CHECKSUM)
#define LIN_CH_DATA0(base)                      (((LIN_CH_Type *)(base))->DATA0)
#define LIN_CH_DATA1(base)                      (((LIN_CH_Type *)(base))->DATA1)
#define LIN_CH_INTR(base)                       (((LIN_CH_Type *)(base))->INTR)
#define LIN_CH_INTR_SET(base)                   (((LIN_CH_Type *)(base))->INTR_SET)
#define LIN_CH_INTR_MASK(base)                  (((LIN_CH_Type *)(base))->INTR_MASK)
#define LIN_CH_INTR_MASKED(base)                (((LIN_CH_Type *)(base))->INTR_MASKED)

#define LIN_ERROR_CTL(base)                     (((LIN_Type *)(base))->ERROR_CTL)
#define LIN_TEST_CTL(base)                      (((LIN_Type *)(base))->TEST_CTL)
#endif /* CY_IP_MXLIN */

/*******************************************************************************
*                MXKEYSCAN
*******************************************************************************/
#if defined (CY_IP_MXKEYSCAN)

#define KEYSCAN_CTL(base)                       (((MXKEYSCAN_Type *)(base))->KEYSCAN_CTL)
#define KEYSCAN_DEBOUNCE(base)                  (((MXKEYSCAN_Type *)(base))->DEBOUNCE)
#define KEYSCAN_KEYFIFO_CNT(base)               (((MXKEYSCAN_Type *)(base))->KEYFIFO_CNT)
#define KEYSCAN_KEYFIFO(base)                   (((MXKEYSCAN_Type *)(base))->KEYFIFO)
#define KEYSCAN_MIA_CTL(base)                   (((MXKEYSCAN_Type *)(base))->MIA_CTL)
#define KEYSCAN_MIA_STATUS(base)                (((MXKEYSCAN_Type *)(base))->MIA_STATUS)
#define KEYSCAN_KSI_USED(base)                  (((MXKEYSCAN_Type *)(base))->KSI_USED)
#define KEYSCAN_INTR(base)                      (((MXKEYSCAN_Type *)(base))->INTR)
#define KEYSCAN_INTR_SET(base)                  (((MXKEYSCAN_Type *)(base))->INTR_SET)
#define KEYSCAN_INTR_MASK(base)                 (((MXKEYSCAN_Type *)(base))->INTR_MASK)
#define KEYSCAN_INTR_MASKED(base)               (((MXKEYSCAN_Type *)(base))->INTR_MASKED)

#endif /* CY_IP_MXKEYSCAN */

#define MPC_Type                                 RAMC_MPC_Type
#ifdef CPUSS_PC_NR
#define MPC_PC_NR                                CPUSS_PC_NR
#else
#define MPC_PC_NR                                RAMC0_MPC_PC_NR
#endif

/*******************************************************************************
*                MS_CTL
*******************************************************************************/
#if defined (CY_IP_M33SYSCPUSS_VERSION) && (CY_IP_M33SYSCPUSS_VERSION > 1U)

#define MS_CTL_PC_CTL_VX(index)          (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->MS[(index)].CTL)
#define MS_CTL_PC_VAL_VX(index)          (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->MS_PC[(index)].PC)
#define MS_CTL_PC_READ_MIRROR_VX(index)  (((MS_CTL_2_1_Type*) GET_NSALIAS_ADDRESS(MS_CTL_2_1_BASE))->MS_PC[(index)].PC_READ_MIR)
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_VX   (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->CODE_MS0_MSC_ACG_CTL)
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_VX    (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->SYS_MS0_MSC_ACG_CTL)
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_VX    (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->SYS_MS1_MSC_ACG_CTL)
#define MS_CTL_EXP_MS_MSC_ACG_CTL_VX     (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->EXP_MS_MSC_ACG_CTL)
#define MS_CTL_DMAC0_MSC_ACG_CTL_VX      (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->DMAC0_MSC_ACG_CTL)
#define MS_CTL_DMAC1_MSC_ACG_CTL_VX      (((MS_CTL_2_1_Type*) MS_CTL_2_1_BASE)->DMAC1_MSC_ACG_CTL)

/* MS_CTL.CODE_MS0_MSC_ACG_CTL */
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos   MS_CTL_2_1_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk   MS_CTL_2_1_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_SEC_RESP_VX_Pos        MS_CTL_2_1_CODE_MS0_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_SEC_RESP_VX_Msk        MS_CTL_2_1_CODE_MS0_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.SYS_MS0_MSC_ACG_CTL */
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos    MS_CTL_2_1_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk    MS_CTL_2_1_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_SEC_RESP_VX_Pos         MS_CTL_2_1_SYS_MS0_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_SEC_RESP_VX_Msk         MS_CTL_2_1_SYS_MS0_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.SYS_MS1_MSC_ACG_CTL */
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos    MS_CTL_2_1_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk    MS_CTL_2_1_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_SEC_RESP_VX_Pos         MS_CTL_2_1_SYS_MS1_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_SEC_RESP_VX_Msk         MS_CTL_2_1_SYS_MS1_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.EXP_MS_MSC_ACG_CTL */
#define MS_CTL_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos     MS_CTL_2_1_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk     MS_CTL_2_1_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_EXP_MS_MSC_ACG_CTL_SEC_RESP_VX_Pos          MS_CTL_2_1_EXP_MS_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_EXP_MS_MSC_ACG_CTL_SEC_RESP_VX_Msk          MS_CTL_2_1_EXP_MS_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.DMAC0_MSC_ACG_CTL */
#define MS_CTL_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos      MS_CTL_2_1_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk      MS_CTL_2_1_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_DMAC0_MSC_ACG_CTL_SEC_RESP_VX_Pos           MS_CTL_2_1_DMAC0_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_DMAC0_MSC_ACG_CTL_SEC_RESP_VX_Msk           MS_CTL_2_1_DMAC0_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.DMAC1_MSC_ACG_CTL */
#define MS_CTL_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos      MS_CTL_2_1_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk      MS_CTL_2_1_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_DMAC1_MSC_ACG_CTL_SEC_RESP_VX_Pos           MS_CTL_2_1_DMAC1_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_DMAC1_MSC_ACG_CTL_SEC_RESP_VX_Msk           MS_CTL_2_1_DMAC1_MSC_ACG_CTL_SEC_RESP_Msk

#else

#define MS_CTL_PC_CTL_VX(index)          (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->MS[(index)].CTL)
#define MS_CTL_PC_VAL_VX(index)          (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->MS_PC[(index)].PC)
#define MS_CTL_PC_READ_MIRROR_VX(index)  (((MS_CTL_1_2_Type*) GET_NSALIAS_ADDRESS(MS_CTL_1_2_BASE))->MS_PC[(index)].PC_READ_MIR)
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_VX   (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->CODE_MS0_MSC_ACG_CTL)
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_VX    (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->SYS_MS0_MSC_ACG_CTL)
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_VX    (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->SYS_MS1_MSC_ACG_CTL)
#define MS_CTL_EXP_MS_MSC_ACG_CTL_VX     (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->EXP_MS_MSC_ACG_CTL)
#define MS_CTL_DMAC0_MSC_ACG_CTL_VX      (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->DMAC0_MSC_ACG_CTL)
#define MS_CTL_DMAC1_MSC_ACG_CTL_VX      (((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)->DMAC1_MSC_ACG_CTL)

/* MS_CTL.CODE_MS0_MSC_ACG_CTL */
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos   MS_CTL_1_2_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk   MS_CTL_1_2_CODE_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_SEC_RESP_VX_Pos        MS_CTL_1_2_CODE_MS0_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_CODE_MS0_MSC_ACG_CTL_SEC_RESP_VX_Msk        MS_CTL_1_2_CODE_MS0_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.SYS_MS0_MSC_ACG_CTL */
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos    MS_CTL_1_2_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk    MS_CTL_1_2_SYS_MS0_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_SEC_RESP_VX_Pos         MS_CTL_1_2_SYS_MS0_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_SYS_MS0_MSC_ACG_CTL_SEC_RESP_VX_Msk         MS_CTL_1_2_SYS_MS0_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.SYS_MS1_MSC_ACG_CTL */
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos    MS_CTL_1_2_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk    MS_CTL_1_2_SYS_MS1_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_SEC_RESP_VX_Pos         MS_CTL_1_2_SYS_MS1_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_SYS_MS1_MSC_ACG_CTL_SEC_RESP_VX_Msk         MS_CTL_1_2_SYS_MS1_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.EXP_MS_MSC_ACG_CTL */
#define MS_CTL_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos     MS_CTL_1_2_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk     MS_CTL_1_2_EXP_MS_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_EXP_MS_MSC_ACG_CTL_SEC_RESP_VX_Pos          MS_CTL_1_2_EXP_MS_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_EXP_MS_MSC_ACG_CTL_SEC_RESP_VX_Msk          MS_CTL_1_2_EXP_MS_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.DMAC0_MSC_ACG_CTL */
#define MS_CTL_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos      MS_CTL_1_2_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk      MS_CTL_1_2_DMAC0_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_DMAC0_MSC_ACG_CTL_SEC_RESP_VX_Pos           MS_CTL_1_2_DMAC0_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_DMAC0_MSC_ACG_CTL_SEC_RESP_VX_Msk           MS_CTL_1_2_DMAC0_MSC_ACG_CTL_SEC_RESP_Msk
/* MS_CTL.DMAC1_MSC_ACG_CTL */
#define MS_CTL_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Pos      MS_CTL_1_2_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_Pos
#define MS_CTL_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_VX_Msk      MS_CTL_1_2_DMAC1_MSC_ACG_CTL_CFG_GATE_RESP_Msk
#define MS_CTL_DMAC1_MSC_ACG_CTL_SEC_RESP_VX_Pos           MS_CTL_1_2_DMAC1_MSC_ACG_CTL_SEC_RESP_Pos
#define MS_CTL_DMAC1_MSC_ACG_CTL_SEC_RESP_VX_Msk           MS_CTL_1_2_DMAC1_MSC_ACG_CTL_SEC_RESP_Msk

#endif


/*******************************************************************************
*                MXSRAMC
*******************************************************************************/
#define MXSRAMC_STATUS                                 (((RAMC_Type *) RAMC0_BASE)->STATUS)
#define MXSRAMC_PWR_MACRO_CTL                          (((RAMC_Type *) RAMC0_BASE)->PWR_MACRO_CTL)
#define MXSRAMC_PWR_MACRO_CTL_LOCK                     (((RAMC_Type *) RAMC0_BASE)->PWR_MACRO_CTL_LOCK)


#define MXSRAMC_PWR_MACRO_CTL_LOCK_CLR0                0X00000001U
#define MXSRAMC_PWR_MACRO_CTL_LOCK_CLR1                0X00000002U
#define MXSRAMC_PWR_MACRO_CTL_LOCK_SET01               0X00000003U
#define CY_CPUSS_RAMC0_MACRO_NR                        CPUSS_RAMC0_MACRO_NR


/*******************************************************************************
*                FLASHC
*******************************************************************************/

#define FLASHC_FLASH_CTL                    (((FLASHC_Type *)(FLASHC))->FLASH_CTL)
#define FLASHC_FLASH_ECC_INJ_EN             (((FLASHC_Type *)(FLASHC))->ECC_INJ_EN)
#define FLASHC_FLASH_ECC_INJ_CTL            (((FLASHC_Type *)(FLASHC))->ECC_INJ_CTL)

#if defined (CY_DEVICE_PSC3)
#define SBUS_ALIAS_OFFSET                   (0x20000000UL)
#define FLASH_SBUS_ALIAS_ADDRESS(addr)      (uint32_t)(((uint32_t)(addr)) | SBUS_ALIAS_OFFSET)
#define IS_FLASH_ADDRESS_IN_SFLASH_SECNUM(addr)      ((((addr) >= CY_FLASH_BASE + 0x00020000UL) && ((addr) < CY_FLASH_BASE + CY_FLASH_SIZE))? true : false)
#endif  /* CY_DEVICE_PSC3 */

/*******************************************************************************
*                PPC
*******************************************************************************/
#if defined (CY_DEVICE_PSC3)
#define PPC_VALIDATE(ipInst, regionID)                  ((((ipInst) == PPC) && ((regionID) <= (uint32_t)PROT_MCPASS))? true : false)
#else
#define PPC_VALIDATE(ipInst, regionID)                  ((((ipInst) == PPC) && ((regionID) <= (uint32_t)PROT_BTSS_SECURE))? true : false)
#endif /* CY_DEVICE_PSC3 */

#if defined (CY_IP_MXSPERI_VERSION) && (CY_IP_MXSPERI_VERSION > 1U)
#define PPC_Type PPC_PPC_Type
#define PPC_CTL_RESP_CFG_Msk PPC_PPC_CTL_RESP_CFG_Msk
#endif


/*******************************************************************************
*            CORDIC
*******************************************************************************/
#if defined (CY_DEVICE_PSC3)
typedef MXCORDIC_1_0_Type MXCORDIC_Type;

#define MXCORDIC    MXCORDIC_1_0

/* MXCORDIC.CTL */
#define MXCORDIC_CTL_ENABLED_Pos                MXCORDIC_1_0_CTL_ENABLED_Pos
#define MXCORDIC_CTL_ENABLED_Msk                MXCORDIC_1_0_CTL_ENABLED_Msk
/* MXCORDIC.ID */
#define MXCORDIC_ID_MOD_REV_Pos                MXCORDIC_1_0_ID_MOD_REV_Pos
#define MXCORDIC_ID_MOD_REV_Msk                MXCORDIC_1_0_ID_MOD_REV_Msk
#define MXCORDIC_ID_MOD_TYPE_Pos               MXCORDIC_1_0_ID_MOD_TYPE_Pos
#define MXCORDIC_ID_MOD_TYPE_Msk               MXCORDIC_1_0_ID_MOD_TYPE_Msk
#define MXCORDIC_ID_MOD_NUMBER_Pos             MXCORDIC_1_0_ID_MOD_NUMBER_Pos
#define MXCORDIC_ID_MOD_NUMBER_Msk             MXCORDIC_1_0_ID_MOD_NUMBER_Msk
/* MXCORDIC.INTR */
#define MXCORDIC_INTR_CDEOC_Pos                MXCORDIC_1_0_INTR_CDEOC_Pos
#define MXCORDIC_INTR_CDEOC_Msk                MXCORDIC_1_0_INTR_CDEOC_Msk
#define MXCORDIC_INTR_CDERR_Pos                MXCORDIC_1_0_INTR_CDERR_Pos
#define MXCORDIC_INTR_CDERR_Msk                MXCORDIC_1_0_INTR_CDERR_Msk
/* MXCORDIC.INTR_SET */
#define MXCORDIC_INTR_SET_CDEOC_Pos            MXCORDIC_1_0_INTR_SET_CDEOC_Pos
#define MXCORDIC_INTR_SET_CDEOC_Msk            MXCORDIC_1_0_INTR_SET_CDEOC_Msk
#define MXCORDIC_INTR_SET_CDERR_Pos            MXCORDIC_1_0_INTR_SET_CDERR_Pos
#define MXCORDIC_INTR_SET_CDERR_Msk            MXCORDIC_1_0_INTR_SET_CDERR_Msk
/* MXCORDIC.INTR_MASK */
#define MXCORDIC_INTR_MASK_CDEOC_Pos           MXCORDIC_1_0_INTR_MASK_CDEOC_Pos
#define MXCORDIC_INTR_MASK_CDEOC_Msk           MXCORDIC_1_0_INTR_MASK_CDEOC_Msk
#define MXCORDIC_INTR_MASK_CDERR_Pos           MXCORDIC_1_0_INTR_MASK_CDERR_Pos
#define MXCORDIC_INTR_MASK_CDERR_Msk           MXCORDIC_1_0_INTR_MASK_CDERR_Msk
/* MXCORDIC.INTR_MASKED */
#define MXCORDIC_INTR_MASKED_CDEOC_Pos         MXCORDIC_1_0_INTR_MASKED_CDEOC_Pos
#define MXCORDIC_INTR_MASKED_CDEOC_Msk         MXCORDIC_1_0_INTR_MASKED_CDEOC_Msk
#define MXCORDIC_INTR_MASKED_CDERR_Pos         MXCORDIC_1_0_INTR_MASKED_CDERR_Pos
#define MXCORDIC_INTR_MASKED_CDERR_Msk         MXCORDIC_1_0_INTR_MASKED_CDERR_Msk
/* MXCORDIC.KEEP */
#define MXCORDIC_KEEP_KEEPX_Pos                MXCORDIC_1_0_KEEP_KEEPX_Pos
#define MXCORDIC_KEEP_KEEPX_Msk                MXCORDIC_1_0_KEEP_KEEPX_Msk
#define MXCORDIC_KEEP_KEEPY_Pos                MXCORDIC_1_0_KEEP_KEEPY_Pos
#define MXCORDIC_KEEP_KEEPY_Msk                MXCORDIC_1_0_KEEP_KEEPY_Msk
#define MXCORDIC_KEEP_KEEPZ_Pos                MXCORDIC_1_0_KEEP_KEEPZ_Pos
#define MXCORDIC_KEEP_KEEPZ_Msk                MXCORDIC_1_0_KEEP_KEEPZ_Msk
/* MXCORDIC.CON */
#define MXCORDIC_CON_MODE_Pos                  MXCORDIC_1_0_CON_MODE_Pos
#define MXCORDIC_CON_MODE_Msk                  MXCORDIC_1_0_CON_MODE_Msk
#define MXCORDIC_CON_ROTVEC_Pos                MXCORDIC_1_0_CON_ROTVEC_Pos
#define MXCORDIC_CON_ROTVEC_Msk                MXCORDIC_1_0_CON_ROTVEC_Msk
#define MXCORDIC_CON_ST_MODE_Pos               MXCORDIC_1_0_CON_ST_MODE_Pos
#define MXCORDIC_CON_ST_MODE_Msk               MXCORDIC_1_0_CON_ST_MODE_Msk
#define MXCORDIC_CON_X_USIGN_Pos               MXCORDIC_1_0_CON_X_USIGN_Pos
#define MXCORDIC_CON_X_USIGN_Msk               MXCORDIC_1_0_CON_X_USIGN_Msk
#define MXCORDIC_CON_MPS_Pos                   MXCORDIC_1_0_CON_MPS_Pos
#define MXCORDIC_CON_MPS_Msk                   MXCORDIC_1_0_CON_MPS_Msk
#define MXCORDIC_CON_N_ITER_Pos                MXCORDIC_1_0_CON_N_ITER_Pos
#define MXCORDIC_CON_N_ITER_Msk                MXCORDIC_1_0_CON_N_ITER_Msk
/* MXCORDIC.CORDX */
#define MXCORDIC_CORDX_DATA_Pos                MXCORDIC_1_0_CORDX_DATA_Pos
#define MXCORDIC_CORDX_DATA_Msk                MXCORDIC_1_0_CORDX_DATA_Msk
/* MXCORDIC.CORDY */
#define MXCORDIC_CORDY_DATA_Pos                MXCORDIC_1_0_CORDY_DATA_Pos
#define MXCORDIC_CORDY_DATA_Msk                MXCORDIC_1_0_CORDY_DATA_Msk
/* MXCORDIC.CORDZ */
#define MXCORDIC_CORDZ_DATA_Pos                MXCORDIC_1_0_CORDZ_DATA_Pos
#define MXCORDIC_CORDZ_DATA_Msk                MXCORDIC_1_0_CORDZ_DATA_Msk
/* MXCORDIC.CORRX */
#define MXCORDIC_CORRX_RESULT_Pos              MXCORDIC_1_0_CORRX_RESULT_Pos
#define MXCORDIC_CORRX_RESULT_Msk              MXCORDIC_1_0_CORRX_RESULT_Msk
/* MXCORDIC.CORRY */
#define MXCORDIC_CORRY_RESULT_Pos              MXCORDIC_1_0_CORRY_RESULT_Pos
#define MXCORDIC_CORRY_RESULT_Msk              MXCORDIC_1_0_CORRY_RESULT_Msk
/* MXCORDIC.CORRZ */
#define MXCORDIC_CORRZ_RESULT_Pos              MXCORDIC_1_0_CORRZ_RESULT_Pos
#define MXCORDIC_CORRZ_RESULT_Msk              MXCORDIC_1_0_CORRZ_RESULT_Msk
/* MXCORDIC.STAT */
#define MXCORDIC_STAT_BSY_Pos                  MXCORDIC_1_0_STAT_BSY_Pos
#define MXCORDIC_STAT_BSY_Msk                  MXCORDIC_1_0_STAT_BSY_Msk
/* MXCORDIC.START_CMD */
#define MXCORDIC_START_CMD_ST_Pos              MXCORDIC_1_0_START_CMD_ST_Pos
#define MXCORDIC_START_CMD_ST_Msk              MXCORDIC_1_0_START_CMD_ST_Msk

#define MXCORDIC_CTL(base)                           (((MXCORDIC_Type *)(base))->CTL)
#define MXCORDIC_INTR(base)                          (((MXCORDIC_Type *)(base))->INTR)
#define MXCORDIC_INTR_SET(base)                      (((MXCORDIC_Type *)(base))->INTR_SET)
#define MXCORDIC_INTR_MASK(base)                     (((MXCORDIC_Type *)(base))->INTR_MASK)
#define MXCORDIC_INTR_MASKED(base)                   (((MXCORDIC_Type *)(base))->INTR_MASKED)
#define MXCORDIC_KEEP(base)                          (((MXCORDIC_Type *)(base))->KEEP)
#define MXCORDIC_CON(base)                           (((MXCORDIC_Type *)(base))->CON)
#define MXCORDIC_CORDX(base)                         (((MXCORDIC_Type *)(base))->CORDX)
#define MXCORDIC_CORDY(base)                         (((MXCORDIC_Type *)(base))->CORDY)
#define MXCORDIC_CORDZ(base)                         (((MXCORDIC_Type *)(base))->CORDZ)
#define MXCORDIC_CORRX(base)                         (((MXCORDIC_Type *)(base))->CORRX)
#define MXCORDIC_CORRY(base)                         (((MXCORDIC_Type *)(base))->CORRY)
#define MXCORDIC_CORRZ(base)                         (((MXCORDIC_Type *)(base))->CORRZ)
#define MXCORDIC_STAT(base)                          (((MXCORDIC_Type *)(base))->STAT)
#define MXCORDIC_START_CMD(base)                     (((MXCORDIC_Type *)(base))->START_CMD)

#endif


/*******************************************************************************
*                HPPASS
*******************************************************************************/

#ifdef CY_IP_MXS40MCPASS
#define HPPASS_AC_CTRL(base)                         (((HPPASS_Type *)(base))->ACTRLR.CTRL)
#define HPPASS_AC_BLOCK_STATUS(base)                 (((HPPASS_Type *)(base))->ACTRLR.BLOCK_STATUS)
#define HPPASS_AC_STATUS(base)                       (((HPPASS_Type *)(base))->ACTRLR.STATUS)
#define HPPASS_AC_CMD_RUN(base)                      (((HPPASS_Type *)(base))->ACTRLR.CMD_RUN)
#define HPPASS_AC_CMD_STATE(base)                    (((HPPASS_Type *)(base))->ACTRLR.CMD_STATE)
#define HPPASS_AC_CFG(base)                          (((HPPASS_Type *)(base))->ACTRLR.CFG)
#define HPPASS_AC_CNTR_STATUS(base, cntIdx)          (((HPPASS_Type *)(base))->ACTRLR.CNTR_STATUS[cntIdx])
#define HPPASS_AC_TT_CFG0(base, rowIdx)              (((HPPASS_ACTRLR_TTCFG_Type *)(&((HPPASS_Type *)base)->ACTRLR.TTCFG[rowIdx]))->TT_CFG0)
#define HPPASS_AC_TT_CFG1(base, rowIdx)              (((HPPASS_ACTRLR_TTCFG_Type *)(&((HPPASS_Type *)base)->ACTRLR.TTCFG[rowIdx]))->TT_CFG1)
#define HPPASS_AC_TT_CFG2(base, rowIdx)              (((HPPASS_ACTRLR_TTCFG_Type *)(&((HPPASS_Type *)base)->ACTRLR.TTCFG[rowIdx]))->TT_CFG2)
#define HPPASS_AC_TT_CFG3(base, rowIdx)              (((HPPASS_ACTRLR_TTCFG_Type *)(&((HPPASS_Type *)base)->ACTRLR.TTCFG[rowIdx]))->TT_CFG3)
#define HPPASS_FIFO_INTR(base)                       (((HPPASS_Type *)(base))->MMIO.FIFO_INTR)
#define HPPASS_FIFO_INTR_SET(base)                   (((HPPASS_Type *)(base))->MMIO.FIFO_INTR_SET)
#define HPPASS_FIFO_INTR_MASK(base)                  (((HPPASS_Type *)(base))->MMIO.FIFO_INTR_MASK)
#define HPPASS_FIFO_INTR_MASKED(base)                (((HPPASS_Type *)(base))->MMIO.FIFO_INTR_MASKED)
#define HPPASS_MMIO_INTR(base)                       (((HPPASS_Type *)(base))->MMIO.HPPASS_INTR)
#define HPPASS_MMIO_INTR_SET(base)                   (((HPPASS_Type *)(base))->MMIO.HPPASS_INTR_SET)
#define HPPASS_MMIO_INTR_MASK(base)                  (((HPPASS_Type *)(base))->MMIO.HPPASS_INTR_MASK)
#define HPPASS_MMIO_TR_LEVEL_CFG(base)               (((HPPASS_Type *)(base))->MMIO.TR_LEVEL_CFG)
#define HPPASS_MMIO_TR_LEVEL_OUT(base, trigIdx)      (((HPPASS_Type *)(base))->MMIO.TR_LEVEL_OUT[trigIdx])
#define HPPASS_MMIO_TR_PULSE_OUT(base, trigIdx)      (((HPPASS_Type *)(base))->MMIO.TR_PULSE_OUT[trigIdx])
#define HPPASS_MMIO_INTR_MASKED(base)                (((HPPASS_Type *)(base))->MMIO.HPPASS_INTR_MASKED)
#define HPPASS_MMIO_FIFO_CFG(base)                   (((HPPASS_Type *)(base))->MMIO.FIFO.CFG)
#define HPPASS_MMIO_FIFO_LEVEL(base, fifoIdx)        (((HPPASS_Type *)(base))->MMIO.FIFO.LEVEL[fifoIdx])
#define HPPASS_MMIO_FIFO_USED(base, fifoIdx)         (((HPPASS_Type *)(base))->MMIO.FIFO.USED[fifoIdx])
#define HPPASS_MMIO_FIFO_RD_DATA(base, fifoIdx)      (((HPPASS_Type *)(base))->MMIO.FIFO.RD_DATA[fifoIdx])
#define HPPASS_SAR_CALOFFST(base, idx)               (((HPPASS_Type *)(base))->SARADC.CALOFFST[idx])
#define HPPASS_SAR_CALLIN(base, idx)                 (((HPPASS_Type *)(base))->SARADC.CALLIN[idx])
#define HPPASS_SAR_CALGAINC(base)                    (((HPPASS_Type *)(base))->SARADC.CALGAINC)
#define HPPASS_SAR_CALGAINF(base)                    (((HPPASS_Type *)(base))->SARADC.CALGAINF)
#define HPPASS_SAR_CTRL(base)                        (((HPPASS_Type *)(base))->SAR.CFG.CTRL)
#define HPPASS_SAR_RESULT_INTR(base)                 (((HPPASS_Type *)(base))->SAR.CFG.SAR_RESULT_INTR)
#define HPPASS_SAR_RESULT_INTR_SET(base)             (((HPPASS_Type *)(base))->SAR.CFG.SAR_RESULT_INTR_SET)
#define HPPASS_SAR_RESULT_INTR_MASK(base)            (((HPPASS_Type *)(base))->SAR.CFG.SAR_RESULT_INTR_MASK)
#define HPPASS_SAR_RESULT_INTR_MASKED(base)          (((HPPASS_Type *)(base))->SAR.CFG.SAR_RESULT_INTR_MASKED)
#define HPPASS_SAR_LIMIT_INTR(base)                  (((HPPASS_Type *)(base))->SAR.CFG.SAR_RANGE_INTR)
#define HPPASS_SAR_LIMIT_INTR_SET(base)              (((HPPASS_Type *)(base))->SAR.CFG.SAR_RANGE_INTR_SET)
#define HPPASS_SAR_LIMIT_INTR_MASK(base)             (((HPPASS_Type *)(base))->SAR.CFG.SAR_RANGE_INTR_MASK)
#define HPPASS_SAR_LIMIT_INTR_MASKED(base)           (((HPPASS_Type *)(base))->SAR.CFG.SAR_RANGE_INTR_MASKED)
#define HPPASS_SAR_GROUP_HOLD_VIOLATION(base)        (((HPPASS_Type *)(base))->SAR.CFG.ENTRY_HOLD_VIOLATION)
#define HPPASS_SAR_GROUP_HOLD_CNT(base)              (((HPPASS_Type *)(base))->SAR.CFG.ENTRY_HOLD_CNT)
#define HPPASS_SAR_LIMIT_STATUS(base)                (((HPPASS_Type *)(base))->SAR.CFG.RANGE_STATUS)
#define HPPASS_SAR_STATUS(base)                      (((HPPASS_Type *)(base))->SAR.CFG.SAR_STATUS)
#define HPPASS_SAR_RESULT_STATUS(base)               (((HPPASS_Type *)(base))->SAR.CFG.RESULT_UPDATED)
#define HPPASS_SAR_RESULT_OVERFLOW(base)             (((HPPASS_Type *)(base))->SAR.CFG.RESULT_OVERFLOW)
#define HPPASS_SAR_RESULT_MASK(base)                 (((HPPASS_Type *)(base))->SAR.CFG.RESULT_MASK)
#define HPPASS_SAR_CHAN_RESULT(base, chanIdx)        (((HPPASS_Type *)(base))->SAR.CFG.CHAN_RESULT[chanIdx])
#define HPPASS_SAR_CHAN_RESULT_PACKED(base, chanIdx) (((HPPASS_Type *)(base))->SAR.CFG.CHAN_RESULT_PACKED[chanIdx])
#define HPPASS_SAR_FIR_RESULT(base, firIdx)          (((HPPASS_Type *)(base))->SAR.CFG.FIR_RESULT[firIdx])
#define HPPASS_SAR_LIMIT_CFG(base, limIdx)           (((HPPASS_Type *)(base))->SAR.CFG.RANGE_CFG[limIdx])
#define HPPASS_SAR_LIMIT_LOW(base, limIdx)           (((HPPASS_Type *)(base))->SAR.CFG.RANGE_LOW[limIdx])
#define HPPASS_SAR_LIMIT_HIGH(base, limIdx)          (((HPPASS_Type *)(base))->SAR.CFG.RANGE_HIGH[limIdx])
#define HPPASS_SAR_AROUTE_STATUS(base)               (((HPPASS_Type *)(base))->SAR.CFG.AROUTE_STATUS)
#define HPPASS_SAR_AROUTE_CTRL_MODE(base)            (((HPPASS_Type *)(base))->SAR.CFG.AROUTE_CTRL_MODE)
#define HPPASS_SAR_AROUTE_FW_CTRL(base)              (((HPPASS_Type *)(base))->SAR.CFG.AROUTE_FW_CTRL)
#define HPPASS_SAR_AROUTE_FW_CTRL_CLR(base)          (((HPPASS_Type *)(base))->SAR.CFG.AROUTE_FW_CTRL_CLR)
#define HPPASS_SAR_TEMPSENSE_CTRL(base)              (((HPPASS_Type *)(base))->SAR.CFG.TEMPSENSE_CTRL)
#define HPPASS_SAR_SAMP_EN(base)                     (((HPPASS_Type *)(base))->SAR.CFG.SAMP_EN)
#define HPPASS_SAR_SAMP_GAIN(base)                   (((HPPASS_Type *)(base))->SAR.CFG.SAMP_GAIN)
#define HPPASS_SAR_SAMPLE_TIME(base, timIdx)         (((HPPASS_Type *)(base))->SAR.CFG.SAMPLE_TIME[timIdx])
#define HPPASS_SAR_CHAN_CFG(base, chanIdx)           (((HPPASS_Type *)(base))->SAR.CFG.CHAN_CFG[chanIdx])
#define HPPASS_SAR_CHAN_COEFF(base, coefIdx)         (((HPPASS_Type *)(base))->SAR.CFG.CHAN_COEFF[coefIdx])
#define HPPASS_SAR_FIR_CFG(base, firIdx)             (((HPPASS_Type *)(base))->SAR.CFG.FIR_CFG[firIdx])
#define HPPASS_SAR_SEQ_GROUP(base, grpIdx)           (((HPPASS_Type *)(base))->SAR.SEQ_ENTRY[grpIdx])
#define HPPASS_SAR_FIR_COEFS(base, firIdx, coefIdx)  (((HPPASS_Type *)(base))->SAR.FIR[firIdx].FIR_COEFS[coefIdx])
#define HPPASS_CSG_SLICE_CMP_CFG(base, slcIdx)       (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].CMP_CFG)
#define HPPASS_CSG_SLICE_DAC_CFG(base, slcIdx)       (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_CFG)
#define HPPASS_CSG_SLICE_DAC_PARAM_SYNC(base, slcIdx)   (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_PARAM_SYNC)
#define HPPASS_CSG_SLICE_DAC_MODE_START(base, slcIdx)   (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_MODE_START)
#define HPPASS_CSG_SLICE_DAC_VAL_A(base, slcIdx)     (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_VAL_A)
#define HPPASS_CSG_SLICE_DAC_VAL_B(base, slcIdx)     (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_VAL_B)
#define HPPASS_CSG_SLICE_DAC_PERIOD(base, slcIdx)    (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_PERIOD)
#define HPPASS_CSG_SLICE_DAC_VAL(base, slcIdx)       (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_VAL)
#define HPPASS_CSG_SLICE_DAC_STATUS(base, slcIdx)    (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].DAC_STATUS)
#define HPPASS_CSG_SLICE_CMP_STATUS(base, slcIdx)    (((HPPASS_Type *)(base))->CSG.SLICE[slcIdx].CMP_STATUS)
#define HPPASS_CSG_LUT_CFG(base, lutIdx, dataIdx)    (((HPPASS_Type *)(base))->CSG.LUT_CFG[lutIdx].LUT_DATA[dataIdx])
#define HPPASS_CSG_CTRL(base)                        (((HPPASS_Type *)(base))->CSG.CSG_CTRL)
#define HPPASS_CSG_DAC_INTR(base)                    (((HPPASS_Type *)(base))->CSG.DAC_INTR)
#define HPPASS_CSG_DAC_INTR_SET(base)                (((HPPASS_Type *)(base))->CSG.DAC_INTR_SET)
#define HPPASS_CSG_DAC_INTR_MASK(base)               (((HPPASS_Type *)(base))->CSG.DAC_INTR_MASK)
#define HPPASS_CSG_DAC_INTR_MASKED(base)             (((HPPASS_Type *)(base))->CSG.DAC_INTR_MASKED)
#define HPPASS_CSG_CMP_INTR(base)                    (((HPPASS_Type *)(base))->CSG.CMP_INTR)
#define HPPASS_CSG_CMP_INTR_SET(base)                (((HPPASS_Type *)(base))->CSG.CMP_INTR_SET)
#define HPPASS_CSG_CMP_INTR_MASK(base)               (((HPPASS_Type *)(base))->CSG.CMP_INTR_MASK)
#define HPPASS_CSG_CMP_INTR_MASKED(base)             (((HPPASS_Type *)(base))->CSG.CMP_INTR_MASKED)

#define HPPASS_SAR_GROUP_TR_COLLISION(base)          (((HPPASS_Type *)(base))->SAR.CFG.ENTRY_TR_COLLISION)
#define HPPASS_INFRA_TR_IN_SEL(base)                 (((HPPASS_Type *)(base))->INFRA.TR_IN_SEL)
#define HPPASS_INFRA_HW_TR_MODE(base)                (((HPPASS_Type *)(base))->INFRA.HW_TR_MODE)
#define HPPASS_INFRA_FW_TR_PULSE(base)               (((HPPASS_Type *)(base))->INFRA.FW_TR_PULSE)
#define HPPASS_INFRA_FW_TR_LEVEL(base)               (((HPPASS_Type *)(base))->INFRA.FW_TR_LEVEL)
#define HPPASS_INFRA_CLOCK_STARTUP_DIV(base)         (((HPPASS_Type *)(base))->INFRA.CLOCK_STARTUP_DIV)
#define HPPASS_INFRA_STARTUP_CFG(base, cfg)          (((HPPASS_Type *)(base))->INFRA.STARTUP_CFG[cfg])
#define HPPASS_INFRA_AREF_CTRL(base)                 (((HPPASS_Type *)(base))->INFRA.AREFV2.AREF_CTRL)
#define HPPASS_INFRA_VDDA_STATUS(base)               (((HPPASS_Type *)(base))->INFRA.VDDA_STATUS)

#define CY_HPPASS_FIFO_RD_DATA_RESULT_Pos    (0UL)
#define CY_HPPASS_FIFO_RD_DATA_RESULT_Msk    (0xFFFFUL)

#define CY_HPPASS_FIFO_RD_DATA_CHAN_ID_Pos   (16UL)
#define CY_HPPASS_FIFO_RD_DATA_CHAN_ID_Msk   (0x1F0000UL)
#endif

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.6')

#endif /* CY_DEVICE_H_ */

/* [] END OF FILE */

