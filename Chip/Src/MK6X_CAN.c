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
**CAN基址指针
*/
CAN_MemMapPtr CANN[CAN_CAN_MAX]=
{
  CAN0_BASE_PTR,//CAN0基址指针
  #ifdef MK66F18
  CAN1_BASE_PTR,//CAN1基址指针
  #endif
};

/*
**CAN时钟源50MHz
*/
CAN_Baud_CFG_n CAN_Baud_CFG_50000K[CAN_BAUD_MAX]=
{
  //BAND,PRESDIV,PROP_SEG,PSEG1,PSEG2,RJW
  {10,  624,    4,      0,      0,      0},//采样点:87.50%
  {20,  124,    12,     2,      2,      2},//采样点:85.00%
  {50,  124,    4,      0,      0,      0},//采样点:87.50%
  {100, 24,     12,     2,      2,      2},//采样点:85.00%
  {125, 24,     10,     1,      1,      1},//采样点:87.50%
  {250, 24,     4,      0,      0,      0},//采样点:87.50%
  {500, 4,      12,     2,      2,      2},//采样点:85.00%
  {1000,1,      9,      6,      6,      3},//采样点:72.00%
};

/*
**CAN时钟源60MHz
*/
CAN_Baud_CFG_n CAN_Baud_CFG_60000K[CAN_BAUD_MAX]=
{
  //BAND,PRESDIV,PROP_SEG,PSEG1,PSEG2,RJW
  {10,  249,    16,     2,      2,      2},//采样点:87.50%
  {20,  124,    16,     2,      2,      2},//采样点:87.50%
  {50,  49,     16,     2,      2,      2},//采样点:87.50%
  {100, 24,     16,     2,      2,      2},//采样点:87.50%
  {125, 19,     16,     2,      2,      2},//采样点:87.50%
  {250, 9,      16,     2,      2,      2},//采样点:87.50%
  {500, 4,      16,     2,      2,      2},//采样点:87.50%
  {1000,2,      8,      4,      4,      3},//采样点:75.00%
};

/*
 *  @brief      设置CAN的波特率
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      CAN_BAUD_n      CAN_BAUD_x      波特率编号
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
    CAN_CLK_KHz = MK6X_Bus_KHz;         //总线时钟Bus
  }
  else
  {
    CAN_CLK_KHz = EXTAL_IN_MHz * 1000;  //晶振时钟OSC
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
  
  //进入冻结模式
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
  
  //配置寄存器
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
  
  //恢复CAN操作模式
  if(!BFreezeMode)
  {
    CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_HALT_MASK;
    
    while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK);
    
    while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_NOTRDY_MASK);
  }
  
}

/*
 *  @brief      CAN 初始化
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      CAN_BAUD_n      CAN_BAUD_x      波特率编号
 *  @param      CAN_MODE        CAN_MODE_x      CAN 模式(正常模式,回环模式)
 *  @param      CAN_CLKSRC_n    CAN_CLKSRC_x    CAN 时钟源(总线时钟,外部晶振)
 *  @since      v1.0
 *  Sample usage:       CAN_Init(CAN1,CAN_BAUD_20K,CAN_LOOPBACK);   //初始化 CAN1,波特率 20Kb/s,回环模式
 */
void CAN_Init(CAN_CANn CAN_CANx,CAN_BAUD_n CAN_BAUD_x,CAN_MODE CAN_MODE_x,CAN_CLKSRC_n CAN_CLKSRC_x)
{
  uint8 i=0;
  
  switch(CAN_CANx)
  {
    case CAN_CAN0:
                  SIM_SCGC6 |= SIM_SCGC6_FLEXCAN0_MASK;//CAN0时钟使能
                  PORT_Init(CAN0_TX_PIN,ALT2);
                  PORT_Init(CAN0_RX_PIN,ALT2);
                  break;
    #ifdef MK66F18
    case CAN_CAN1:
                  SIM_SCGC3 |= SIM_SCGC3_FLEXCAN1_MASK;//CAN1时钟使能
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
    CAN_CTRL1_REG(CANN[CAN_CANx]) |= CAN_CTRL1_CLKSRC_MASK;//总线Bus时钟
  }
  else
  {
    OSC_CR |= OSC_CR_ERCLKEN_MASK;//外部晶振时钟OSC
  }
  
  CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_MDIS_MASK;            //CAN模块使能
  CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_FRZ_MASK;              //CAN冻结模式使能
  while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_LPMACK_MASK);     //等待复位
  CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_SOFTRST_MASK;          //软件复位
  while(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK));  //等待进入冻结模式
  
  for(i=16;i>0;i--)
  {
    CAN_CS_REG(CANN[CAN_CANx],i) = 0;
    CAN_ID_REG(CANN[CAN_CANx],i) = 0;
    CAN_WORD0_REG(CANN[CAN_CANx],i) = 0;
    CAN_WORD1_REG(CANN[CAN_CANx],i) = 0;
  }
  
  CAN_CTRL2_REG(CANN[CAN_CANx]) = (0 | CAN_CTRL2_TASD(22));
  CAN_MCR_REG(CANN[CAN_CANx]) = (CAN_MCR_REG(CANN[CAN_CANx]) & (~CAN_MCR_IDAM_MASK)) | CAN_MCR_IDAM(0);
  
  //设置波特率
  CAN_Set_Baud(CAN_CANx,CAN_BAUD_x);
  
  if(CAN_MODE_x == CAN_LOOPBACK)
  {
    CAN_CTRL1_REG(CANN[CAN_CANx]) |= CAN_CTRL1_LPB_MASK;//回环模式
  }
  
  //默认独立掩码
  CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_IRMQ_MASK;
  
  for(i=NUMBER_OF_MB;i>0;i--)
  {
    CAN_RXIMR_REG(CANN[CAN_CANx],i) = 0;
  }
  
  CAN_RXMGMASK_REG(CANN[CAN_CANx]) = 0;
  CAN_RX14MASK_REG(CANN[CAN_CANx]) = 0;
  CAN_RX15MASK_REG(CANN[CAN_CANx]) = 0;
  
  //冻结模式下完成配置
  CAN_MCR_REG(CANN[CAN_CANx]) &= ~CAN_MCR_HALT_MASK;
  
  //等待同步退出冻结模式
  while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK);
  
  //等待不在冻结模式,休眠模式,停止模式
  while(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_NOTRDY_MASK);
  
}

/*
 *  @brief      CAN 发送数据
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @param      CAN_USR_ID_n    CAN_USR_ID_x    ID编号
 *  @param      uint8           Len             数据长度
 *  @param      void*           Buff            缓冲区地址
 *  @since      v1.0
 *  Sample usage:       CAN_Tx(CAN1,CAN_TX_MB,can_tx_id,DATA_LEN, txbuff);  //CAN发送数据.缓冲区CAN_TX_MB,报文ID:tx_ID,数据缓冲区txbuff,长度 DATA_LEN
 */
void CAN_Tx(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n CAN_USR_ID_x,uint8 Len,void *Buff)
{
  uint32 Word=0;
  
  ASSERT(Len <= 8);
  
  CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = (0
                                         | CAN_CS_CODE(CAN_CS_CODE_TX_INACTIVE)         //缓冲区写非激活代码
                                         | (CAN_USR_ID_x.IDE << CAN_CS_IDE_SHIFT)       //缓冲区写IDE位
                                         | (CAN_USR_ID_x.RTR << CAN_CS_RTR_SHIFT)       //缓冲区写RTR位
                                         | CAN_CS_DLC(Len)                              //缓冲区写数据长度
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
  
  //开始发送
  CAN_CS_REG(CANN[CAN_CANx],MB_NUM_x) = (0
                                         | CAN_CS_CODE(CAN_CS_CODE_TX_DATA)
                                         | CAN_CS_DLC(Len)
                                         );
  
  //限时等待发送完成
  while(!(CAN_IFLAG1_REG(CANN[CAN_CANx]) & (1 << MB_NUM_x)));
  
  //清报文缓冲区中断标志
  CAN_IFLAG1_REG(CANN[CAN_CANx]) = (1 << MB_NUM_x);
  
}

/*
 *  @brief      使能 CAN 接收缓冲区
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @param      CAN_USR_ID_n    CAN_USR_ID_x    ID编号
 *  @since      v1.0
 *  Sample usage:      CAN_RxBuff_Enble(CAN1,CAN_RX_MB,can_my_id);//使能接收缓冲区
 */
void CAN_RxBuff_Enable(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,CAN_USR_ID_n CAN_USR_ID_x)
{
  //将MB配置为非激活状态
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
 *  @brief      CAN 接收掩码配置
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @param      uint32          Mask            掩码
 *  @param      uint8           IsIRMQ          是否选择独立掩码（0为全局掩码，其他为独立掩码）
 *  @since      v5.0
 *  Sample usage:      CAN_RxBuff_Mask(CAN1,CAN_RX_MB,0x00FF,1);//CAN1 的CAN_RX_MB 缓冲区 配置掩码为 0x00FF
 */
void CAN_RxBuff_Mask(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x,uint32 Mask,uint8 IsIRMQ)
{
  uint8 BFreezeMode=0;
  
  //进入冻结模式
  if(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_HALT_MASK))
  {
    CAN_MCR_REG(CANN[CAN_CANx]) |= CAN_MCR_HALT_MASK;
    
    //等待进入冻结模式
    while(!(CAN_MCR_REG(CANN[CAN_CANx]) & CAN_MCR_FRZACK_MASK));
    
    BFreezeMode = 0;
  }
  else
  {
    BFreezeMode = 1;
  }
  
  if(IsIRMQ != 0)//独立掩码
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
 *  @brief      CAN 接收数据
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @param      CAN_USR_ID_n    CAN_USR_ID_x    ID编号
 *  @param      uint8           Len             数据长度
 *  @param      void*           Buff            缓冲区地址
 *  @since      v1.0
 *  Sample usage:       CAN_Rx(CAN1,CAN_RX_MB,&can_rx_id,&can_rx_len,can_rx_data);  //CAN 从 CAN_RX_MB 接收数据 ，接收到的 ID 保存在 can_rx_id 里，长度保存在 can_rx_len，数据保存在 can_rx_data
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
 *  @brief      使能 CAN 缓冲区接收和发送中断
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @since      v1.0
 *  Sample usage:       CAN_Irq_En(CAN1,MB_NUM_5);
 */
void CAN_Irq_En(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x)
{
  CAN_IMASK1_REG(CANN[CAN_CANx]) = (1 << MB_NUM_x);
  
  if(CAN_CANx == CAN_CAN0)
  {
    enable_irq(CAN0_ORed_Message_buffer_IRQn);//CANO IRQ中断
  }
  #ifdef MK66F18
  else if(CAN_CANx == CAN_CAN1)
  {
    enable_irq(CAN1_ORed_Message_buffer_IRQn);//CAN1 IRQ中断
  }
  #endif
  else
  {
    ASSERT(0);
  }
  
}

/*
 *  @brief      清 CAN 缓冲区中断标志
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @since      v1.0
 *  Sample usage:       CAN_Clear_Flag(CAN1,MB_NUM_5);
 */
void CAN_Clear_Flag(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x)
{
  CAN_IFLAG1_REG(CANN[CAN_CANx]) = (1 << MB_NUM_x);
}

/*
 *  @brief      获得 CAN 缓冲区中断标志
 *  @param      CAN_CANn        CAN_CANx        CAN 模块号
 *  @param      MB_NUM_n        MB_NUM_x        缓冲区编号
 *  @since      v1.0
 *  Sample usage:       CAN_Get_Flag(CAN1,MB_NUM_5);
 */
uint32 CAN_Get_Flag(CAN_CANn CAN_CANx,MB_NUM_n MB_NUM_x)
{
  return (CAN_IFLAG1_REG(CANN[CAN_CANx]) & (1 << MB_NUM_x));
}