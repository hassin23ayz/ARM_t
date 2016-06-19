#ifdef __cplusplus
extern "C" {
#endif

#include "TM4C123.h"                    // Device header
#include "RTE_Components.h"             // Component selection

void wait(void);  //using while loop 
static volatile unsigned int delayTimeTick = 0;
void my_delay_ms(unsigned int ticksIn_ms);  //using system core clock 

int main(void)
{

	SystemInit();  //would initialize MCU's clock system, FLASH memoy interface
	SysTick_Config(SystemCoreClock/1000);
	//general purpose I/O rin mode Clock gating control register
	SYSCTL->RCGCGPIO = 0x20;  //enable PORTF only
	
	//RGB leds are connected to PF1, PF2, PF3 
	
	//GPIO direction register
	GPIOF->DIR = 0xE;
	//GPIO digital enable register
	GPIOF->DEN = 0xE;
	
	while(1)
	{
		//GPIO Data register
		
		GPIOF->DATA = 0x02; //0b0010 red on
		//wait();
		my_delay_ms(500);
		GPIOF->DATA = 0x04; //0b0100 blue on
		//wait();
		my_delay_ms(500);
		GPIOF->DATA = 0x08; //0b1000 green on
		//wait();
		my_delay_ms(500);
	}
	return 0;
}

void wait(void)
{
	uint32_t clockCounter = 0;
	while(clockCounter++ < 1000000)
		;
}

extern "C" {
	void SysTick_Handler()
		{
			if(delayTimeTick < 0xFFFFFFFF)
				{
					delayTimeTick++;
				}
		}
}


void my_delay_ms(unsigned int ticksIn_ms)
{
	delayTimeTick = 0;
	while(delayTimeTick < ticksIn_ms)
	{}
}

#ifdef __cplusplus
}
#endif