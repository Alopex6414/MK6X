/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PORT.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**PTX端口基址指针
*/
PORT_MemMapPtr PORTX[PORT_PTX_MAX]=
{
  PORTA_BASE_PTR,//PTA基址指针
  PORTB_BASE_PTR,//PTB基址指针
  PORTC_BASE_PTR,//PTC基址指针
  PORTD_BASE_PTR,//PTD基址指针
  PORTE_BASE_PTR,//PTE基址指针
};

/*
 *  @brief      PORT初始化
 *  @param      PTXn    PTXx    端口
 *  @param      uint32  CFG     端口属性配置，如触发选项和上拉下拉选项
 *  @since      v1.0
 *  @note       与PORT_Init_NoALT不同的是，此函数需要配置 MUX 复用功能，
                否则 MUX = ALT0
 *  Sample usage:       PORT_Init(PTA8, IRQ_RISING | PF | ALT1 | PULLUP );    //初始化 PTA8 管脚，上升沿触发中断，带无源滤波器，复用功能为GPIO ，上拉电阻
 */
void PORT_Init(PTXn PTXx,uint32 CFG)
{
  switch(PORT_PTX(PTXx))//选择Enable时钟
  {
    case PORT_PTA:
                  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
                  break;
    case PORT_PTB:
                  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
                  break;
    case PORT_PTC:
                  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
                  break;
    case PORT_PTD:
                  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
                  break;
    case PORT_PTE:
                  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  PORT_ISFR_REG(PORTX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//清中断标志
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) &= ~PORT_PCR_MUX_MASK;//清空原MUX寄存器值
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) |= (0 | CFG);//MUX管脚功能复用
  
}

/*
 *  @brief      PORT初始化
 *  @param      PTXn    PTXx    端口
 *  @param      uint32  CFG     端口属性配置，如触发选项和上拉下拉选项
 *  @since      v1.0
 *  @note       与PORT_Init不同的是，此函数不需要配置 MUX 复用功能（即使配置了也不生效），
                MUX 保留 为原先寄存器配置的值
 *  Sample usage:       PORT_Init_NoALT (PTA8, IRQ_RISING | PF | PULLUP );    //初始化 PTA8 管脚，上升沿触发中断，带无源滤波器，保留原先复用功能，上拉电阻
 */
void PORT_Init_NoALT(PTXn PTXx,uint32 CFG)
{
  switch(PORT_PTX(PTXx))//选择Enable时钟
  {
    case PORT_PTA:
                  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
                  break;
    case PORT_PTB:
                  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
                  break;
    case PORT_PTC:
                  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
                  break;
    case PORT_PTD:
                  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
                  break;
    case PORT_PTE:
                  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  PORT_ISFR_REG(PORTX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//清中断标志
  CFG &= ~PORT_PCR_MUX_MASK;//清除配置MUX
  CFG |= (PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) & PORT_PCR_MUX_MASK);//读取原来MUX配置
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) |= (0 | CFG);//MUX管脚功能复用
  
}

/*
 *  @brief      PORT初始化EXIT外部中断
 *  @param      PTXn    PTXx    端口
 *  @param      uint32  CFG     端口属性配置，如触发选项和上拉下拉选项
 *  @since      v1.0
 *  @note       
 *  Sample usage:       PORT_Init_Exit(PTA13,IRQ_RISING)//PTA13,上升沿触发外部中断
 */
void PORT_Init_Exit(PTXn PTXx,uint32 CFG)
{
  switch(PORT_PTX(PTXx))//选择Enable时钟
  {
    case PORT_PTA:
                  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
                  break;
    case PORT_PTB:
                  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
                  break;
    case PORT_PTC:
                  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
                  break;
    case PORT_PTD:
                  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
                  break;
    case PORT_PTE:
                  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) &= ~PORT_PCR_MUX_MASK;//清空原MUX寄存器值
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) |= (0 | ALT1 | CFG);//MUX管脚功能复用
  GPIO_PDDR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));//管脚设置为输入模式
  PORT_ISFR_REG(PORTX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//清中断标志
  
}