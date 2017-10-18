/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_USB.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_USB_H__
#define __MK6X_USB_H__

#include "Common.h"

//USB配置相关宏
#define USB_CLOCK_PLL                   //USB使用PLL时钟
#define USB_CLK_DIV             4       //USB时钟源分频因子
#define USB_CLK_FRAC            1       //USB时钟源倍频因子

/*
**function declaration
*/
extern void USB_Init(void);
extern void USB_COM_Init(void);
extern void USB_Enum_Wait(void);
extern uint8 USB_COM_Rx(uint8_t *Rx_Buf);
extern void USB_COM_Tx(uint8 *Tx_Buf,uint8 Len);

#endif