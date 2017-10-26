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

#include <project.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heartbeat.h"

void handleHeartbeat();

void heartbeat_detect() {
    //const int PEAK_MULTIPLIER = 10000;
    const double PEAK_SINK = .0001;
    const double HIGH_THRESHOLD = .9;
    const double LOW_THRESHOLD = .85;
    
    long clock = 0;
    
    double peak = 0;
    bool heartbeatState = false;
    while (1) {
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        uint8 sample = ADC_GetResult8();
        
        if (sample>peak) peak = sample;
        else peak -= PEAK_SINK;
        //if (sample>(peak*.9)) LED_Write(1);
        //else LED_Write(0);
        if (!heartbeatState && sample>(peak*HIGH_THRESHOLD)) {
            LED_Write(1);
            heartbeatState = true;
            
            /*uint32 counter = 4294967295 - HeartbeatTimer_ReadCounter();
            char counterString[12]; //<10 digits>\r\n
            sprintf(counterString, "%lu\r\n", (unsigned long)counter);
            USBUART_PutString(counterString);
            HeartbeatTimer_WriteCounter(4294967295);*/
            handleHeartbeat();
        }
        else if (heartbeatState && sample<(peak*LOW_THRESHOLD)) {
            LED_Write(0);
            heartbeatState = false;
        }
        
        DAC_SetValue(sample/2); //DAC goes to 4.096V, ADC goes to 2.048V
        
        clock++;
    }
}

static const float timerClockFrequency = 24000000;
//static const int heartbeatAverageN = 5;
#define heartbeatAverageN 5
static uint32 heartbeatTimes[heartbeatAverageN];
void handleHeartbeat() {
    //most recent heartbeat time goes in heartbeatTimes[0]
    for (int i = heartbeatAverageN-1; i>0; i--) {
        heartbeatTimes[i] = heartbeatTimes[i-1];
    }
    heartbeatTimes[0] = HeartbeatTimer_ReadCounter();
    
    uint32 totalTime = heartbeatTimes[heartbeatAverageN-1] - heartbeatTimes[0];
    uint32 averageTime = totalTime / heartbeatAverageN-1;
    char timeString[20];
    sprintf(timeString, "%lu\r\n", averageTime);
    USBUART_PutString(timeString);
}

/* [] END OF FILE */