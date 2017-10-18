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

//USB������غ�
#define USB_CLOCK_PLL                   //USBʹ��PLLʱ��
#define USB_CLK_DIV             4       //USBʱ��Դ��Ƶ����
#define USB_CLK_FRAC            1       //USBʱ��Դ��Ƶ����

/*
**function declaration
*/
extern void USB_Init(void);
extern void USB_COM_Init(void);
extern void USB_Enum_Wait(void);
extern uint8 USB_COM_Rx(uint8_t *Rx_Buf);
extern void USB_COM_Tx(uint8 *Tx_Buf,uint8 Len);

#endif