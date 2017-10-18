/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PIT.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      PITn��ʱ�ж�
 *  @param      PITn    PITx    ģ���(PIT0~PIT3)
 *  @param      uint32  PIT_Count       ��ʱ�ж�ʱ��(��λΪbusʱ������)
 *  @since      v1.0
 *  Sample usage:
                PIT_Init(PIT0,1000);                           //��ʱ 1000 ��busʱ�� ���ж�
                Set_Vector_Handler(PIT0_VECTORn,pit_hander);   //�����жϷ��������ж���������
                enable_irq(PIT0_IRQn);                         //ʹ��PIT�ж�
 */
void PIT_Init(PITn PITx,uint32 PIT_Count)
{
  //����PITģ���,PIT��ʱֵ����0
  ASSERT((PITx <= PIT3) && (PIT_Count > 0));
  
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;//PITʱ��ʹ��
  
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);//����ģʽ��PIT����,PITʹ��
  PIT_LDVAL(PITx) = PIT_Count - 1;//����PIT��ʱ����ֵ(��������)
  
  PIT_Flag_Clear(PITx);//���жϱ�־
  
  PIT_TCTRL(PITx) = (0 | PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);//��ʱ���ж�ʹ��,��ʱ��ʹ��,��ʹ�ü���������
  
}

/*
 *  @brief      PITn��ʱ
 *  @param      PITn    PITx    ģ���(PIT0~PIT3)
 *  @param      uint32  PIT_Count       ��ʱʱ��(��λΪbusʱ������)
 *  @since      v1.0
 *  Sample usage:       PIT_Delay(PIT0, 1000);  //��ʱ 1000 ��busʱ��
 */
void PIT_Delay(PITn PITx,uint32 PIT_Count)
{
  //����PITģ���,PIT��ʱֵ����0
  ASSERT((PITx <= PIT3) && (PIT_Count > 0));
  
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;//PITʱ��ʹ��
  
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);//����ģʽ��PIT����,PITʹ��
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//��ֹPIT�ж�
  PIT_LDVAL(PITx) = PIT_Count - 1;//����PIT��ʱ����ֵ(��������)
  
  PIT_Flag_Clear(PITx);//���жϱ�־
  
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//��ֹPIT�ж�
  
  
  PIT_TCTRL(PITx) = (0 | PIT_TCTRL_TEN_MASK);//��ʱ��ʹ��,��ʹ�ü���������
  
  while((PIT_TFLG(PITx) & PIT_TFLG_TIF_MASK) != PIT_TFLG_TIF_MASK);
  
  PIT_Flag_Clear(PITx);//���жϱ�־
  
}

/*
 *  @brief      PITn��ʱ��ʼ
 *  @param      PITn    PITx    ģ���(PIT0~PIT3)
 *  @since      v1.0
 *  Sample usage:       PIT_Time_Start(PIT0);//PIT0��ʱ��ʼ
 */
void PIT_Time_Start(PITn PITx)
{
  //����PITģ���
  ASSERT(PITx <= PIT3);
  
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;//PITʱ��ʹ��
  
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);//����ģʽ��PIT����,PITʹ��
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//��ֹPIT�ж�
  PIT_LDVAL(PITx) = ~0;//����PIT��ʱ����ֵ(��������)
  
  PIT_Flag_Clear(PITx);//���жϱ�־
  
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//��ֹPIT�ж�
  PIT_TCTRL(PITx) = (0 | PIT_TCTRL_TEN_MASK);//��ʱ��ʹ��,��ʹ�ü���������
  
}

/*
 *  @brief      ��ȡ PITn��ʱʱ��(��ʱʱ��رն�ʱ��)
 *  @param      PITn    PITx    ģ���(PIT0~PIT3)
 *  @since      v1.0
 *  Sample usage:       uint32 time = PIT_Time_Get(PIT0);       //��ȡ PITn��ʱʱ��
 */
uint32 PIT_Time_Get(PITn PITx)
{
  uint32 PIT_Value=0;
  
  //����PITģ���
  ASSERT(PITx <= PIT3);
  
  PIT_Value = ~0 - PIT_CVAL(PITx);//����ʱ��ֵ=������ֵ0~-��ǰ����ֵPIT_CVAL
  
  if(PIT_TFLG(PITx) & PIT_TFLG_TIF_MASK)//�Ƿ񳬳�����ʱ��
  {
    PIT_Flag_Clear(PITx);//�����־����
    PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//��ֹPIT�ж�
    return ~0;
  }
  
  if(PIT_Value == ~0)
  {
    PIT_Value = 0xffffffff - 0x1;
  }
  
  return PIT_Value;
  
}

/*
 *  @brief      �ر�PIT
 *  @param      PITn    PITx    ģ���(PIT0~PIT3)
 *  @since      v1.0
 *  Sample usage:        PIT_Close(PIT0);       //�ر�PIT
 */
void PIT_Close(PITn PITx)
{
  //����PITģ���
  ASSERT(PITx <= PIT3);
  
  PIT_Flag_Clear(PITx);//�����־����
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//��ֹPIT�ж�
  
}