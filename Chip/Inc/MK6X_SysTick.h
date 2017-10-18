/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_SysTick.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_SYSTICK_H__
#define __MK6X_SYSTICK_H__


#include "Common.h"

/*
**SysTick ±÷”
*/
#define SYSTICK_CLK_KHZ MK6X_Core_KHz

#define SysTick_DELAY_US(us)    SysTick_Delay(us * (SYSTICK_CLK_KHZ / 1000))
#define SysTick_DELAY_NS(ns)    SysTick_Delay(ns * (SYSTICK_CLK_KHZ / 1000000))

#define SysTick_TIMING_MS(ms)   SysTick_Timing(ms * (SYSTICK_CLK_KHZ))
#define SysTick_TIMING_US(us)   SysTick_Timing(us * (SYSTICK_CLK_KHZ / 1000))
#define SysTick_TIMING_NS(ns)   SysTick_Timing(ns * (SYSTICK_CLK_KHZ / 1000000))

/*
**function declaration
*/
extern void SysTick_Delay(uint32 SysTick_Time);
extern void SysTick_Delay_ms(uint32 SysTick_Time_ms);
extern void SysTick_Timing(uint32 SysTick_Time);

#endif