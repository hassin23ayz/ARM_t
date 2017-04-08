#include "TM4C123.h"                    // Device header
#include <stdio.h>

#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}

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
		//ITM_SendChar('A');
		//GPIO Data register
		printf("hello");
		
		GPIOF->DATA = 0x02; //0b0010 red on
		//wait();
		my_delay_ms(1000);
		GPIOF->DATA = 0x04; //0b0100 blue on
		//wait();
		my_delay_ms(1000);
		GPIOF->DATA = 0x08; //0b1000 green on
		//wait();
		my_delay_ms(1000);
	}
	return 0;
}

void wait(void)
{
	uint32_t clockCounter = 0;
	while(clockCounter++ < 1000000)
		;
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

