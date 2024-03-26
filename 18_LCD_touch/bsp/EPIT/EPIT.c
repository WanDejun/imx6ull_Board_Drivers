#include "EPIT.h"
#include "config.h"
#include "int.h"
#include "led.h"

void EPIT1_IRQn_Handler(uint32_t gicciar, void *param);

void EPIT_Init(uint32_t prescalar, uint32_t value) {
	/*时钟源为66Mhz的ipg_clk_root*/
	prescalar = prescalar > 0x3fff ? 0x3fff : prescalar;

	EPIT1->CR |= (1 << 1) | (1 << 2) | (1 << 3) | (prescalar << 4) | (1 << 24);

	EPIT1->LR = value; // 重装值
	EPIT1->CMPR = 0; // 比较值

	system_register_irqhandler(EPIT1_IRQn, EPIT1_IRQn_Handler, NULL); // 注册中断向量表
	GIC_EnableIRQ(EPIT1_IRQn);
}

void EPIT_ClearITFlag(void) {
	EPIT1->SR |= 1;
}

void EPIT_Cmd(uint32_t cmd) {
	if (cmd) {
		EPIT1->CR |= 1;
	}
	else {
		EPIT1->CR &= ~1;
	}
}
