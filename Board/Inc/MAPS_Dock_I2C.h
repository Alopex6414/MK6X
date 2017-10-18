/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_I2C.h
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_I2C_H__
#define __MAPS_DOCK_I2C_H__

#include "Common.h"

/*
**I2C地址
*/
#define I2C_ADR_24C02   0x50    //24C02地址(E2PROM)
#define I2C_ADR_CS43L22 0x4A    //CS43L22地址

/*
**内部寄存器地址
*/
//24C02
#define I2C_24C02_MAX_ADR       0x00000100      //24C02最大地址255Byte

/*
**I2C通信相关宏
*/
#define MAPS_Dock_I2C_Delay(us) DELAY_US(us)    //I2C延时us

/*
**function declaration
*/
extern void MAPS_Dock_24C02_Write_Byte(uint8 Addr,uint8 Data);
extern uint8 MAPS_Dock_24C02_Read_Byte(uint8 Addr);
extern void MAPS_Dock_24C02_Write_Buff(uint8 Addr,uint8 *Buff);
extern void MAPS_Dock_24C02_Read_Buff(uint8 Addr,uint8 *Buff,uint8 Length);

#endif