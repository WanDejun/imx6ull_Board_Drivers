#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "MCIMX6Y2.h"
#include "led.h"
#include "delay.h"
#include "clk.h"
#include "key.h"

void init() {
	ARM_clk_init();
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	Key_Init();
}

int main(void) {
	init();

	while(1) {	
		led_flip();
		delay(200);
		led_flip();
		delay(200);
		led_flip();
		delay(200);
	}
	return 0;
}
