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
**MPU6050�ڲ��Ĵ�����
*/
//MPU6050�豸��ַ
#define I2C_ADR_MPU6050 0xD0

//MPU6050�ڲ��Ĵ�����ַ
#define	PWR_MGMT_1      0x6B	//��Դ����,����ֵ:0x00(��������)
#define	SMPLRT_DIV	0x19	//�����ǲ�����,����ֵ:0x07(125Hz)
#define	CONFIG		0x1A	//��ͨ�˲�Ƶ��,����ֵ:0x06(5Hz)
#define	GYRO_CONFIG	0x1B	//�������Լ켰������Χ,����ֵ:0x18(���Լ�,2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ�,������Χ����ͨ�˲�Ƶ��,����ֵ:0x01(���Լ�,2G,5Hz)
#define	ACCEL_XOUT_H	0x3B    //���ٶȼ�X���λ���
#define	ACCEL_XOUT_L	0x3C    //���ٶȼ�X���λ���
#define	ACCEL_YOUT_H	0x3D    //���ٶȼ�Y���λ���
#define	ACCEL_YOUT_L	0x3E    //���ٶȼ�Y���λ���
#define	ACCEL_ZOUT_H	0x3F    //���ٶȼ�Z���λ���
#define	ACCEL_ZOUT_L	0x40    //���ٶȼ�Z���λ���
#define	TEMP_OUT_H      0x41    //�¶ȴ�������λ���
#define	TEMP_OUT_L	0x42    //�¶ȴ�������λ���
#define	GYRO_XOUT_H	0x43    //������X���λ���
#define	GYRO_XOUT_L	0x44	//������X���λ���
#define	GYRO_YOUT_H	0x45    //������Y���λ���
#define	GYRO_YOUT_L	0x46    //������Y���λ���
#define	GYRO_ZOUT_H	0x47    //������Z���λ���
#define	GYRO_ZOUT_L	0x48    //������Z���λ���
#define	WHO_AM_I        0x75	//I2C��ַ�Ĵ���(Ĭ����ֵ0x68,ֻ��)

//I2C�˿ں�
//I2C SCL�˿ڳ�ʼ��
#ifndef I2C_PORT_INIT_SCL
#define I2C_PORT_INIT_SCL       GPIO_Init(PTC0,GPO,0)
#endif
//I2C SDA�˿ڳ�ʼ��
#ifndef I2C_PORT_INIT_SDA
#define I2C_PORT_INIT_SDA       GPIO_Init(PTB22,GPO,0)
#endif
//I2C SCL�˿����
#ifndef I2C_DDR_OUT_SCL
#define I2C_DDR_OUT_SCL         GPIO_DDRX(PTC0,1)
#endif
//I2C SDA�˿����
#ifndef I2C_DDR_OUT_SDA
#define I2C_DDR_OUT_SDA         GPIO_DDRX(PTB22,1)
#endif
//I2C SDA�˿�����
#ifndef I2C_DDR_IN_SDA
#define I2C_DDR_IN_SDA          GPIO_DDRX(PTB22,0)
#endif
//I2C SCL�˿ڸߵ�ƽ
#ifndef I2C_SET_SCL_H
#define I2C_SET_SCL_H           GPIO_SET(PTC0,1)
#endif
//I2C SCL�˿ڵ͵�ƽ
#ifndef I2C_SET_SCL_L
#define I2C_SET_SCL_L           GPIO_SET(PTC0,0)
#endif
//I2C SDA�˿ڸߵ�ƽ
#ifndef I2C_SET_SDA_H
#define I2C_SET_SDA_H           GPIO_SET(PTB22,1)
#endif
//I2C SDA�˿ڵ͵�ƽ
#ifndef I2C_SET_SDA_L
#define I2C_SET_SDA_L           GPIO_SET(PTB22,0)
#endif
//I2C SDA�˿������ź�
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