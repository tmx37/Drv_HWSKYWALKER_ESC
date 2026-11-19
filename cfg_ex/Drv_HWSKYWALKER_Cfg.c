/*
 * Drv_HWSKYWALKER_Cfg.c
 *
 *  Created on: Mar 19, 2025
 *      Author: tmx37
 */

#include "Drv_HWSKYWALKER_Cfg.h"
#include "Drv_HWSKYWALKER.h"

static Drv_HWSKYWALKER_Config_t mConfigData;

GenUtl_Err_t MockUartTrasmit(const uint8_t* pData, uint16_t Size, uint32_t Timeout);
GenUtl_Err_t MockSetPwm(uint32_t Value);
void MockDelay(uint32_t Delay);


GenUtl_Err_t Drv_HWSKYWALKER_Cfg_Init()
{
    GenUtl_Err_t ErrCode;
    mConfigData.pfUartTrasmitCB = MockUartTrasmit;
    mConfigData.pfSetPwmCB = MockSetPwm;
    mConfigData.pfDelayCB = MockDelay;
    ErrCode = Drv_HWSKYWALKER_Init(&mConfigData);
    return ErrCode;
}

/**
 * Add here mock functions
 */
GenUtl_Err_t MockUartTrasmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    /** NB: Attach here correct UART call to device interface */
    /** 
     *  NB: This should be changed with a dedicated communication module call for uart interfaces.
     *  UART could be used by multiple modules or communications and should be handled only by one module.
     */
    return OUT_OK;
}

GenUtl_Err_t MockSetPwm(uint32_t Value)
{
    /** NB: Attach to correct timer instance (eg: TIM1->CCR1) */
    (void)Value;
    return OUT_OK;
}

void MockDelay(uint32_t Delay)
{
    (void)Delay;
}
