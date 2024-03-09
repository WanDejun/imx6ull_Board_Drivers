#include "config.h"
#include "GPIO.h"
#include "CCM.h"

void clock_init(){
    // 初始化外设时钟
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

void led_init() {
    IOMUX_SW_MUX_InitTypeDef IOMUX_SW_MUX_InitStructure;

    IOMUX_SW_MUX_InitStructure.SION = GPIO_SION_OFF;
    IOMUX_SW_MUX_InitStructure.MUX_MODE = GPIO_ALT5;

    IOMUX_SW_MUX_Init(&IOMUX_SW_MUX_InitStructure, &(IOMUX_SW_MUX->GPIO1_IO03));

    IOMUX_SW_PAD_InitTypeDef IOMUX_SW_PAD_InitStructure;
    IOMUX_SW_PAD_InitStructure.HYS = GPIO_HYS_ON;
    IOMUX_SW_PAD_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    IOMUX_SW_PAD_InitStructure.PUE = GPIO_PUE_1_Pull;
    IOMUX_SW_PAD_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    IOMUX_SW_PAD_InitStructure.ODE = GPIO_OD_Disabled;
    IOMUX_SW_PAD_InitStructure.SPEED = GPIO_SPEED_0_low_50MHz_;
    IOMUX_SW_PAD_InitStructure.DSE = GPIO_DSE_5_R0_5;
    IOMUX_SW_PAD_InitStructure.SRE = GPIO_SRE_0_Slow_Slew_Rate;

    IOMUX_SW_PAD_Init(&IOMUX_SW_PAD_InitStructure, &(IOMUX_SW_PAD->GPIO1_IO03));
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