/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       USB_CDC.h
 * @brief      USB_LIB
 */

#ifndef __USB_CDC_H__
#define __USB_CDC_H__

#include "USB.h"
#include "FSL_Types.h"

#define CDC_INPointer   gu8EP2_IN_ODD_Buffer
#define CDC_OUTPointer  gu8EP3_OUT_ODD_Buffer

/* Defines */
#define CDC_BUFFER_SIZE 128
#define EP_OUT          EP3
#define EP_IN           EP2

/* USB_CDC Definitions */
#define WAITING_FOR_ENUMERATION 0x00
#define SET_LINE_CODING         0x20
#define GET_LINE_CODING         0x21
#define SET_CONTROL_LINE_STATE  0x22
#define LOADER_MODE             0xAA
#define GET_INTERFACE           0x0A
#define GET_STATUS              0x00
#define CLEAR_FEATURE           0x01
#define SET_FEATURE             0x03

/*
**结构体类型
*/
typedef struct
{
  uint32 DTERate;
  uint8  CharFormat;
  uint8  ParityType;
  uint8  Databits;
}CDC_Line_Coding;

/*
**variate declaration
*/
extern uint8 u8CDCState;
extern uint8 CDC_OUT_Data[];
extern CDC_Line_Coding com_cfg;

/*
**function declaration
*/
extern void CDC_Init(void);
extern void CDC_Engine(void);
extern uint8 CDC_InterfaceReq_Handler(void);

#endif