/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_It.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_IT_H__
#define __MK6X_IT_H__

#include "Common.h"
#include "MK6X_Vectors.h"

#undef  VECTOR_077
#define VECTOR_077      PORTC_PTC19_IRQHandler

#undef  VECTOR_078
#define VECTOR_078      PORTD_PTD15_IRQHandler

#undef  VECTOR_064
#define VECTOR_064      PIT0_IRQHandler

/*
**variate declaration
*/
extern int PIT_Count;//PIT计数值
extern uint16 ADC_Convert_Result[2];//ADC采样值

/*
**function declaration
*/
extern void PORTC_PTC19_IRQHandler(void);
extern void PORTD_PTD15_IRQHandler(void);
extern void PIT0_IRQHandler(void);



#endif