/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_ADC.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**ADC基址指针
*/
ADC_MemMapPtr ADCN[ADC_ADC_MAX]=
{
  ADC0_BASE_PTR,
  ADC1_BASE_PTR,
};

/*
 *  @brief      ADC初始化
 *  @param      ADCn_CHn        ADCn_CHx         ADC通道
 *  @since      v1.0
 *  @note       此初始化仅支持软件触发，不是每个通道都支持ADC 软件触发，
                具体说明见 ADCn_CHn 的注释说明
 *  Sample usage:       ADC_Init(ADC0_SE10);    //初始化 ADC0_SE10,使用 PTA7 管脚
 */
void ADC_Init(ADCn_CHn ADCn_CHx)
{
  switch(ADCn(ADCn_CHx))//选择ADC模块
  {
    case ADC_ADC0://ADC0
                  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;//ADC0时钟使能
                  SIM_SOPT7 &= ~(SIM_SOPT7_ADC0ALTTRGEN_MASK | SIM_SOPT7_ADC0PRETRGSEL_MASK);//ADC0选择PDB触发
                  SIM_SOPT7 |= SIM_SOPT7_ADC0TRGSEL(0);//ADC0PDB触发
                  break;
    case ADC_ADC1://ADC1
                  SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;//ADC1时钟使能
                  SIM_SOPT7 &= ~(SIM_SOPT7_ADC1ALTTRGEN_MASK | SIM_SOPT7_ADC1PRETRGSEL_MASK);//ADC1选择PDB触发
                  SIM_SOPT7 |= SIM_SOPT7_ADC1TRGSEL(0);//ADC1PDB触发
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  switch(ADCn_CHx)//选择ADC通道
  {
    /*
    **ADC0
    */
    case ADC0_SE8://PTB0
                  PORT_Init(PTB0, ALT0);
                  break;
    case ADC0_SE9://PTB1
                  PORT_Init(PTB1, ALT0);
                  break;
    case ADC0_SE10://PTA7
                  PORT_Init(PTA7, ALT0);
                  break;
    case ADC0_SE11://PTA8
                  PORT_Init(PTA8, ALT0);
                  break;
    case ADC0_SE12://PTB2
                  PORT_Init(PTB2, ALT0);
                  break;
    case ADC0_SE13://PTB3
                  PORT_Init(PTB3, ALT0);
                  break;
    case ADC0_SE14://PTC0
                  PORT_Init(PTC0, ALT0);
                  break;
    case ADC0_SE15://PTC1
                  PORT_Init(PTC1, ALT0);
                  break;
    case ADC0_SE17://PTE24
                  PORT_Init(PTE24,ALT0);
                  break;
    case ADC0_SE18://PTE25
                  PORT_Init(PTE25,ALT0);
                  break;
    
    /*
    **ADC0不需要配置复用管脚
    */
    case ADC0_DP0:
    case ADC0_DP1:
    case ADC0_DP3:
    case ADC0_DM0:              // ADC0_DM0
    case ADC0_DM1:              // ADC0_DM1
    case ADC0_SE16:             // ADC0_SE16
    case Temp0_Sensor:          // Temperature Sensor,内部温度测量，可用ADC函数
    case VREFH0:                // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
    case VREFL0:                // 参考低电压,可用ADC函数 ,结果恒为 0
                  break;
    
    /*
    **ADC1
    */
    case ADC1_SE4a://PTE0
                  PORT_Init(PTE0,ALT0);
                  break;
    case ADC1_SE5a://PTE1
                  PORT_Init(PTE1,ALT0);
                  break;
    case ADC1_SE6a://PTE2
                  PORT_Init(PTE2,ALT0);
                  break;
    case ADC1_SE7a://PTE3
                  PORT_Init(PTE3,ALT0);
                  break;              
    case ADC1_SE8://PTB0
                  PORT_Init(PTB0,ALT0);
                  break;
    case ADC1_SE9://PTB1
                  PORT_Init(PTB1,ALT0);
                  break;
    case ADC1_SE10://PTB4
                  PORT_Init(PTB4,ALT0);
                  break;
    case ADC1_SE11://PTB5
                  PORT_Init(PTB5,ALT0);
                  break;
    case ADC1_SE12://PTB6
                  PORT_Init(PTB6,ALT0);
                  break;
    case ADC1_SE13://PTB7
                  PORT_Init(PTB7,ALT0);
                  break;
    case ADC1_SE14://PTB10
                  PORT_Init(PTB10,ALT0);
                  break;
    case ADC1_SE15://PTB11
                  PORT_Init(PTB11,ALT0);
                  break;
    case ADC1_SE17://PTA17
                  PORT_Init(PTA17,ALT0);
                  break;
                  
    /*
    **ADC1不需要配置复用管脚
    */              
    case ADC1_DP0:
    case ADC1_DP1:
    case ADC1_DP3:
    case ADC1_SE16:             // ADC1_SE16
    case VREF_OUTPUT:           // VREF Output
    case ADC1_DM0:              // ADC1_DM0
    case ADC1_DM1:              // ADC1_DM1
    case Temp1_Sensor:          // Temperature Sensor,内部温度测量，可用ADC函数
    case VREFH1:                // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
    case VREFL1:                // 参考低电压,可用ADC函数 ,结果恒为 0
                  break;
    
    default:
                  ASSERT(0);
                  break;                
  }
  
}

/*
 *  @brief      启动ADC软件采样(不支持B通道)
 *  @param      ADCn_CHn        ADCn_CHx        ADC通道
 *  @param      ADC_nBit        ADC_xbit        ADC精度(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @since      v5.0
 *  @note       此函数内部调用，启动后即可等待数据采集完成
 *  Sample usage:       ADC_Start(ADC0_SE10, ADC_8Bit);
 */
static void ADC_Start(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit)
{
  //ADC配置寄存器1
  ADC_CFG1_REG(ADCN[ADCn(ADCn_CHx)]) = (0
                                         | ADC_CFG1_ADIV(2)             //ADC时钟4分频,2^n,n=0~3
                                         | ADC_CFG1_ADLSMP_MASK         //ADC长采样时间,0:短采样时间,1:长采样时间
                                         | ADC_CFG1_MODE(ADC_xBit)      //ADC转换精度选择
                                         | ADC_CFG1_ADICLK(0)           //ADC时钟采用总线时钟,00:Bus,01:Bus/2,10:ALTCLK,11:ADACK
                                         );
  
  //ADC配置寄存器2
  ADC_CFG2_REG(ADCN[ADCn(ADCn_CHx)]) = (0
                                         | ADC_CFG2_ADHSC_MASK          //高速采样转换序列
                                         | ADC_CFG2_ADLSTS(0)           //默认最长采样时间,24个ADCK
                                         );
  
  
  //ADC状态控制寄存器(A通道)
  ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) = (0
                                                      | ADC_SC1_AIEN_MASK                  //转换完成中断使能
                                                      | ADC_SC1_ADCH(ADC_CHn(ADCn_CHx))    //选择ADC转换通道
                                                      );
  
}

/*
 *  @brief      停止ADC软件采样
 *  @param      ADC_ADCn        ADC_ADCx        ADC通道
 *  @since      v1.0
 *  Sample usage:       ADC_Stop(ADC_ADC0);
 */
void ADC_Stop(ADC_ADCn ADC_ADCx)
{
  //断言ADC模块号ADC_ADC0,ADC_ADC1
  ASSERT(ADC_ADCx <= ADC_ADC1);
  
  ADC_SC1_REG(ADCN[ADC_ADCx],ADC_Channel_A) = (0
                                               | ADC_SC1_AIEN_MASK              //ADC转换完成中断使能
                                               | ADC_SC1_ADCH(Module0_Dis)     //ADC模块禁止
                                               );
  
}

/*
 *  @brief      获取ADC采样值(不支持B通道)
 *  @param      ADCn_CHn        ADCn_CHx        ADC通道
 *  @param      ADC_nBit        ADC_xbit        ADC精度(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @return     采样值
 *  @since      v1.0
 *  Sample usage:       uint16 var = ADC_Once(ADC0_SE10,ADC_8Bit);
 */
uint16 ADC_Once(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit)
{
  uint16 ADC_Result=0;
  
  ADC_Start(ADCn_CHx,ADC_xBit);//启动ADC转换
  
  while((ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
  
  ADC_Result = ADC_R_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A);//获取ADC转换结果
  
  ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) &= ~ADC_SC1_COCO_MASK;//ADC转换完成标志位清零
  
  return ADC_Result;
}

/*
 *  @brief      ADC采样N次采样均值值(不支持B通道)
 *  @param      ADCn_CHn        ADCn_CHx        ADC通道
 *  @param      ADC_nBit        ADC_xbit        ADC精度(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @param      uint8           ADC_Samp_Num
 *  @return     采样值
 *  @since      v1.0
 *  Sample usage:       uint16 var = ADC_Average(ADC0_SE10,ADC_8Bit,20);
 */
uint16 ADC_Average(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit,uint8 ADC_Samp_Num)
{
  uint8 i=0;
  uint16 ADC_Samp_Ave=0;
  uint32 ADC_Samp_Temp=0;
  
  for(i=0;i<ADC_Samp_Num;i++)
  {
    ADC_Start(ADCn_CHx,ADC_xBit);//启动ADC转换
    
    while((ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
    
    ADC_Samp_Temp += ADC_R_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A);//获取ADC转换结果
    
    ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) &= ~ADC_SC1_COCO_MASK;//ADC转换完成标志位清零
  }
  
  ADC_Samp_Ave = ADC_Samp_Temp / ADC_Samp_Num;
  
  return ADC_Samp_Ave;
}

/*
 *  @brief      ADC采样N次存储到数组(不支持B通道)
 *  @param      ADCn_CHn        ADCn_CHx        ADC通道
 *  @param      ADC_nBit        ADC_xbit        ADC精度(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @param      uint16          ADC_Array[]     ADC数组
 *  @return     采样值
 *  @since      v1.0
 *  Sample usage:               ADC_Samp_Array(ADC0_SE10,ADC_12Bit,&ADC_Array[0])
 */
void ADC_Samp_Array(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit,uint16 *ADC_Array)
{
  uint8 i=0;
  uint8 ADC_Array_Size=0;
  
  ADC_Array_Size = (sizeof(ADC_Array) / sizeof(uint16));
  
  for(i=0;i<ADC_Array_Size;i++)
  {
    ADC_Start(ADCn_CHx,ADC_xBit);//启动ADC转换
    
    while((ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
    
    *ADC_Array++ = ADC_R_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A);//获取ADC转换结果
    
    ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) &= ~ADC_SC1_COCO_MASK;//ADC转换完成标志位清零
  }
  
}