#include "LPC13xx.h"                    // Device header
#include "gpio.h"

static volatile unsigned int delayTimeTick = 0;

void my_delay_ms(unsigned int ticksIn_ms);

int main(void)
{
	SystemInit();
	SysTick_Config(SystemCoreClock/2);
	
	GPIOInit();
	GPIOSetDir( 3, 5, 1 );  //(portNum, bitPos, dir )
	GPIOSetValue( 3, 5, 0 );
	while(1)
	{
		GPIOSetValue( 3, 5, 0 );
		my_delay_ms(1000);
		GPIOSetValue( 3, 5, 1 );
		my_delay_ms(1000);
	}
	
	return 1;
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

