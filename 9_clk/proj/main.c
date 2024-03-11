#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "MCIMX6Y2.h"
#include "led.h"
#include "delay.h"
#include "clk.h"
#include "key.h"

void init() {
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	Key_Init();
}

int main(void) {
	init();

	while(1) {	
		if (GetKeyStatus() == ON) {
			led_flip();
			while (GetKeyStatus() == ON);
		}
	}
	return 0;
}
