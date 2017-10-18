/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_Misc.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_MISC_H__
#define __MK6X_MISC_H__

#include "Common.h"

/*
**中断有关宏
*/
#define enable_irq(irq)                 NVIC_EnableIRQ(irq)         //使能IRQ
#define disable_irq(irq)                NVIC_DisableIRQ(irq)        //禁止IRQ
#define set_irq_priority(irq,pri0)      NVIC_SetPriority(irq,pri0)  //设置优先级

#define EnableInterrupts                __enable_irq()              //使能全部中断
#define DisableInterrupts               __disable_irq()             //禁止全部中断

/*
**variate declaration
*/

/*
**function declaration
*/
extern void write_vtor (int vtor);
extern void Set_Vector_Handler(VECTORn_t vector,void pfunc_handler(void));

#endif