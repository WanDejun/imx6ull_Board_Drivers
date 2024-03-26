#ifndef __KEY_H
#define __KEY_H
#include "cc.h"
#include "MCIMX6Y2.h"

#define KEY0 GPIO_Pin_18

typedef enum {
	KEY_OFF = OFF,
	KEY_ON = ON
} KeyStatus;

void Key_Init();
KeyStatus GetKeyStatus();

#endif
