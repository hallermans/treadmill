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
#include "watchdog.h"

bool error = false;

CY_ISR(WATCHDOG_HANDLER) {
    if (!ERROR1_Read() || !ERROR2_Read()) error = true;
}

void watchdog_start() {
    WATCHDOG_INTERRUPT_StartEx(WATCHDOG_HANDLER);
    WATCHDOG_TIMER_Start();
}

/* [] END OF FILE */
