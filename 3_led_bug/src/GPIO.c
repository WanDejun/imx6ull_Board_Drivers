#include "../inc/GPIO.h"

void IOMUX_SW_MUX_Init(IOMUX_SW_MUX_InitTypeDef* IOMUX_SW_MUX_InitStructure, volatile unsigned int* IO) {
    *(IO) &= 0x00000000;
    *(IO) |= (IOMUX_SW_MUX_InitStructure->SION << 4);
    *(IO) |= (IOMUX_SW_MUX_InitStructure->MUX_MODE);
}

void IOMUX_SW_PAD_Init(IOMUX_SW_PAD_InitTypeDef* IOMUX_SW_PAD_InitStructure, volatile unsigned int* IO) {
    *(IO) &= 0x00000000;
    *(IO) |= (IOMUX_SW_PAD_InitStructure->HYS << 16);
    *(IO) |= (IOMUX_SW_PAD_InitStructure->PUS << 14);
    *(IO) |= (IOMUX_SW_PAD_InitStructure->PUE << 13);
    *(IO) |= (IOMUX_SW_PAD_InitStructure->PKE << 12);

    *(IO) |= (IOMUX_SW_PAD_InitStructure->ODE << 11);
    *(IO) |= (IOMUX_SW_PAD_InitStructure->SPEED << 6);
    *(IO) |= (IOMUX_SW_PAD_InitStructure->DSE << 3);
    *(IO) |= (IOMUX_SW_PAD_InitStructure->SRE);
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
    return GPIO_Port->PSR & GPIO_Pin_x;
}

unsigned int GPIO_ReadBits(GPIO_Type* GPIO_Port) {
    return GPIO_Port->PSR;
}
