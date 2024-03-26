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

void init() {
    ARM_clk_init(); /* 系统时钟 */
    clk_enable();   /* 使能所有的时钟 */
    int_Init();     /* 中断初始化 */
    delay_Init();

    led_init(); /* 初始化led */
    UART_print_Init(UART1);
    rgblcd_Init();
    // EXTI_Init();
    EPIT_Init(65, 500000);	/* 定时器初始化 */
	EPIT_Cmd(ENABLE);
    // Key_Init();				/* 按键初始化 */
}

int main(void) {
    init();

    rgblcd_SetBKColor(RGBLCD_RGB(0x66, 0xcc, 0xff));

    rgblcd_ClearArea(200, 80, 400, 320);

    rgblcd_ReverseArea(200, 80, 200, 320);

    rgblcd_ShowHexNum(20, 20, 0xffffffff, 8, 24, 1, 0x66ccff);

    rgblcd_DrawFastHLine(0, 200, 200, 0x33ff44);

    rgblcd_DrawFastVLine(700, 200, 200, 0x456789);

    rgblcd_DrawRectangle(600, 300, 50, 50, 1, 0x123456);

    rgblcd_DrawCircle(400, 420, 20, 0, 0x987654);

    delay_ms(5000);

	uint32_t state = 0, red = 0xff, green = 0, blue = 0, color = 0, i;
    while (1) {
		delay_ms(100);
        for (i = 800; i > 0; i--) {
            // Draw a vertical line 1 pixel wide in the selected colour
            rgblcd_DrawFastVLine(i, 0, 480, color);  // in this example tft.width() returns the pixel width of the display
            // This is a "state machine" that ramps up/down the colour brightnesses in sequence
            switch (state) {
                case 0:
                    green++;
                    if (green & 0x100) {
                        green = 0xff;
                        state = 1;
                    }
                    break;
                case 1:
                    red--;
                    if (red & 0x100) {
                        red = 0;
                        state = 2;
                    }
                    break;
                case 2:
                    blue++;
                    if (blue & 0x100) {
                        blue = 0xff;
                        state = 3;
                    }
                    break;
                case 3:
                    green--;
                    if (green & 0x100) {
                        green = 0;
                        state = 4;
                    }
                    break;
                case 4:
                    red++;
                    if (red & 0x100) {
                        red = 0xff;
                        state = 5;
                    }
                    break;
                case 5:
                    blue--;
                    if (blue & 0x100) {
                        blue = 0;
                        state = 0;
                    }
                    break;
            }
            color = red << 16 | green << 8 | blue;
        }
    }

    return 0;
}
