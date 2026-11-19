
#ifndef DRV_HWSKYWALKER_INC_DRV_HWSKYWALKER_H_
#define DRV_HWSKYWALKER_INC_DRV_HWSKYWALKER_H_

#include "Drv_HWSKYWALKER_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef GenUtl_Err_t (*Drv_HWSKYWALKER_Uart_TrasmitCB_t)(const uint8_t *pData, uint16_t Size, uint32_t Timeout);
typedef GenUtl_Err_t (*Drv_HWSKYWALKER_SetPwmCB_t)(uint32_t PwmValue);
typedef void (*Drv_HWSKYWALKER_DelayCB_t)(uint32_t Delay);

typedef struct 
{
    Drv_HWSKYWALKER_Uart_TrasmitCB_t pfUartTrasmitCB;
    Drv_HWSKYWALKER_SetPwmCB_t pfSetPwmCB;
    Drv_HWSKYWALKER_DelayCB_t pfDelayCB;
} Drv_HWSKYWALKER_Config_t;

GenUtl_Err_t Drv_HWSKYWALKER_Init(const Drv_HWSKYWALKER_Config_t *pConfigData);

GenUtl_Err_t Drv_HWSKYWALKER_Test();

#ifdef __cplusplus
}
#endif

#endif /* DRV_HWSKYWALKER_INC_DRV_HWSKYWALKER_H_ */
