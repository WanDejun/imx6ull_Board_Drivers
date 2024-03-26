#include "EPIT.h"
#include "EXTI.h"
#include "UART.h"
#include "UART_print.h"
#include "clk.h"
#include "config.h"
#include "delay.h"
#include "int.h"
#include "key.h"
#include "led.h"
#include "rgblcd.h"
#include "rgblcd_api.h"
#include "stdio.h"
#include "MPU6050.h"

void init() {
    ARM_clk_init(); /* 系统时钟 */
    clk_enable();   /* 使能所有的时钟 */
    int_Init();     /* 中断初始化 */
    delay_Init();

    led_init(); /* 初始化led */
    UART_print_Init(UART1);
    rgblcd_Init();
    // EXTI_Init();
    EPIT_Init(65, 500000);	/* 定时器初始化 */
	EPIT_Cmd(ENABLE);
    MPU6050_Init();
    // Key_Init();				/* 按键初始化 */
}

int main(void) {
    init();

    rgblcd_SetBKColor(RGBLCD_WHITE);

    uint8_t ID = MPU6050_ReadByte(0x75); // WHOAMI
    rgblcd_ShowHexNum(50, 50, ID, 8, 24, 0, RGBLCD_BLACK);
    delay_ms(500);

    uint16_t DataH, DataL, AccX, AccY, AccZ, GyroX, GyroY, GyroZ;

    while (1) {
        DataH = MPU6050_ReadByte(MPU6050_ACCEL_XOUT_H);
        DataL = MPU6050_ReadByte(MPU6050_ACCEL_XOUT_L);
        AccX = DataH << 8 | DataL;
        rgblcd_ShowHexNum(50, 100, AccX, 8, 24, 0, RGBLCD_BLACK);
        
        DataH = MPU6050_ReadByte(MPU6050_ACCEL_YOUT_H);
        DataL = MPU6050_ReadByte(MPU6050_ACCEL_YOUT_L);
        AccY = DataH << 8 | DataL;
        rgblcd_ShowHexNum(50, 150, AccY, 8, 24, 0, RGBLCD_BLACK);
        
        DataH = MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_H);
        DataL = MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_L);
        AccZ = DataH << 8 | DataL;
        rgblcd_ShowHexNum(50, 200, AccZ, 8, 24, 0, RGBLCD_BLACK);
        
        DataH = MPU6050_ReadByte(MPU6050_GYRO_XOUT_H);
        DataL = MPU6050_ReadByte(MPU6050_GYRO_XOUT_L);
        GyroX = DataH << 8 | DataL;
        rgblcd_ShowHexNum(50, 250, GyroX, 8, 24, 0, RGBLCD_BLACK);
        
        DataH = MPU6050_ReadByte(MPU6050_GYRO_YOUT_H);
        DataL = MPU6050_ReadByte(MPU6050_GYRO_YOUT_L);
        GyroY = DataH << 8 | DataL;
        rgblcd_ShowHexNum(50, 300, GyroY, 8, 24, 0, RGBLCD_BLACK);
        
        DataH = MPU6050_ReadByte(MPU6050_GYRO_ZOUT_H);
        DataL = MPU6050_ReadByte(MPU6050_GYRO_ZOUT_L);
        GyroZ= DataH << 8 | DataL;
        rgblcd_ShowHexNum(50, 350, GyroZ, 8, 24, 0, RGBLCD_BLACK);

        delay_ms(50);
    }

    return 0;
}
