/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_UART.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**UART��ַָ��
*/
UART_MemMapPtr UARTN[UART_UART_MAX]=
{
  UART0_BASE_PTR,//UART0��ַָ��
  UART1_BASE_PTR,//UART1��ַָ��
  UART2_BASE_PTR,//UART2��ַָ��
  UART3_BASE_PTR,//UART3��ַָ��
  UART4_BASE_PTR,//UART4��ַָ��
  #ifdef MK64F12
  UART5_BASE_PTR,//UART5��ַָ��
  #endif
};

/*
 *  @brief      ��ʼ������UART,���ò�����
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @param      uint32          UART_Baud       ������,��9600��19200��56000��115200��
 *  @since      v1.0
 *  Sample usage:       UART_Init(UART3,115200);        //��ʼ������,������Ϊ115200
 */
void UART_Init(UART_UARTn UART_UARTx,uint32 UART_Baud)
{
  uint8 UART_Temp=0;
  uint32 UART_SysClk=0;
  register uint16 UART_Sbr=0;
  register uint16 UART_Brfa=0;
  
  //UART�ܽŸ���
  switch(UART_UARTx)
  {
    case UART_UART0:
                    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;//UART0ʱ��ʹ��
                    if(UART0_RX_PIN == PTA1)
                    {
                      PORT_Init(UART0_RX_PIN,ALT2);
                    }
                    else if((UART0_RX_PIN == PTA15) || (UART0_RX_PIN == PTB16) || (UART0_RX_PIN == PTD6))
                    {
                      PORT_Init(UART0_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if(UART0_TX_PIN == PTA2)
                    {
                      PORT_Init(UART0_TX_PIN,ALT2);
                    }
                    else if((UART0_TX_PIN == PTA14) || (UART0_TX_PIN == PTB17) || (UART0_TX_PIN == PTD7))
                    {
                      PORT_Init(UART0_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART1:
                    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;//UART1ʱ��ʹ��
                    if((UART1_RX_PIN == PTC3) || (UART1_RX_PIN == PTE1))
                    {
                      PORT_Init(UART1_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART1_TX_PIN == PTC4) || (UART1_TX_PIN == PTE0))
                    {
                      PORT_Init(UART1_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART2:
                    SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;//UART2ʱ��ʹ��
                    if(UART2_RX_PIN == PTD2)
                    {
                      PORT_Init(UART2_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if(UART2_TX_PIN == PTD3)
                    {
                      PORT_Init(UART2_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART3:
                    SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;//UART3ʱ��ʹ��
                    if((UART3_RX_PIN == PTB10)|| (UART3_RX_PIN == PTC16) || (UART3_RX_PIN == PTE5))
                    {
                      PORT_Init(UART3_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART3_TX_PIN == PTB11) || (UART3_TX_PIN == PTC17) || (UART3_TX_PIN == PTE4))
                    {
                      PORT_Init(UART3_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART4:
                    SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;//UART4ʱ��ʹ��
                    if((UART4_RX_PIN == PTC14) || (UART4_RX_PIN == PTE25))
                    {
                      PORT_Init(UART4_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART4_TX_PIN == PTC15) || (UART4_TX_PIN == PTE24))
                    {
                      PORT_Init(UART4_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    #ifdef MK64F12
    case UART_UART5:
                    SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
                    if((UART5_RX_PIN == PTD8) || (UART5_RX_PIN == PTE9))
                    {
                      PORT_Init(UART5_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART5_TX_PIN == PTD9) ||(UART5_TX_PIN == PTE8))
                    {
                      PORT_Init(UART5_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    #endif                
    default:
                    ASSERT(0);
                    break;
  }
  
  //UART�Ĵ�������
  UART_C2_REG(UARTN[UART_UARTx]) &= ~(0 | UART_C2_RE_MASK | UART_C2_TE_MASK);//��ֹ���ܷ���
  UART_C1_REG(UARTN[UART_UARTx]) = 0;
  
  //UARTʱ������
  if(UART_UARTx == UART_UART0 || UART_UARTx == UART_UART1)//UART0,UART1
  {
    UART_SysClk = MK6X_Core_KHz * 1000;//Coreʱ��
  }
  else
  {
    UART_SysClk = MK6X_Bus_KHz * 1000;//Busʱ��
  }
  
  //UART�����ʼ��� UART_Baud = UART_SysClk / (16 * (SBR + BRFD))
  UART_Sbr = (uint16)(UART_SysClk / (UART_Baud * 16));
  
  if(UART_Sbr > 0x1FFF)
  {
    UART_Sbr = 0x1FFF;
  }
  
  //BRFA�����ʵ���ֵ
  UART_Brfa = (UART_SysClk / UART_Baud) - (UART_Sbr * 16);
  ASSERT(UART_Brfa <= 0x1F);
  
  //UART����
  UART_Temp = UART_BDH_REG(UARTN[UART_UARTx]) & (~UART_BDH_SBR_MASK);//����BDH�Ĵ�����������
  UART_BDH_REG(UARTN[UART_UARTx]) = UART_Temp | UART_BDH_SBR(UART_Sbr >> 8);//BDH�����ʸ�λд��
  UART_BDL_REG(UARTN[UART_UARTx]) = UART_BDL_SBR(UART_Sbr & 0xff);//BDL�����ʵ�λд��
  
  UART_Temp = UART_C4_REG(UARTN[UART_UARTx]) & (~UART_C4_BRFA_MASK);//����C4�Ĵ�����������
  UART_C4_REG(UARTN[UART_UARTx]) = UART_Temp | UART_C4_BRFA(UART_Brfa);//C4д��BRFA�����ʵ���ֵ
  
  //UART����FIFO
  UART_PFIFO_REG(UARTN[UART_UARTx]) = (0 | UART_PFIFO_RXFE_MASK | UART_PFIFO_TXFE_MASK);
  
  //�����ͽ���
  UART_C2_REG(UARTN[UART_UARTx]) |= (0 | UART_C2_RE_MASK | UART_C2_TE_MASK);//�����ͽ���
  
}

/*
 *  @brief      UART����1���ֽ�
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @param      char            ch              UART�����ֽ�
 *  @since      v1.0
 *  Sample usage:
                        UART_GetChar(UART3,&ch);   //�ȴ�����1���ֽ�,���浽ch��
 */
void UART_GetChar(UART_UARTn UART_UARTx,char *ch)
{
  while(!(UART_S1_REG(UARTN[UART_UARTx]) & UART_S1_RDRF_MASK));//�ȴ����ݽ���
  
  *ch = UART_D_REG(UARTN[UART_UARTx]);//��ȡ����Ĵ�������ֵ
}

/*
 *  @brief      UART����һ���ֽ�
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @param      char            ch              UART�����ֽ�
 *  @since      v1.0
 *  Sample usage:       UART_PutChar(UART3,'A');  //�����ֽ�'A'
 */
void UART_PutChar(UART_UARTn UART_UARTx,char ch)
{
  while(!(UART_S1_REG(UARTN[UART_UARTx]) & UART_S1_TDRE_MASK));//�ȴ����ͻ���
  
  UART_D_REG(UARTN[UART_UARTx]) = (uint8)ch;//����һ���ֽ�����
}

/*
 *  @brief      UART�����ַ���(��NULLֹͣ����)
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @param      str             �ַ�����ַ
 *  @since      v1.0
 *  Sample usage:       UART_PutStr(UART3,"1234567");//ʵ�ʷ�����7���ֽ�
 */
void UART_PutStr(UART_UARTn UART_UARTx,const uint8 *str)
{
  for(;*str!='\0';str++)
  {
    while(!(UART_S1_REG(UARTN[UART_UARTx]) & UART_S1_TDRE_MASK));//�ȴ����ͻ���
  
    UART_D_REG(UARTN[UART_UARTx]) = (uint8)(*str);//����һ���ֽ�����
  }
}

/*
 *  @brief      ��UART�����ж�
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Rx_IRQ_En(UART3);         //������3�����ж�
 */
void UART_Rx_IRQ_En(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) |= UART_C2_RIE_MASK;//UART�����ж�ʹ��
  if(UART_UARTx == UART_UART4)
  {
    enable_irq(UART4_RX_TX_IRQn);//IRQ�ж�
  }
  else
  {
    enable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//IRQ�ж�
  }
}

/*
 *  @brief      ��UART�����ж�
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Tx_IRQ_En(UART3);         //������3�����ж�
 */
void UART_Tx_IRQ_En(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) |= UART_C2_TIE_MASK;//UART�����ж�ʹ��
  if(UART_UARTx == UART_UART4)
  {
    enable_irq(UART4_RX_TX_IRQn);//IRQ�ж�
  }
  else
  {
    enable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//IRQ�ж�
  }
}

/*
 *  @brief      ��UART�����ж�
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Rx_IRQ_Dis(UART3);         //�ش���3�����ж�
 */
void UART_Rx_IRQ_Dis(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) &= ~UART_C2_RIE_MASK;//UART�����жϹر�
  
  if(!(UART_C2_REG(UARTN[UART_UARTx]) & (UART_C2_TIE_MASK | UART_C2_TCIE_MASK)))
  {
    if(UART_UARTx == UART_UART4)
    {
      disable_irq(UART4_RX_TX_IRQn);//�ر��ж�
    }
    else
    {
      disable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//�ر��ж�
    }
  }
}

/*
 *  @brief      ��UART�����ж�
 *  @param      UART_UARTn      UART_UARTx      ģ���(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Tx_IRQ_Dis(UART3);         //�ش���3�����ж�
 */
void UART_Tx_IRQ_Dis(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) &= ~UART_C2_TIE_MASK;//UART�����жϹر�
  
  if(!(UART_C2_REG(UARTN[UART_UARTx]) & UART_C2_RIE_MASK))
  {
    if(UART_UARTx == UART_UART4)
    {
      disable_irq(UART4_RX_TX_IRQn);//�ر��ж�
    }
    else
    {
      disable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//�ر��ж�
    }
  }
}