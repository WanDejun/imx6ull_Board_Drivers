#ifndef __GPIO_H
#define __GPIO_H

typedef enum  {
    BitReset = 0,
    BitSet = 1,
} BitAction_t;

#define GPIO1                               ((volatile unsigned int*)0x0209C000)
#define GPIO1_DR                            ((volatile unsigned int*)0x0209C000)
#define GPIO1_GDIR                          ((volatile unsigned int*)0x0209C004) 
#define GPIO1_RSP                           ((volatile unsigned int*)0x0209C008) 
#define GPIO1_ICR1                          ((volatile unsigned int*)0x0209C00C) 
#define GPIO1_ICR2                          ((volatile unsigned int*)0x0209C010) 
#define GPIO1_IMR                           ((volatile unsigned int*)0x0209C014) 
#define GPIO1_ISR                           ((volatile unsigned int*)0x0209C018) 
#define GPIO1_EDGE_SEL                      ((volatile unsigned int*)0x0209C01C) 

#define GPIO2                               ((volatile unsigned int*)0x020A0000)
#define GPIO2_DR                            ((volatile unsigned int*)0x020A0000)
#define GPIO2_GDIR                          ((volatile unsigned int*)0x020A0004) 
#define GPIO2_RSP                           ((volatile unsigned int*)0x020A0008) 
#define GPIO2_ICR1                          ((volatile unsigned int*)0x020A000C) 
#define GPIO2_ICR2                          ((volatile unsigned int*)0x020A0010) 
#define GPIO2_IMR                           ((volatile unsigned int*)0x020A0014) 
#define GPIO2_ISR                           ((volatile unsigned int*)0x020A0018) 
#define GPIO2_EDGE_SEL                      ((volatile unsigned int*)0x020A001C) 

#define GPIO3                               ((volatile unsigned int*)0x020A4000)
#define GPIO3_GDIR                          ((volatile unsigned int*)0x020A4004) 
#define GPIO3_RSP                           ((volatile unsigned int*)0x020A4008) 
#define GPIO3_ICR1                          ((volatile unsigned int*)0x020A400C) 
#define GPIO3_ICR2                          ((volatile unsigned int*)0x020A4010) 
#define GPIO3_IMR                           ((volatile unsigned int*)0x020A4014) 
#define GPIO3_ISR                           ((volatile unsigned int*)0x020A4018) 
#define GPIO3_EDGE_SEL                      ((volatile unsigned int*)0x020A401C) 

#define GPIO4                               ((volatile unsigned int*)0x020A8000)
#define GPIO4_GDIR                          ((volatile unsigned int*)0x020A8004) 
#define GPIO4_RSP                           ((volatile unsigned int*)0x020A8008) 
#define GPIO4_ICR1                          ((volatile unsigned int*)0x020A800C) 
#define GPIO4_ICR2                          ((volatile unsigned int*)0x020A8010) 
#define GPIO4_IMR                           ((volatile unsigned int*)0x020A8014) 
#define GPIO4_ISR                           ((volatile unsigned int*)0x020A8018) 
#define GPIO4_EDGE_SEL                      ((volatile unsigned int*)0x020A801C) 

#define GPIO5                               ((volatile unsigned int*)0x020AC000)
#define GPIO5_GDIR                          ((volatile unsigned int*)0x020AC004) 
#define GPIO5_RSP                           ((volatile unsigned int*)0x020AC008) 
#define GPIO5_ICR1                          ((volatile unsigned int*)0x020AC00C) 
#define GPIO5_ICR2                          ((volatile unsigned int*)0x020AC010) 
#define GPIO5_IMR                           ((volatile unsigned int*)0x020AC014) 
#define GPIO5_ISR                           ((volatile unsigned int*)0x020AC018)
#define GPIO5_EDGE_SEL                      ((volatile unsigned int*)0x020AC01C)

#define GPIO_Pin_0      0x00000001
#define GPIO_Pin_1      0x00000002
#define GPIO_Pin_2      0x00000004
#define GPIO_Pin_3      0x00000008
#define GPIO_Pin_4      0x00000010
#define GPIO_Pin_5      0x00000020
#define GPIO_Pin_6      0x00000040
#define GPIO_Pin_7      0x00000080
#define GPIO_Pin_8      0x00000100
#define GPIO_Pin_9      0x00000200
#define GPIO_Pin_10     0x00000400
#define GPIO_Pin_11     0x00000800
#define GPIO_Pin_12     0x00001000
#define GPIO_Pin_13     0x00002000
#define GPIO_Pin_14     0x00004000
#define GPIO_Pin_15     0x00008000
#define GPIO_Pin_16     0x00010000
#define GPIO_Pin_17     0x00020000
#define GPIO_Pin_18     0x00040000
#define GPIO_Pin_19     0x00080000
#define GPIO_Pin_20     0x00100000
#define GPIO_Pin_21     0x00200000
#define GPIO_Pin_22     0x00400000
#define GPIO_Pin_23     0x00800000
#define GPIO_Pin_24     0x01000000
#define GPIO_Pin_25     0x02000000
#define GPIO_Pin_26     0x04000000
#define GPIO_Pin_27     0x08000000
#define GPIO_Pin_28     0x10000000
#define GPIO_Pin_29     0x20000000
#define GPIO_Pin_30     0x40000000
#define GPIO_Pin_31     0x80000000

void GPIO_SetBit(volatile unsigned int* GPIO_Port, unsigned int GPIO_Pin, BitAction_t BitAction);
void GPIO_SetBits(volatile unsigned int* GPIO_Port, unsigned int BitActions);
BitAction_t GPIO_ReadBit(volatile unsigned int* GPIO_Port, unsigned int GPIO_Pin);
unsigned int GPIO_ReadBits(volatile unsigned int* GPIO_Port);

#endif
