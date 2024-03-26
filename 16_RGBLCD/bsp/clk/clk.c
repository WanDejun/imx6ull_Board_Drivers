#include "clk.h"
#include "MCIMX6Y2.h"

void clk_enable(void) {
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

void ARM_clk_init() {
	if((((CCM->CCSR) >> 2) & 0x1 ) == 0) 	/* 当前pll1_sw_clk使用的pll1_main_clk*/
	{	
		CCM->CCSR &= ~(1 << 8);				/* 配置step_clk时钟源为24MH OSC */	
		CCM->CCSR |= (1 << 2);				/* 配置pll1_sw_clk时钟源为step_clk */
	}
	
	CCM_ANALOG->PLL_ARM &= ~(0x7f); // 清空低 7 位
	CCM_ANALOG->PLL_ARM |= (82 | (1 << 13)); // 设置 pll1_main_clk(PLL1) 倍频

	CCM->CCSR &= ~(1 << 2); // pll1_sw_clk 选择为 pll1_main_clk
	CCM->CACRR = 0; // ARM_CLK_ROOT二分频

	uint32_t reg = 0;

	// 初始化PLL2_PFD
	reg = CCM_ANALOG->PFD_528;
	reg &= ~(0x3f3f3f3f); 
	reg |= (27 << 0); // PLL2_PFD0 = 352MHz
	reg |= (16 << 8); // PLL2_PFD1 = 594MHz
	reg |= (24 << 16); // PLL2_PFD2 = 369MHz
	reg |= (32 << 24); // PLL2_PFD3 = 297MHz
	CCM_ANALOG->PFD_528 = reg;

	// 初始化PLL3_PFD
	reg = CCM_ANALOG->PFD_480;
	reg &= ~(0x3f3f3f3f); 
	reg |= (12 << 0); // PLL3_PFD0 = 720MHz
	reg |= (16 << 8); // PLL3_PFD1 = 540MHz
	reg |= (17 << 16); // PLL3_PFD2 = 508MHz
	reg |= (19 << 24); // PLL3_PFD3 = 454.7MHz
	CCM_ANALOG->PFD_480 = reg;

	// 初始化AHB_CLK_ROOT = 132MHz
	CCM->CBCMR &= ~(3 << 18); // 清零
	CCM->CBCMR |= 1 << 18; // 设置pre_periph_clock = PLL2_PFD2 = 396MHz

	CCM->CBCDR &= ~(7 << 10); // CBCDR[AHB_PODF]3分频
	while (CCM->CDHIPR & (1 << 1)); // 等待AHB_PODF设置完成
	CCM->CBCDR |= 2 << 10; 
	while (CCM->CDHIPR & (1 << 1)); // 等待AHB_PODF设置完成

	CCM->CBCDR &= ~(1 << 25); //PERIPH_CLK_SEL
	while (CCM->CDHIPR & (1 << 5)); // 等待PERIPH_CLK_SEL设置完成

	// 初始化PERCLK_CLK_ROOT = 66MHz
	CCM->CBCDR &= ~(3 << 8); // 清空CBCDR[IPG_PODF]
	CCM->CBCDR |= (1 << 8); // 设置 清空CBCDR[IPG_PODF] 2分频

	CCM->CSCMR1 &= ~(1 << 6); // 设置CSCMR1[PERCLK_CLK_SEL] 选择ipg clk root
	CCM->CSCMR1 &= ~(0x3f << 0); // CSCMR1[PERCLK_PODF] = 0 ,1分频
}


/*
	@ 功能: 设置lcdif外设时钟(VEDIO_PLL) = 24MHz * loopDiv / preDiv / div
	@ 输入: 
		loopDiv: DIV_SELECT (VEDIO_PLL分频值)
			范围: 27-54
		preDiv: 一级分频(LCDIF1_PRED)
			范围: 1-8
		div: 二级分频(LCDIF1_PRED)
			范围: 1-8
	@ 输出: 无
*/
void lcdclk_init(uint32_t loopDiv, uint32_t preDiv, uint32_t div) {
	/*不使用分数分频值*/
	CCM_ANALOG->PLL_VIDEO_NUM = 0; // 分子 = 1
	CCM_ANALOG->PLL_VIDEO_DENOM = 0; // 分母 = 1

	CCM_ANALOG->PLL_VIDEO = (1 << 13) | (2 << 19) | (loopDiv); // ENABLE_OUTPUT POST_DIV_SELECT DIV_SELECT

	CCM_ANALOG->MISC2 &= ~(3 << 30); // VIDEO_DIV = 0 (1分频)

	CCM->CSCDR2 &= ~(7 << 15);
	CCM->CSCDR2 |= (2 << 15); // 选择PLL5

	CCM->CSCDR2 &= ~(7 << 12); // 一级分频(LCDIF1_PRED)
	CCM->CSCDR2 |= ((preDiv - 1) << 12);

	CCM->CBCMR &= ~(7 << 23); // 二级分频(LCDIF1_PRED)
	CCM->CBCMR |= ((div - 1) << 23);

	CCM->CSCDR2 &= ~(7 << 9);
}
