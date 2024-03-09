#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "MCIMX6Y2.h"
#include "led.h"

void clk_enable(void) {
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

void delay_short(volatile unsigned int n) {
	while(n--){}
}

void delay(volatile unsigned int n) {
	while(n--) 	{
		delay_short(0x7ff);
	}
}

/*
 * @description	: mian函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void) {
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/

	while(1) {	
		led_off();		/* 关闭LED 			*/
		delay(500);		/* 延时500ms 			*/

		led_on();		/* 打开LED 			*/
		delay(500);		/* 延时500ms 			*/
	}
	return 0;
}
