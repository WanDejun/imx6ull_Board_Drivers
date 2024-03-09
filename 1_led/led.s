.global _start @ 全局标号 

_start: 
@ 开启时钟
    ldr r1, =0xFFFFFFFF @ 要写入的值 

    ldr r0, =0x020C4068 @ CCGR0 
    str r1, [r0]        @ 写入 

    ldr r0, =0x020C406C @ CCGR1 
    str r1, [r0]        @ 写入 

    ldr r0, =0x020C4070 @ CCGR2 
    str r1, [r0]        @ 写入 

    ldr r0, =0x020C4074 @ CCGR3 
    str r1, [r0]        @ 写入 

    ldr r0, =0x020C4078 @ CCGR4 
    str r1, [r0]        @ 写入 

    ldr r0, =0x020C407C @ CCGR5 
    str r1, [r0]        @ 写入 

    ldr r0, =0x020C4080 @ CCGR6 
    str r1, [r0]        @ 写入 

@ 引脚复用 
    @ IOMUXC_SW_MUX_CTL_PAD_GPIO_IO03 *(0x020E0068) 
    @ IOMUXC_SW_MUX_CTL_PAD_GPIO_IO03 = 5 
    ldr r1, =0x05
    ldr r0, =0x020E0068 @ IOMUXC_SW_MUX_CTL_PAD_GPIO_IO03 
    str r1, [r0]        @ 写入   

@ 配置GPIO 
    @ IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 *(0x020E02F4) 
    @ IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 5 

    @ bit0 : 0 低速 
    @ bit5:3 : 110 R0/6 驱动能力 
    @ bit7:5 : 10 100MHz 
    @ bit11 : 0 关闭开漏输出 
    @ bit12 : 1 使能pull/keeper 
    @ bit13 : 0 keeper 
    @ bit15:14 : 00 100k下拉 
    @ bit16 : 0 关闭hys 
    ldr r1, =0x000010B0
    ldr r0, =0x020E02F4 @ IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 
    str r1, [r0]        @ 写入   

@ GPIO 输入输出配置
    @ GPIO1_GDIR *(0x0209_C004) 
    @ GPIO1_GDIR = 0x08 3脚设为输出

    ldr r1, =0x08
    ldr r0, =0x0209C004
    str r1, [r0]        @ 写入   

@ 输出GPIO1_IO03为 低电平(0)
    @ GPIO1_DR *(0x0209_C000) 
    @ GPIO1_DR = 0x00 

    ldr r1, =0x00000000
    ldr r0, =0x0209C000
    str r1, [r0]        @ 写入 

loop:
    b loop
    