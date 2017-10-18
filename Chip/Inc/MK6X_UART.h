/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_UART.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_UART_H__
#define __MK6X_UART_H__

#include "Common.h"

/*
**UART¶Ë¿ÚÃ¶¾Ù(UART0~UART4)
*/
typedef enum
{
  UART_UART0,
  UART_UART1,
  UART_UART2,
  UART_UART3,
  UART_UART4,
  #ifdef MK64F12
  UART_UART5,
  #endif
  UART_UART_MAX,
}UART_UARTn;


/*
**variate declaration
*/
extern UART_MemMapPtr UARTN[UART_UART_MAX];

/*
**function declaration
*/
extern void UART_Init(UART_UARTn UART_UARTx,uint32 UART_Baud);
extern void UART_GetChar(UART_UARTn UART_UARTx,char *ch);
extern void UART_PutChar(UART_UARTn UART_UARTx,char ch);
extern void UART_PutStr(UART_UARTn UART_UARTx,const uint8 *str);
extern void UART_Rx_IRQ_En(UART_UARTn UART_UARTx);
extern void UART_Tx_IRQ_En(UART_UARTn UART_UARTx);
extern void UART_Rx_IRQ_Dis(UART_UARTn UART_UARTx);
extern void UART_Tx_IRQ_Dis(UART_UARTn UART_UARTx);


#endif