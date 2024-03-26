#include "config.h"
#include "led.h"
#include "delay.h"
#include "clk.h"
#include "key.h"
#include "int.h"
#include "EXTI.h"

void init() {
	ARM_clk_init(); 	/* 系统时钟 */
	clk_enable();		/* 使能所有的时钟 */
	int_Init();			/* 中断初始化 */
	EXTI_Init();
	led_init();			/* 初始化led */
	Key_Init();			/* 按键初始化 */
}

int main(void) {
	init();

	while(1) {	

	}

	return 0;
}
