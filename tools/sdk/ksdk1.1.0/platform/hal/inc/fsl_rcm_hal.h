/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_RCM_HAL_H__)
#define __FSL_RCM_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

/*! @addtogroup rcm_hal*/
/*! @{*/

/*! @file fsl_rcm_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief System Reset Source Name definitions */
typedef enum _rcm_source_names {
    kRcmWakeup,                     /* low-leakage wakeup reset */
    kRcmLowVoltDetect,              /* low voltage detect reset */
#if FSL_FEATURE_RCM_HAS_LOC
    kRcmLossOfClk,                  /* loss of clock reset */
#endif
#if FSL_FEATURE_RCM_HAS_LOL
    kRcmLossOfLock,                 /* loss of lock reset */
#endif
    kRcmWatchDog,                   /* watch dog reset */
    kRcmExternalPin,                /* external pin reset */
    kRcmPowerOn,                    /* power on reset */
#if FSL_FEATURE_RCM_HAS_JTAG
    kRcmJtag,                       /* JTAG generated reset */
#endif
    kRcmCoreLockup,                 /* core lockup reset */
    kRcmSoftware,                   /* software reset */
    kRcmMdmAp,                      /* MDM-AP system reset. */
#if FSL_FEATURE_RCM_HAS_EZPORT
    kRcmEzport,                     /* EzPort reset */
#endif
    kRcmStopModeAckErr,             /* stop mode ack error reset */
    kRcmSrcNameMax
} rcm_source_names_t;

/*! @brief Reset pin filter select in Run and Wait modes */
typedef enum _rcm_filter_run_wait_modes {
    kRcmFilterDisabled,          /* all filtering disabled */
    kRcmFilterBusClk,            /* Bus clock filter enabled */
    kRcmFilterLpoClk,            /* LPO clock filter enabled */
    kRcmFilterReserverd          /* reserved setting */
} rcm_filter_run_wait_modes_t;

#if FSL_FEATURE_RCM_HAS_BOOTROM
/*! @brief Boot from ROM configuration. */
typedef enum _rcm_boot_rom_config {
    kRcmBootFlash,       /* boot from flash */
    kRcmBootRomCfg0,     /* boot from boot rom due to BOOTCFG0 */
    kRcmBootRomFopt,     /* boot from boot rom due to FOPT[7] */
    kRcmBootRomBoth      /* boot from boot rom due to both BOOTCFG0 and FOPT[7] */
} rcm_boot_rom_config_t;
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Reset Control Module APIs*/
/*@{*/

/*!
 * @brief Gets the reset source status.
 *
 * This function gets the current reset source status for a specified source.
 *
 * @param baseAddr     Register base address of RCM
 * @param srcName      reset source name
 * @return status      true or false for specified reset source
 */
bool RCM_HAL_GetSrcStatusCmd(uint32_t baseAddr, rcm_source_names_t srcName);

#if FSL_FEATURE_RCM_HAS_SSRS
/*!
 * @brief Gets the sticky reset source status.
 *
 * This function gets the current reset source status that have not been cleared
 * by software for a specified source.
 *
 * @param baseAddr     Register base address of RCM
 * @param srcName      reset source name
 * @return status      true or false for specified reset source
 */
bool RCM_HAL_GetStickySrcStatusCmd(uint32_t baseAddr, rcm_source_names_t srcName);

/*!
 * @brief Clear the sticky reset source status.
 *
 * This function clears all the sticky system reset flags.
 *
 * @param baseAddr     Register base address of RCM
 */
void RCM_HAL_ClearStickySrcStatus(uint32_t baseAddr);
#endif

/*!
 * @brief Sets the reset pin filter in stop mode.
 *
 * This function  sets the reset pin filter enable setting in stop mode.
 *
 * @param baseAddr     Register base address of RCM
 * @param enable      enable or disable the filter in stop mode
 */
static inline void RCM_HAL_SetFilterStopModeCmd(uint32_t baseAddr, bool enable)
{
    BW_RCM_RPFC_RSTFLTSS(baseAddr, enable);
}

/*!
 * @brief Gets the reset pin filter in stop mode.
 *
 * This function gets the reset pin filter enable setting in stop mode.
 *
 * @param baseAddr     Register base address of RCM
 * @return enable      true/false to enable or disable the filter in stop mode
 */
static inline bool RCM_HAL_GetFilterStopModeCmd(uint32_t baseAddr)
{
    return (bool)BR_RCM_RPFC_RSTFLTSS(baseAddr);
}

/*!
 * @brief Sets the reset pin filter in run and wait mode.
 *
 * This function sets the reset pin filter enable setting in run/wait mode.
 *
 * @param baseAddr     Register base address of RCM
 * @param mode  to be set for reset filter in run/wait mode
 */
static inline void RCM_HAL_SetFilterRunWaitMode(uint32_t baseAddr, rcm_filter_run_wait_modes_t mode)
{
    BW_RCM_RPFC_RSTFLTSRW(baseAddr, mode);
}

/*!
 * @brief Gets the reset pin filter for stop mode.
 *
 * This function gets the reset pin filter enable setting for stop mode.
 *
 * @param baseAddr     Register base address of RCM
 * @return mode  for reset filter in run/wait mode
 */
static inline rcm_filter_run_wait_modes_t RCM_HAL_GetFilterRunWaitMode(uint32_t baseAddr)
{
    return (rcm_filter_run_wait_modes_t)BR_RCM_RPFC_RSTFLTSRW(baseAddr);
}

/*!
 * @brief Sets the reset pin filter width.
 *
 * This function sets the reset pin filter width.
 *
 * @param baseAddr     Register base address of RCM
 * @param width  to be set for reset filter width
 */
static inline void RCM_HAL_SetFilterWidth(uint32_t baseAddr, uint32_t width)
{
    BW_RCM_RPFW_RSTFLTSEL(baseAddr, width);
}

/*!
 * @brief Gets the reset pin filter for stop mode.
 *
 * This function gets the reset pin filter width.
 *
 * @param baseAddr     Register base address of RCM
 * @return width reset filter width
 */
static inline uint32_t RCM_HAL_GetFilterWidth(uint32_t baseAddr)
{
    return (uint32_t)BR_RCM_RPFW_RSTFLTSEL(baseAddr);
}

#if FSL_FEATURE_RCM_HAS_EZPMS
/*!
 * @brief Gets the EZP_MS_B pin assert status.
 *
 * This function gets the easy port mode status (EZP_MS_B) pin assert status.
 *
 * @param baseAddr     Register base address of RCM
 * @return status  true - asserted, false - reasserted
 */
static inline bool RCM_HAL_GetEasyPortModeStatusCmd(uint32_t baseAddr)
{
    return (bool)BR_RCM_MR_EZP_MS(baseAddr);
}
#endif

#if FSL_FEATURE_RCM_HAS_BOOTROM
/*!
 * @brief Force the boot from ROM.
 *
 * This function forces boot from ROM during all subsequent system resets.
 *
 * @param baseAddr     Register base address of RCM
 * @param config       Boot configuration.
 */
static inline void RCM_HAL_SetForceBootRomSrc(uint32_t baseAddr,
                                              rcm_boot_rom_config_t config)
{
    BW_RCM_FM_FORCEROM(baseAddr, config);
}

/*!
 * @brief Get the force ROM boot setting.
 *
 * This function gets the force ROM boot setting.
 *
 * @param baseAddr     Register base address of RCM
 * @return The force ROM boot source.
 */
static inline rcm_boot_rom_config_t RCM_HAL_GetForceBootRomSrc(uint32_t baseAddr)
{
    return (rcm_boot_rom_config_t)BR_RCM_FM_FORCEROM(baseAddr);
}

/*!
 * @brief Get the ROM boot source.
 *
 * This function gets the ROM boot source during the last chip reset.
 *
 * @param baseAddr     Register base address of RCM
 * @return The ROM boot source.
 */
static inline rcm_boot_rom_config_t RCM_HAL_GetBootRomSrc(uint32_t baseAddr)
{
    return (rcm_boot_rom_config_t)BR_RCM_MR_BOOTROM(baseAddr);
}

/*!
 * @brief Clear the ROM boot source flag.
 *
 * This function clears the ROM boot source flag.
 *
 * @param baseAddr     Register base address of RCM
 */
static inline void RCM_HAL_ClearBootRomSrc(uint32_t baseAddr)
{
    BW_RCM_MR_BOOTROM(baseAddr, kRcmBootRomBoth);
}
#endif

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_RCM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

