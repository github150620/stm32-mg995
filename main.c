#include "stm32f10x.h"

void delay(int i) {
	while(--i>0);
}

int main() {
	GPIO_InitTypeDef        GPIO_InitStrue;
	TIM_OCInitTypeDef       TIM_OCInitStrue;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStrue);
	
	TIM_TimeBaseInitStrue.TIM_Period        = 2000;         // 20ms = 2000 * 10us
	TIM_TimeBaseInitStrue.TIM_Prescaler     = 720;          // 10us = 72MHz / 720
	TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStrue.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStrue);
	
	TIM_OCInitStrue.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStrue.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStrue.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM1, &TIM_OCInitStrue);
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_Cmd(TIM1, ENABLE);
	
	while (1) {
		TIM_SetCompare1(TIM1, 150); // 1.5ms  90°
		delay(50000000);
		TIM_SetCompare1(TIM1, 50); // 0.5ms   0°
		delay(50000000);
		TIM_SetCompare1(TIM1, 150); // 1.5ms  90°
		delay(50000000);
		TIM_SetCompare1(TIM1, 250); // 2.5ms 180°
		delay(50000000);
	}
}
