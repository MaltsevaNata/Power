#include "mcu_support_package/inc/stm32f4xx.h"

// Перед использованием не забудьте выбрать микроконтроллер - с помощью дефайнов вида STM32F407xx и STM32F40_41xxx - на весь проект
// И выбрать правильную частоту кварца, установив на весь проект дефайн HSE_VALUE=8000000 или HSE_VALUE=12000000
// И выбрать правильный startup-файл с расширением .s в группе mcu_support_package


#define BLINKING  1
#define BUTTON    2


#define CURRENT_PART 2

#if CURRENT_PART == BLINKING

int main(void)
{

	RCC->AHB1ENR = 0x8;
	GPIOD->MODER = 0x1000000;
	GPIOD->OTYPER = 0x0;
	__disable_irq();
	SysTick_Config(SystemCoreClock/15);	
	
	while(1) {
		if (SysTick->CTRL & (1<<16) ) { 
			GPIOD->ODR ^= 0x1000;
		}
	}
}


#elif CURRENT_PART == BUTTON
int main(void)
{
	while(1) {
	}
}


#else

    #error "You should define CURRENT_PART to enable some part of the assignment"

#endif
