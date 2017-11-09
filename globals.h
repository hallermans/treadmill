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

#ifndef GLOBALS_H
#define GLOBALS_H

//static const double HEARTRATE_SETPOINT = 240;
static const double PWM_SLEW_COEFFICIENT = .0000001;
static const double PWM_MAX_SLEW_RATE = .000001;

enum states {HEARTRATE_SELECTION, RUNNING, RAMPDOWN};
extern enum states currentState;
extern double pwm_duty;
extern double heartrate;
extern double heartrate_setpoint;
    
#endif

/* [] END OF FILE */
