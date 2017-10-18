/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_Misc.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      设置中断向量表地址
 *  @param      vtor    新的中断向量表地址
 *  @since      v1.0
 *  Sample usage:       write_vtor ((uint32)__VECTOR_RAM);  //新的中断向量地址
 */
void write_vtor (int vtor)
{
    ASSERT(vtor % 0x200 == 0);   //Vector Table base offset field. This value must be a multiple of 0x200.

    /* Write the VTOR with the new value */
    SCB->VTOR = vtor;
}

/*
 *  @brief      设置中断向量表里的中断服务函数
 *  @since      v1.0
 *  @warning    只有中断向量表位于icf指定的RAM区域时，此函数才有效
 *  Sample usage:       Set_Vector_Handler(UART3_RX_TX_VECTORn , uart3_handler);    //把 uart3_handler 函数添加到中断向量表
 */
void Set_Vector_Handler(VECTORn_t vector,void pfunc_handler(void))
{
    extern uint32 __VECTOR_RAM[];

    ASSERT(SCB->VTOR == (uint32)__VECTOR_RAM);  //断言，检测中断向量表是否在 RAM 里

    __VECTOR_RAM[vector] = (uint32)pfunc_handler;
}