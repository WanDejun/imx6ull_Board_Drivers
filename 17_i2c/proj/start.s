.global _start  		/* 全局标号 */


/*
 * 描述：	_start函数，程序从此函数开始执行，此函数主要功能是设置C
 *		 运行环境。
 */
_start:
	/***** 中断向量表 *****/
	ldr pc, =Reset_Handler // 复位中断
	ldr pc, =Undefined_Handler // 未定义中断
	ldr pc, =SVC_Handler // SVC 中断
	ldr pc, =PreAbort_Handler // 预取中断
	ldr pc, =DataAbort_Handler // 数据中断
	ldr pc, =NotUsed_Handler // 未使用中断
	ldr pc, =IRQ_Handler // 外部中断
	ldr pc, =FIQ_Handler // FIQ 中断

Reset_Handler:
	cpsid i // 关闭IRQ

/* 关闭 I-Cache D-Cache 和 MMU  */
	MRC p15, 0, r0, c1, c0, 0 /* 读取p15 r0 c1 c0 0 */
	bic r0, r0, #(1 << 12) /* 关闭I-Cache */
	bic r0, r0, #(1 << 11) /* 关闭分支预测 */
	bic r0, r0, #(1 << 2) /* 关闭D-Cache */
	bic r0, r0, #(1 << 1) /* 关闭对齐 */
	bic r0, r0, #(1 << 0) /* 关闭MMU */
	MCR p15, 0, r0, c1, c0, 0 /* 写入p15 r0 c1 c0 0 */

	/* 设置中断向量偏移 */
	ldr r0, = 0x87800000
	dsb
	isb
	MCR p15, 0, r0, c12, c0, 0 /* 写入VBAR(中断向量偏移基地址) */
	dsb
	isb

	/* 清BSS段 */
.global __bss_start
_bss_start:
	.word __bss_start

.global __bss_end
_bss_end:
	.word __bss_end

	ldr r0, _bss_start
	ldr r1, _bss_end
	mov r2,  #0
bss_loop:
	stmia r0!, {r2}		/* 向r0的地址写入0,然后r0寄存器保存的地址值加1 */
	cmp r0, r1  		/* 比较r0和r1，也就是__bss_start和__bss_end的值*/
	ble bss_loop		/* 如果小于等于的话就跳转到bss_loop继续清bss段*/


	/* 进入IRQ模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 */
	orr r0, r0, #0x12 	/* r0或上0x13,表示使用IRQ模式 */
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 */
	ldr sp,=0X80600000	/* 设置IRQ下的栈指针 */

	/* 进入SYS模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 */
	orr r0, r0, #0x1f 	/* r0或上0x13,表示使用SYS模式 */
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 */
	ldr sp,=0X80400000	/* 设置SYS下的栈指针 */

	/* 进入SVC模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 */
	orr r0, r0, #0x13 	/* r0或上0x13,表示使用SVC模式 */
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 */
	ldr sp,=0X80200000	/* 设置SVC下的栈指针 */

	cpsie i // 打开IRQ

	/* 跳转main函数 */
	b main				/* 跳转到main函数 		 */

Undefined_Handler:
	ldr r0, =Undefined_Handler
	bx r0

SVC_Handler:
	ldr r0, =SVC_Handler
	bx r0

PreAbort_Handler:
	ldr r0, =PreAbort_Handler
	bx r0

DataAbort_Handler:
	ldr r0, =DataAbort_Handler
	bx r0
NotUsed_Handler:
	ldr r0, NotUsed_Handler
	bx r0
IRQ_Handler:
	push {lr} // 保护IRQ现场
	push {r0-r3, r12}

	mrs r0, spsr
	push {r0}

	mrc p15, 4, r1, c15, c0, 0 // 读取GIC(中断控制器)控制器的寄存器组首地址

	add r1, r1, #0x2000 // GIC控制器的CPU接口端首地址
	ldr r0, [r1, #0x0c] // 读取中断ID GICC_IAR

	push {r0, r1}

	cps #0x13 // 进入SVC模式

	push {lr} // 保护SVC模式现场
	ldr r2, =system_irqhandler //r0为参数
	blx r2

	pop {lr} // 还原SVC模式现场
	cps #0x12
	pop {r0, r1}
	str r0, [r1, #0x10] // 中断完成后将对应的GICC_IAR的值写入EOIR

	pop {r0}
	msr spsr_cxsf, r0 // 恢复 spsr

	pop {r0-r3, r12} // 还原IRQ模式现场
	pop {lr}
	subs pc, lr, #4


FIQ_Handler:
	ldr r0, =FIQ_Handler
	bx r0

