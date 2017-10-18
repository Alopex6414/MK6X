/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_WDOG.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_WDOG_H__
#define __MK6X_WDOG_H__

#include "Common.h"

/*
**function declaration
*/
extern void WDOG_Unlock(void);
extern void WDOG_Feed(void);
extern void WDOG_Disable(void);
extern void WDOG_Enable(void);
extern void WDOG_Init(uint32 WDOG_Cnt);

#endif