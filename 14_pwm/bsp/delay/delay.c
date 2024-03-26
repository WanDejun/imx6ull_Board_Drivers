#include "config.h"
#include "delay.h"

void delay_Init(void) {
	GPT2->CR = 0;
	GPT2->CR = (1 << 1) | (1 << 6) | (1 << 9);
	GPT2->PR = 66 - 1;

	GPT2->CR |= 1;
}

inline void delay_us(uint32_t microsecond) {
	uint32_t st = GPT2->CNT, ed, t;
	while (1) {
		if (GPT2->CNT - st >= microsecond) break;
	}
}

inline void delay_ms(uint32_t millisecond) {
	while(millisecond--) 	{
		delay_us(1000);
	}
}
