#include "UART.h"
#include "GPIO.h"

/*
 * @description 		: 波特率计算公式，
 *    			  	  	  可以用此函数计算出指定串口对应的UFCR，
 * 				          UBIR和UBMR这三个寄存器的值
 * @param - base		: 要计算的串口。
 * @param - baudrate	: 要使用的波特率。
 * @param - srcclock_hz	:串口时钟源频率，单位Hz
 * @return		: 无
 */
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz) {
    uint32_t numerator = 0u;		//分子
    uint32_t denominator = 0U;		//分母
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0) {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK)) {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator) {
            numerator = 1;
        }
        if (0 == denominator) {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider) {
        case 1:
            refFreqDiv = 0x05;
            break;
        case 2:
            refFreqDiv = 0x04;
            break;
        case 3:
            refFreqDiv = 0x03;
            break;
        case 4:
            refFreqDiv = 0x02;
            break;
        case 5:
            refFreqDiv = 0x01;
            break;
        case 6:
            refFreqDiv = 0x00;
            break;
        case 7:
            refFreqDiv = 0x06;
            break;
        default:
            refFreqDiv = 0x05;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0) {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);

    if (baudDiff < (baudrate / 100) * 3) {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1); //要先写UBIR寄存器，然后在写UBMR寄存器，3592页 
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
        //base->ONEMS = UART_ONEMS_ONEMS(srcclock_hz / (1000 * divider));
    }

}

void UART_Init(UART_Type* UARTx) {
    UART_Cmd(UARTx, DISABLE);
    UART_SoftwareReset(UARTx);

    UARTx->UCR1 = 0;

    UARTx->UCR2 &= ~(0xfffffffe);
    UARTx->UCR2 = (1 << 1) | (1 << 2) | (1 << 5) | (1 << 14);

    UARTx->UCR3 |= (1 << 2);

    /* 设置波特率 为115200 */
    uart_setbaudrate(UART1, 115200, 80000000);

    UART_Cmd(UART1, ENABLE);
}

/*
    @ 使能UART
*/
void UART_Cmd(UART_Type* UARTx, uint32_t NewState) { 
	if (NewState) UARTx->UCR1 |= 1;
	else UARTx->UCR1 &= ~(1);
}

void UART_SoftwareReset(UART_Type* UARTx) {
    UARTx->UCR2 &= (1 << 0);
    while (!(UARTx->UCR2 & 0x01)); // 等待复位完成
}

void UART_putc(UART_Type* UARTx, char c) {
    while (!(UARTx->USR2 & (1 << 3)));
    UARTx->UTXD = c;
}

char UART_getc(UART_Type* UARTx) {
    while (!(UARTx->USR2 & (1 << 0))); // 等待数据
    return UARTx->URXD;
}

void UART_puts(UART_Type* UARTx, const char* str) {
    while (*str) {
        UART_putc(UARTx, *(str++));
    }
}

/*
 * 2020-2-16 15:44:27
 * 解决编译问题：
 * /opt/FriendlyARM/toolschain/4.4.3/lib/gcc/arm-none-linux-gnueabi/4.4.3//libgcc.a(_dvmd_lnx.o): In function `__div0':
 * /opt/FriendlyARM/mini2440/build-toolschain/working/src/gcc-4.4.3/libgcc/../gcc/config/arm/lib1funcs.asm:1093: undefined reference to `raise'
 * 代码参考u-boot-2012.04.01
 */
int raise (int signum) {
	return 0;
}
