#include "GPIO.h"

void GPIO_SetBit(volatile unsigned int* GPIO_Port, unsigned int GPIO_Pin, BitAction_t BitAction) {
    if (BitAction) {
        *(GPIO_Port) |= GPIO_Pin;
    }
    else {
        *(GPIO_Port) &= ~(GPIO_Pin);
    }
}

void GPIO_SetBits(volatile unsigned int* GPIO_Port, unsigned int BitActions) {
    *(GPIO_Port) = BitActions;
}

BitAction_t GPIO_ReadBit(volatile unsigned int* GPIO_Port, unsigned int GPIO_Pin) {
    return *(GPIO_Port) & (GPIO_Pin);
}
unsigned int GPIO_ReadBits(volatile unsigned int* GPIO_Port) {
    return *(GPIO_Port);
}