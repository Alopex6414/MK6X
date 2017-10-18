/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_I2C.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      I2C��ָ����ַд��һ���ֽ�
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_I2C_Write_Reg();
 */
static inline void MAPS_Dock_I2C_Write_Reg(I2C_I2Cn I2C_I2Cx,uint8 I2C_SlaveID,uint8 I2C_Reg,uint8 I2C_Data)
{
  I2C_Start(I2C_I2Cx);//���������ź�
  I2C_Write_Byte(I2C_I2Cx,(I2C_SlaveID << 1) | MWSR);
  I2C_Write_Byte(I2C_I2Cx,I2C_Reg);
  I2C_Write_Byte(I2C_I2Cx,I2C_Data);
  I2C_Stop(I2C_I2Cx);
  MAPS_Dock_I2C_Delay(10);
}

/*
 *  @brief      I2C��ָ����ַ����һ���ֽ�
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_I2C_Read_Reg();
 */
static inline uint8 MAPS_Dock_I2C_Read_Reg(I2C_I2Cn I2C_I2Cx,uint8 I2C_SlaveID,uint8 I2C_Reg)
{
  uint8 I2C_Result=0;
  
  I2C_Start(I2C_I2Cx);//���������ź�
  I2C_Write_Byte(I2C_I2Cx,(I2C_SlaveID << 1) | MWSR);
  I2C_Write_Byte(I2C_I2Cx,I2C_Reg);
  I2C_ReStart(I2C_I2Cx);
  I2C_Write_Byte(I2C_I2Cx,(I2C_SlaveID << 1) | MRSW);
  I2C_PutInRx(I2C_I2Cx);
  I2C_Result = I2C_D_REG(I2CN[I2C_I2Cx]);
  I2C_Wait(I2C_I2Cx);
  I2C_Stop(I2C_I2Cx);
  I2C_Result = I2C_D_REG(I2CN[I2C_I2Cx]);
  MAPS_Dock_I2C_Delay(10);
  
  return I2C_Result;
}

/*
 *  @brief      24C02ָ����ַд��һ���ֽ�
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_24C02_Write_Byte();
 */
void MAPS_Dock_24C02_Write_Byte(uint8 Addr,uint8 Data)
{
  MAPS_Dock_I2C_Write_Reg(I2C_I2C0,I2C_ADR_24C02,Addr,Data);
  MAPS_Dock_I2C_Delay(5000);//д��E2PROM��Ҫ5Ms��ʱ
}

/*
 *  @brief      24C02ָ����ַ����һ���ֽ�
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_24C02_Read_Byte();
 */
uint8 MAPS_Dock_24C02_Read_Byte(uint8 Addr)
{
  uint8 I2C_Result=0;
  
  I2C_Result = MAPS_Dock_I2C_Read_Reg(I2C_I2C0,I2C_ADR_24C02,Addr);
  
  return I2C_Result;
}

/*
 *  @brief      24C02ָ����ַд���ַ�������
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_24C02_Write_Buff();
 */
void MAPS_Dock_24C02_Write_Buff(uint8 Addr,uint8 *Buff)
{
  uint8 i=0;
  uint8 Len=0;//���鳤��
  uint8 *Buff_Size=Buff;
  
  while(*Buff_Size++ != 0)
  {
    Len++;
  }
  
  for(i=0;i<Len;i++)
  {
    MAPS_Dock_I2C_Write_Reg(I2C_I2C0,I2C_ADR_24C02,(Addr+i),*(Buff+i));
    MAPS_Dock_I2C_Delay(5000);//д��E2PROM��Ҫ5Ms��ʱ
  }
}

/*
 *  @brief      24C02ָ����ַ�����ַ�������
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_24C02_Read_Buff();
 */
void MAPS_Dock_24C02_Read_Buff(uint8 Addr,uint8 *Buff,uint8 Length)
{
  uint8 i=0;
  uint8 Len=Length;//���鳤��
  
  for(i=0;i<Len;i++)
  {
    *(Buff+i) = MAPS_Dock_I2C_Read_Reg(I2C_I2C0,I2C_ADR_24C02,(Addr+i));
  }
}