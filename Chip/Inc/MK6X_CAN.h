/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_CAN.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_CAN_H__
#define __MK6X_CAN_H__

#include "Common.h"

/*
**CANģ��ö��
*/
typedef enum
{
  CAN_CAN0,
  #ifdef MK66F18
  CAN_CAN1,
  #endif
  CAN_CAN_MAX,
}CAN_CANn;

/*
**MB���������
*/
typedef enum
{
  MB_NUM_0,
  MB_NUM_1,
  MB_NUM_2,
  MB_NUM_3,
  MB_NUM_4,
  MB_NUM_5,
  MB_NUM_6,
  MB_NUM_7,
  MB_NUM_8,
  MB_NUM_9,
  MB_NUM_10,
  MB_NUM_11,
  MB_NUM_12,
  MB_NUM_13,
  MB_NUM_14,
  MB_NUM_15,
  NUMBER_OF_MB,
}MB_NUM_n;

/*
**CAN����ģʽ
*/
typedef enum
{
  CAN_NORMAL,   //����ģʽ
  CAN_LOOPBACK, //�ػ�ģʽ
}CAN_MODE;

/*
**CAN������ö��
*/
typedef enum
{
  CAN_BAUD_10K,
  CAN_BAUD_20K,
  CAN_BAUD_50K,
  CAN_BAUD_100K,
  CAN_BAUD_125K,
  CAN_BAUD_250K,
  CAN_BAUD_500K,
  CAN_BAUD_1M,
  CAN_BAUD_MAX,
}CAN_BAUD_n;

/*
**CAN����ʱ��Դѡ��
*/
typedef enum
{
  CAN_CLKSRC_BUS,//����Busʱ��
  CAN_CLKSRC_OSC,//�ⲿOSC����
}CAN_CLKSRC_n;

/*
**CAN�����ʼĴ������ýṹ��
*/
typedef struct
{
  uint32_t Baud;        //������(KB/S)
  uint16_t Presdiv;     //��Ƶϵ��
  uint8_t  Prop_Seg;    //����ʱ���
  uint8_t  PSeg1;       //��λ�����1
  uint8_t  PSeg2;       //��λ�����2
  uint8_t  RJW;         //ͬ����ת���
  uint8_t  Res[2];      //����
}CAN_Baud_CFG_n;

/*
**�û�����CAN ID
*/
typedef struct
{
  uint32 ID:29;         //ID
  uint32 IDE:1;         //IDE   1:��չID,0:��׼ID
  uint32 RTR:1;         //RTR   1:Զ��֡,0:����֡
}CAN_USR_ID_n;

//CAN IDֵԽ��,�������ȼ�Խ��
//CAN ������������

//���ڷ��ͻ������ı��Ļ���������
#define CAN_CS_CODE_TX_INACTIVE         B8(1000)            //MB���ڷǼ���״̬
#define CAN_CS_CODE_TX_ABORT            B8(1001)            //MB������
#define CAN_CS_CODE_TX_DATA             B8(1100)            //MBΪһ����������֡(MB��RTRλΪ0)
#define CAN_CS_CODE_TX_REMOTE           B8(1100)            //MBΪһ������Զ������֡(MB��RTRλΪ1)
#define CAN_CS_CODE_TX_TANSWER          B8(1110)            //MBΪ��Զ������֡��һ�����ͻ�Ӧ֡

//���ڽ��ջ������ı��Ļ���������
#define CAN_CS_CODE_RX_INACTIVE         B8(0000)            //MB���ڷǼ���״̬
#define CAN_CS_CODE_RX_EMPTY            B8(0100)            //MB�����Ϊ��
#define CAN_CS_CODE_RX_FULL             B8(0010)            //MBΪ��
#define CAN_CS_CODE_RX_OVERRUN          B8(0110)            //д�뵽һ��������������MB������
#define CAN_CS_CODE_RX_RANSWER          B8(1010)            //һ����֡������Ϊȷ��һ��Զ������֡���ҷ���һ���ظ�֡.
#define CAN_CS_CODE_RX_BUSY             B8(0001)            //���ڸ��� MB ������.CPU���������MB

/*
**variate declaration
*/
extern CAN_MemMapPtr CANN[CAN_CAN_MAX];

/*
**function declaration
*/
extern void CAN_Init(CAN_CANn CAN_CANx,CAN_BAUD_n CAN_BAUD_x,CAN_MODE CAN_MODE_x,CAN_CLKSRC_n CAN_CLKSRC_x);
extern void CAN_Tx(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n CAN_USR_ID_x,uint8 Len,void *Buff);
extern void CAN_RxBuff_Enable(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n CAN_USR_ID_x);
extern void CAN_RxBuff_Mask(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,uint32 Mask,uint8 IsIRMQ);
extern void CAN_Rx(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n *CAN_USR_ID_x,uint8 *Len,void *Buff);
extern void CAN_Irq_En(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x);
extern void CAN_Clear_Flag(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x);
extern uint32 CAN_Get_Flag(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x);

#endif