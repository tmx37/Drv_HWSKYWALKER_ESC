#include "Drv_HwSkyWalker.h"

/** 
      TODO:
        - verificare codice errori
        - verificare 
        - Includere un controllo di alimentazione per controllare l'alimentazione dei motori da lipo, direttamente su scheda, per permettere agli altri componenti di 
          continuare a funzionare per operazioni di programmazione, setting, debug, segnalazione da remoto con risparmio energetico e via così.. Aggiungere anche bypass 
          fisico sul circuito

  NOTE ESC rev-eng:
    - appena data tensione "principale" (dalla lipo) all'ESC, questo necessiterà di una "Startup routine" (da confrontare con il manuale) per effettuare 
      delle specie di controlli (presumo di configurazione iniziale): passa se faccio andare il pwm da 0 a 45880 (~70% circa del pwm)
    - motore a velocità "0" a circa 70% del PWM: ~45880
    - motore a velocità "100" a circa 99% del PWM: ~64879 
    - ESC ha una sorta di protezione contro l'eccessivo consumo da parte del motore (es: elica bloccata), per evitare consumi troppo elevati
    - ESC genera errore se, appena data alimentazione, non viene fatto un ciclo da 0 a regime (probabile startup routine), forse per evitare comandi troppo "bruschi"
    - ESC rileva numero di celle dell'alimentazione, nello specifico se 3 o 4 celle (testato)

    - ESC CALIBRATION:
      * Set PWM to MAX ;
      * Plug in battery, Motor will play "1 2 3" sound to indicate ESC is normally powered on;
      * Motor will sound 2 short times to indicate max throttle endpoint is accepted;
      * Set PWM to MIN, within 5 seconds after the two short beeps: the minimum throttle position will be accepted 1 second later;
      * Motor will beep "Number" beeps to indicate the number of LiPo cells you have plugged in;
      * Motor will beep a long beep to indicate calibration is complete.
    
    - ESC NORMAL START-UP PROCESS:
      * Set PWM to MIN;
      * Plug in battery, Motor will play "1 2 3" sound to indicate ESC is normally powered on;
      * Motor will beep "Number" beeps to indicate the number of LiPo cells you have plugged in;
      * Motor will beep a long beep to indicate ESC is ready to go.
    
    - PROGRAM ESC WITH THE TRANSMITTER:
      * Enter programming mode
        > Turn on transmitter
        > Move throttle stick to top position
        > Plug in battery
        > 2 seconds later motor will beep 2 short times
        > 5 seconds later it will beep again 
        > You will be in programming mode
      * Select parameter items
        > 12 distinct beeps play circularly;
        > set PWM to MIN within 3 seconds after the right sound, you will enter the corresponding parameter item;
          #1....Brake Type............"B-"
          #2....Brake Force..........."B-B-"
          #3....Voltage Cutoff Type..."B-B-B-"
          #4....LiPo Cells............"B-B-B-B-"
          #5....Cutoff Voltage........"B-----"
          #6....Start-up Mode........."B-----B-"
          #7....Timing................"B-----B-B-"
          #8....Active Freewheeling..."B-----B-B-B-"
          #9....Search Mode..........."B-----B-B-B-B-"
          #10...Factory Reset........."B-----B-----"
          #11...Exit.................."B-----B-----B-"
      * Select parameter values
        > Motor bips circularly: put high value when the sound with the corresponding value is met. Then, a sound will be reproduced and the ESC will retun to Paremeter items selection.
            |    B1    |    B2    |    B3    |    B4    |    B5    |
          ----------------------------------------------------------
          #1| Disabled |  Normal  |  Reverse |Linear Rev|          |
          #2|   Low    |  Medium  |   High   |          |          | 
          #3|   Soft   |   Hard   |          |          |          |
          #4| AutoCalc |    2S    |    3S    |          |          |
            |          |    3S    |    4S    |    5S    |    6S    |
          #5| Disabled |   Low    |  Medium  |   High   |          |
          #6|  Normal  |   Soft   | Very Soft|          |          |          
          #7|   Low    |  Medium  |   High   |          |          |
          #8|   On     |   Off    |          |          |          |
          #9|   Off    |   5min   |   10min  |   15min  |          |
      * Exit programming mode
        > Bring PWM value to bottom withing 3 seconds after Two Long and one short beeps
*/

static Drv_HWSKYWALKER_Uart_TrasmitCB_t mUartTrasmitCB;
static Drv_HWSKYWALKER_SetPwmCB_t mSetPwmCB;
static Drv_HWSKYWALKER_DelayCB_t mDelayCB;

GenUtl_Err_t Drv_HWSKYWALKER_Init(const Drv_HWSKYWALKER_Config_t *pConfigData)
{
	mUartTrasmitCB = pConfigData->pfUartTrasmitCB;
	mSetPwmCB = pConfigData->pfSetPwmCB;
	mDelayCB = pConfigData->pfDelayCB;
	return OUT_OK;
}

GenUtl_Err_t Drv_HWSKYWALKER_Test()
{
    
    // Waiting startup procedure to end 
    // TODO: make an external fw with buttons driver to make esc configuration easy
    mDelayCB(2500);
    mUartTrasmitCB("\r\n", strlen("\r\n"), DRV_HWSKYWALKER_UART_MAX_DELAY);

    // 65530 - 45880 = 19650;
    // x : 19650 = 1 : 100;
    // value = 45880 + x -> pwm speed

    // TIM1->CCR1 = 50*(19650/100) + 45880;

    uint8_t pwm_percent = 0;
	mSetPwmCB((pwm_percent * 196) + 45880);

    mUartTrasmitCB("Going up..",  strlen("Going up.."), DRV_HWSKYWALKER_UART_MAX_DELAY);
    for(int i=45880; i<64879; i+=50) // from 70% (~45880) to 100% (~65530)
    {
		mSetPwmCB(i);
      	mDelayCB(5);
    }

    mUartTrasmitCB("\r\n", strlen("\r\n"), DRV_HWSKYWALKER_UART_MAX_DELAY);
    mDelayCB(2500);

    mUartTrasmitCB("Going down..", strlen("Going down.."), DRV_HWSKYWALKER_UART_MAX_DELAY);
    for(int i=64879; i>45880; i-=50) // from 100% (~65530) to 70% (~45880) 
    {
		mSetPwmCB(i);
      	mDelayCB(5);
    }
    
    return OUT_OK;
}