#include "config.h"
#include "GPIO.h"
#include "CCM.h"

void clock_init(){
    // 初始化外设时钟
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

void led_init() {
    // 初始化GPIO
    *(IOMUXC_SW_MUX_CTL_PAD_GPIO_IO03) = 0x05; // 引脚复用
    *(IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03) = 0x10b0; // 电气属性
    *(GPIO1_GDIR) = 0x08;
}

void init() {
    clock_init();
    led_init();
}

int main() {
    init();

    // 设置led闪烁
    int i;

    
    while (1) {
        GPIO_SetBit(GPIO1, GPIO_Pin_3, BitReset);

        for (i = 0; i < 0xfffff; i++);

        GPIO_SetBit(GPIO1, GPIO_Pin_3, BitSet);

        for (i = 0; i < 0xfffff; i++);
    }

    return 0;
}