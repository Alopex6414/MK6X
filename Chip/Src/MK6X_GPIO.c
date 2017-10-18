/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_GPIO.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**GPIO基址指针
*/
GPIO_MemMapPtr GPIOX[PORT_PTX_MAX]=
{
  PTA_BASE_PTR,//PTA基址指针
  PTB_BASE_PTR,//PTB基址指针
  PTC_BASE_PTR,//PTC基址指针
  PTD_BASE_PTR,//PTD基址指针
  PTE_BASE_PTR,//PTE基址指针
};

/*
 *  @brief      初始化GPIO
 *  @param      PTXn            PTXx    端口
 *  @param      GPIO_CFG        CFG     引脚方向,0=输入,1=输出
 *  @param      uint8           DATA    输出初始状态,0=低电平,1=高电平(对输入无效)
 *  @since      v1.0
 *  Sample usage:       GPIO_Init(PTA8, GPI,0);    //初始化 PTA8 管脚为输入
 */
void GPIO_Init(PTXn PTXx,GPIO_CFG CFG,uint8 DATA)
{
  PORT_Init(PTXx,ALT1);//初始化为GPIO
  
  if(CFG == GPI)//GPIO Input
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDDR 管脚号 清0，即对应管脚配置为端口方向输入
  }
  else//GPIO Output
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDDR 管脚号 置1，即对应管脚配置为端口方向输出
    
    if(DATA == 0)//低电平
    {
      GPIO_PDOR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDOR 管脚号 清0，即对应管脚配置为端口输出低电平
    }
    else//高电平
    {
      GPIO_PDOR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDOR 管脚号 置1，即对应管脚配置为端口输出高电平
    }
    
  }
  
}

/*
 *  @brief      设置引脚数据方向
 *  @param      PTXn            PTXx    端口
 *  @param      GPIO_CFG        CFG     引脚方向,0=输入,1=输出
 *  @since      v1.0
 *  Sample usage:       GPIO_DDR(PTA8, GPI);    //设置 PTA8 管脚为输入
 */
void GPIO_DDR(PTXn PTXx,GPIO_CFG CFG)
{
  if(CFG == GPI)
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDDR 管脚号 清0，即对应管脚配置为端口方向输入
  }
  else
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDDR 管脚号 置1，即对应管脚配置为端口方向输出
  }
}

/*
 *  @brief      设置引脚状态
 *  @param      PTXn     PTXx    端口
 *  @param      uint8    DATA    输出初始状态,0=低电平,1=高电平(对输入无效)
 *  @since      v1.0
 *  @warning    务必保证数据方向为输出(DEBUG模式下,有断言进行检测)
 *  Sample usage:       GPIO_Set(PTA8, 1);    // PTA8 管脚 输出 1
 */
void GPIO_Set(PTXn PTXx,uint8 DATA)
{
  ASSERT(BIT_GET(GPIO_PDDR_REG(GPIOX_BASE(PTXx)),PORT_PTn(PTXx)) == GPO);
  
  if(DATA == 0)//低电平
  {
    GPIO_PDOR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDOR 管脚号 清0，即对应管脚配置为端口输出低电平
  }
  else//高电平
  {
    GPIO_PDOR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDOR 管脚号 置1，即对应管脚配置为端口输出高电平
  }
}

/*
 *  @brief      反转引脚状态
 *  @param      PTXn    PTXx    端口
 *  @since      v1.0
 *  @warning    务必保证数据方向为输出(DEBUG模式下,有断言进行检测)
 *  Sample usage:       GPIO_Turn(PTA8);    // PTA8 管脚 输出 反转
 */
void GPIO_Turn(PTXn PTXx)
{
  ASSERT(BIT_GET(GPIO_PDDR_REG(GPIOX_BASE(PTXx)),PORT_PTn(PTXx)) == GPO);
  
  GPIO_PTOR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//管脚配置为端口输出反转

}

/*
 *  @brief      读取引脚输入状态
 *  @param      PTXn    PTXx    端口
 *  @return     管脚的状态,1为高电平,0为低电平
 *  @since      v1.0
 *  @warning    务必保证数据方向为输入(DEBUG模式下，有断言进行检测)
 *  Sample usage:       uint8 GPIO_DATA = GPIO_Get(PTA8);    // 获取 PTA8 管脚 输入电平
 */
uint8 GPIO_Get(PTXn PTXx)
{
  uint8 GPIO_Data=0;
  
  ASSERT(BIT_GET(GPIO_PDDR_REG(GPIOX_BASE(PTXx)),PORT_PTn(PTXx)) == GPI);
  
  GPIO_Data = (GPIO_PDIR_REG(GPIOX_BASE(PTXx)) >> PORT_PTn(PTXx)) & 0x01;
  
  return GPIO_Data;
}