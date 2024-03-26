#include "config.h"
#include "EXTI.h"
#include "int.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "GPIO.h"

void GPIO1_Combined_16_31_IRQn_Handler(uint32_t gicciar, void *param);

void EXTI_Init(void) {
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, GPIO1_Combined_16_31_IRQn_Handler, NULL); // 注册中断向量表
	GPIO_IT_Config(GPIO1, KEY0, GPIO_IntBothEdge); // GPIO 中断配置
	GPIO_IT_ClearStatus(GPIO1, GPIO_Pin_All); // 清除中断标志位

	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn); // 开启GIC中断通道
	GPIO_IT_Enable(GPIO1, KEY0); // 开启GPIO中断
}

void GPIO1_Combined_16_31_IRQn_Handler(uint32_t gicciar, void *param) {
	__IO uint32_t flag = GPIO1->ISR;

	if (flag & KEY0) {
		delay(10);
		if (GPIO_ReadBit(GPIO1, KEY0)) { // 上升沿

		}
		else { // 下降沿
			led_flip();
		}
		
		GPIO_IT_ClearStatus(GPIO1, KEY0);
	}
}
