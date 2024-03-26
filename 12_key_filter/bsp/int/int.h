/*
 @ 中断驱动代码
*/
#ifndef __INT_H
#define __INT_H
#include "config.h"

typedef void (*system_irq_handler_t)(uint32_t gicciar, void *param);

typedef struct  _sys_irq_handle {
	system_irq_handler_t irqHandler;
	void *userParam;
} sys_irq_handle_t;

/*中断初始化函数*/
void int_Init();
/*注册中断函数*/
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void* parma);

#endif
