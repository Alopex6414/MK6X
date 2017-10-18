/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       FSL_Types.h
 * @brief      USB_LIB
 */

#ifndef __FSL_TYPES_H__
#define __FSL_TYPES_H__

#include "Common.h"

#define FLAG_SET(BitNumber, Register)   (Register |=(1<<BitNumber))
#define FLAG_CLR(BitNumber, Register)   (Register &=~(1<<BitNumber))
#define FLAG_CHK(BitNumber, Register)   (Register & (1<<BitNumber))

#define _OUT            1
#define _IN             0
#define _ON             0
#define _OFF            1
#define _HIGH           1
#define _LOW            0

#define _BGND   asm(HALT)
#define _NOP    asm(NOP)

#endif