#ifndef __RGBLCD_H
#define __RGBLCD_H

#include "config.h"
#include "rgblcd_api.h"

/* 屏幕ID */
#define ATK4342		0X4342	/* 4.3寸480*272 	*/
#define ATK4384		0X4384	/* 4.3寸800*480 	*/
#define ATK7084		0X7084	/* 7寸800*480 		*/
#define ATK7016		0X7016	/* 7寸1024*600 		*/
#define ATK1018		0X1018	/* 10.1寸1280*800 	*/
#define ATKVGA		0xff00 /* VGA */

/* LCD显存地址 */
#define LCD_FRAMEBUF_ADDR	(0x89000000)


/* rgblcd屏幕信息结构体 */
typedef struct 
{
    uint16_t height;
    uint16_t width;
    uint16_t pixsize;   // 每个像素的字节数
    uint16_t vspw; // 竖直vspw时间
    uint16_t vbpd; // 竖直vspw后等待时间
    uint16_t vfpd; // 竖直数据发送完之后等待时间
    uint16_t hspw; // 竖直vspw时间
    uint16_t hbpd; // 竖直vspw后等待时间
    uint16_t hfpd; // 竖直数据发送完之后等待时间

    uint32_t frameBuffer; // 缓存起始地址
    color_t frontColor; //前景色
    color_t backColor; //背景色
} rgblcd_typedef;



void rgblcd_Init();
uint16_t rgblcd_read_panelid();

void rgblcd_reset(void);
void rgblcd_noreset(void);
void rgblcd_Cmd(uint32_t cmd);

#endif