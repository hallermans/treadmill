/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include <project.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "heartbeat.h"

void heartbeat_detect() {
    //const int PEAK_MULTIPLIER = 10000;
    const double PEAK_SINK = .0001;
    
    double peak = 0;
    bool top = false;
    while (1) {
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        uint8 sample = ADC_GetResult8();
        if (sample>peak) peak = sample;
        else peak -= PEAK_SINK;
        //if (sample>(peak*.9)) LED_Write(1);
        //else LED_Write(0);
        if (sample>(peak*.9) && !top) {
            LED_Write(1);
            top = true;
            char time[100];
            itoa(clock()/CLOCKS_PER_SEC, time, 10);
            USBUART_PutString(time);
            USBUART_PutString("\n");
        }
        else if (sample<(peak*.9) && top) {
            LED_Write(0);
            top = false;
        }
        DAC_SetValue(sample/2);
    }
}