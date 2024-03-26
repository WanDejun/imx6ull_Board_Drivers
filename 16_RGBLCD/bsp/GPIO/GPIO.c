#include "GPIO.h"
#include "fsl_iomuxc.h"

void GPIO_Init(uint32_t muxRegister, uint32_t muxMode, uint32_t inputRegister, uint32_t inputDaisy,
						 uint32_t configRegister, GPIO_InitTypeDef* GPIO_InitStructure) {
	uint32_t config = 0;
	config |= (GPIO_InitStructure->HYS << 16);
    config |= (GPIO_InitStructure->PUS << 14);
    config |= (GPIO_InitStructure->PUE << 13);
    config |= (GPIO_InitStructure->PKE << 12);

    config |= (GPIO_InitStructure->ODE << 11);
    config |= (GPIO_InitStructure->SPEED << 6);
    config |= (GPIO_InitStructure->DSE << 3);
    config |= (GPIO_InitStructure->SRE);

	IOMUXC_SetPinMux(muxRegister, muxMode, inputRegister, inputDaisy, configRegister, GPIO_InitStructure->SION);
	IOMUXC_SetPinConfig(muxRegister, muxMode, inputRegister, inputDaisy, configRegister, config);
}

void GPIO_WriteBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x, BitAction_t BitAction) {
    if (BitAction)
        GPIO_Port->DR |= GPIO_Pin_x;
    else 
        GPIO_Port->DR &= (~GPIO_Pin_x);
}

void GPIO_WriteBits(GPIO_Type* GPIO_Port, unsigned int BitActions) {
    GPIO_Port->DR = BitActions;
}

BitAction_t GPIO_ReadBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x) {
    return GPIO_Port->PSR & GPIO_Pin_x ? BitSet : BitReset;
}

unsigned int GPIO_ReadBits(GPIO_Type* GPIO_Port) {
    return GPIO_Port->PSR;
}

/* 使能指定IO中断 */
void GPIO_IT_Enable(GPIO_Type* base, uint32_t GPIO_pin_n) {
	base->IMR |= GPIO_pin_n;
}

/* 关闭指定IO中断 */
void GPIO_IT_Disable(GPIO_Type* base, uint32_t GPIO_pin_n) {
	base->IMR &= ~GPIO_pin_n;
}

/* 清除标志位, 写1清除 */
void GPIO_ClearITFlag(GPIO_Type* base, uint32_t GPIO_pin_n) {
	base->ISR |= GPIO_pin_n;
}

/* 读取标志位, 高电平表示中断触发 */
int GPIO_GetITFlag(GPIO_Type* base, uint32_t GPIO_pin_n) {
	return base->ISR &= GPIO_pin_n ? 1 : 0;
}

void GPIO_IT_Config(GPIO_Type* base, uint32_t GPIO_pin_n, gpio_interupt_mode_t IT_mode) {
    uint32_t pin;
    for (pin = 0; GPIO_pin_n != 1; pin++, GPIO_pin_n >>= 1);
    
    uint32_t icrShift = pin;
    __IO uint32_t* icr = pin < 0x10 ? &(base->ICR1) : (icrShift &= 0xf, icr = &(base->ICR2));

    base->EDGE_SEL &= ~(1 << pin);
    icrShift <<= 1;

    switch (IT_mode) {
    case GPIO_IntLowLevel:
        *(icr) &= ~(3 << icrShift);
        break;
    case GPIO_IntHighLevel:
        *(icr) &= ~(3 << icrShift);
        *(icr) |= 1 << icrShift;
        break;
    case GPIO_IntRisingEdge:
        *(icr) &= ~(3 << icrShift);
        *(icr) |= 2 << icrShift;
        break;
    case GPIO_IntFallingEdge:
        *(icr) &= ~(3 << icrShift);
        *(icr) |= 3 << icrShift;
        break;
    default:
        base->EDGE_SEL |= (1 << pin);
        break;
    }
}
