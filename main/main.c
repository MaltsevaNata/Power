#include "mcu_support_package/inc/stm32f10x.h"
#include <stdbool.h>
#include "math.h"

static void play(void);
static void scan(void);

static int sins[100] = {50, 53, 56, 59, 62, 65, 68, 71, 74, 76, 79, 81, 84, 86, 88, 90, 92, 93, 95, 96, 97, 98, 99, 99, 99, 100, 99, 99, 99, 98,
 97, 96, 95, 93, 92, 90, 88, 86, 84, 81, 79, 76, 74, 71, 68, 65, 62, 59, 56, 53, 50, 46, 43, 40, 37, 34, 31, 28, 25, 23,
 20, 18, 15, 13, 11, 9, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 9, 11, 13, 15, 18, 20, 23, 25, 28, 31,
34, 37, 40, 43, 46};

static int freq[7] = {1046, 1175, 1318, 1396, 1568, 1720, 1975};
static int piano[7] = {0};

static volatile unsigned int loops = 0;

void SysTick_Handler(void) {
	if (loops >= 100) { 
		loops = 0;
	}
	 TIM_SetCompare1(TIM3, sins[loops]);
	loops++;
}

void TIM3_IRQHandler(void){

	//loops++;
	//TIM_SetCompare1(TIM3, sins[loops]);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

}


int main(void)
{

	//Сенсорные кнопки РА1..РА7
	GPIO_InitTypeDef buttons;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	buttons.GPIO_Mode = GPIO_Mode_IPD;
	buttons.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &buttons);



	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //динамик PC6
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//TIM3

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); //тактирование внутреннего мультиплексора

	TIM_TimeBaseInitTypeDef Timer_3;


	TIM_TimeBaseStructInit(&Timer_3); //заполнение по умолчанию

	Timer_3.TIM_Prescaler = SystemCoreClock / 10000000 - 1; //задаем нужную частоту 100 кГц
	//каждые 10^-4 новая ступенька
	Timer_3.TIM_Period = 100; //через 100 ступенек происходит прерывание, то есть 10^-2 с 			МАКСИМУМ ДЛЯ СЧЕТЧИКА (АМПЛИТУДА), НЕ МЕНЯТЬ
	//чтобы светодиод зажегся за 1 секунду полностью, нужно 100 таких периодов

	TIM_TimeBaseInit(TIM3, &Timer_3);

	GPIO_InitTypeDef speaker;
	speaker.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); 
	speaker.GPIO_Pin = GPIO_Pin_6;
	speaker.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &speaker);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	
	
	//настройка канала 1
	TIM_OCInitTypeDef tim_channel;
	TIM_OCStructInit(&tim_channel); //заполнение по умолчанию
	tim_channel.TIM_OCMode = TIM_OCMode_PWM1;
	tim_channel.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OC1Init(TIM3, &tim_channel);
	
	
	__disable_irq();

	while(1){
		scan();
		play();
	}
		
	return 0;
}




void play() {

	__disable_irq();
	for (int but =0; but <7; but ++) {
		if (piano[but] == 1) {
			SysTick_Config(SystemCoreClock/freq[but]);
			__enable_irq();
			NVIC_EnableIRQ(SysTick_IRQn);
			//SysTick->CTRL &= SysTick_CTRL_TICKINT; 
		}
		
		else {
		__disable_irq();
		TIM_SetCompare1(TIM3, sins[loops]);
		}
	}

}

/*
void play(void) {

	__disable_irq();
	
	for (int but =0; but <7; but ++) {
		if (piano[but] == 1) {
			SysTick_Config(SystemCoreClock/freq[but]);
			//__enable_irq();
			SysTick->CTRL &= ~SysTick_CTRL_TICKINT; 
			NVIC_EnableIRQ(TIM3_IRQn);
			
			while (!(SysTick->CTRL & (1<<16) )) {} 
			//TIM_SetCompare1(TIM3, sins[loops]);
			NVIC_DisableIRQ(TIM3_IRQn);

			while (!(SysTick->CTRL & (1<<16) )) {}
			//TIM_SetCompare1(TIM3, 0);
		}
		else { 
			__disable_irq();
			TIM_SetCompare1(TIM3, 0);
		}
		
	}

}*/

void scan(void) { //ДОДЕЛАТЬ ДЛЯ PC4
	__disable_irq();

	SysTick_Config(SystemCoreClock/10000);

	__enable_irq();

		for (int but = 0; but <7; but++) {

			if (GPIOA->IDR & (1<<but)) {
				piano[but] = 1;
			}	
			else {
				piano[but] = 0;
			}
		}

}




// В Project->Options->Linker, Scatter File выбран файл stack_protection.sct
// он обеспечивает падение в HardFault при переполнении стека
// Из-за этого может выдаваться ложное предупреждение "AppData\Local\Temp\p2830-2(34): warning:  #1-D: last line of file ends without a newline"

#ifdef USE_FULL_ASSERT

// эта функция вызывается, если assert_param обнаружил ошибку
void assert_failed(uint8_t * file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    (void)file;
    (void)line;

    __disable_irq();
    while(1)
    {
        // это ассемблерная инструкция "отладчик, стой тут"
        // если вы попали сюда, значит вы ошиблись в параметрах вызова функции из SPL.
        // Смотрите в call stack, чтобы найти ее
        __BKPT(0xAB);
    }
}

#endif
