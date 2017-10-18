/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DAC.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**DAC基址指针
*/
DAC_MemMapPtr DACN[DAC_DAC_MAX]=
{
  DAC0_BASE_PTR,//DAC0基址指针
  DAC1_BASE_PTR,//DAC1基址指针
};

/*
 *  @brief      DAC初始化
 *  @param      DAC_DACn        DAC_DACx        DAC模块号
 *  @since      v1.0
 *  Sample usage:       DAC_Init(DAC1);//初始化 DAC1
 */
void DAC_Init(DAC_DACn DAC_DACx)
{
  ASSERT(DAC_DACx <= DAC_DAC1);
  
  switch(DAC_DACx)
  {
    case DAC_DAC0:
                  SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;//DAC0时钟使能
                  break;
    case DAC_DAC1:
                  SIM_SCGC2 |= SIM_SCGC2_DAC1_MASK;//DAC1时钟使能
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  /*
  **DAC_C0寄存器配置
  */
  DAC_C0_REG(DACN[DAC_DACx]) = (0
                                | DAC_C0_DACTRGSEL_MASK         //DAC软件触发
                                | DAC_C0_DACRFS_MASK            //DAC参考源VDD(3.3V)
                                | DAC_C0_DACEN_MASK             //DAC系统使能
                                );
  
  /*
  **DAC_C1寄存器配置
  */
  DAC_C1_REG(DACN[DAC_DACx]) = (0);
  
  /*
  **DAC_C2寄存器配置
  */
  DAC_C2_REG(DACN[DAC_DACx]) = (0 | DAC_C2_DACBFRP(0));
  
  //输出最低电压
  DAC_DATH_REG(DACN[DAC_DACx],0) = 0;
  DAC_DATL_REG(DACN[DAC_DACx],0) = 0;
    
}

/*
 *  @brief      DAC输出
 *  @param      DAC_DACn        DAC_DACx        DAC模块号
 *  @param      uint16          DAC_Value       输出模拟量所对应的数字量(12bit)
 *  @since      v1.0
 *  Sample usage:       DAC_Out (DAC1 ,0x100);    //初始化 DAC1 输出 0x100 数字量对应的模拟量
 */
void DAC_Out(DAC_DACn DAC_DACx,uint16 DAC_Value)
{
  //断言DAC输出值为12Bit
  ASSERT(DAC_Value < 0x1000);
  
  DAC_DATH_REG(DACN[DAC_DACx],0) = (DAC_Value >> 8);    //DAC输出高位寄存器
  DAC_DATL_REG(DACN[DAC_DACx],0) = (DAC_Value & 0xff);  //DAC输出地位寄存器
  
}