#include "pwm_by_GPT.h"
#include "int.h"
#include "config.h"
#include "GPIO.h"

void pwm_by_GPT_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_OFF;
	
	/*PAD 输入配置*/
	GPIO_InitStructure.HYS = GPIO_HYS_OFF;
    GPIO_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /* 输出配置 */
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_1_medium_100MHz; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_5_R0_5; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_1_Fast_Slew_Rate; // 压摆率
	GPIO_Init(IOMUXC_GPIO1_IO02_GPT1_COMPARE2, &GPIO_InitStructure);

	GPT1->CR = 0;
	GPT1->CR = (1 << 1) | (1 << 6) | (1 << 23);
	GPT1->PR = 66 - 1; // 66分频 -> 2Mhz

	GPT1->OCR[0] = 200 - 1;
	GPT1->OCR[1] = 50; // 占空比

	void GPT1_IRQn_Handler(uint32_t gicciar, void *param);
	system_register_irqhandler(GPT1_IRQn, GPT1_IRQn_Handler, NULL);
	GIC_EnableIRQ(GPT1_IRQn);
	
	GPT1->IR |= (1 << 0); // OF1中断
	GPT1->CR |= 1; // 使能GPT1
}
