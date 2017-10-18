/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FTM.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_FTM_H__
#define __MK6X_FTM_H__

#include "Common.h"

/*
**FTMģ���ö��
*/
typedef enum
{
  FTM_FTM0,
  FTM_FTM1,
  FTM_FTM2,
  FTM_FTM3,
  FTM_FTM_MAX,
}FTM_FTMn;

/*
**FTMͨ����
*/
typedef enum
{
  FTM_CH0,
  FTM_CH1,
  FTM_CH2,
  FTM_CH3,
  FTM_CH4,
  FTM_CH5,
  FTM_CH6,
  FTM_CH7,
}FTM_CHn;

/*
**FTM��Ƶϵ��
*/
typedef enum
{
  FTM_PS_1,
  FTM_PS_2,
  FTM_PS_4,
  FTM_PS_8,
  FTM_PS_16,
  FTM_PS_32,
  FTM_PS_64,
  FTM_PS_128,
  FTM_PS_MAX,
}FTM_PS_n;

/*
**FTM���벶׽
*/
typedef enum
{
  FTM_Rising,                   //�����ز�׽
  FTM_Falling,                  //�½��ز�׽
  FTM_Rising_or_Falling,        //�����ز�׽
}FTM_INPUT_CFG;

/*
**FTMģ��PWM��������
*/
#define FTM0_PRECISON   10000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define FTM1_PRECISON   10000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define FTM2_PRECISON   10000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define FTM3_PRECISON   10000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON


/*
**variate declaration
*/
extern FTM_MemMapPtr FTMN[FTM_FTM_MAX];

/*
**function declaration
*/
extern void FTM_PWM_Init(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,uint32 FTM_Freq,uint32 FTM_Duty);
extern void FTM_PWM_Duty(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,uint32 FTM_Duty);
extern void FTM_PWM_Freq(FTM_FTMn FTM_FTMx,uint32 FTM_Freq);
extern void FTM_Input_Init(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,FTM_INPUT_CFG FTM_CFG,FTM_PS_n FTM_PS_x);
extern uint16 FTM_Input_Get(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx);
extern void FTM_Input_Clean(FTM_FTMn FTM_FTMx);
extern void FTM_QUAD_Init(FTM_FTMn FTM_FTMx);
extern int16 FTM_QUAD_Get(FTM_FTMn FTM_FTMx);
extern void FTM_QUAD_Clean(FTM_FTMn FTM_FTMx);

#endif