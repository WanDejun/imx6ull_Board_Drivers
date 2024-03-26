#include "PWM.h"

void PWM_Init(PWM_Type* PWMx, uint32_t Preiod, uint32_t Sample) {
    PWM1->PWMCR = 0;
    PWM1->PWMCR |= (1 << 16) | (65 << 4) | (1 << 26);
    
    PWM_SetPreiod(PWMx, Preiod);

    uint8_t i;
    for (i = 0; i < 4; i++) PWM_SetSample(PWMx, Sample);
}

inline void PWM_ENABLE(PWM_Type* PWMx, uint8_t cmd) {
    if (cmd) {
        PWMx->PWMCR |= (1 << 0);
    }
    else {
        PWMx->PWMCR &= ~(1 << 0);
    }
}

/* 设置PWM周期(Preiod寄存器) */
inline void PWM_SetPreiod(PWM_Type* PWMx, uint32_t Preiod) {
    uint32_t regval;
    if (Preiod < 2)
        regval = 2;
    else
        regval = Preiod - 2;

    PWMx->PWMPR = (regval & 0xffff);
}

/* 设置Sample寄存器(用于设置占空比) */
inline void PWM_SetSample(PWM_Type* PWMx, uint32_t Sample) { PWMx->PWMSAR = Sample; }