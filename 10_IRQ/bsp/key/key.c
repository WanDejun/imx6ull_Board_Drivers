#include "key.h"
#include "GPIO.h"
#include "fsl_iomuxc.h"
#include "delay.h"
#include "int.h"
#include "led.h"

#define KEY0 GPIO_Pin_18

static const uint32_t key[1] = { KEY0 };
KeyStatus keyStatus_Buf[1];

void GPIO1_Combined_16_31_IRQn_Handler(uint32_t gicciar, void *param);

void Key_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_OFF;

	GPIO_InitStructure.HYS = GPIO_HYS_ON;
    GPIO_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_0_low_50MHz_; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_0_output_driver_disabled_; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_0_Slow_Slew_Rate; // 压摆率

	GPIO_Init(IOMUXC_UART1_CTS_B_GPIO1_IO18, &GPIO_InitStructure);

	/* 3、初始化GPIO */
	GPIO1->GDIR &= ~(key[0]);

	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, GPIO1_Combined_16_31_IRQn_Handler, NULL);
	GPIO_IT_Config(GPIO1, KEY0, GPIO_IntBothEdge);
	GPIO_IT_ClearStatus(GPIO1, KEY0);

	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
	GPIO_IT_Enable(GPIO1, KEY0);

}

KeyStatus GetKeyStatus() {
	uint32_t t = (GPIO1->PSR & key[0]);
	delay(10);
	if (t == (GPIO1->PSR & key[0])) keyStatus_Buf[0] = t ? KEY_OFF : KEY_ON;

	return keyStatus_Buf[0];
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
