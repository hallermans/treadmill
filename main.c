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
#include "Speaker.h"
#include "heartbeat.h"

static void initializeComponents();
static void splashscreen();
static void adjust_pwm();

static const double HEARTRATE_SETPOINT = 240;
static const double PWM_SLEW_COEFFICIENT = .0000001;
static const double PWM_MAX_SLEW_RATE = .000001;
static double pwm_duty = .5;

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
        adjust_pwm();
    }
}

static void adjust_pwm() {
    double pwm_delta = PWM_SLEW_COEFFICIENT * (HEARTRATE_SETPOINT - heartrate);
    if (pwm_delta>PWM_MAX_SLEW_RATE) pwm_delta = PWM_MAX_SLEW_RATE;
    else if (pwm_delta<-PWM_MAX_SLEW_RATE) pwm_delta = -PWM_MAX_SLEW_RATE;
    
    pwm_duty += pwm_delta;
    if (pwm_duty>1) pwm_duty = 1;
    else if (pwm_duty<0) pwm_duty = 0;
    
    PWM_WriteCompare(pwm_duty * 256);
}

static void initializeComponents() {
    ADC_Start();
    ADC_StartConvert();
    DAC_Start();
    
    HeartbeatTimer_Start();
    
    LCD_Start();
    
    PWM_Start();
    
    USBUART_Start(0, USBUART_5V_OPERATION);
    while (USBUART_GetConfiguration()==0);
    USBUART_CDC_Init();
}

static void splashscreen() {
    for (int i=0; i<16; i++) {
        LCD_Position(0, i);
        LCD_PutChar(LCD_CUSTOM_0);
        CyDelayUs((uint16_t)100000);
    }
    LCD_Position(0, 0);
    LCD_PrintString("   Welcome to   ");
    LCD_Position(1, 0);
    LCD_PrintString("  My Treadmill  ");
    
    /*Speaker_playNote(0, 1);
    Speaker_playNote(7, 1);
    Speaker_playNote(12, 1);
    Speaker_playNote(16, .25);
    Speaker_playNote(15, 1.75);*/
}

/* [] END OF FILE */
