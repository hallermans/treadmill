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
#include <stdio.h>
#include "globals.h"
#include "watchdog.h"
#include "heartrate_selection.h"
#include "running.h"
#include "rampdown.h"
#include "error.h"

static void initializeComponents();

double pwm_duty = 0;

enum states currentState = HEARTRATE_SELECTION;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    initializeComponents();

    for(;;)
    {        
        if (error) runError();
        else if (currentState==HEARTRATE_SELECTION) runHeartrateSelection();
        else if (currentState==RUNNING) runRunning();
        else if (currentState==RAMPDOWN) runRampdown();
        else runError();
    }
}



static void initializeComponents() {
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    
    ADC_Start();
    ADC_StartConvert();
    DAC_Start();
    DAC_SetValue(100);
    
    HeartbeatTimer_Start();
    
    LCD_Start();
    
    PWM_Start();
    PWM_WriteCompare(0);
    
    USBUART_Start(0, USBUART_5V_OPERATION);
    while (USBUART_GetConfiguration()==0);
    USBUART_CDC_Init();
    
    watchdog_start();
}

/* [] END OF FILE */
