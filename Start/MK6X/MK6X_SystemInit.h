/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_SystemInit.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */
#ifndef __MK6X_SYSTEMINIT_H__
#define __MK6X_SYSTEMINIT_H__

#include "Common.h"


/*
**variate declaration
*/
extern uint16  MK6X_Core_MHz;
extern uint32  MK6X_Core_KHz;
extern uint32  MK6X_Bus_KHz;

/*
**function declaration
*/
extern void Common_StartUp(void);
extern void SysInit(void);
extern void Start(void);


#endif