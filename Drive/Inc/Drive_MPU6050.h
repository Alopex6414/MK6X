/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Drive_MPU6050.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __DRIVE_MPU6050_H__
#define __DRIVE_MPU6050_H__

#include "Common.h"

/*
**MPU6050内部寄存器宏
*/
//MPU6050设备地址
#define I2C_ADR_MPU6050 0xD0

//MPU6050内部寄存器地址
#define	PWR_MGMT_1      0x6B	//电源管理,典型值:0x00(正常启用)
#define	SMPLRT_DIV	0x19	//陀螺仪采样率,典型值:0x07(125Hz)
#define	CONFIG		0x1A	//低通滤波频率,典型值:0x06(5Hz)
#define	GYRO_CONFIG	0x1B	//陀螺仪自检及测量范围,典型值:0x18(不自检,2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检,测量范围及高通滤波频率,典型值:0x01(不自检,2G,5Hz)
#define	ACCEL_XOUT_H	0x3B    //加速度计X轴高位输出
#define	ACCEL_XOUT_L	0x3C    //加速度计X轴低位输出
#define	ACCEL_YOUT_H	0x3D    //加速度计Y轴高位输出
#define	ACCEL_YOUT_L	0x3E    //加速度计Y轴低位输出
#define	ACCEL_ZOUT_H	0x3F    //加速度计Z轴高位输出
#define	ACCEL_ZOUT_L	0x40    //加速度计Z轴低位输出
#define	TEMP_OUT_H      0x41    //温度传感器高位输出
#define	TEMP_OUT_L	0x42    //温度传感器低位输出
#define	GYRO_XOUT_H	0x43    //陀螺仪X轴高位输出
#define	GYRO_XOUT_L	0x44	//陀螺仪X轴低位输出
#define	GYRO_YOUT_H	0x45    //陀螺仪Y轴高位输出
#define	GYRO_YOUT_L	0x46    //陀螺仪Y轴低位输出
#define	GYRO_ZOUT_H	0x47    //陀螺仪Z轴高位输出
#define	GYRO_ZOUT_L	0x48    //陀螺仪Z轴低位输出
#define	WHO_AM_I        0x75	//I2C地址寄存器(默认数值0x68,只读)

//I2C端口宏
//I2C SCL端口初始化
#ifndef I2C_PORT_INIT_SCL
#define I2C_PORT_INIT_SCL       GPIO_Init(PTC0,GPO,0)
#endif
//I2C SDA端口初始化
#ifndef I2C_PORT_INIT_SDA
#define I2C_PORT_INIT_SDA       GPIO_Init(PTB22,GPO,0)
#endif
//I2C SCL端口输出
#ifndef I2C_DDR_OUT_SCL
#define I2C_DDR_OUT_SCL         GPIO_DDRX(PTC0,1)
#endif
//I2C SDA端口输出
#ifndef I2C_DDR_OUT_SDA
#define I2C_DDR_OUT_SDA         GPIO_DDRX(PTB22,1)
#endif
//I2C SDA端口输入
#ifndef I2C_DDR_IN_SDA
#define I2C_DDR_IN_SDA          GPIO_DDRX(PTB22,0)
#endif
//I2C SCL端口高电平
#ifndef I2C_SET_SCL_H
#define I2C_SET_SCL_H           GPIO_SET(PTC0,1)
#endif
//I2C SCL端口低电平
#ifndef I2C_SET_SCL_L
#define I2C_SET_SCL_L           GPIO_SET(PTC0,0)
#endif
//I2C SDA端口高电平
#ifndef I2C_SET_SDA_H
#define I2C_SET_SDA_H           GPIO_SET(PTB22,1)
#endif
//I2C SDA端口低电平
#ifndef I2C_SET_SDA_L
#define I2C_SET_SDA_L           GPIO_SET(PTB22,0)
#endif
//I2C SDA端口输入信号
#ifndef I2C_GET_SDA_IN
#define I2C_GET_SDA_IN          GPIO_GET(PTB22)
#endif

#define I2C_DELAY_TIME          I2C_Delay(10)

/*
**function declaration
*/
extern void I2C_GPIO_Start(void);
extern void I2C_GPIO_Stop(void);
extern void I2C_GPIO_Send_Ack(int Ack);
extern uint8 I2C_GPIO_Recv_Ack(void);
extern uint8 I2C_GPIO_Send_Byte(uint8 I2C_Data);
extern uint8 I2C_GPIO_Recv_Byte(void);
extern void I2C_GPIO_Write_Reg(uint8 I2C_Div_Adr,uint8 I2C_Reg_Adr,uint8 I2C_Data);
extern uint8 I2C_GPIO_Read_Reg_Byte(uint8 I2C_Div_Adr,uint8 I2C_Reg_Adr);
extern int I2C_GPIO_Read_Reg_Word(uint8 I2C_Div_Adr,uint8 I2C_Reg_Adr);
extern int MPU_Get_Acc_X(void);
extern int MPU_Get_Acc_Y(void);
extern int MPU_Get_Acc_Z(void);
extern int MPU_Get_Gyro_X(void);
extern int MPU_Get_Gyro_Y(void);
extern int MPU_Get_Gyro_Z(void);
extern void MPU6050_Init(void);
extern void I2C_GPIO_Init(void);

#endif