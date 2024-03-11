#include "gpio.h"
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

void GPIO_SetBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x, BitAction_t BitAction) {
    if (BitAction)
        GPIO_Port->DR |= 1 << GPIO_Pin_x;
    else 
        GPIO_Port->DR &= ~(1 << GPIO_Pin_x);
}

void GPIO_SetBits(GPIO_Type* GPIO_Port, unsigned int BitActions) {
    GPIO_Port->DR = BitActions;
}

BitAction_t GPIO_ReadBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x) {
    return GPIO_Port->PSR & GPIO_Pin_x ? BitSet : BitReset;
}

unsigned int GPIO_ReadBits(GPIO_Type* GPIO_Port) {
    return GPIO_Port->PSR;
}
