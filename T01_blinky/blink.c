#include "sam3xa.h"                     // Device header
#include "RTE_Components.h"             // Component selection
#include "hw_led.h"

int main()
{
	SystemInit();  //would initialize MCU's clock system, FLASH memoy interface
	SysTick_Config(SystemCoreClock/2);
	LED_INIT();
	LED_OFF();
	return 0;
}

/*__irq void SysTick_Handler()
{
	static _Bool toggle = 1;
	
	if (toggle == 1) {
		LED_ON();
		toggle = 0;
	}
	else {
		LED_OFF();
		toggle = 1;
	}
}*/