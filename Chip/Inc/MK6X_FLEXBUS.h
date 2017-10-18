/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FLEXBUS.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_FLEXBUS_H__
#define __MK6X_FLEXBUS_H__

#include "Common.h"

//下面两个参数都与 flexbus_8080_init 函数相关，修改后可能需要修改 flexbus_8080_init 函数的内容
#define FB_BA       0x6000      //基地址     = FB_BA * 0x10000 ，用于区分 不同的片选信号
                                //参考 System memory map 的说明， External Memory 的范围为 0x6000_0000 ~ 0x9FFF_FFFF
                                //即 FB_BA 的取值范围为 0x6000 ~ 0x9FFF

#define FB_BAM      0x0800      //基地址掩膜 = (FB_BA + FB_BAM)* 0x10000 ，用于区分 同一个CS控制的两个不连续的块的地址

#define FB_8080_CMD     (*(volatile uint16 *)(FB_BA * 0x10000))
#define FB_8080_DATA    (*(volatile uint16 *)((FB_BA + FB_BAM )* 0x10000))

/*
**function declaration
*/
extern void FlexBus_8080_Init(void);


#endif