#include "i2c.h"

void I2C_Init(I2C_Type* I2Cx) {
    I2Cx->I2CR &= ~(1 << 7); // 关闭I2C

    I2Cx->IFDR = 0x15;  // 640分频
    I2Cx->I2CR |= (1 << 7);
}

uint8_t I2C_master_start(I2C_Type* I2Cx, uint8_t address, I2C_direction_t direction) {
    if (I2Cx->I2SR & (1 << 5)) {  // 忙
        return I2C_STATUS_BUSY;
    }

    /* 设置为主机模式 */
    I2Cx->I2CR |= (1 << 5) | (1 << 4);  // 主机 发送

    /* 产生START信号(写入地址时，硬件产生START), 以及从机地址发送 */
    I2Cx->I2DR = ((uint32_t)address << 1 | (direction == I2C_READ ? 1 : 0));

    return I2C_STATUS_OK;
}

uint8_t I2C_master_stop(I2C_Type* I2Cx) {
    uint16_t timeout = 0xffff;

    /* 清除I2CR的bit5 : 3 */

    I2Cx->I2CR &= ~(1 << 3 | 1 << 4 | 1 << 5);

    while (I2Cx->I2SR & (1 << 5)) {
        timeout--;
        if (!timeout) { return I2C_STATUS_TIMEOUT; }
    }

    return I2C_STATUS_OK;
}

uint8_t I2C_master_restart(I2C_Type* I2Cx, uint8_t address, I2C_direction_t direction) {
    if (I2Cx->I2SR & (1 << 5) && ((I2Cx->I2CR) & (1 << 5)) == 0) {  // 忙
        return 1;
    }

    I2Cx->I2CR |= ((1 << 2) | (1 << 4));
    I2Cx->I2DR = ((uint32_t)address << 1 | (direction == I2C_READ ? 1 : 0));

    return I2C_STATUS_OK;
}

uint8_t I2C_check_and_clear_error(I2C_Type* I2Cx, uint32_t status) {
    /* 检查仲裁丢失错误 */
    if (status & (1 << 4)) {  // 仲裁丢失
        I2Cx->I2SR &= ~(1 << 4);
        I2Cx->I2CR &= ~(1 << 7);
        I2Cx->I2CR |= (1 << 7);
        return I2C_STATUS_ARBITRATIONLOST;
    }
    else if (status & (1 << 0)) { return I2C_STATUS_NACK; }
    return I2C_STATUS_OK;
}

void I2C_master_write(I2C_Type* I2Cx, uint8_t* buf, uint32_t size) {
    while (!(I2Cx->I2SR & (1 << 7)));

    I2Cx->I2SR &= ~(1 << 1);  // 清除中断标志位

    I2Cx->I2CR |= (1 << 4);  // 置发送状态

    while (size--) {
        I2Cx->I2DR = *(buf++);

        while (!(I2Cx->I2SR & (1 << 1)));  // 手动清除中断
        I2Cx->I2SR &= ~(1 << 1);

        if (I2C_check_and_clear_error(I2Cx, I2Cx->I2SR)) break;
    }
    I2Cx->I2SR &= ~(1 << 1);  // 手动清除中断
    I2C_master_stop(I2Cx);
}

void I2C_master_read(I2C_Type* I2Cx, uint8_t* buf, uint32_t size) {
    __IO uint8_t dummy = 0;  // 假读
    dummy++;

    while (!(I2Cx->I2SR & (1 << 7)));

    I2Cx->I2SR &= ~(1 << 1);
    I2Cx->I2CR &= ~((1 << 4) | (1 << 3));

    /* 如果只接收一个字节数据的话发送NACK信号 */
	if(size == 1)
        I2Cx->I2CR |= (1 << 3);

	dummy = I2Cx->I2DR; /* 假读 */

    while (size--) {
        while (!(I2Cx->I2SR & (1 << 1)));  // 等待传输完成
        I2Cx->I2SR &= ~(1 << 1);

        if (size == 0) { I2C_master_stop(I2Cx); }

        if (size == 1) {
            I2Cx->I2CR |= (1 << 3);  // 读取到倒数第二个数据时置nack
        }
        *buf++ = I2Cx->I2DR;
    }
}

/*
 * @description	: I2C数据传输，包括读和写
 * @param - base: 要使用的IIC
 * @param - xfer: 传输结构体
 * @return 		: 传输结果,0 成功，其他值 失败;
 */
uint8_t I2C_master_transfer(I2C_Type* base, I2C_transfer_t* xfer) {
    unsigned char   ret = 0;
    I2C_direction_t direction = xfer->direction;

    base->I2SR &= ~((1 << 1) | (1 << 4)); /* 清除标志位 */

    /* 等待传输完成 */
    while (!((base->I2SR >> 7) & 0X1)) {};

    /* 如果是读的话，要先发送寄存器地址，所以要先将方向改为写 */
    if ((xfer->subaddressSize > 0) && (xfer->direction == I2C_READ)) { direction = I2C_WRITE; }

    ret = I2C_master_start(base, xfer->slaveAddress, direction); /* 发送开始信号 */
    if (ret) { return ret; }

    while (!(base->I2SR & (1 << 1))) {}; /* 等待传输完成 */

    ret = I2C_check_and_clear_error(base, base->I2SR); /* 检查是否出现传输错误 */
    if (ret) {
        I2C_master_stop(base); /* 发送出错，发送停止信号 */
        return ret;
    }

    /* 发送寄存器地址 */
    if (xfer->subaddressSize) {
        do {
            base->I2SR &= ~(1 << 1); /* 清除标志位 */
            xfer->subaddressSize--;  /* 地址长度减一 */

            base->I2DR = ((xfer->subaddress) >> (8 * xfer->subaddressSize));  // 向I2DR寄存器写入子地址

            while (!(base->I2SR & (1 << 1)))
                ; /* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = I2C_check_and_clear_error(base, base->I2SR);
            if (ret) {
                I2C_master_stop(base); /* 发送停止信号 */
                return ret;
            }
        } while ((xfer->subaddressSize > 0) && (ret == I2C_STATUS_OK));

        if (xfer->direction == I2C_READ) {/* 读取数据 */
            base->I2SR &= ~(1 << 1);                                       /* 清除中断挂起位 */
            I2C_master_restart(base, xfer->slaveAddress, I2C_READ); /* 发送重复开始信号和从机地址 */
            while (!(base->I2SR & (1 << 1))) {};                           /* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = I2C_check_and_clear_error(base, base->I2SR);
            if (ret) {
                ret = I2C_STATUS_ADDRNAK;
                I2C_master_stop(base); /* 发送停止信号 */
                return ret;
            }
        }
    }

    /* 发送数据 */
    if ((xfer->direction == I2C_WRITE) && (xfer->dataSize > 0)) { I2C_master_write(base, xfer->data, xfer->dataSize); }

    /* 读取数据 */
    if ((xfer->direction == I2C_READ) && (xfer->dataSize > 0)) { I2C_master_read(base, xfer->data, xfer->dataSize); }
    return 0;
}
