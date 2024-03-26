#include "key.h"
#include "GPIO.h"
#include "fsl_iomuxc.h"
#include "delay.h"
#include "int.h"
#include "led.h"

static const uint32_t key[1] = { KEY0 };
KeyStatus keyStatus_Buf[1];

void Key_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_OFF;

	GPIO_InitStructure.HYS = GPIO_HYS_ON;
    GPIO_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_0_low_50MHz; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_0_output_driver_disabled; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_0_Slow_Slew_Rate; // 压摆率

	GPIO_Init(IOMUXC_UART1_CTS_B_GPIO1_IO18, &GPIO_InitStructure);

	/* 3、初始化GPIO */
	GPIO1->GDIR &= ~(key[0]);
}

inline KeyStatus GetKeyStatus() {
	return keyStatus_Buf[0];
}

