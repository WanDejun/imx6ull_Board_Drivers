#ifndef __PWM_H
#define __PWM_H

#include "config.h"

void PWM_Init(PWM_Type* PWMx, uint32_t Preiod, uint32_t Sample);
inline void PWM_ENABLE(PWM_Type* PWMx, uint8_t cmd);
inline void PWM_SetPreiod(PWM_Type* PWMx, uint32_t Preiod);
inline void PWM_SetSample(PWM_Type* PWMx, uint32_t Sample);

#endif 
