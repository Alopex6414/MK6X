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
 *  @brief      解锁WDOG
 *  @since      v1.0
 */
void WDOG_Unlock(void)
{
  uint8 WDOG_Temp=0;
  
  WDOG_Temp = __get_BASEPRI();//返回寄存器 PRIMASK 的值(1bit) 1:关中断 0:开中断
  
  DisableInterrupts;//关总中断
  
  WDOG_UNLOCK = 0xC520;//向WDOG_UNLOCK寄存器先后写入0xC520和0xD928解锁WDOG
  WDOG_UNLOCK = 0xD928;
  
  if(WDOG_Temp == 0)//解锁之前是开中断
  {
    EnableInterrupts;//开总中断
  }
  
}

/*
 *  @brief      更新WDOG计数器
 *  @since      v1.0
 */
void WDOG_Feed(void)
{
  uint8 WDOG_Temp=0;
  
  WDOG_Temp = __get_BASEPRI();//返回寄存器 PRIMASK 的值(1bit) 1:关中断 0:开中断
  
  DisableInterrupts;//关总中断
  
  WDOG_REFRESH = 0xA602;//更新WDOG计数器,Feed Dog
  WDOG_REFRESH = 0xB480;
  
  if(WDOG_Temp == 0)//解锁之前是开中断
  {
    EnableInterrupts;//开总中断
  }
}

/*
 *  @brief      禁止WDOG
 *  @since      v1.0
 */
void WDOG_Disable(void)
{
  WDOG_Unlock();//解锁WDOG,配置WDOG寄存器
  WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;//WDOGEN清零,禁止WDOG
}

/*
 *  @brief      启用WDOG
 *  @since      v1.0
 */
void WDOG_Enable(void)
{
  WDOG_Unlock();//解锁WDOG,配置WDOG寄存器
  WDOG_STCTRLH |= WDOG_STCTRLH_WDOGEN_MASK;//WDOGEN置位,启用WDOG
}

/*
 *  @brief      初始化WDOG，设置时间
 *  @param      WDOG_Cnt    时间(单位MS)
 *  @since      v1.0
 */
void WDOG_Init(uint32 WDOG_Cnt)
{
  ASSERT(WDOG_Cnt >= 4);//计数时钟最少为4毫秒
  
  WDOG_Unlock();//解锁WDOG,配置WDOG寄存器
  
  WDOG_PRESC = WDOG_PRESC_PRESCVAL(0);//设置分频系数 = PRESCVAL +1(PRESCVAL取值范围为0~7)
  
  WDOG_TOVALH = WDOG_Cnt >> 16;//设置WDOG时间
  WDOG_TOVALL = (uint16)(WDOG_Cnt & 0x0000ffff);
  
  WDOG_STCTRLH = (0 | WDOG_STCTRLH_WDOGEN_MASK          //WDOG使能
                    | WDOG_STCTRLH_ALLOWUPDATE_MASK     //WDOG允许更新
                    | WDOG_STCTRLH_STOPEN_MASK          //WDOG在停止模式
                    | WDOG_STCTRLH_WAITEN_MASK          //WDOG在等待模式
                  );
  
}