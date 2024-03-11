#include "led.h"
#include "gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "MCIMX6Y2.h"
/*
 * @description	: 初始化LED对应的GPIO
 * @param 		: 无
 * @return 		: 无
 */
void led_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_OFF;

	GPIO_InitStructure.HYS = GPIO_HYS_OFF;
    GPIO_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_0_low_50MHz_; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_0_output_driver_disabled_; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_0_Slow_Slew_Rate; // 压摆率
	GPIO_Init(IOMUXC_GPIO1_IO01_GPIO1_IO01, &GPIO_InitStructure);

	/* 3、初始化GPIO */
	GPIO1->GDIR = 0X0000008;	/* GPIO1_IO03设置为输出 */

	/* 4、设置GPIO1_IO03输出高电平，关闭LED0 */	
	GPIO1->DR |= (1 << 3); 
}

void led_on(void) {
	GPIO1->DR &= ~(1 << 3); 
}

void led_off(void) {
	GPIO1->DR |= (1 << 3); 
}

void led_flip(void) {
	GPIO1->DR ^= (1 << 3); 
}
