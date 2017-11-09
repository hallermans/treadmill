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
#include <stdbool.h>
#include "globals.h"
#include "running.h"
#include "heartbeat.h"

static void adjust_pwm();

void runRunning() {
    static bool firstEntry = true;
    
    if (firstEntry) {
        firstEntry = false;
        LCD_Position(0, 0);
        LCD_PrintString("    Running     ");
        LCD_Position(1, 0);
        LCD_PrintString("                ");
    }
    
    heartbeat_sample();
    adjust_pwm();
    
    if (!STOP_Read()) currentState = RAMPDOWN;
}

static void adjust_pwm() {
    double pwm_delta = PWM_SLEW_COEFFICIENT * (heartrate_setpoint - heartrate);
    if (pwm_delta>PWM_MAX_SLEW_RATE) pwm_delta = PWM_MAX_SLEW_RATE;
    else if (pwm_delta<-PWM_MAX_SLEW_RATE) pwm_delta = -PWM_MAX_SLEW_RATE;
    
    pwm_duty += pwm_delta;
    if (pwm_duty>1) pwm_duty = 1;
    else if (pwm_duty<0) pwm_duty = 0;
    
    PWM_WriteCompare(pwm_duty * 256);
}

/* [] END OF FILE */
