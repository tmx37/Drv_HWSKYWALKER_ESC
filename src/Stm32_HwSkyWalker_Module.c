#include "Stm32_HwSkyWalker_Module.h"

/**
 * NOTE:
 *  Skywalker A40 needs these caracteristics to work:
 *      > 50Hz, 20ms period (adjust prescaler on timer output)
 *      > 1~2 ms pulse witdth to control (1000~2000 on timer output)
 *      > Duty cycle is not important at all
 *      > Keep 1ms pulse width value for 2~5 seconds at startup to make ESC 
 *        know flight controller is ready to fly
 *      > Implement safety clamps for input values (they should always be from 1000 to 2000)
 */

int test()
{
    //  HAL_ADC_Start(&hadc1);
    //  HAL_ADC_PollForConversion(&hadc1, 1);
    //  AD_RES = HAL_ADC_GetValue(&hadc1);

    //   // Map ADC (0–4095) → 1000–2000 µs
    //   ValueToTransmit = 1000 + (AD_RES * 1000) / 4095;

    //   // Safety clamp
    //   if (ValueToTransmit < 1000) ValueToTransmit = 1000;
    //   if (ValueToTransmit > 2000) ValueToTransmit = 2000;

    //   TIM1->CCR1 = ValueToTransmit;

    //  int len = snprintf(BufferToTransmit, sizeof(BufferToTransmit), "%lu\r\n", ValueToTransmit);
    //  HAL_UART_Transmit(&huart2, (uint8_t*)BufferToTransmit, len, HAL_MAX_DELAY);
     
    //  HAL_Delay(5);
    return 1;
}