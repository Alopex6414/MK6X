/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DAC.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_DAC_H__
#define __MK6X_DAC_H__

#include "Common.h"

/*
**DACÄ£¿éÃ¶¾Ù
*/
typedef enum
{
  DAC_DAC0,
  DAC_DAC1,
  DAC_DAC_MAX,
}DAC_DACn;

/*
**variate declaration
*/
extern DAC_MemMapPtr DACN[DAC_DAC_MAX];

/*
**function declaration
*/
extern void DAC_Init(DAC_DACn DAC_DACx);
extern void DAC_Out(DAC_DACn DAC_DACx,uint16 DAC_Value);


#endif