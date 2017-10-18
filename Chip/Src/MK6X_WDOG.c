/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_WDOG.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      ����WDOG
 *  @since      v1.0
 */
void WDOG_Unlock(void)
{
  uint8 WDOG_Temp=0;
  
  WDOG_Temp = __get_BASEPRI();//���ؼĴ��� PRIMASK ��ֵ(1bit) 1:���ж� 0:���ж�
  
  DisableInterrupts;//�����ж�
  
  WDOG_UNLOCK = 0xC520;//��WDOG_UNLOCK�Ĵ����Ⱥ�д��0xC520��0xD928����WDOG
  WDOG_UNLOCK = 0xD928;
  
  if(WDOG_Temp == 0)//����֮ǰ�ǿ��ж�
  {
    EnableInterrupts;//�����ж�
  }
  
}

/*
 *  @brief      ����WDOG������
 *  @since      v1.0
 */
void WDOG_Feed(void)
{
  uint8 WDOG_Temp=0;
  
  WDOG_Temp = __get_BASEPRI();//���ؼĴ��� PRIMASK ��ֵ(1bit) 1:���ж� 0:���ж�
  
  DisableInterrupts;//�����ж�
  
  WDOG_REFRESH = 0xA602;//����WDOG������,Feed Dog
  WDOG_REFRESH = 0xB480;
  
  if(WDOG_Temp == 0)//����֮ǰ�ǿ��ж�
  {
    EnableInterrupts;//�����ж�
  }
}

/*
 *  @brief      ��ֹWDOG
 *  @since      v1.0
 */
void WDOG_Disable(void)
{
  WDOG_Unlock();//����WDOG,����WDOG�Ĵ���
  WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;//WDOGEN����,��ֹWDOG
}

/*
 *  @brief      ����WDOG
 *  @since      v1.0
 */
void WDOG_Enable(void)
{
  WDOG_Unlock();//����WDOG,����WDOG�Ĵ���
  WDOG_STCTRLH |= WDOG_STCTRLH_WDOGEN_MASK;//WDOGEN��λ,����WDOG
}

/*
 *  @brief      ��ʼ��WDOG������ʱ��
 *  @param      WDOG_Cnt    ʱ��(��λMS)
 *  @since      v1.0
 */
void WDOG_Init(uint32 WDOG_Cnt)
{
  ASSERT(WDOG_Cnt >= 4);//����ʱ������Ϊ4����
  
  WDOG_Unlock();//����WDOG,����WDOG�Ĵ���
  
  WDOG_PRESC = WDOG_PRESC_PRESCVAL(0);//���÷�Ƶϵ�� = PRESCVAL +1(PRESCVALȡֵ��ΧΪ0~7)
  
  WDOG_TOVALH = WDOG_Cnt >> 16;//����WDOGʱ��
  WDOG_TOVALL = (uint16)(WDOG_Cnt & 0x0000ffff);
  
  WDOG_STCTRLH = (0 | WDOG_STCTRLH_WDOGEN_MASK          //WDOGʹ��
                    | WDOG_STCTRLH_ALLOWUPDATE_MASK     //WDOG�������
                    | WDOG_STCTRLH_STOPEN_MASK          //WDOG��ֹͣģʽ
                    | WDOG_STCTRLH_WAITEN_MASK          //WDOG�ڵȴ�ģʽ
                  );
  
}