/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_CAN.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**CAN��ַָ��
*/
CAN_MemMapPtr CANN[CAN_CAN_MAX]=
{
  CAN0_BASE_PTR,//CAN0��ַָ��
  #ifdef MK66F18
  CAN1_BASE_PTR,//CAN1��ַָ��
  #endif
};

/*
**CANʱ��Դ50MHz
*/
CAN_Baud_CFG_n CAN_Baud_CFG_50000K[CAN_BAUD_MAX]=
{
  //BAND,PRESDIV,PROP_SEG,PSEG1,PSEG2,RJW
  {10,  624,    4,      0,      0,      0},//������:87.50%
  {20,  124,    12,     2,      2,      2},//������:85.00%
  {50,  124,    4,      0,      0,      0},//������:87.50%
  {100, 24,     12,     2,      2,      2},//������:85.00%
  {125, 24,     10,     1,      1,      1},//������:87.50%
  {250, 24,     4,      0,      0,      0},//������:87.50%
  {500, 4,      12,     2,      2,      2},//������:85.00%
  {1000,1,      9,      6,      6,      3},//������:72.00%
};

/*
**CANʱ��Դ60MHz
*/
CAN_Baud_CFG_n CAN_Baud_CFG_60000K[CAN_BAUD_MAX]=
{
  //BAND,PRESDIV,PROP_SEG,PSEG1,PSEG2,RJW
  {10,  249,    16,     2,      2,      2},//������:87.50%
  {20,  124,    16,     2,      2,      2},//������:87.50%
  {50,  49,     16,     2,      2,      2},//������:87.50%
  {100, 24,     16,     2,      2,      2},//������:87.50%
  {125, 19,     16,     2,      2,      2},//������:87.50%
  {250, 9,      16,     2,      2,      2},//������:87.50%
  {500, 4,      16,     2,      2,      2},//������:87.50%
  {1000,2,      8,      4,      4,      3},//������:75.00%
};

/*
 *  @brief      ����CAN�Ĳ�����
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      CAN_BAUD_n      CAN_BAUD_x      �����ʱ��
 *  @since      v1.0
 *  Sample usage:       CAN_Set_Baud(CAN1,CAN_BAUD_20K)
 */
static void CAN_Set_Baud(CAN_CANn CAN_CANx,CAN_BAUD_n CAN_BAUD_x)
{
  CAN_Baud_CFG_n *PCAN_Baud;
  uint32 CAN_CLK_KHz=0;
  uint8 BFreezeMode=0;
  
  if(CAN_CTRL1_REG(CANN[CAN_CANx]) & CAN_CTRL1_CLKSRC_MASK)
  {
    CAN_CLK_KHz = MK6X_Bus_KHz;         //����ʱ��Bus
  }
  else
  {
    CAN_CLK_KHz = EXTAL_IN_MHz * 1000;  //����ʱ��OSC
  }
  
  if(CAN_CLK_KHz == 50000)
  {
    PCAN_Baud = &CAN_Baud_CFG_50000K[CAN_BAUD_x];
  }
  else if(CAN_CLK_KHz == 60000)
  {
    PCAN_Baud = &CAN_Baud_CFG_60000K[CAN_BAUD_x];
  }
  else
  {
    ASSERT(0);
  }
  
  //���붳��ģʽ
  if(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_HALT_MASK))
  {
    CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_HALT_MASK;
    
    while(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK));
    
    BFreezeMode = 0;
  }
  else
  {
    BFreezeMode = 1;
  }
  
  //���üĴ���
  CAN_CTRL1_REG(CANN[CAN_CANx]) &= ~(0
                                     | CAN_CTRL1_PROPSEG_MASK
                                     | CAN_CTRL1_RJW_MASK
                                     | CAN_CTRL1_PSEG1_MASK
                                     | CAN_CTRL1_PSEG2_MASK
                                     | CAN_CTRL1_PRESDIV_MASK
                                     );
  
  CAN_CTRL1_REG(CANN[CAN_CANx]) |= (0
                                    | CAN_CTRL1_PROPSEG(PCAN_Baud->Prop_Seg)
                                    | CAN_CTRL1_RJW(PCAN_Baud->RJW)
                                    | CAN_CTRL1_PSEG1(PCAN_Baud->PSeg1)
                                    | CAN_CTRL1_PSEG2(PCAN_Baud->PSeg2)
                                    | CAN_CTRL1_PRESDIV(PCAN_Baud->Presdiv)
                                    );
  
  //�ָ�CAN����ģʽ
  if(!BFreezeMode)
  {
    CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_HALT_MASK;
    
    while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK);
    
    while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_NOTRDY_MASK);
  }
  
}

/*
 *  @brief      CAN ��ʼ��
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      CAN_BAUD_n      CAN_BAUD_x      �����ʱ��
 *  @param      CAN_MODE        CAN_MODE_x      CAN ģʽ(����ģʽ,�ػ�ģʽ)
 *  @param      CAN_CLKSRC_n    CAN_CLKSRC_x    CAN ʱ��Դ(����ʱ��,�ⲿ����)
 *  @since      v1.0
 *  Sample usage:       CAN_Init(CAN1,CAN_BAUD_20K,CAN_LOOPBACK);   //��ʼ�� CAN1,������ 20Kb/s,�ػ�ģʽ
 */
void CAN_Init(CAN_CANn CAN_CANx,CAN_BAUD_n CAN_BAUD_x,CAN_MODE CAN_MODE_x,CAN_CLKSRC_n CAN_CLKSRC_x)
{
  uint8 i=0;
  
  switch(CAN_CANx)
  {
    case CAN_CAN0:
                  SIM_SCGC6 |= SIM_SCGC6_FLEXCAN0_MASK;//CAN0ʱ��ʹ��
                  PORT_Init(CAN0_TX_PIN,ALT2);
                  PORT_Init(CAN0_RX_PIN,ALT2);
                  break;
    #ifdef MK66F18
    case CAN_CAN1:
                  SIM_SCGC3 |= SIM_SCGC3_FLEXCAN1_MASK;//CAN1ʱ��ʹ��
                  PORT_Init(CAN1_TX_PIN,ALT2);
                  PORT_Init(CAN1_RX_PIN,ALT2);
                  break;
    #endif
    default:
                  ASSERT(0);
                  break;
  }
  
  if(CAN_CLKSRC_x == CAN_CLKSRC_BUS)
  {
    CAN_CTRL1_REG(CANN[CAN_CANx]) |= CAN_CTRL1_CLKSRC_MASK;//����Busʱ��
  }
  else
  {
    OSC_CR |= OSC_CR_ERCLKEN_MASK;//�ⲿ����ʱ��OSC
  }
  
  CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_MDIS_MASK;            //CANģ��ʹ��
  CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_FRZ_MASK;              //CAN����ģʽʹ��
  while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_LPMACK_MASK);     //�ȴ���λ
  CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_SOFTRST_MASK;          //�����λ
  while(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK));  //�ȴ����붳��ģʽ
  
  for(i=16;i>0;i--)
  {
    CAN_CS_REG(CANN[CAN_CANx],i) = 0;
    CAN_ID_REG(CANN[CAN_CANx],i) = 0;
    CAN_WORD0_REG(CANN[CAN_CANx],i) = 0;
    CAN_WORD1_REG(CANN[CAN_CANx],i) = 0;
  }
  
  CAN_CTRL2_REG(CANN[CAN_CANx]) = (0 | CAN_CTRL2_TASD(22));
  CAN_MCR_REG(CANN[CAN_CANx]) = (CAN_MCR_REG(CANN[CAN_CANx]) & (~CAN_MCR_IDAM_MASK)) | CAN_MCR_IDAM(0);
  
  //���ò�����
  CAN_Set_Baud(CAN_CANx,CAN_BAUD_x);
  
  if(CAN_MODE_x == CAN_LOOPBACK)
  {
    CAN_CTRL1_REG(CANN[CAN_CANx]) |= CAN_CTRL1_LPB_MASK;//�ػ�ģʽ
  }
  
  //Ĭ�϶�������
  CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_IRMQ_MASK;
  
  for(i=NUMBER_OF_MB;i>0;i--)
  {
    CAN_RXIMR_REG(CANN[CAN_CANx],i) = 0;
  }
  
  CAN_RXMGMASK_REG(CANN[CAN_CANx]) = 0;
  CAN_RX14MASK_REG(CANN[CAN_CANx]) = 0;
  CAN_RX15MASK_REG(CANN[CAN_CANx]) = 0;
  
  //����ģʽ���������
  CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_HALT_MASK;
  
  //�ȴ�ͬ���˳�����ģʽ
  while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK);
  
  //�ȴ����ڶ���ģʽ,����ģʽ,ֹͣģʽ
  while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_NOTRDY_MASK);
  
}

/*
 *  @brief      CAN ��������
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @param      CAN_USR_ID_n    CAN_USR_ID_x    ID���
 *  @param      uint8           Len             ���ݳ���
 *  @param      void*           Buff            ��������ַ
 *  @since      v1.0
 *  Sample usage:       CAN_Tx(CAN1,CAN_TX_MB,can_tx_id,DATA_LEN, txbuff);  //CAN��������.������CAN_TX_MB,����ID:tx_ID,���ݻ�����txbuff,���� DATA_LEN
 */
void CAN_Tx(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n CAN_USR_ID_x,uint8 Len,void *Buff)
{
  uint32 Word=0;
  
  ASSERT(Len <= 8);
  
  CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = (0
                                         | CAN_CS_CODE(CAN_CS_CODE_TX_INACTIVE)         //������д�Ǽ������
                                         | (CAN_USR_ID_x.IDE << CAN_CS_IDE_SHIFT)       //������дIDEλ
                                         | (CAN_USR_ID_x.RTR << CAN_CS_RTR_SHIFT)       //������дRTRλ
                                         | CAN_CS_DLC(Len)                              //������д���ݳ���
                                         );
  
  if(CAN_USR_ID_x.IDE)
  {
    CAN_ID_REG(CANN[CAN_CANx],MB_NUM_x) = (0 | CAN_ID_PRIO(1) | CAN_ID_EXT(CAN_USR_ID_x.ID));
  }
  else
  {
    CAN_ID_REG(CANN[CAN_CANx],MB_NUM_x) = (0 | CAN_ID_PRIO(1) | CAN_ID_STD(CAN_USR_ID_x.ID));
  }
  
  Word = *(uint32*)Buff;
  CAN_WORD0_REG(CANN[CAN_CANx],MB_NUM_x) = SWAP32(Word);
  Word = *((uint32*)Buff + 1);
  CAN_WORD1_REG(CANN[CAN_CANx],MB_NUM_x) = SWAP32(Word);
  
  //��ʼ����
  CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = (0
                                         | CAN_CS_CODE(CAN_CS_CODE_TX_DATA)
                                         | CAN_CS_DLC(Len)
                                         );
  
  //��ʱ�ȴ��������
  while(!(CAN_IFLAG1_REG(CANN[CAN_CANx]) & (1 << MB_NUM_x)));
  
  //�屨�Ļ������жϱ�־
  CAN_IFLAG1_REG(CANN[CAN_CANx]) = (1 << MB_NUM_x);
  
}

/*
 *  @brief      ʹ�� CAN ���ջ�����
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @param      CAN_USR_ID_n    CAN_USR_ID_x    ID���
 *  @since      v1.0
 *  Sample usage:      CAN_RxBuff_Enble(CAN1,CAN_RX_MB,can_my_id);//ʹ�ܽ��ջ�����
 */
void CAN_RxBuff_Enable(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n CAN_USR_ID_x)
{
  //��MB����Ϊ�Ǽ���״̬
  CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = CAN_CS_CODE(CAN_CS_CODE_RX_INACTIVE);
  
  if(CAN_USR_ID_x.IDE)
  {
    CAN_ID_REG(CANN[CAN_CANx],MB_NUM_x) = (0 | CAN_ID_EXT(CAN_USR_ID_x.ID));
    
    CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = (0
                                           | CAN_CS_IDE_MASK
                                           | (CAN_USR_ID_x.RTR << CAN_CS_IDE_SHIFT)
                                           | CAN_CS_CODE(CAN_CS_CODE_RX_EMPTY)
                                           ); 
  }
  else
  {
    CAN_ID_REG(CANN[CAN_CANx],MB_NUM_x) = (0 | CAN_ID_STD(CAN_USR_ID_x.ID));
    
    CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = (0
                                           | (CAN_USR_ID_x.RTR << CAN_CS_IDE_SHIFT)
                                           | CAN_CS_CODE(CAN_CS_CODE_RX_EMPTY)
                                           ); 
  }
  
}

/*
 *  @brief      CAN ������������
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @param      uint32          Mask            ����
 *  @param      uint8           IsIRMQ          �Ƿ�ѡ��������루0Ϊȫ�����룬����Ϊ�������룩
 *  @since      v5.0
 *  Sample usage:      CAN_RxBuff_Mask(CAN1,CAN_RX_MB,0x00FF,1);//CAN1 ��CAN_RX_MB ������ ��������Ϊ 0x00FF
 */
void CAN_RxBuff_Mask(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,uint32 Mask,uint8 IsIRMQ)
{
  uint8 BFreezeMode=0;
  
  //���붳��ģʽ
  if(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_HALT_MASK))
  {
    CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_HALT_MASK;
    
    //�ȴ����붳��ģʽ
    while(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK));
    
    BFreezeMode = 0;
  }
  else
  {
    BFreezeMode = 1;
  }
  
  if(IsIRMQ != 0)//��������
  {
    CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_IRMQ_MASK;
    CAN_RXIMR_REG(CANN[CAN_CANx],MB_NUM_x) = Mask;
  }
  else
  {
    CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_IRMQ_MASK;
    
    if(MB_NUM_x == MB_NUM_14)
    {
      CAN_RX14MASK_REG(CANN[CAN_CANx]) = Mask;
    }
    else if(MB_NUM_x == MB_NUM_15)
    {
      CAN_RX15MASK_REG(CANN[CAN_CANx]) = Mask;
    }
    else
    {
      CAN_RXMGMASK_REG(CANN[CAN_CANx]) = Mask;
    }
  }
  
  if(!BFreezeMode)
  {
    CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_HALT_MASK;
    
    while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK);
    
    while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_NOTRDY_MASK);
  }
  
}

/*
 *  @brief      CAN ��������
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @param      CAN_USR_ID_n    CAN_USR_ID_x    ID���
 *  @param      uint8           Len             ���ݳ���
 *  @param      void*           Buff            ��������ַ
 *  @since      v1.0
 *  Sample usage:       CAN_Rx(CAN1,CAN_RX_MB,&can_rx_id,&can_rx_len,can_rx_data);  //CAN �� CAN_RX_MB �������� �����յ��� ID ������ can_rx_id ����ȱ����� can_rx_len�����ݱ����� can_rx_data
 */
void CAN_Rx(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n *CAN_USR_ID_x,uint8 *Len,void *Buff)
{
  uint8 Lenth=0;
  uint32 Word=0;
  
  *(uint32*)CAN_USR_ID_x = 0;
  
  if((CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) & CAN_CS_CODE_MASK) != CAN_CS_CODE(CAN_CS_CODE_RX_FULL))
  {
    *Len = 0;
    return;
  }
  
  Lenth = (CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) & CAN_CS_DLC_MASK) >> CAN_CS_DLC_SHIFT;
  
  if(Lenth < 1)
  {
    *Len = 0;
    return;
  }
  
  if(!(CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) & CAN_CS_IDE_MASK))
  {
    CAN_USR_ID_x->ID = (CAN_ID_REG(CANN[CAN_CANx],MB_NUM_x) & CAN_ID_STD_MASK) >> CAN_ID_STD_SHIFT;
  }
  else
  {
    CAN_USR_ID_x->ID = (CAN_ID_REG(CANN[CAN_CANx],MB_NUM_x) & CAN_ID_EXT_MASK) >> CAN_ID_EXT_SHIFT;
    CAN_USR_ID_x->IDE = 1;
  }
  
  if(CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) & CAN_CS_RTR_MASK)
  {
    CAN_USR_ID_x->RTR = 1;
  }
  
  Word = CAN_WORD0_REG(CANN[CAN_CANx],MB_NUM_x);
  *((uint32 *)Buff) = SWAP32(Word);
  
  Word = CAN_WORD1_REG(CANN[CAN_CANx],MB_NUM_x);
  *((uint32 *)Buff + 1) = SWAP32(Word);
  
  *Len = Lenth;
  
  CAN_TIMER_REG(CANN[CAN_CANx]);
}

/*
 *  @brief      ʹ�� CAN ���������պͷ����ж�
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @since      v1.0
 *  Sample usage:       CAN_Irq_En(CAN1,MB_NUM_5);
 */
void CAN_Irq_En(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x)
{
  CAN_IMASK1_REG(CANN[CAN_CANx]) = (1 << MB_NUM_x);
  
  if(CAN_CANx == CAN_CAN0)
  {
    enable_irq(CAN0_ORed_Message_buffer_IRQn);//CANO IRQ�ж�
  }
  #ifdef MK66F18
  else if(CAN_CANx == CAN_CAN1)
  {
    enable_irq(CAN1_ORed_Message_buffer_IRQn);//CAN1 IRQ�ж�
  }
  #endif
  else
  {
    ASSERT(0);
  }
  
}

/*
 *  @brief      �� CAN �������жϱ�־
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @since      v1.0
 *  Sample usage:       CAN_Clear_Flag(CAN1,MB_NUM_5);
 */
void CAN_Clear_Flag(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x)
{
  CAN_IFLAG1_REG(CANN[CAN_CANx]) = (1 << MB_NUM_x);
}

/*
 *  @brief      ��� CAN �������жϱ�־
 *  @param      CAN_CANn        CAN_CANx        CAN ģ���
 *  @param      MB_NUM_n        MB_NUM_x        ���������
 *  @since      v1.0
 *  Sample usage:       CAN_Get_Flag(CAN1,MB_NUM_5);
 */
uint32 CAN_Get_Flag(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x)
{
  return (CAN_IFLAG1_REG(CANN[CAN_CANx]) & (1 << MB_NUM_x));
}