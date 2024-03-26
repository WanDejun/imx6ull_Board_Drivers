#include "config.h"
#include "led.h"
#include "delay.h"
#include "clk.h"
#include "key.h"
#include "int.h"
#include "EXTI.h"
#include "EPIT.h"
#include "pwm.h"

void init() {
	ARM_clk_init(); 		/* 系统时钟 */
	clk_enable();			/* 使能所有的时钟 */
	delay_Init();
	int_Init();				/* 中断初始化 */
	led_init();				/* 初始化led */
	pwm_Init();
	//EXTI_Init();
	//EPIT_Init(65, 5000);	/* 定时器初始化 */
	//Key_Init();				/* 按键初始化 */
}

int main(void) {
	init();

	while(1) {	
		// led_flip();
		// delay_ms(500);
		// led_flip();
		// delay_ms(500);
	}

	return 0;
}
