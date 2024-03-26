#include "rgblcd.h"
#include "GPIO.h"
#include "config.h"
#include "stdio.h"
#include "delay.h"
#include "rgblcd_api.h"

rgblcd_typedef rgblcd_device;

void rgblcdIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_OFF;

	GPIO_InitStructure.HYS = GPIO_HYS_OFF;
    GPIO_InitStructure.PUS = GPIO_PUS_0_100K_Ohm_Pull_Down;
    GPIO_InitStructure.PUE = GPIO_PUE_0_Keeper;
    GPIO_InitStructure.PKE = GPIO_PKE_0_Pull_Keeper_Disabled;

    /*PAD 输出配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_3_max_200MHz; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_7_R0_7; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_1_Fast_Slew_Rate; // 压摆率
	
    /* LCD_Data引脚初始化 */
   	GPIO_Init(IOMUXC_LCD_DATA00_LCDIF_DATA00, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA01_LCDIF_DATA01, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA02_LCDIF_DATA02, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA03_LCDIF_DATA03, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA04_LCDIF_DATA04, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA05_LCDIF_DATA05, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA06_LCDIF_DATA06, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA07_LCDIF_DATA07, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA08_LCDIF_DATA08, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA09_LCDIF_DATA09, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA10_LCDIF_DATA10, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA11_LCDIF_DATA11, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA12_LCDIF_DATA12, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA13_LCDIF_DATA13, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA14_LCDIF_DATA14, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA15_LCDIF_DATA15, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA16_LCDIF_DATA16, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA17_LCDIF_DATA17, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA18_LCDIF_DATA18, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA19_LCDIF_DATA19, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA20_LCDIF_DATA20, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA21_LCDIF_DATA21, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA22_LCDIF_DATA22, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA23_LCDIF_DATA23, &GPIO_InitStructure);

	GPIO_Init(IOMUXC_LCD_CLK_LCDIF_CLK, &GPIO_InitStructure);	
	GPIO_Init(IOMUXC_LCD_ENABLE_LCDIF_ENABLE, &GPIO_InitStructure);	
	GPIO_Init(IOMUXC_LCD_HSYNC_LCDIF_HSYNC, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_VSYNC_LCDIF_VSYNC, &GPIO_InitStructure);

    /* 背光初始化 */
    GPIO_Init(IOMUXC_GPIO1_IO08_GPIO1_IO08, &GPIO_InitStructure);
    GPIO1->GDIR |= (1 << 8);
    GPIO_WriteBit(GPIO1, GPIO_Pin_8, 1);
}

void lcdclk_init(uint32_t loopDiv, uint32_t preDiv, uint32_t div);

void rgblcd_Init() {
    uint16_t rgblcdID = rgblcd_read_panelid();
    printf("LCD_ID = Ox%x\r\n", rgblcdID);
    
    rgblcdIO_Init();

    rgblcd_reset();
    delay_ms(10);
    rgblcd_noreset();

    /* TFTLCD参数结构体初始化 */
	switch (rgblcdID) {
    case (ATK4342):
		rgblcd_device.height = 272;	
		rgblcd_device.width = 480;
		rgblcd_device.vspw = 1;
		rgblcd_device.vbpd = 8;
		rgblcd_device.vfpd = 8;
		rgblcd_device.hspw = 1;
		rgblcd_device.hbpd = 40;
		rgblcd_device.hfpd = 5; 	
		lcdclk_init(27, 8, 8);	/* 初始化LCD时钟 10.1MHz */
        break;
    case (ATK4384):
		rgblcd_device.height = 480;	
		rgblcd_device.width = 800;
		rgblcd_device.vspw = 3;
		rgblcd_device.vbpd = 32;
		rgblcd_device.vfpd = 13;
		rgblcd_device.hspw = 48;
		rgblcd_device.hbpd = 88;
		rgblcd_device.hfpd = 40;
		lcdclk_init(42, 4, 8);	/* 初始化LCD时钟 31.5MHz */
        break;
    case (ATK7084):
		rgblcd_device.height = 480;	
		rgblcd_device.width = 800;
		rgblcd_device.vspw = 1;
		rgblcd_device.vbpd = 23;
		rgblcd_device.vfpd = 22;
		rgblcd_device.hspw = 1;
		rgblcd_device.hbpd = 46;
		rgblcd_device.hfpd = 210;	
		lcdclk_init(30, 3, 7);	/* 初始化LCD时钟 34.2MHz */
        break;
    case (ATK7016):
		rgblcd_device.height = 600;	
		rgblcd_device.width = 1024;
		rgblcd_device.vspw = 3;
		rgblcd_device.vbpd = 20;
		rgblcd_device.vfpd = 12;
		rgblcd_device.hspw = 20;
		rgblcd_device.hbpd = 140;
		rgblcd_device.hfpd = 160;
		lcdclk_init(32, 3, 5);	/* 初始化LCD时钟 51.2MHz */
        break;
    case (ATK1018):
		rgblcd_device.height = 800;	
		rgblcd_device.width = 1280;
		rgblcd_device.vspw = 3;
		rgblcd_device.vbpd = 10;
		rgblcd_device.vfpd = 10;
		rgblcd_device.hspw = 10;
		rgblcd_device.hbpd = 80;
		rgblcd_device.hfpd = 70;
		lcdclk_init(35, 3, 5);	/* 初始化LCD时钟 56MHz */
        break;
    default:
		rgblcd_device.height = 768;	
		rgblcd_device.width = 1366;
		rgblcd_device.vspw = 3;
		rgblcd_device.vbpd = 24;
		rgblcd_device.vfpd = 3;
		rgblcd_device.hspw = 143;
		rgblcd_device.hbpd = 213;
		rgblcd_device.hfpd = 70;
		lcdclk_init(32, 3, 3);	/* 初始化LCD时钟 85MHz */
	}

	rgblcd_device.pixsize = 4;				/* ARGB8888模式，每个像素4字节 */
	rgblcd_device.frameBuffer = LCD_FRAMEBUF_ADDR;	
	rgblcd_device.backColor = RGBLCD_WHITE;	/* 背景色为白色 */
	rgblcd_device.frontColor = RGBLCD_BLACK;	/* 前景色为黑色 */


    LCDIF->CTRL = (1 << 19) | (1 << 17) | (3 << 10) | (3 << 8) | (1 << 5);

    LCDIF->CTRL1 = (7 << 16);

    LCDIF->TRANSFER_COUNT = (rgblcd_device.height << 16)| rgblcd_device.width; // 行列数

    LCDIF->VDCTRL0 = rgblcd_device.vspw | (1 << 20) | (1 << 21) | (1 << 24) | (1 << 28);

    LCDIF->VDCTRL1 = rgblcd_device.vspw + rgblcd_device.vbpd + rgblcd_device.height + rgblcd_device.vfpd;
   
    LCDIF->VDCTRL2 =    (rgblcd_device.hspw + rgblcd_device.hbpd + rgblcd_device.width + rgblcd_device.hfpd) | 
                        (rgblcd_device.hspw << 18);

    LCDIF->VDCTRL3 = (rgblcd_device.vspw + rgblcd_device.vbpd) | ((rgblcd_device.hbpd + rgblcd_device.hspw) << 16);

    LCDIF->VDCTRL4 = (rgblcd_device.width) | (1 << 18);

    LCDIF->CUR_BUF = rgblcd_device.frameBuffer;
    LCDIF->NEXT_BUF = rgblcd_device.frameBuffer;

    rgblcd_Cmd(ENABLE);
    delay_ms(10);
    rgblcd_Clear();
}

/* 读取屏幕id */
uint16_t rgblcd_read_panelid() {
    /* 打开模拟开关 设置lcd_vsync为高电平 */
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_ON;

	GPIO_InitStructure.HYS = GPIO_HYS_OFF;
    GPIO_InitStructure.PUS = GPIO_PUS_1_47K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_0_Keeper;
    GPIO_InitStructure.PKE = GPIO_PKE_0_Pull_Keeper_Disabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_2_medium_100MHz; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_6_R0_6; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_0_Slow_Slew_Rate; // 压摆率
	
    GPIO_Init(IOMUXC_LCD_VSYNC_GPIO3_IO03, &GPIO_InitStructure);

    GPIO3->GDIR |= 1 << 3;
    GPIO_WriteBit(GPIO3, GPIO_Pin_3, 1);

    GPIO_InitStructure.PUS = GPIO_PUS_3_22K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;
    GPIO_InitStructure.DSE = GPIO_DSE_0_output_driver_disabled; // 输出驱动能力

	GPIO_Init(IOMUXC_LCD_DATA07_GPIO3_IO12, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA15_GPIO3_IO20, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_LCD_DATA23_GPIO3_IO28, &GPIO_InitStructure);
    GPIO3->GDIR &= ~(1 << 12 | 1 << 20 | 1 << 28);

    uint16_t idx = 0;
    idx |= GPIO_ReadBit(GPIO3, GPIO_Pin_28);
    idx |= GPIO_ReadBit(GPIO3, GPIO_Pin_20) << 1;
    idx |= GPIO_ReadBit(GPIO3, GPIO_Pin_12) << 2;

    switch (idx) {
    case 0:
        return ATK4342;
        break;
    case 1:
        return ATK7084;
        break;
    case 2:
        return ATK7016;
        break;
    case 4:
        return ATK4384;
        break;
    case 5:
        return ATK1018;
        break;
    default:
        break;
    }

    return idx;
}

void rgblcd_reset(void)
{
	LCDIF->CTRL |= 1 << 31; /* 强制复位 */
}

/*
 * @description	: 结束复位ELCDIF接口
 * @param 		: 无
 * @return 		: 无
 */
void rgblcd_noreset(void)
{
	LCDIF->CTRL &= 0 << 31; /* 取消强制复位 */
}

void rgblcd_Cmd(uint32_t cmd) {
    if (cmd)
        LCDIF->CTRL |= 1;
    else 
        LCDIF->CTRL &= ~1;
}

