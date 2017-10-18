/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_I2C.h
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_I2C_H__
#define __MAPS_DOCK_I2C_H__

#include "Common.h"

/*
**I2C��ַ
*/
#define I2C_ADR_24C02   0x50    //24C02��ַ(E2PROM)
#define I2C_ADR_CS43L22 0x4A    //CS43L22��ַ

/*
**�ڲ��Ĵ�����ַ
*/
//24C02
#define I2C_24C02_MAX_ADR       0x00000100      //24C02����ַ255Byte

/*
**I2Cͨ����غ�
*/
#define MAPS_Dock_I2C_Delay(us) DELAY_US(us)    //I2C��ʱus

/*
**function declaration
*/
extern void MAPS_Dock_24C02_Write_Byte(uint8 Addr,uint8 Data);
extern uint8 MAPS_Dock_24C02_Read_Byte(uint8 Addr);
extern void MAPS_Dock_24C02_Write_Buff(uint8 Addr,uint8 *Buff);
extern void MAPS_Dock_24C02_Read_Buff(uint8 Addr,uint8 *Buff,uint8 Length);

#endif