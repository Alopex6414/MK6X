/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Drive_MPU6050.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**I2C起始信号
*/
void I2C_GPIO_Start(void)
{
  I2C_DDR_OUT_SDA;      //SDA输出
  I2C_SET_SDA_H;        //SDA高电平
  I2C_SET_SCL_H;        //SCL高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_SET_SDA_L;        //SDA低电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_SET_SCL_L;        //SCL低电平
}

/*
**I2C停止信号
*/
void I2C_GPIO_Stop(void)
{
  I2C_DDR_OUT_SDA;      //SDA输出
  I2C_SET_SDA_L;        //SDA低电平
  I2C_SET_SCL_H;        //SCL高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_SET_SDA_H;        //SDA高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
}

/*
**I2C发送应答信号
*/
void I2C_GPIO_Send_Ack(int Ack)
{
  I2C_DDR_OUT_SDA;      //SDA输出
  if(Ack == 0)
  {
    I2C_SET_SDA_L;      //SDA低电平
  }
  else
  {
    I2C_SET_SDA_H;      //SDA高电平
  }
  I2C_SET_SCL_H;        //SCL高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_SET_SCL_L;        //SCL低电平
  I2C_DELAY_TIME;       //I2C延时10Nop
}

/*
**I2C接收应答信号
*/
uint8 I2C_GPIO_Recv_Ack(void)
{
  uint8 Recv=0;
  
  I2C_DDR_IN_SDA;       //SDA输入
  I2C_SET_SCL_H;        //SCL高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  Recv = I2C_GET_SDA_IN;//读取SDA信号
  I2C_SET_SCL_L;        //SCL低电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  return Recv;
}

/*
**I2C发送一字节数据
*/
uint8 I2C_GPIO_Send_Byte(uint8 I2C_Data)
{
  uint8 i=0;
  uint8 Ack=0;
  
  I2C_DDR_OUT_SDA;      //SDA输出
  for(i=0;i<8;i++)
  {
    if((I2C_Data<<i)&0x80)
    {
      I2C_SET_SDA_H;    //SDA高电平
    }
    else
    {
      I2C_SET_SDA_L;    //SDA低电平
    }
    I2C_DELAY_TIME;     //I2C延时10Nop
    I2C_SET_SCL_H;      //SCL高电平
    I2C_DELAY_TIME;     //I2C延时10Nop
    I2C_SET_SCL_L;      //SCL低电平
    I2C_DELAY_TIME;     //I2C延时10Nop
  }
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_SET_SDA_H;        //SDA高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_SET_SCL_H;        //SCL高电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  I2C_DDR_IN_SDA;       //SDA输入
  if(I2C_GET_SDA_IN == 1)
  {
    Ack = 0;
  }
  else
  {
    Ack = 1;
  }
  I2C_SET_SCL_L;        //SCL低电平
  I2C_DELAY_TIME;       //I2C延时10Nop
  return Ack;
}

/*
**I2C接收一字节数据
*/
uint8 I2C_GPIO_Recv_Byte(void)
{
  uint8 i=0;
  uint8 Data=0;
  
  I2C_DDR_OUT_SDA;      //SDA输出
  I2C_SET_SDA_H;        //SDA高电平
  I2C_DDR_IN_SDA;       //SDA输入
  for(i=0;i<8;i++)
  {
    Data<<=1;
    I2C_SET_SCL_H;      //SCL高电平
    I2C_DELAY_TIME;     //I2C延时10Nop
    Data|=I2C_GET_SDA_IN;
    I2C_SET_SCL_L;      //SCL低电平
    I2C_DELAY_TIME;     //I2C延时10Nop
  }
  return Data;
}

/*
**I2C写寄存器
*/
void I2C_GPIO_Write_Reg(uint8 I2C_Div_Adr,uint8 I2C_Reg_Adr,uint8 I2C_Data)
{
  I2C_GPIO_Start();
  I2C_GPIO_Send_Byte(I2C_Div_Adr);
  I2C_GPIO_Send_Byte(I2C_Reg_Adr);
  I2C_GPIO_Send_Byte(I2C_Data);
  I2C_GPIO_Stop();
}

/*
**I2C读寄存器
*/
//读一个字节
uint8 I2C_GPIO_Read_Reg_Byte(uint8 I2C_Div_Adr,uint8 I2C_Reg_Adr)
{
  uint8 I2C_Data=0;
  
  I2C_GPIO_Start();
  I2C_GPIO_Send_Byte(I2C_Div_Adr);
  I2C_GPIO_Send_Byte(I2C_Reg_Adr);
  I2C_GPIO_Start();
  I2C_GPIO_Send_Byte(I2C_Div_Adr+1);
  I2C_Data = I2C_GPIO_Recv_Byte();
  I2C_GPIO_Send_Ack(1);
  I2C_GPIO_Stop();
  
  return I2C_Data;
}

//读一个字
int I2C_GPIO_Read_Reg_Word(uint8 I2C_Div_Adr,uint8 I2C_Reg_Adr)
{
  uint8 I2C_Reg_H=0;
  uint8 I2C_Reg_L=0;
  
  I2C_Reg_H = I2C_GPIO_Read_Reg_Byte(I2C_Div_Adr,I2C_Reg_Adr);
  I2C_Reg_L = I2C_GPIO_Read_Reg_Byte(I2C_Div_Adr,I2C_Reg_Adr+1);
  
  return ((I2C_Reg_H<<8)+I2C_Reg_L);
}

/*
**MPU6050 X轴加速度值
*/
int MPU_Get_Acc_X(void)
{
  int Temp=0;
  Temp = I2C_GPIO_Read_Reg_Word(I2C_ADR_MPU6050,ACCEL_XOUT_H);
  return Temp;
}

/*
**MPU6050 Y轴加速度值
*/
int MPU_Get_Acc_Y(void)
{
  int Temp=0;
  Temp = I2C_GPIO_Read_Reg_Word(I2C_ADR_MPU6050,ACCEL_YOUT_H);
  return Temp;
}

/*
**MPU6050 Z轴加速度值
*/
int MPU_Get_Acc_Z(void)
{
  int Temp=0;
  Temp = I2C_GPIO_Read_Reg_Word(I2C_ADR_MPU6050,ACCEL_ZOUT_H);
  return Temp;
}

/*
**MPU6050 X轴角速度值
*/
int MPU_Get_Gyro_X(void)
{
  int Temp=0;
  Temp = I2C_GPIO_Read_Reg_Word(I2C_ADR_MPU6050,GYRO_XOUT_H);
  return Temp;
}

/*
**MPU6050 Y轴角速度值
*/
int MPU_Get_Gyro_Y(void)
{
  int Temp=0;
  Temp = I2C_GPIO_Read_Reg_Word(I2C_ADR_MPU6050,GYRO_YOUT_H);
  return Temp;
}

/*
**MPU6050 Z轴角速度值
*/
int MPU_Get_Gyro_Z(void)
{
  int Temp=0;
  Temp = I2C_GPIO_Read_Reg_Word(I2C_ADR_MPU6050,GYRO_ZOUT_H);
  return Temp;
}

/*
**MPU6050初始化
*/
void MPU6050_Init(void)
{
  I2C_GPIO_Write_Reg(I2C_ADR_MPU6050,PWR_MGMT_1,0x00);
  I2C_GPIO_Write_Reg(I2C_ADR_MPU6050,SMPLRT_DIV,0x00);
  I2C_GPIO_Write_Reg(I2C_ADR_MPU6050,CONFIG,0x00);
  I2C_GPIO_Write_Reg(I2C_ADR_MPU6050,ACCEL_CONFIG,0x09);
  I2C_GPIO_Write_Reg(I2C_ADR_MPU6050,GYRO_CONFIG,0x18);
}

/*
**I2C初始化
*/
void I2C_GPIO_Init(void)
{
  I2C_PORT_INIT_SCL;
  I2C_PORT_INIT_SDA;
  MPU6050_Init();
}