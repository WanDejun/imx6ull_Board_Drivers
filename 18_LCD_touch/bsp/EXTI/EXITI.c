#include "config.h"
#include "EXTI.h"
#include "int.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "GPIO.h"
#include "EPIT.h"

void GPIO1_Combined_16_31_IRQn_Handler(uint32_t gicciar, void *param);

void EXTI_Init(void) {
	/* 
		@ GPIO1_Combined_16_31_IRQn 的 GPIO_Pin_15 初始化 
	*/
	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn); // 开启GIC中断通道
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, GPIO1_Combined_16_31_IRQn_Handler, NULL); // 注册中断向量表
	
	GPIO_IT_Config(GPIO1, KEY0, GPIO_IntBothEdge); // GPIO 中断配置
	GPIO_ClearITFlag(GPIO1, GPIO_Pin_All); // 清除中断标志位
	GPIO_IT_Enable(GPIO1, KEY0); // 开启GPIO中断
}

void GPIO1_Combined_16_31_IRQn_Handler(uint32_t gicciar, void *param) { // 
	__IO uint32_t flag = GPIO1->ISR;

	if (flag & KEY0) {
		EPIT_Cmd(ENABLE);
		
		GPIO_ClearITFlag(GPIO1, KEY0);
	}
}


void EPIT1_IRQn_Handler(uint32_t gicciar, void *param) {
	// extern KeyStatus keyStatus_Buf[1];
	// if (EPIT1->SR) {
	// 	EPIT_Cmd(DISABLE);
	// 	if (GPIO_ReadBit(GPIO1, KEY0)) { // 上升沿
	// 		keyStatus_Buf[0] = KEY_OFF;
	// 	}
	// 	else { // 下降沿
	// 		keyStatus_Buf[0] = KEY_ON;
	// 		led_flip();
	// 	}
	// 	EPIT_ClearITFlag();
	// }
	if (EPIT1->SR) {
		led_flip();
		
		EPIT_ClearITFlag();
	}
}

void GPT1_IRQn_Handler(uint32_t GIC_NUM, void *parma){
	if (GPT1->SR & (1 << 0)) {
		GPT1->CR |= (1 << 30); // 手动翻转OM2

		GPT1->SR |= (1 << 0); // 清除标志位
	}
}

