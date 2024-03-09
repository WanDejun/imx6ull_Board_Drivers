#ifndef __CCM_H
#define __CCM_H
/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	:	 imx6ul.h
作者	   : 左忠凯
版本	   : V1.0
描述	   : IMX6UL相关寄存器定义，参考STM32寄存器定义方法
其他	   : 无
日志	   : 初版V1.0 2019/1/3 左忠凯创建
**************************************************************/
/* 
 * CCM寄存器结构体定义，分为CCM和CCM_ANALOG 
 */
typedef struct  {
	volatile unsigned int CCR;
	volatile unsigned int CCDR;
	volatile unsigned int CSR;
	volatile unsigned int CCSR;
	volatile unsigned int CACRR;
	volatile unsigned int CBCDR;
	volatile unsigned int CBCMR;
	volatile unsigned int CSCMR1;
	volatile unsigned int CSCMR2;
	volatile unsigned int CSCDR1;
	volatile unsigned int CS1CDR;
	volatile unsigned int CS2CDR;
	volatile unsigned int CDCDR;
	volatile unsigned int CHSCCDR;
	volatile unsigned int CSCDR2;
	volatile unsigned int CSCDR3;	
	volatile unsigned int RESERVED_1[2];
	volatile unsigned int CDHIPR;  
	volatile unsigned int RESERVED_2[2];
	volatile unsigned int CLPCR;
	volatile unsigned int CISR;
	volatile unsigned int CIMR;
	volatile unsigned int CCOSR;
	volatile unsigned int CGPR;
	volatile unsigned int CCGR0;
	volatile unsigned int CCGR1;
	volatile unsigned int CCGR2;
	volatile unsigned int CCGR3;
	volatile unsigned int CCGR4;
	volatile unsigned int CCGR5;
	volatile unsigned int CCGR6;
	volatile unsigned int RESERVED_3[1];
	volatile unsigned int CMEOR;	
} CCM_Type; 

typedef struct {
	volatile unsigned int PLL_ARM;
	volatile unsigned int PLL_ARM_SET;
	volatile unsigned int PLL_ARM_CLR;
	volatile unsigned int PLL_ARM_TOG;
	volatile unsigned int PLL_USB1;
	volatile unsigned int PLL_USB1_SET;
	volatile unsigned int PLL_USB1_CLR;
	volatile unsigned int PLL_USB1_TOG;
	volatile unsigned int PLL_USB2;
	volatile unsigned int PLL_USB2_SET;
	volatile unsigned int PLL_USB2_CLR;
	volatile unsigned int PLL_USB2_TOG;
	volatile unsigned int PLL_SYS;
	volatile unsigned int PLL_SYS_SET;
	volatile unsigned int PLL_SYS_CLR;
	volatile unsigned int PLL_SYS_TOG;
	volatile unsigned int PLL_SYS_SS;
	volatile unsigned int RESERVED_1[3];
	volatile unsigned int PLL_SYS_NUM;
	volatile unsigned int RESERVED_2[3];
	volatile unsigned int PLL_SYS_DENOM; 
	volatile unsigned int RESERVED_3[3];
	volatile unsigned int PLL_AUDIO;
	volatile unsigned int PLL_AUDIO_SET;
	volatile unsigned int PLL_AUDIO_CLR;
	volatile unsigned int PLL_AUDIO_TOG;
	volatile unsigned int PLL_AUDIO_DENOM;
	volatile unsigned int RESERVED_4[3];
	volatile unsigned int PLL_VIDEO;
	volatile unsigned int PLL_VIDEO_SET;
	volatile unsigned int PLL_VIDEO_CLR;
	volatile unsigned int PLL_VIDEO_TOG;
	volatile unsigned int PLL_VIDEO_NUM;
	volatile unsigned int RESERVED_5[3];
	volatile unsigned int PLL_VIDEO_DENOM;
	volatile unsigned int RESERVED_6[7];
	volatile unsigned int PLL_ENET;
	volatile unsigned int PLL_ENET_SET;
	volatile unsigned int PLL_ENET_CLR;
	volatile unsigned int PLL_ENET_TOG;
	volatile unsigned int PFD_480;
	volatile unsigned int PFD_480_SET;
	volatile unsigned int PFD_480_CLR;
	volatile unsigned int PFD_480_TOG;
	volatile unsigned int PFD_528;
	volatile unsigned int PFD_528_SET;
	volatile unsigned int PFD_528_CLR;
	volatile unsigned int PFD_528_TOG;
	volatile unsigned int RESERVED_7[16];
	volatile unsigned int MISC0;
	volatile unsigned int MISC0_SET;
	volatile unsigned int MISC0_CLR;
	volatile unsigned int MISC0_TOG;
	volatile unsigned int MISC1;
	volatile unsigned int MISC1_SET;
	volatile unsigned int MISC1_CLR;
	volatile unsigned int MISC1_TOG;
	volatile unsigned int MISC2;
	volatile unsigned int MISC2_SET;
	volatile unsigned int MISC2_CLR;
	volatile unsigned int MISC2_TOG;
} CCM_ANALOG_Type; 


/* 
 * 外设指针 
 */
#define CCM_BASE					(0X020C4000)
#define CCM_ANALOG_BASE				(0X020C8000)
#define CCM					((CCM_Type *)CCM_BASE)
#define CCM_ANALOG			((CCM_ANALOG_Type *)CCM_ANALOG_BASE)

#endif
