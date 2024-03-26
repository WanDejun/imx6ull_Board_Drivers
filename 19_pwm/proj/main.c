#include "EPIT.h"
#include "EXTI.h"
#include "UART.h"
#include "UART_print.h"
#include "clk.h"
#include "config.h"
#include "delay.h"
#include "int.h"
#include "key.h"
#include "led.h"
#include "rgblcd.h"
#include "rgblcd_api.h"
#include "stdio.h"
#include "gt9147.h"
#include "LCD_BackLight.h"

/*
 * @description	: 使能I.MX6U的硬件NEON和FPU
 * @param 		: 无
 * @return 		: 无
 */
 void imx6ul_hardfpu_enable(void) {
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);
	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);
}

void init() {
    ARM_clk_init(); /* 系统时钟 */
    clk_enable();   /* 使能所有的时钟 */
    int_Init();     /* 中断初始化 */
    delay_Init();
    imx6ul_hardfpu_enable();

    led_init(); /* 初始化led */
    UART_print_Init(UART1);
    rgblcd_Init();
    // EXTI_Init();
    EPIT_Init(65, 500000);	/* 定时器初始化 */
	EPIT_Cmd(ENABLE);
    gt9147_Init();
    LCD_BackLight_Init();
    // Key_Init();				/* 按键初始化 */
}

int main(void) {
    init();

    uint16_t i, x, y;

    while (1) {
        for (i = 0; i < gt9147_dev.point_num; i++) {
            x = gt9147_dev.x[i]; 
            y = gt9147_dev.y[i];
            if (x != 0 || y != 0) {
                rgblcd_DrawCircle(x, y, 40, 1, RGBLCD_YELLOW);
            }
        }
        delay_ms(10);
        rgblcd_Clear();
    }

    return 0;
}
