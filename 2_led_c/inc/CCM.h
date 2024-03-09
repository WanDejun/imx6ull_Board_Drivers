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

#define CCM_BASE					(0X020C4000)
#define CCM_ANALOG_BASE				(0X020C8000)
/* 
 * 外设指针 
 */
#define CCM					((CCM_Type *)CCM_BASE)
#define CCM_ANALOG			((CCM_ANALOG_Type *)CCM_ANALOG_BASE)


/**********************CCG0***********************/
#define CCG0_aips_tz1_clock                 		0x00 << 1
#define CCG0_aips_tz2_clock                 		0x01 << 1
#define CCG0_apbhdma_hclk_clock             		0x02 << 1
#define CCG0_asrc_clock                     		0x03 << 1
// #define unused                           		0x04 << 1
#define CCG0_dcp_clock                      		0x05 << 1
#define CCG0_enet_clock                     		0x06 << 1
#define CCG0_can1_clock                     		0x07 << 1
#define CCG0_can1_serial_clock              		0x08 << 1
#define CCG0_can2_clock                     		0x09 << 1
#define CCG0_can2_serial_clock              		0x0a << 1
#define CCG0_CPU_debug_clock                		0x0b << 1
#define CCG0_gpt2_bus_clock                 		0x0c << 1
#define CCG0_gpt2_serial_clock              		0x0d << 1
#define CCG0_uart2_clock                    		0x0e << 1
#define CCG0_gpio2_clock                    		0x0f << 1


/**********************CCG1***********************/
#define CCG1_ecspi1_clock                   		0x00 << 1
#define CCG1_ecspi2_clock                   		0x01 << 1
#define CCG1_ecspi3_clock            				0x02 << 1
#define CCG1_ecspi4_clock                   		0x03 << 1
#define CCG1_adc2_clock                     		0x04 << 1
#define CCG1_uart3_clock                    		0x05 << 1
#define CCG1_epit1_clock                    		0x06 << 1
#define CCG1_epit2_clock                    		0x07 << 1
#define CCG1_adc1_serial_clock              		0x08 << 1
#define CCG1_sim_s_clock                    		0x09 << 1
#define CCG1_gpt_bus_clock              			0x0a << 1
#define CCG1_gpt_serial_clock						0x0b << 1
#define CCG1_uart4_clock 							0x0c << 1
#define CCG1_gpio1_clock              				0x0d << 1
#define CCG1_csu_clock                    			0x0e << 1
//#define unused									0x0f << 1


/**********************CCG2***********************/
#define CCG2_esai_clock								0x00 << 1
#define CCG2_csi_clock             					0x01 << 1
#define CCG2_iomuxc_snvs_clock              		0x02 << 1
#define CCG2_i2c1_serial_clock             			0x03 << 1
#define CCG2_i2c2_serial _clock             		0x04 << 1
#define CCG2_i2c3_serial_clock              		0x05 << 1
#define CCG2_OCOTP_CTRL_clock              			0x06 << 1
#define CCG2_iomux_ipt_clk_io_clock         		0x07 << 1
#define CCG2_ipmux1_clock             				0x08 << 1
#define CCG2_ipmux2_clock                			0x09 << 1
#define CCG2_ipmux3_clock                			0x0a << 1
#define CCG2_ipsync_ip2apb_tzasc1_ipg_clock 		0x0b << 1
// #define unused									0x0c << 1
#define CCG2_gpio3_clock                    		0x0d << 1
#define CCG2_lcd_clock                    			0x0e << 1
#define CCG2_pxp_clock                    			0x0f << 1


/**********************CCG3***********************/
// #define Reserved                       			0x00 << 1
#define CCG3_uart5_clock                    		0x01 << 1
#define CCG3_epdc_clock             				0x02 << 1
#define CCG3_uart6_clock                    		0x03 << 1
#define CCG3_CA7_CCM_DAP_clock             			0x03 << 1
#define CCG3_lcdif1_pix_clock         				0x05 << 1
#define CCG3_gpio4_clock             				0x06 << 1
#define CCG3_qspi_clock                     		0x07 << 1
#define CCG3_wdog1_serial_clock						0x08 << 1
#define CCG3_a7_clkdiv_patch_clock 					0x09 << 1
#define CCG3_mmdc_core_aclk_fast_core_p0_clock		0x0a << 1
// #define Reserved
#define CCG3_mmdc_core_ipg_clk_p0_clock         	0x0c << 1
#define CCG3_mmdc_core_ipg_clk_p1_clock       		0x0d << 1
#define CCG3_ocram_clock                    		0x0e << 1
#define CCG3_iomuxc_snvs_gpr_clock            		0x0f << 1


/**********************CCG4***********************/
// #define Reserved
#define CCG4_iomuxc_clock                       	0x01 << 1
#define CCG4_omuxc_gpr_clock             			0x02 << 1
#define CCG4_sim_cpu_clock                     		0x03 << 1
#define CCG4_cxapbsyncbridge_slave_clock			0x03 << 1
#define CCG4_tsc_dig_clock                      	0x05 << 1
#define CCG4_pl301_mx6qper1_mainclk_enable 			0x06 << 1
#define CCG4_pl301_mx6qper2_mainclk_enable			0x07 << 1
#define CCG4_pwm1_clock								0x08 << 1
#define CCG4_pwm2_clock 							0x09 << 1
#define CCG4_pwm3_clock								0x0a << 1
#define CCG4_pwm4_clock 							0x0b << 1
#define CCG4_rawnand_u_bch_input_apb_clock          0x0c << 1
#define CCG4_rawnand_u_gpmi_bch_input_bch_clock		0x0d << 1
#define CCG4_rawnand_u_gpmi_bch_input_gpmi_io_clock	0x0e << 1
#define CCG4_rawnand_u_gpmi_input_apb_clock     	0x0f <5 1


/**********************CCG5***********************/
#define CCG5_rom_clock                      		0x00 << 1
#define CCG5_sctr_clock                     		0x01 << 1
#define CCG5_snvs_dryice_clock             			0x02 << 1
#define CCG5_sdma_clock                     		0x03 << 1
#define CCG5_kpp_clock                     			0x04 << 1
#define CCG5_wdog2_clock                      		0x05 << 1
#define CCG5_spba_clock                     		0x06 << 1
#define CCG5_spdif_clock                     		0x07 << 1
#define CCG5_sim_main_clock              			0x08 << 1
#define CCG5_snvs_hp_clock                    	 	0x09 << 1
#define CCG5_snvs_lp_clock              			0x0a << 1
#define CCG5_sai3_clock                				0x0b << 1
#define CCG5_uart1_clock                 			0x0c << 1
#define CCG5_uart7_clock              				0x0d << 1
#define CCG5_sai1_clock                    			0x0e << 1
#define CCG5_sai2_clock                    			0x0f << 1

#endif
