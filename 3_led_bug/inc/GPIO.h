#ifndef __GPIO_H
#define __GPIO_H

typedef enum {
    BitReset = 0,
    BitSet = !BitReset,
} BitAction_t;

/* 
 * IOMUX寄存器组
 */
typedef struct {
	volatile unsigned int BOOT_MODE0;
	volatile unsigned int BOOT_MODE1;
	volatile unsigned int SNVS_TAMPER0;
	volatile unsigned int SNVS_TAMPER1;
	volatile unsigned int SNVS_TAMPER2;
	volatile unsigned int SNVS_TAMPER3;
	volatile unsigned int SNVS_TAMPER4;
	volatile unsigned int SNVS_TAMPER5;
	volatile unsigned int SNVS_TAMPER6;
	volatile unsigned int SNVS_TAMPER7;
	volatile unsigned int SNVS_TAMPER8;
	volatile unsigned int SNVS_TAMPER9;
	volatile unsigned int JTAG_MOD;
	volatile unsigned int JTAG_TMS;
	volatile unsigned int JTAG_TDO;
	volatile unsigned int JTAG_TDI;
	volatile unsigned int JTAG_TCK;
	volatile unsigned int JTAG_TRST_B;
	volatile unsigned int GPIO1_IO00;
	volatile unsigned int GPIO1_IO01;
	volatile unsigned int GPIO1_IO02;
	volatile unsigned int GPIO1_IO03;
	volatile unsigned int GPIO1_IO04;
	volatile unsigned int GPIO1_IO05;
	volatile unsigned int GPIO1_IO06;
	volatile unsigned int GPIO1_IO07;
	volatile unsigned int GPIO1_IO08;
	volatile unsigned int GPIO1_IO09;
	volatile unsigned int UART1_TX_DATA;
	volatile unsigned int UART1_RX_DATA;
	volatile unsigned int UART1_CTS_B;
	volatile unsigned int UART1_RTS_B;
	volatile unsigned int UART2_TX_DATA;
	volatile unsigned int UART2_RX_DATA;
	volatile unsigned int UART2_CTS_B;
	volatile unsigned int UART2_RTS_B;
	volatile unsigned int UART3_TX_DATA;
	volatile unsigned int UART3_RX_DATA;
	volatile unsigned int UART3_CTS_B;
	volatile unsigned int UART3_RTS_B;
	volatile unsigned int UART4_TX_DATA;
	volatile unsigned int UART4_RX_DATA;
	volatile unsigned int UART5_TX_DATA;
	volatile unsigned int UART5_RX_DATA;
	volatile unsigned int ENET1_RX_DATA0;
	volatile unsigned int ENET1_RX_DATA1;
	volatile unsigned int ENET1_RX_EN;
	volatile unsigned int ENET1_TX_DATA0;
	volatile unsigned int ENET1_TX_DATA1;
	volatile unsigned int ENET1_TX_EN;
	volatile unsigned int ENET1_TX_CLK;
	volatile unsigned int ENET1_RX_ER;
	volatile unsigned int ENET2_RX_DATA0;
	volatile unsigned int ENET2_RX_DATA1;
	volatile unsigned int ENET2_RX_EN;
	volatile unsigned int ENET2_TX_DATA0;
	volatile unsigned int ENET2_TX_DATA1;
	volatile unsigned int ENET2_TX_EN;
	volatile unsigned int ENET2_TX_CLK;
	volatile unsigned int ENET2_RX_ER;
	volatile unsigned int LCD_CLK;
	volatile unsigned int LCD_ENABLE;
	volatile unsigned int LCD_HSYNC;
	volatile unsigned int LCD_VSYNC;
	volatile unsigned int LCD_RESET;
	volatile unsigned int LCD_DATA00;
	volatile unsigned int LCD_DATA01;
	volatile unsigned int LCD_DATA02;
	volatile unsigned int LCD_DATA03;
	volatile unsigned int LCD_DATA04;
	volatile unsigned int LCD_DATA05;
	volatile unsigned int LCD_DATA06;
	volatile unsigned int LCD_DATA07;
	volatile unsigned int LCD_DATA08;
	volatile unsigned int LCD_DATA09;
	volatile unsigned int LCD_DATA10;
	volatile unsigned int LCD_DATA11;
	volatile unsigned int LCD_DATA12;
	volatile unsigned int LCD_DATA13;
	volatile unsigned int LCD_DATA14;
	volatile unsigned int LCD_DATA15;
	volatile unsigned int LCD_DATA16;
	volatile unsigned int LCD_DATA17;
	volatile unsigned int LCD_DATA18;
	volatile unsigned int LCD_DATA19;
	volatile unsigned int LCD_DATA20;
	volatile unsigned int LCD_DATA21;
	volatile unsigned int LCD_DATA22;
	volatile unsigned int LCD_DATA23;
	volatile unsigned int NAND_RE_B;
	volatile unsigned int NAND_WE_B;
	volatile unsigned int NAND_DATA00;
	volatile unsigned int NAND_DATA01;
	volatile unsigned int NAND_DATA02;
	volatile unsigned int NAND_DATA03;
	volatile unsigned int NAND_DATA04;
	volatile unsigned int NAND_DATA05;
	volatile unsigned int NAND_DATA06;
	volatile unsigned int NAND_DATA07;
	volatile unsigned int NAND_ALE;
	volatile unsigned int NAND_WP_B;
	volatile unsigned int NAND_READY_B;
	volatile unsigned int NAND_CE0_B;
	volatile unsigned int NAND_CE1_B;
	volatile unsigned int NAND_CLE;
	volatile unsigned int NAND_DQS;
	volatile unsigned int SD1_CMD;
	volatile unsigned int SD1_CLK;
	volatile unsigned int SD1_DATA0;
	volatile unsigned int SD1_DATA1;
	volatile unsigned int SD1_DATA2;
	volatile unsigned int SD1_DATA3;
	volatile unsigned int CSI_MCLK;
	volatile unsigned int CSI_PIXCLK;
	volatile unsigned int CSI_VSYNC;
	volatile unsigned int CSI_HSYNC;
	volatile unsigned int CSI_DATA00;
	volatile unsigned int CSI_DATA01;
	volatile unsigned int CSI_DATA02;
	volatile unsigned int CSI_DATA03;
	volatile unsigned int CSI_DATA04;
	volatile unsigned int CSI_DATA05;
	volatile unsigned int CSI_DATA06;
	volatile unsigned int CSI_DATA07;
} IOMUX_SW_MUX_Type;

typedef struct {
	volatile unsigned int DRAM_ADDR00;
	volatile unsigned int DRAM_ADDR01;
	volatile unsigned int DRAM_ADDR02;
	volatile unsigned int DRAM_ADDR03;
	volatile unsigned int DRAM_ADDR04;
	volatile unsigned int DRAM_ADDR05;
	volatile unsigned int DRAM_ADDR06;
	volatile unsigned int DRAM_ADDR07;
	volatile unsigned int DRAM_ADDR08;
	volatile unsigned int DRAM_ADDR09;
	volatile unsigned int DRAM_ADDR10;
	volatile unsigned int DRAM_ADDR11;
	volatile unsigned int DRAM_ADDR12;
	volatile unsigned int DRAM_ADDR13;
	volatile unsigned int DRAM_ADDR14;
	volatile unsigned int DRAM_ADDR15;
	volatile unsigned int DRAM_DQM0;
	volatile unsigned int DRAM_DQM1;
	volatile unsigned int DRAM_RAS_B;
	volatile unsigned int DRAM_CAS_B;
	volatile unsigned int DRAM_CS0_B;
	volatile unsigned int DRAM_CS1_B;
	volatile unsigned int DRAM_SDWE_B;
	volatile unsigned int DRAM_ODT0;
	volatile unsigned int DRAM_ODT1;
	volatile unsigned int DRAM_SDBA0;
	volatile unsigned int DRAM_SDBA1;
	volatile unsigned int DRAM_SDBA2;
	volatile unsigned int DRAM_SDCKE0;
	volatile unsigned int DRAM_SDCKE1;
	volatile unsigned int DRAM_SDCLK0_P;
	volatile unsigned int DRAM_SDQS0_P;
	volatile unsigned int DRAM_SDQS1_P;
	volatile unsigned int DRAM_RESET;
	volatile unsigned int TEST_MODE;
	volatile unsigned int POR_B;
	volatile unsigned int ONOFF;
	volatile unsigned int SNVS_PMIC_ON_REQ;
	volatile unsigned int CCM_PMIC_STBY_REQ;
	volatile unsigned int BOOT_MODE0;
	volatile unsigned int BOOT_MODE1;
	volatile unsigned int SNVS_TAMPER0;
	volatile unsigned int SNVS_TAMPER1;
	volatile unsigned int SNVS_TAMPER2;
	volatile unsigned int SNVS_TAMPER3;
	volatile unsigned int SNVS_TAMPER4;
	volatile unsigned int SNVS_TAMPER5;
	volatile unsigned int SNVS_TAMPER6;
	volatile unsigned int SNVS_TAMPER7;
	volatile unsigned int SNVS_TAMPER8;
	volatile unsigned int SNVS_TAMPER9;
	volatile unsigned int JTAG_MOD;
	volatile unsigned int JTAG_TMS;
	volatile unsigned int JTAG_TDO;
	volatile unsigned int JTAG_TDI;
	volatile unsigned int JTAG_TCK;
	volatile unsigned int JTAG_TRST_B;
	volatile unsigned int GPIO1_IO00;
	volatile unsigned int GPIO1_IO01;
	volatile unsigned int GPIO1_IO02;
	volatile unsigned int GPIO1_IO03;
	volatile unsigned int GPIO1_IO04;
	volatile unsigned int GPIO1_IO05;
	volatile unsigned int GPIO1_IO06;
	volatile unsigned int GPIO1_IO07;
	volatile unsigned int GPIO1_IO08;
	volatile unsigned int GPIO1_IO09;
	volatile unsigned int UART1_TX_DATA;
	volatile unsigned int UART1_RX_DATA;
	volatile unsigned int UART1_CTS_B;
	volatile unsigned int UART1_RTS_B;
	volatile unsigned int UART2_TX_DATA;
	volatile unsigned int UART2_RX_DATA;
	volatile unsigned int UART2_CTS_B;
	volatile unsigned int UART2_RTS_B;
	volatile unsigned int UART3_TX_DATA;
	volatile unsigned int UART3_RX_DATA;
	volatile unsigned int UART3_CTS_B;
	volatile unsigned int UART3_RTS_B;
	volatile unsigned int UART4_TX_DATA;
	volatile unsigned int UART4_RX_DATA;
	volatile unsigned int UART5_TX_DATA;
	volatile unsigned int UART5_RX_DATA;
	volatile unsigned int ENET1_RX_DATA0;
	volatile unsigned int ENET1_RX_DATA1;
	volatile unsigned int ENET1_RX_EN;
	volatile unsigned int ENET1_TX_DATA0;
	volatile unsigned int ENET1_TX_DATA1;
	volatile unsigned int ENET1_TX_EN;
	volatile unsigned int ENET1_TX_CLK;
	volatile unsigned int ENET1_RX_ER;
	volatile unsigned int ENET2_RX_DATA0;
	volatile unsigned int ENET2_RX_DATA1;
	volatile unsigned int ENET2_RX_EN;
	volatile unsigned int ENET2_TX_DATA0;
	volatile unsigned int ENET2_TX_DATA1;
	volatile unsigned int ENET2_TX_EN;
	volatile unsigned int ENET2_TX_CLK;
	volatile unsigned int ENET2_RX_ER;
	volatile unsigned int LCD_CLK;
	volatile unsigned int LCD_ENABLE;
	volatile unsigned int LCD_HSYNC;
	volatile unsigned int LCD_VSYNC;
	volatile unsigned int LCD_RESET;
	volatile unsigned int LCD_DATA00;
	volatile unsigned int LCD_DATA01;
	volatile unsigned int LCD_DATA02;
	volatile unsigned int LCD_DATA03;
	volatile unsigned int LCD_DATA04;
	volatile unsigned int LCD_DATA05;
	volatile unsigned int LCD_DATA06;
	volatile unsigned int LCD_DATA07;
	volatile unsigned int LCD_DATA08;
	volatile unsigned int LCD_DATA09;
	volatile unsigned int LCD_DATA10;
	volatile unsigned int LCD_DATA11;
	volatile unsigned int LCD_DATA12;
	volatile unsigned int LCD_DATA13;
	volatile unsigned int LCD_DATA14;
	volatile unsigned int LCD_DATA15;
	volatile unsigned int LCD_DATA16;
	volatile unsigned int LCD_DATA17;
	volatile unsigned int LCD_DATA18;
	volatile unsigned int LCD_DATA19;
	volatile unsigned int LCD_DATA20;
	volatile unsigned int LCD_DATA21;
	volatile unsigned int LCD_DATA22;
	volatile unsigned int LCD_DATA23;
	volatile unsigned int NAND_RE_B;
	volatile unsigned int NAND_WE_B;
	volatile unsigned int NAND_DATA00;
	volatile unsigned int NAND_DATA01;
	volatile unsigned int NAND_DATA02;
	volatile unsigned int NAND_DATA03;
	volatile unsigned int NAND_DATA04;
	volatile unsigned int NAND_DATA05;
	volatile unsigned int NAND_DATA06;
	volatile unsigned int NAND_DATA07;
	volatile unsigned int NAND_ALE;
	volatile unsigned int NAND_WP_B;
	volatile unsigned int NAND_READY_B;
	volatile unsigned int NAND_CE0_B;
	volatile unsigned int NAND_CE1_B;
	volatile unsigned int NAND_CLE;
	volatile unsigned int NAND_DQS;
	volatile unsigned int SD1_CMD;
	volatile unsigned int SD1_CLK;
	volatile unsigned int SD1_DATA0;
	volatile unsigned int SD1_DATA1;
	volatile unsigned int SD1_DATA2;
	volatile unsigned int SD1_DATA3;
	volatile unsigned int CSI_MCLK;
	volatile unsigned int CSI_PIXCLK;
	volatile unsigned int CSI_VSYNC;
	volatile unsigned int CSI_HSYNC;
	volatile unsigned int CSI_DATA00;
	volatile unsigned int CSI_DATA01;
	volatile unsigned int CSI_DATA02;
	volatile unsigned int CSI_DATA03;
	volatile unsigned int CSI_DATA04;
	volatile unsigned int CSI_DATA05;
	volatile unsigned int CSI_DATA06;
	volatile unsigned int CSI_DATA07;
	volatile unsigned int GRP_ADDDS;
	volatile unsigned int GRP_DDRMODE_CTL;
	volatile unsigned int GRP_B0DS;
	volatile unsigned int GRP_DDRPK;
	volatile unsigned int GRP_CTLDS;
	volatile unsigned int GRP_B1DS;
	volatile unsigned int GRP_DDRHYS;
	volatile unsigned int GRP_DDRPKE;
	volatile unsigned int GRP_DDRMODE;
	volatile unsigned int GRP_DDR_TYPE;
} IOMUX_SW_PAD_Type;

/* 
 * GPIO寄存器结构体
 */
typedef struct {
	volatile unsigned int DR;							
	volatile unsigned int GDIR; 							
	volatile unsigned int PSR;								
	volatile unsigned int ICR1; 							
	volatile unsigned int ICR2; 							 
	volatile unsigned int IMR;								 
	volatile unsigned int ISR;			
	volatile unsigned int EDGE_SEL;  
} GPIO_Type;

typedef enum {
    GPIO_Pin_0  = 0x00000001,
    GPIO_Pin_1  = 0x00000002,
    GPIO_Pin_2  = 0x00000004,
    GPIO_Pin_3  = 0x00000008,
    GPIO_Pin_4  = 0x00000010,
    GPIO_Pin_5  = 0x00000020,
    GPIO_Pin_6  = 0x00000040,
    GPIO_Pin_7  = 0x00000080,
    GPIO_Pin_8  = 0x00000100,
    GPIO_Pin_9  = 0x00000200,
    GPIO_Pin_10 = 0x00000400,
    GPIO_Pin_11 = 0x00000800,
    GPIO_Pin_12 = 0x00001000,
    GPIO_Pin_13 = 0x00002000,
    GPIO_Pin_14 = 0x00004000,
    GPIO_Pin_15 = 0x00008000,
    GPIO_Pin_16 = 0x00010000,
    GPIO_Pin_17 = 0x00020000,
    GPIO_Pin_18 = 0x00040000,
    GPIO_Pin_19 = 0x00080000,
    GPIO_Pin_20 = 0x00100000,
    GPIO_Pin_21 = 0x00200000,
    GPIO_Pin_22 = 0x00400000,
    GPIO_Pin_23 = 0x00800000,
    GPIO_Pin_24 = 0x01000000,
    GPIO_Pin_25 = 0x02000000,
    GPIO_Pin_26 = 0x04000000,
    GPIO_Pin_27 = 0x08000000,
    GPIO_Pin_28 = 0x10000000,
    GPIO_Pin_29 = 0x20000000,
    GPIO_Pin_30 = 0x40000000,
    GPIO_Pin_31 = 0x80000000,
} GPIO_Pin_t;


/* 
 * 外设寄存器组的基地址 
 */

#define IOMUX_SW_MUX_BASE			(0X020E0014)
#define IOMUX_SW_PAD_BASE			(0X020E0204)
#define GPIO1_BASE                  (0x0209C000)
#define GPIO2_BASE                  (0x020A0000)
#define GPIO3_BASE                  (0x020A4000)
#define GPIO4_BASE                  (0x020A8000)
#define GPIO5_BASE                  (0x020AC000)

#define IOMUX_SW_MUX		((IOMUX_SW_MUX_Type*)IOMUX_SW_MUX_BASE)
#define IOMUX_SW_PAD		((IOMUX_SW_PAD_Type*)IOMUX_SW_PAD_BASE)
#define GPIO1				((GPIO_Type*)GPIO1_BASE)
#define GPIO2				((GPIO_Type*)GPIO2_BASE)
#define GPIO3				((GPIO_Type*)GPIO3_BASE)
#define GPIO4				((GPIO_Type*)GPIO4_BASE)
#define GPIO5				((GPIO_Type*)GPIO5_BASE)

typedef enum {
    GPIO_SION_OFF = 0, // 输出模式不能输入
    GPIO_SION_ON = 1, // 输出模式可以输入
} SION_t;

typedef enum {
    GPIO_ALT0 = 0x00,
    GPIO_ALT1 = 0x01,
    GPIO_ALT2 = 0x02,
    GPIO_ALT3 = 0x03,
    GPIO_ALT4 = 0x04,
    GPIO_ALT5 = 0x05,
    GPIO_ALT6 = 0x06,
    GPIO_ALT7 = 0x07,
    GPIO_ALT8 = 0x08,
    GPIO_ALT9 = 0x09,
    GPIO_ALT10 = 0x0a,
    GPIO_ALT11 = 0x0b,
    GPIO_ALT12 = 0x0c,
    GPIO_ALT13 = 0x0d,
    GPIO_ALT14 = 0x0e,
    GPIO_ALT15 = 0x0f,
} MUX_MODE_t;

typedef enum {
    GPIO_HYS_OFF = 0, // 失能迟滞比较器
    GPIO_HYS_ON = 1, // 使能迟滞比较器
} HYS_t;

typedef enum {
    GPIO_PUS_0_100K_Ohm_Pull_Down = 0, //100k上拉
    GPIO_PUS_1_47K_Ohm_Pull_Up = 1,
    GPIO_PUS_2_100K_Ohm_Pull_Up = 2,
    GPIO_PUS_3_22K_Ohm_Pull_Up = 3,
} PUS_t;

typedef enum {
    GPIO_PUE_0_Keeper = 0, //保持引脚悬空前一瞬间的电平
    GPIO_PUE_1_Pull = 1, // 启用上下拉电阻
} PUE_t;

typedef enum {
    GPIO_PKE_0_Pull_Keeper_Disabled = 0, // 禁用PUE选择位
    GPIO_PKE_1_Pull_Keeper_Enabled = 1, // 启用PUE选择位
} PKE_t;

typedef enum {
    GPIO_OD_Disabled = 0, // 禁用开漏
    GPIO_OD_Enabled = 1, // 启用开漏
} ODE_t;

/*GPIO翻转速度*/
typedef enum {
    GPIO_SPEED_0_low_50MHz_ = 0,
    GPIO_SPEED_1_medium_100MHz_ = 1,
    GPIO_SPEED_2_medium_100MHz_ = 2,
    GPIO_SPEED_3_max_200MHz_ = 3
} SPEED_t;

/*驱动能力(内阻大小)*/
typedef enum {
    // R0 = 260 Ohm(3_3V), 150 Ohm(1.8V), 240 Ohm(DDR)
    GPIO_DSE_0_output_driver_disabled_ = 0,
    GPIO_DSE_1_R0_1 = 1,
    GPIO_DSE_2_R0_2 = 2,
    GPIO_DSE_3_R0_3 = 3,
    GPIO_DSE_4_R0_4 = 4,
    GPIO_DSE_5_R0_5 = 5,
    GPIO_DSE_6_R0_6 = 6,
    GPIO_DSE_7_R0_7 = 7
} DSE_t;

/*压摆率(波形变化的陡峭程度)*/
typedef enum {
    GPIO_SRE_0_Slow_Slew_Rate = 0,
    GPIO_SRE_1_Fast_Slew_Rate = 1,
} SRE_t;

typedef struct {
    /*MUX*/
    SION_t SION; //若开启选项, 则在GPIO口配置为输出的情况下,仍然可以通过GPIO->PSR读取当前IO口的电平.
    MUX_MODE_t MUX_MODE; // 复用功能选择
} IOMUX_SW_MUX_InitTypeDef;

typedef struct {
    /*PAD 输入配置*/
    HYS_t HYS; // Hysteresis(迟滞比较器,用于减少输入噪声) Disabled / ENABLE
    PUS_t PUS; // 上下拉电阻选择
    PKE_t PUE; // 输入引脚保持功能(在引脚悬空时,是启用上下拉电阻还是保持悬空前一瞬间的电平)
    PKE_t PKE; // 复用功能选择

    /*PAD 输入配置*/
    ODE_t ODE; // 开漏(开路)输出使能
    SPEED_t SPEED; // 输出电平翻转速度
    DSE_t DSE; // 输出驱动能力
    SRE_t SRE; // 压摆率
} IOMUX_SW_PAD_InitTypeDef;

void IOMUX_SW_MUX_Init(IOMUX_SW_MUX_InitTypeDef* IOMUX_SW_MUX_InitStructure, volatile unsigned int* IO);
void IOMUX_SW_PAD_Init(IOMUX_SW_PAD_InitTypeDef* IOMUX_SW_PAD_InitStructure, volatile unsigned int* IO);
void GPIO_SetBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x, BitAction_t BitAction);
void GPIO_SetBits(GPIO_Type* GPIO_Port, unsigned int BitActions);
BitAction_t GPIO_ReadBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x);
unsigned int GPIO_ReadBits(GPIO_Type* GPIO_Port);

#endif
