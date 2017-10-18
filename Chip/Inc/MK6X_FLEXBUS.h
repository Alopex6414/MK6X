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

//���������������� flexbus_8080_init ������أ��޸ĺ������Ҫ�޸� flexbus_8080_init ����������
#define FB_BA       0x6000      //����ַ     = FB_BA * 0x10000 ���������� ��ͬ��Ƭѡ�ź�
                                //�ο� System memory map ��˵���� External Memory �ķ�ΧΪ 0x6000_0000 ~ 0x9FFF_FFFF
                                //�� FB_BA ��ȡֵ��ΧΪ 0x6000 ~ 0x9FFF

#define FB_BAM      0x0800      //����ַ��Ĥ = (FB_BA + FB_BAM)* 0x10000 ���������� ͬһ��CS���Ƶ������������Ŀ�ĵ�ַ

#define FB_8080_CMD     (*(volatile uint16 *)(FB_BA * 0x10000))
#define FB_8080_DATA    (*(volatile uint16 *)((FB_BA + FB_BAM )* 0x10000))

/*
**function declaration
*/
extern void FlexBus_8080_Init(void);


#endif