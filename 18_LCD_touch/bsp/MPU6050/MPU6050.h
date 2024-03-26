#ifndef __MPU6050__H
#define __MPU6050__H

#include "config.h"
#include "i2c.h"
#include "MPU6050_Reg.h"

void MPU6050_Init();
uint8_t MPU6050_ReadByte(uint8_t reg);
void MPU6050_WriteByte(uint8_t reg, uint8_t val);

#endif
