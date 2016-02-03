#include "LPC13xx.h"                    // Device header
#include "gpio.h"

int main(void)
{
	//SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config((SystemCoreClock/10000));
	
	  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	
	GPIOSetDir( 2, 0, 1 );
	GPIOSetValue( 2, 0, 0 );
	
	return 0;
}