/*
 *  Matthew Hoffman
 *  CpE403 - Advanced Embedded Systems, Fall 2017
 *  Lab03-T01
 *  Task 01: Determine the current period and on-time of the LED blinking.
 *  Change the delay of the LED blink (approx. 0.333 sec) by changing the clock source and
 *  configuration – do not change the delay value – determine the CLK frequency – verify the
 *  delay to be approx. 0.333 sec
*/
//Variable definitions for the C99 Standard
#include <stdint.h>
//Boolean definitions for the C99 Standard
#include <stdbool.h>
/*
Macros defining the memory map of the Tiva C Series device.
This includes defines such as peripheral base address
locations such as GPIO_PORTF_BASE.
*/
#include "inc/hw_memmap.h"
//Defines common types and macros
#include "inc/hw_types.h"
/*
 * Defines and macros for System Control API of DriverLib.
 * This includes API functions such as SysCtlClockSet and SysCtlClockGet
*/
#include "driverlib/sysctl.h"
/*
 * Defines and macros for GPIO API of DriverLib.  This includes
 * API functions such as GPIOPinTypePWM and GPIOPinWrite
 */
#include "driverlib/gpio.h"
// RED  :pin1
// BLUE :pin2
// GREEN:pin3
uint8_t ui8PinData = 14;
int main(void)
{
    // PLL is 400MHZ, Autodivides by 2.  # in SYSDIV Divides it again giving us 40MHz
    // By dividing by 11 we get an approx .333 sec LED blink
    SysCtlClockSet(SYSCTL_SYSDIV_11|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    // Enables Clock(must do this before calling any peripheral specific driverLib function
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
        SysCtlDelay(2000000); // 3 clock cycles = 1 CPU Cycle, 2000000 * 3 = 6000000 CPU cycle delay
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
        SysCtlDelay(2000000); // 3 clock cycles = 1 CPU Cycle, 2000000 * 3 = 6000000 CPU cycle delay

        if (ui8PinData == 8)
        {
            ui8PinData = 4;
        }
        else if (ui8PinData == 4)
        {
            ui8PinData = 2;
        }
        else
        {
            ui8PinData = 8;
        }


    } // end while
}
