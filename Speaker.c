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
#include "Speaker.h"
#include <project.h>
#include <math.h>

void Speaker_playNote(int note, double duration) {
    double frequency = 400 * pow(2, note/12.0);
    int period_us = 1000000/frequency;
    int cycles = frequency * duration;
    
    for (int i=0; i<cycles; i++) {
        BEEP_Write(1);
        CyDelayUs(period_us/2);
        BEEP_Write(0);
        CyDelayUs(period_us/2);
    }
}

/* [] END OF FILE */
