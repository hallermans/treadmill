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

static void handleHeartbeat();

static bool peak = 0;
static bool heartbeatState = false;

static const double PEAK_SINK = .0001;
static const double HIGH_THRESHOLD = .9;
static const double LOW_THRESHOLD = .85;
void heartbeat_sample() {    
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    uint8 sample = ADC_GetResult8();
    
    if (sample>peak) peak = sample;
    else peak -= PEAK_SINK;
    
    if (!heartbeatState && sample>(peak*HIGH_THRESHOLD)) {
        heartbeatState = true;
        LED_Write(1);
        
        handleHeartbeat();
    }
    else if (heartbeatState && sample<(peak*LOW_THRESHOLD)) {
        heartbeatState = false;
        LED_Write(0);
    }
    
    DAC_SetValue(sample/2); //DAC goes to 4.096V, ADC goes to 2.048V
}

static const int TIMER_CLOCK_FREQUENCY = 24000000;
#define NUMBER_OF_HEARTBEATS 5
static uint32 heartbeatTimes[NUMBER_OF_HEARTBEATS];
static void handleHeartbeat() {
    //most recent heartbeat time goes in heartbeatTimes[NUMBER_OF_HEARTBEATS]
    for (int i=0; i<NUMBER_OF_HEARTBEATS-1; i++) {
        heartbeatTimes[i] = heartbeatTimes[i+1];
    }
    heartbeatTimes[NUMBER_OF_HEARTBEATS-1] = HeartbeatTimer_ReadCounter();
    
    long totalTime = (heartbeatTimes[0] - heartbeatTimes[NUMBER_OF_HEARTBEATS-1]) / TIMER_CLOCK_FREQUENCY;
    if (totalTime<0) totalTime += 4294967296;
    heartrate = 5 / totalTime;
}

/* [] END OF FILE */