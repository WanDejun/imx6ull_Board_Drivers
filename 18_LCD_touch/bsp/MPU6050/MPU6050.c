#include "MPU6050.h"
#include "MPU6050_Reg.h"
#include "GPIO.h"
#include "delay.h"

void MPU6050_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.SION = GPIO_SION_ON;

	GPIO_InitStructure.HYS = GPIO_HYS_OFF;
    GPIO_InitStructure.PUS = GPIO_PUS_1_47K_Ohm_Pull_Up;
    GPIO_InitStructure.PUE = GPIO_PUE_1_Pull;
    GPIO_InitStructure.PKE = GPIO_PKE_1_Pull_Keeper_Enabled;

    /*PAD 输入配置*/
    GPIO_InitStructure.ODE = GPIO_OD_Disabled;
    GPIO_InitStructure.SPEED = GPIO_SPEED_2_medium_100MHz; // 输出电平翻转速度
    GPIO_InitStructure.DSE = GPIO_DSE_6_R0_6; // 输出驱动能力
    GPIO_InitStructure.SRE = GPIO_SRE_1_Fast_Slew_Rate; // 压摆率

	GPIO_Init(IOMUXC_UART4_TX_DATA_I2C1_SCL, &GPIO_InitStructure);
	GPIO_Init(IOMUXC_UART4_RX_DATA_I2C1_SDA, &GPIO_InitStructure);

    I2C_Init(I2C1);

    delay_ms(20);
    
    MPU6050_WriteByte(MPU6050_PWR_MGMT_1, 0x01);
    delay_ms(20);
	MPU6050_WriteByte(MPU6050_PWR_MGMT_1, 0x00);
    delay_ms(20);
	MPU6050_WriteByte(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteByte(MPU6050_CONFIG, 0x06);
	MPU6050_WriteByte(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteByte(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_ReadByte(uint8_t reg) {
    uint8_t val = 0;

    I2C_transfer_t xfer;
    xfer.data = &val;
    xfer.dataSize = 1;
    xfer.direction = I2C_READ;
    xfer.slaveAddress = MPU6050_ADDRESS;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1;

    I2C_master_transfer(I2C1, &xfer);
    return val;
}

void MPU6050_WriteByte(uint8_t reg, uint8_t val) {
    I2C_transfer_t xfer;
    xfer.data = &val;
    xfer.dataSize = 1;
    xfer.direction = I2C_WRITE;
    xfer.slaveAddress = MPU6050_ADDRESS;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1;

    val = I2C_master_transfer(I2C1, &xfer);
}
