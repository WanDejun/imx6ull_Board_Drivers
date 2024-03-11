#include "led.h"
#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "MCIMX6Y2.h"
/*
 * @description	: 初始化LED对应的GPIO
 * @param 		: 无
 * @return 		: 无
 */
void led_init(void)
{
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO01_GPIO1_IO01, 0);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO01_GPIO1_IO01, 0x10B0);

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
