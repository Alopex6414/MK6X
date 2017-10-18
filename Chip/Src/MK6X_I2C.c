/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_I2C.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**I2C基址指针
*/
I2C_MemMapPtr I2CN[I2C_I2C_MAX]=
{
  I2C0_BASE_PTR,//I2C0基址指针
  I2C1_BASE_PTR,//I2C1基址指针
  I2C2_BASE_PTR,//I2C2基址指针
  #ifdef MK66F18
  I2C3_BASE_PTR,//I2C3基址指针
  #endif
};

/*
 *  @brief      I2C初始化,设置波特率
 *  @param      I2C_I2Cn        I2C_I2Cx        I2C模块(I2C0,I2C1,I2C2,I2C3)
 *  @param      uint32          I2C_Baud        期待的波特率
 *  @return     uint32          I2C_Real        实际的波特率
 *  @since      v1.0
 *  Sample usage:       I2C_Init(I2C_I2C0,400000);     //初始化I2C0,期待的波特率为400K
 */
uint32 I2C_Init(I2C_I2Cn I2C_I2Cx,uint32 I2C_Baud)
{
  uint8 I2C_Mult=0;
  uint8 I2C_ICR=0;
  uint8 I2C_N=64;
  uint16 I2C_SCL_Div=0;
  uint16 I2C_Min_Dvalue=~0;
  uint16 I2C_Dvalue=0;
  uint16 ICR_SCL_Divider[64]=
  {
    20, 22, 24, 26, 28, 30, 34, 40, 28, 32, 36, 40, 44, 48, 56, 68,
    48, 56, 64, 72, 80, 88, 104, 128, 80, 96, 112, 128, 144, 160, 192, 240,
    160, 192, 224, 256, 288, 320, 384, 480, 320, 384, 448, 512, 576, 640, 768, 960,
    640, 768, 896, 1024, 1152, 1280, 1536, 1920, 1280, 1536, 1792, 2048, 2304, 2560, 3072, 3840
  };
  
  if(MK6X_Bus_KHz <= 50000)
  {
    I2C_Mult = 0;//Bus
  }
  else if(MK6X_Bus_KHz <= 100000)
  {
    I2C_Mult = 1;//Bus/2
  }
  else
  {
    I2C_Mult = 2;//Bus/4
  }
  
  I2C_SCL_Div = (MK6X_Bus_KHz * 1000) / ((1 << I2C_Mult) * I2C_Baud); 
  
  //I2C管脚复用
  switch(I2C_I2Cx)
  {
    case I2C_I2C0:
                  SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;//I2C0时钟使能
                  if((I2C0_SCL_PIN == PTB0) || (I2C0_SCL_PIN == PTB2) || (I2C0_SCL_PIN == PTD8))
                  {
                    PORT_Init(I2C0_SCL_PIN,ALT2 | ODO | PULLUP);
                  }
                  else if(I2C0_SCL_PIN == PTE24)
                  {
                    PORT_Init(I2C0_SCL_PIN,ALT5 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  
                  if((I2C0_SDA_PIN == PTB1) || (I2C0_SDA_PIN == PTB3) || (I2C0_SDA_PIN == PTD9))
                  {
                    PORT_Init(I2C0_SDA_PIN,ALT2 | ODO | PULLUP);
                  }
                  else if(I2C0_SDA_PIN == PTE25)
                  {
                    PORT_Init(I2C0_SDA_PIN,ALT5 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case I2C_I2C1:
                  SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;//I2C1时钟使能
                  if(I2C1_SCL_PIN == PTE1)
                  {
                    PORT_Init(I2C1_SCL_PIN,ALT6 | ODO | PULLUP);
                  }
                  else if(I2C1_SCL_PIN == PTC10)
                  {
                    PORT_Init(I2C1_SCL_PIN,ALT2 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  
                  if(I2C1_SDA_PIN == PTE0)
                  {
                    PORT_Init(I2C1_SDA_PIN,ALT6 | ODO | PULLUP);
                  }
                  else if(I2C1_SDA_PIN == PTC11)
                  {
                    PORT_Init(I2C1_SDA_PIN,ALT2 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case I2C_I2C2:
                  SIM_SCGC1 |= SIM_SCGC1_I2C2_MASK;//I2C2时钟使能
                  if((I2C2_SCL_PIN == PTA12) || (I2C2_SCL_PIN == PTA14))
                  {
                    PORT_Init(I2C2_SCL_PIN,ALT5 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  
                  if((I2C2_SDA_PIN == PTA11) || (I2C2_SDA_PIN == PTA13))
                  {
                    PORT_Init(I2C2_SDA_PIN,ALT5 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    #ifdef MK66F18
    case I2C_I2C3:
                  SIM_SCGC1 |= SIM_SCGC1_I2C3_MASK;//I2C3时钟使能
                  if(I2C3_SCL_PIN == PTA2)
                  {
                    PORT_Init(I2C3_SCL_PIN,ALT4 | ODO | PULLUP);
                  }
                  else if(I2C3_SCL_PIN == PTE11)
                  {
                    PORT_Init(I2C3_SCL_PIN,ALT2 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  
                  if(I2C3_SDA_PIN == PTA1)
                  {
                    PORT_Init(I2C3_SDA_PIN,ALT4 | ODO | PULLUP);
                  }
                  else if(I2C3_SDA_PIN == PTE10)
                  {
                    PORT_Init(I2C3_SDA_PIN,ALT2 | ODO | PULLUP);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    #endif
    default:
                  ASSERT(0);
                  break;
  }
  
  while(I2C_N)
  {
    I2C_N--;
    I2C_Dvalue = abs(I2C_SCL_Div - ICR_SCL_Divider[I2C_N]);
    
    if(I2C_Dvalue == 0)
    {
      I2C_ICR = I2C_N;
      break;
    }
    
    if(I2C_Dvalue < I2C_Min_Dvalue)
    {
      I2C_ICR = I2C_N;
      I2C_Min_Dvalue = I2C_Dvalue;
    }
  }
  
  I2C_F_REG(I2CN[I2C_I2Cx]) = (0 | I2C_F_MULT(I2C_Mult) | I2C_F_ICR(I2C_ICR));
  I2C_C1_REG(I2CN[I2C_I2Cx]) = (0 | I2C_C1_IICEN_MASK);//I2C Enable
  
  return ((MK6X_Bus_KHz * 1000) / ((1 << I2C_Mult) * ICR_SCL_Divider[I2C_ICR]));
}

/*
 *  @brief      I2C通信结束后需要调用的延时函数
 *  @since      v1.0
 *  @note       如果通信失败，可尝试增大此延时值，确认是否延时导致的
 */
void I2C_Delay(uint16 n)
{
  while(n--)
  {
    asm("nop");
  }
}

/*
 *  @brief      读取I2C设备指定地址寄存器的数据
 *  @param      I2C_I2Cn        I2C_I2Cx        I2C模块(I2C0,I2C1,I2C2,I2C3)
 *  @param      uint8           I2C_SlaveID     从机地址(7位地址)
 *  @param      uint8           I2C_Reg         从机寄存器地址
 *  @return     读取的寄存器值
 *  @since      v1.0
 *  Sample usage:       uint8 value = I2C_Read_Reg(I2C0, 0x1D, 1);
 */
uint8 I2C_Read_Reg(I2C_I2Cn I2C_I2Cx,uint8 I2C_SlaveID,uint8 I2C_Reg)
{
  uint8 I2C_Result=0;
  
  //断言从机地址是7位地址
  ASSERT((I2C_SlaveID & 0x80) == 0);
  
  I2C_Start(I2C_I2Cx);//发送启动信号
  I2C_Write_Byte(I2C_I2Cx,(I2C_SlaveID << 1) | MWSR);
  I2C_Write_Byte(I2C_I2Cx,I2C_Reg);
  I2C_ReStart(I2C_I2Cx);
  I2C_Write_Byte(I2C_I2Cx,(I2C_SlaveID << 1) | MRSW);
  I2C_PutInRx(I2C_I2Cx);
  I2C_Result = I2C_D_REG(I2CN[I2C_I2Cx]);
  I2C_Wait(I2C_I2Cx);
  I2C_Stop(I2C_I2Cx);
  I2C_Result = I2C_D_REG(I2CN[I2C_I2Cx]);
  I2C_Delay(100);
  
  return I2C_Result;
}

/*
 *  @brief      写入一个字节数据到I2C设备指定寄存器地址
 *  @param      I2C_I2Cn        I2C_I2Cx        I2C模块(I2C0,I2C1,I2C2,I2C3)
 *  @param      uint8           I2C_SlaveID     从机地址(7位地址)
 *  @param      uint8           I2C_Reg         从机寄存器地址
 *  @param      uint8           I2C_Data        数据
 *  @since      v1.0
 *  Sample usage:       I2C_Write_Reg(I2C0, 0x1D, 1,2);     //向从机0x1D 的寄存器 1 写入数据 2
 */
void I2C_Write_Reg(I2C_I2Cn I2C_I2Cx,uint8 I2C_SlaveID,uint8 I2C_Reg,uint8 I2C_Data)
{
  I2C_Start(I2C_I2Cx);//发送启动信号
  I2C_Write_Byte(I2C_I2Cx,(I2C_SlaveID << 1) | MWSR);
  I2C_Write_Byte(I2C_I2Cx,I2C_Reg);
  I2C_Write_Byte(I2C_I2Cx,I2C_Data);
  I2C_Stop(I2C_I2Cx);
  I2C_Delay(100);
}