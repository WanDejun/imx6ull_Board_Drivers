#ifndef __EPIT_H
#define __EPIT_H
#include "config.h"

void EPIT_Init(uint32_t prescalar, uint32_t value);
void EPIT_ClearITFlag(void);
void EPIT_Cmd(uint32_t cmd);

#endif
