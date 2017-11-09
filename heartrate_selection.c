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
#include "globals.h"
#include <stdbool.h>
#include <stdio.h>
#include "Speaker.h"
#include "heartrate_selection.h"

static void splashscreen();

double heartrate_setpoint = 60;

void runHeartrateSelection() {
    splashscreen();
}

static void splashscreen() {
    static bool firstEntry = true;
    
    if (firstEntry) {
        firstEntry = false;
        
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
        
        LCD_Position(0, 0);
        LCD_PrintString("Select          ");
        LCD_Position(1, 0);
        LCD_PrintString("Heartrate       ");
    }
    
    if (!CapSense_IsBusy()) {
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        
        uint16 pos =CapSense_GetCentroidPos(CapSense_LINEARSLIDER__LS) * 2;//slider goes to 100, max heart rate is 200
        if (pos!=0xFFFE) {
            heartrate_setpoint = pos;
            char number[10];
            sprintf(number, "%i", (int)heartrate_setpoint);
            LCD_Position(0, 12);
            LCD_PrintString(number);
        }
        
        if (CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN)) {
            currentState = RUNNING;
        }
    }
}

/* [] END OF FILE */
