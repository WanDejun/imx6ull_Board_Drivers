#ifndef __I2C_H
#define __I2C_H
#include "config.h"

/* i2c状态宏定义 */
typedef enum {
    I2C_STATUS_OK               = (0),
    I2C_STATUS_BUSY             = (1),
    I2C_STATUS_IDLE             = (2),
    I2C_STATUS_NACK              = (3),
    I2C_STATUS_ARBITRATIONLOST  = (4), // 仲裁丢失
    I2C_STATUS_TIMEOUT          = (5),
    I2C_STATUS_ADDRNAK          = (6),
} I2C_status_t;

/* 传输方向结构体 */
typedef enum {
    I2C_WRITE = 0,
    I2C_READ = 1,
} I2C_direction_t;


/*
 * 主机传输结构体
 */
typedef struct {
    unsigned char slaveAddress;      	/* 7位从机地址 			*/
    I2C_direction_t direction; 		/* 传输方向 			*/
    unsigned int subaddress;       		/* 寄存器地址			*/
    unsigned char subaddressSize;    	/* 寄存器地址长度 			*/
    unsigned char *volatile data;    	/* 数据缓冲区 			*/
    volatile unsigned int dataSize;  	/* 数据缓冲区长度 			*/
} I2C_transfer_t;


void I2C_Init(I2C_Type* I2Cx);
uint8_t I2C_master_start(I2C_Type* I2Cx, uint8_t address, I2C_direction_t direction);
uint8_t I2C_master_stop(I2C_Type* I2Cx);
uint8_t I2C_master_restart(I2C_Type* I2Cx, uint8_t address, I2C_direction_t direction);
uint8_t I2C_check_and_clear_error(I2C_Type* I2Cx, uint32_t status);
void I2C_master_write(I2C_Type* I2Cx, uint8_t *buf, uint32_t size);
void I2C_master_read(I2C_Type* I2Cx, uint8_t *buf, uint32_t size);
uint8_t I2C_master_transfer(I2C_Type* base, I2C_transfer_t* xfer);

#endif
