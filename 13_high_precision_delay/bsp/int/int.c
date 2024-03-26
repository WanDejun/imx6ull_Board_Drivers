#include "int.h"

static unsigned int irqNesting; // 中断嵌套深度

/*中断处理函数表*/
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];

void default_irqhandler(uint32_t gicciar, void *param);

void system_irqtable_init(void) {
	unsigned int i = 0;
	for (i = 0; i < NUMBER_OF_INT_VECTORS; i++) {
		irqTable[i].irqHandler = default_irqhandler;
		irqTable[i].userParam = NULL;
	}
}

/*注册中断处理函数*/
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void* parma) {
	irqTable[irq].irqHandler = handler;
	irqTable[irq].userParam = parma;
}

void int_Init() {
	/*中断初始化*/
	GIC_Init();
	system_irqtable_init();
	// __set_VBAR((uint32_t)0x87800000); /* 中断向量表偏移 */
}

void system_irqhandler(unsigned int GICC_IAR) {
	uint32_t intNum = GICC_IAR & 0x03ff;

	/*检查中断ID*/
	if (intNum >= NUMBER_OF_INT_VECTORS) {
		return;
	}

	// 调用对应的中断
	irqNesting++;
	irqTable[intNum].irqHandler(intNum, irqTable[intNum].userParam);
	irqNesting--;
}

void default_irqhandler(uint32_t gicciar, void *param) {
	while (1) {

	}
}