.global _start @ 全局标号 

_start: 
    mrs r0, cpsr
    bic r0, r0, #0x1f @ 清除cpsr的bit4-0
    orr r0, r0, #0x13 @ 将cpsr设置为SVC模式
    msr cpsr, r0 @ 将r0写入cpsr

    ldr sp, =0x80200000
    b main @ 跳转到C语言main函数
