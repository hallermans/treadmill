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
#include <stdio.h>
#include "globals.h"
#include "error.h"

void runError() {
    static bool firstEntry = true;
    
    if (firstEntry)
    {
        firstEntry = false;
        LCD_Position(0, 0);
        LCD_PrintString("COMPONENT FAILED");
        LCD_Position(1, 0);
        LCD_PrintString("  DO NOT USE!!  ");
    }
    
    if (pwm_duty>0) pwm_duty -= PWM_MAX_SLEW_RATE;
    PWM_WriteCompare(pwm_duty * 256);
    
    if (pwm_duty<=0) {
        char errorString[20];
        sprintf(errorString, "Error1: %i Error2: %i\r\n", !ERROR1_Read(), !ERROR2_Read());
        USBUART_PutString(errorString);
            
        CyDelay(1000);
    }
}

/* [] END OF FILE */
