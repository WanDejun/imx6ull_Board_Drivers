#ifndef __KEY_H
#define __KEY_H
#include "cc.h"
#include "MCIMX6Y2.h"

typedef enum {
	KEY_OFF = OFF,
	KEY_ON = ON
} KeyStatus;

void Key_Init();
KeyStatus GetKeyStatus();

#endif
