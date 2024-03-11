#include "key.h"
#include "cc.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "delay.h"

static const uint32_t key[1] = {1 << 18};
KeyStatus keyStatus_Buf[1];

void Key_Init() {
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0x178B0);

	/* 3、初始化GPIO */
	GPIO1->GDIR &= ~key[0];
}

KeyStatus GetKeyStatus() {
	uint32_t t = (GPIO1->PSR & key[0]);
	delay(10);
	if (t == (GPIO1->PSR & key[0])) keyStatus_Buf[0] = t ? KEY_OFF : KEY_ON;

	return keyStatus_Buf[0];
}