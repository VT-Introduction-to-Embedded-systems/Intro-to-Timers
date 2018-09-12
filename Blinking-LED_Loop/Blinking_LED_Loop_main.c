// This application uses button 1, LED 1, and LED 2 on Launchpad
// It makes the LED 2 blink
// For button 1 and LED 1 the operation is such that if you press the button 1, as long as you keep the button pressed,
// the LED1 is on. As soon as you release the button, LED1 is off and stays off until the button is pressed again.

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0

// This function initializes all the peripherals
void initialize();

void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();
void TurnOn_Launchpad_Green_LED2();
void TurnOff_Launchpad_Green_LED2();
void Toggle_Launchpad_Green_LED2();

char SwitchStatus_Launchpad_Button1();


int main(void)
{
    int i;
    initialize();
    while (1) {

         // If the button is not pressed, keep the LED off
        if (SwitchStatus_Launchpad_Button1() != PRESSED)
            TurnOff_Launchpad_LED1();
        else
            TurnOn_Launchpad_LED1();

        for (i=0;i<120000;i++);
        Toggle_Launchpad_Green_LED2();

    }
}


// Initialization part is always device dependent and therefore does not change much with HAL
void initialize()
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now.Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing Launchpad LED1, which is on Pin 0 of Port P1 (from page 37 of the Launchpad User Guide)
    // same for Green LED on P2.1
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);

    // step 3: Initializing Launchpad S1 (switch 1 or button 1),
    // which is on Pin1 of Port 1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
}

void TurnOn_Launchpad_LED1()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
void TurnOff_Launchpad_LED1()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void TurnOn_Launchpad_Green_LED2()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
}

void TurnOff_Launchpad_Green_LED2()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
}

void Toggle_Launchpad_Green_LED2()
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
}

char SwitchStatus_Launchpad_Button1()
{
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1));
}
