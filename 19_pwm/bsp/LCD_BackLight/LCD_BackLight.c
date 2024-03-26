#include "LCD_BackLight.h"
#include "GPIO.h"
#include "int.h"
#include "PWM.h"

uint16_t LCD_PWM_Sample;

void LCD_BackLight_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.SION = GPIO_SION_ON;

    GPIO_InitStructure.HYS = GPIO_HYS_ON;
    GPIO_InitStructure.PUS = GPIO_PUS_2_100K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_1_medium_100MHz;  // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_1_R0_1;               // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_1_Fast_Slew_Rate;     // 压摆率

    GPIO_Init(IOMUXC_GPIO1_IO08_PWM1_OUT, &GPIO_InitStructure);

    /* PWM初始化 */
    LCD_BackLightSet(5000);
    PWM_Init(PWM1, 10000, LCD_PWM_Sample);
    
    /* 使能FIFO空中断 */
    PWM1->PWMIR |= 1 << 0;
    PWM1->PWMSR |= (0xff << 3);

    void PWM1_IRQnHandler(uint32_t gicciar, void *param);
	GIC_EnableIRQ(PWM1_IRQn); // 开启GIC中断通道
	system_register_irqhandler(PWM1_IRQn, PWM1_IRQnHandler, NULL); // 注册中断向量表 
    
    PWM_ENABLE(PWM1, ENABLE);
}

/** 
 * @功能: 设置亮度值 
 * @输入: val 亮度值 取值:0-99
 * @输出: 空
 **/
inline void LCD_BackLightSet(uint16_t val) {
    if (val > 9999) val = 9999;
    LCD_PWM_Sample = val;
}

/* 中断服务函数 */
void PWM1_IRQnHandler(uint32_t gicciar, void *param) {
    if (PWM1->PWMSR & (1 << 3)) {
        PWM_SetSample(PWM1, LCD_PWM_Sample);
        PWM_SetSample(PWM1, LCD_PWM_Sample);

        PWM1->PWMSR |= (1 << 3);
    }
}
