/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DWT.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_DWT_H__
#define __MK6X_DWT_H__

#include "Common.h"

#define DWT_CLK_KHZ             MK6X_Core_KHz

/*
**function declaration
*/
extern void DWT_Delay_us(uint32 DWT_us);
extern void DWT_Delay_ms(uint32 DWT_ms);


#endif