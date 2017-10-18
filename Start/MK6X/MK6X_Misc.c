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
 *  @brief      �����ж��������ַ
 *  @param      vtor    �µ��ж��������ַ
 *  @since      v1.0
 *  Sample usage:       write_vtor ((uint32)__VECTOR_RAM);  //�µ��ж�������ַ
 */
void write_vtor (int vtor)
{
    ASSERT(vtor % 0x200 == 0);   //Vector Table base offset field. This value must be a multiple of 0x200.

    /* Write the VTOR with the new value */
    SCB->VTOR = vtor;
}

/*
 *  @brief      �����ж�����������жϷ�����
 *  @since      v1.0
 *  @warning    ֻ���ж�������λ��icfָ����RAM����ʱ���˺�������Ч
 *  Sample usage:       Set_Vector_Handler(UART3_RX_TX_VECTORn , uart3_handler);    //�� uart3_handler ������ӵ��ж�������
 */
void Set_Vector_Handler(VECTORn_t vector,void pfunc_handler(void))
{
    extern uint32 __VECTOR_RAM[];

    ASSERT(SCB->VTOR == (uint32)__VECTOR_RAM);  //���ԣ�����ж��������Ƿ��� RAM ��

    __VECTOR_RAM[vector] = (uint32)pfunc_handler;
}