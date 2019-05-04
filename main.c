

/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"

#include "inc/hw_gpio.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"

#include "time.h"
#include "mat.h"
#include "pwm.h"


#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/udma.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"
#include "driverlib/adc.h"

#include "utils/uartstdio.c"



#include <string.h>

void initPot(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_6);
    ADCSequenceEnable(ADC0_BASE, 0);
}

void delayMs(int n)
{
 int i, j;
 for(i = 0 ; i < n; i++)
 for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);

    uint32_t ui32ADC0Value;

    initPWM();
    initPot();


    float MAX = 1023.0f;
    float MIN = 0.0;

    float   motorL,motorR,throttle;
    char buf[20];

    throttle =0;
    //float index=0.0;

    while(1){

        ADCIntClear(ADC0_BASE, 1);
        ADCProcessorTrigger(ADC0_BASE, 1);
        while(!ADCIntStatus(ADC0_BASE, 1, false)) {
            ;
        }
        ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);

        throttle = ui32ADC0Value;

        //printf("%d\n",(int)throttle);
        motorR = throttle;
        motorL = throttle;


        motorR = constrain(motorR, MAX, MIN);
        motorL = constrain(motorL, MAX, MIN);

        //ftoa(motorR,buf,2);
        //printf("input %s \n",buf);

        writeMotorL(motorL);
        writeMotorR(motorR);
        //Delay(200);
        delayMs(20);
    }
    return 0;
}

