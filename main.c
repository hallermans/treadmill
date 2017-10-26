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
#include "Speaker.h"
#include "heartbeat.h"

void initializeComponents();
void splashscreen();

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    initializeComponents();
    splashscreen();

    for(;;)
    {
        /* Place your application code here. */
        heartbeat_sample();
    }
}

void initializeComponents() {
    ADC_Start();
    ADC_StartConvert();
    DAC_Start();
    
    HeartbeatTimer_Start();
    
    LCD_Start();
    
    USBUART_Start(0, USBUART_5V_OPERATION);
    while (USBUART_GetConfiguration()==0);
    USBUART_CDC_Init();
}

void splashscreen() {
    for (int i=0; i<16; i++) {
        LCD_Position(0, i);
        LCD_PutChar(LCD_CUSTOM_0);
        CyDelayUs((uint16_t)100000);
    }
    LCD_Position(0, 0);
    LCD_PrintString("   Welcome to   ");
    LCD_Position(1, 0);
    LCD_PrintString("  My Treadmill  ");
    
    Speaker_playNote(0, 1);
    Speaker_playNote(7, 1);
    Speaker_playNote(12, 1);
    Speaker_playNote(16, .25);
    Speaker_playNote(15, 1.75);
}

/* [] END OF FILE */
