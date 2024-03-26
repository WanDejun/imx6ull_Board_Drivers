#include "config.h"
#include "led.h"
#include "delay.h"
#include "clk.h"
#include "key.h"
#include "int.h"
#include "EXTI.h"
#include "EPIT.h"
#include "UART.h"
#include "UART_print.h"
#include "stdio.h"

void init() {
	ARM_clk_init(); 		/* 系统时钟 */
	clk_enable();			/* 使能所有的时钟 */
	delay_Init();
	int_Init();				/* 中断初始化 */

	led_init();				/* 初始化led */
	UART_print_Init(UART1);
	//EXTI_Init();
	//EPIT_Init(65, 5000);	/* 定时器初始化 */
	//Key_Init();				/* 按键初始化 */
}

int main(void) {
	init();

	char c;
	while(1) {	
		printf("Hello, input a char:\n");
		c = getc();
		printf("%c", c);
		printf("%c", '\n');
	}

	return 0;
}
