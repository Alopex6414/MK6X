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
**CAN模块枚举
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
**MB缓冲区编号
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
**CAN工作模式
*/
typedef enum
{
  CAN_NORMAL,   //正常模式
  CAN_LOOPBACK, //回环模式
}CAN_MODE;

/*
**CAN波特率枚举
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
**CAN总线时钟源选择
*/
typedef enum
{
  CAN_CLKSRC_BUS,//总线Bus时钟
  CAN_CLKSRC_OSC,//外部OSC晶振
}CAN_CLKSRC_n;

/*
**CAN波特率寄存器配置结构体
*/
typedef struct
{
  uint32_t Baud;        //波特率(KB/S)
  uint16_t Presdiv;     //分频系数
  uint8_t  Prop_Seg;    //传播时间段
  uint8_t  PSeg1;       //相位缓冲段1
  uint8_t  PSeg2;       //相位缓冲段2
  uint8_t  RJW;         //同步跳转宽度
  uint8_t  Res[2];      //保留
}CAN_Baud_CFG_n;

/*
**用户定义CAN ID
*/
typedef struct
{
  uint32 ID:29;         //ID
  uint32 IDE:1;         //IDE   1:扩展ID,0:标准ID
  uint32 RTR:1;         //RTR   1:远程帧,0:数据帧
}CAN_USR_ID_n;

//CAN ID值越低,报文优先级越高
//CAN 掩码用于屏蔽

//用于发送缓冲区的报文缓冲区码字
#define CAN_CS_CODE_TX_INACTIVE         B8(1000)            //MB处于非激活状态
#define CAN_CS_CODE_TX_ABORT            B8(1001)            //MB被丢弃
#define CAN_CS_CODE_TX_DATA             B8(1100)            //MB为一个发送数据帧(MB的RTR位为0)
#define CAN_CS_CODE_TX_REMOTE           B8(1100)            //MB为一个发送远程请求帧(MB的RTR位为1)
#define CAN_CS_CODE_TX_TANSWER          B8(1110)            //MB为是远程请求帧的一个发送回应帧

//用于接收缓冲区的报文缓冲区码字
#define CAN_CS_CODE_RX_INACTIVE         B8(0000)            //MB处于非激活状态
#define CAN_CS_CODE_RX_EMPTY            B8(0100)            //MB激活并且为空
#define CAN_CS_CODE_RX_FULL             B8(0010)            //MB为满
#define CAN_CS_CODE_RX_OVERRUN          B8(0110)            //写入到一个满缓冲区导致MB被覆盖
#define CAN_CS_CODE_RX_RANSWER          B8(1010)            //一个新帧被配置为确认一个远程请求帧并且发送一个回复帧.
#define CAN_CS_CODE_RX_BUSY             B8(0001)            //正在更新 MB 的内容.CPU不允许访问MB

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