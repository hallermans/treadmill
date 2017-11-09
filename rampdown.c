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
#include "rampdown.h"

void runRampdown() {
    static bool firstEntry = true;
    
    if (firstEntry) {
        firstEntry = false;
        LCD_Position(0, 0);
        LCD_PrintString("    Stopping    ");
        LCD_Position(1, 0);
        LCD_PrintString("                ");
    }
    
    pwm_duty -= PWM_MAX_SLEW_RATE;
    PWM_WriteCompare(pwm_duty * 256);
}

/* [] END OF FILE */
