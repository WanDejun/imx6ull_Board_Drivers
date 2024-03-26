#include "config.h"
#include "GPIO.h"
#include "UART.h"

void UART_print_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_OFF;

	GPIO_InitStructure.HYS = GPIO_HYS_OFF;
    GPIO_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_0_low_50MHz; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_6_R0_6; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_0_Slow_Slew_Rate; // 压摆率

	GPIO_Init(IOMUXC_UART1_RX_DATA_UART1_RX, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_UART1_TX_DATA_UART1_TX, &GPIO_InitStructure);

	UART_Init(UART1);
}

void putc(char c) {
	UART_putc(UART1, c);
}

char getc(void) {
	return UART_getc(UART1);
}

void puts(const char* str) {
	UART_puts(UART1, str);
}
