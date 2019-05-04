/*
 * pwm.c
 *
 *  Created on: 30-Apr-2019
 *      Author: acharya
 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "time.h"
#include "pwm.h"
#include "mat.h"


#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"

double period = 50000; // Period of PWM is set to 2.5ms/400Hz with divider 4

#define MIN_PPM  20600 // This value is "how many clock ticks does 1030us takes" div4 - 20600(1010us)
#define MAX_PPM 37200 // Same here but 1860 us - From Afro ESC datasheet.       div4 - 37200(1860us)

void initPWM(){
    //SysCtlPWMClockSet(SYSCTL_PWMDIV_32); // Set divider to 32
    SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
    //SysCtlPWMClockSet(SYSCTL_PWMDIV_2); // Set divider to 2

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enable PWM peripheral
    SysCtlDelay(5); // Insert a few cycles after enabling the peripheral to allow the clock to be fully activated
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Enable GPIOB peripheral
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    SysCtlDelay(5); // Insert a few cycles after enabling the peripheral to allow the clock to be fully activated

    // Use alternate function

    //GPIOPinConfigure(GPIO_PB7_M0PWM1);
    //GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    //GPIOPinConfigure(GPIO_PC5_M0PWM7);

    //GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4); // Use pin with PWM peripheral
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Use pin with PWM peripheral
    //GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
    // Configure the PWM generator for count down mode with immediate updates to the parameters
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //period = (SysCtlClockGet() / 10000 * 15) / 2;

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period); // Set the period
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period);

    // Start the timers in generator 0 and 1
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

//
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 800 );
    // Enable the outputs
    //PWMOutputState(PWM0_BASE,PWM_OUT_1_BIT | PWM_OUT_0_BIT |  PWM_OUT_2_BIT |  PWM_OUT_3_BIT | PWM_OUT_7_BIT, true);
    PWMOutputState(PWM0_BASE,PWM_OUT_2_BIT |  PWM_OUT_3_BIT, true);
}
// LEFT
void writeMotorL(float value){
    //printf("inside pwm %d\n",(int)value);
    value = mapf(value, 0.0, 1023.0,  MIN_PPM, MAX_PPM);
    //printf("%d\n",(int)value);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, value);
}
// RIGHT
void writeMotorR(float value){
    value = mapf(value, 0.0, 1023.0, MIN_PPM, MAX_PPM);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, value);
}



