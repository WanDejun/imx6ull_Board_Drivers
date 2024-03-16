#ifndef __GPIO_H
#define __GPIO_H
#include "MCIMX6Y2.h"
#include "cc.h"

/*描述中断触发类型*/
typedef enum {
    GPIO_Nointmode = 0U,
    GPIO_IntLowLevel = 1U,
    GPIO_IntHighLevel = 2U,
    GPIO_IntRisingEdge = 3U,
    GPIO_IntFallingEdge = 4U,
    GPIO_IntBothEdge = 5U,
} gpio_interupt_mode_t;

typedef enum {
    BitReset = 0,
    BitSet = !BitReset,
} BitAction_t;


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
    GPIO_Pin_All = 0xffffffff,
} GPIO_Pin_t;

/*iomux 初始化结构体和枚举参数*/

typedef enum { //若开启选项, 则在GPIO口配置为输出的情况下,仍然可以通过GPIO->PSR读取当前IO口的电平.
    GPIO_SION_OFF = 0, // 输出模式不能输入
    GPIO_SION_ON = 1, // 输出模式可以输入
} SION_t;

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
	SION_t SION;
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
} GPIO_InitTypeDef;

void GPIO_Init(	uint32_t muxRegister,
				uint32_t muxMode,
				uint32_t inputRegister,
				uint32_t inputDaisy,
				uint32_t configRegister,
				GPIO_InitTypeDef* GPIO_InitStructure);

inline void GPIO_SetBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x, BitAction_t BitAction);
inline void GPIO_SetBits(GPIO_Type* GPIO_Port, unsigned int BitActions);
inline BitAction_t GPIO_ReadBit(GPIO_Type* GPIO_Port, GPIO_Pin_t GPIO_Pin_x);
inline unsigned int GPIO_ReadBits(GPIO_Type* GPIO_Port);


inline void GPIO_IT_Enable(GPIO_Type* base, uint32_t GPIO_Pin_x); /*使能指定IO中断*/
inline void GPIO_IT_Disable(GPIO_Type* base, uint32_t GPIO_Pin_x); /*关闭指定IO中断*/
inline void GPIO_IT_ClearStatus(GPIO_Type* base, uint32_t GPIO_Pin_x); /*清除标志位*/
inline int  GPIO_IT_GetStatus(GPIO_Type* base, uint32_t GPIO_Pin_x); /*读取标志位*/
void GPIO_IT_Config(GPIO_Type* base, uint32_t GPIO_Pin_x, gpio_interupt_mode_t IT_mode);

#endif
