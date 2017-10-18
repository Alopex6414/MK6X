/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FLEXBUS.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      flexbus��ʼ��Ϊ8080Э��
 *  @since      v1.0
 */
void FlexBus_8080_Init(void)
{
  //flexbus ����ֱ��֧�� 8080Э�飬����֧�� 6800Э��
  //���ǿ������� cmd �� data ���ݵĵ�ַ��ͬ���Ӷ�ͨ����ַ�����������������
  SIM_SOPT2 |= SIM_SOPT2_FBSL(3);             //FlexBus��ȫˮƽ:����ָ������ݷ���
  SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;        //ʹ��ʱ��
  
  //�������ݹܽŸ���
  PORT_Init(PTD6 ,ALT5 | HDS);              //PTD6 ����Ϊ fb_ad[0] ,����Ϊ �������������
  PORT_Init(PTD5 ,ALT5 | HDS);              //PTD5 ����Ϊ fb_ad[1] ,����Ϊ �������������
  PORT_Init(PTD4 ,ALT5 | HDS);              //PTD4 ����Ϊ fb_ad[2] ,����Ϊ �������������
  PORT_Init(PTD3 ,ALT5 | HDS);              //PTD3 ����Ϊ fb_ad[3] ,����Ϊ �������������
  PORT_Init(PTD2 ,ALT5 | HDS);              //PTD2 ����Ϊ fb_ad[4] ,����Ϊ �������������
  PORT_Init(PTC10,ALT5 | HDS);              //PTC10����Ϊ fb_ad[5] ,����Ϊ �������������
  PORT_Init(PTC9 ,ALT5 | HDS);              //PTC9 ����Ϊ fb_ad[6] ,����Ϊ �������������
  PORT_Init(PTC8 ,ALT5 | HDS);              //PTC8 ����Ϊ fb_ad[7] ,����Ϊ �������������
  PORT_Init(PTC7 ,ALT5 | HDS);              //PTC7 ����Ϊ fb_ad[8] ,����Ϊ �������������
  PORT_Init(PTC6 ,ALT5 | HDS);              //PTC6 ����Ϊ fb_ad[9] ,����Ϊ �������������
  PORT_Init(PTC5 ,ALT5 | HDS);              //PTC5 ����Ϊ fb_ad[10],����Ϊ �������������
  PORT_Init(PTC4 ,ALT5 | HDS);              //PTC4 ����Ϊ fb_ad[11],����Ϊ �������������
  PORT_Init(PTC2 ,ALT5 | HDS);              //PTC2 ����Ϊ fb_ad[12],����Ϊ �������������
  PORT_Init(PTC1 ,ALT5 | HDS);              //PTC1 ����Ϊ fb_ad[13],����Ϊ �������������
  PORT_Init(PTC0 ,ALT5 | HDS);              //PTC0 ����Ϊ fb_ad[14],����Ϊ �������������
  PORT_Init(PTB18,ALT5 | HDS);              //PTB18����Ϊ fb_ad[15],����Ϊ �������������
  
  //���ÿ��ƹܽŸ���
  //8080����,��Intel����,��Ҫ�ĸ��߿����ߣ�RDдʹ��, WR��ʹ��, RS����/ָ��ѡ��, CSƬѡ
  PORT_Init(PTB19,ALT5 | HDS);              //PTB19����Ϊ fb_oe_b  ,����Ϊ ������������� , fb_oe_b ʱ����� 8080 ���ߵ� RDдʹ��
  PORT_Init(PTD1 ,ALT5 | HDS);              //PTD1 ����Ϊ fb_cs0_b ,����Ϊ ������������� , fb_cs0_bʱ����� 8080 ���ߵ� CSƬѡ
  PORT_Init(PTC11,ALT5 | HDS);              //PTC11����Ϊ fb_r/w   ,����Ϊ ������������� , fb_r/w  ʱ����� 8080 ���ߵ� WR��ʹ��
  
  //Ŀǰ��ȱ 8080 ���ߵ� RS����/ָ��ѡ����
  //flexbus�����ó������ַ�������Ŀ飨��16λ��ַ����ͬ�����Ӷ����õ�ַ�������� 8080 ���ߵ� RS����/ָ��ѡ����
  //��16λ�ĵ�ַ��FB_BA ��������Ϊ 0x6000 �������ѡ��� ��ַ���� fb_ad[16] ~ fb_ad[28]
  //FB_BAM����Ϊ 0x0800 ����ѡ�� fb_ad[27] ��Ϊ RS ��(0x0800 0000 == 1<<27 )
  // RS == 1 ʱ �������ݣ�RS == 0 ʱ��������
  //��� 0x6000 0000 Ϊ �����ַ �� 0x6800 0000 Ϊ���ݶ˿�
  PORT_Init(PTC12 ,ALT5 | HDS);              //PTC12����Ϊ fb_ad[27],����Ϊ ������������� , fb_ad[27]��Ϊ8080 ���ߵ� RS����/ָ��ѡ����

  FB_CSAR(0) = FB_CSAR_BA(FB_BA);            //����ַ Base address
  FB_CSMR(0) = (0
                | FB_CSMR_BAM(FB_BAM)       //BAM = 0x0800 ,���ص�ַ���� Ϊ 0x,800 FFFF ,�� Ƭѡ��Ч�ĵ�ַΪ ����ַ ~ ������ַ + ���ص�ַ���룩 ,0x0800 0000 ��Ӧ�� FB_AD27
                | FB_CSMR_V_MASK            //ʹ��Ƭѡ�ź� FB_CS0
                );
  FB_CSCR(0) = (FB_CSCR_BLS_MASK            //�Ҷ���
                | FB_CSCR_PS(2)             //16Byte����
                | FB_CSCR_AA_MASK           //�Զ�Ӧ��
                );
}