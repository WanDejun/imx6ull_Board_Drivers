#include "config.h"
#include "led.h"
#include "delay.h"
#include "clk.h"
#include "key.h"
#include "int.h"
#include "EXTI.h"
#include "EPIT.h"

void init() {
	ARM_clk_init(); 		/* 系统时钟 */
	clk_enable();			/* 使能所有的时钟 */
	int_Init();				/* 中断初始化 */
	led_init();				/* 初始化led */
	// EXTI_Init();
	EPIT_Init(65, 500000);	/* 定时器初始化 */
	EPIT_Cmd(Enable);
	// Key_Init();				/* 按键初始化 */
}

int main(void) {
	init();

	while(1) {	

	}

	return 0;
}
