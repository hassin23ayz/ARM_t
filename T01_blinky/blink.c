#include "sam3xa.h"                     // Device header
#include "RTE_Components.h"             // Component selection
#include "hw_led.h"

static volatile unsigned int delayTimeTick = 0;

void my_delay_ms(unsigned int ticksIn_ms);

int main()
{
	SystemInit();  //would initialize MCU's clock system, FLASH memoy interface
	SysTick_Config(SystemCoreClock/1000);
	LED_INIT();
	
	while(1)
	{
		LED_OFF();
		my_delay_ms(2000);
		LED_ON();
		my_delay_ms(2000);
	}
	return 0;
}

void SysTick_Handler()
{
	if(delayTimeTick < 0xFFFFFFFF)
	{
		delayTimeTick++;
	}
}

void my_delay_ms(unsigned int ticksIn_ms)
{
	delayTimeTick = 0;
	while(delayTimeTick < ticksIn_ms)
	{}
}
