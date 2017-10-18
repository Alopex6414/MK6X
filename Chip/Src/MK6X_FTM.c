/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FTM.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**FTM基址指针
*/
FTM_MemMapPtr FTMN[FTM_FTM_MAX]=
{
  FTM0_BASE_PTR,//FTM0基址指针
  FTM1_BASE_PTR,//FTM1基址指针
  FTM2_BASE_PTR,//FTM2基址指针
  FTM3_BASE_PTR,//FTM3基址指针
};

/*
 *  @brief      初始化FTM的端口(PORT复用为FTM)
 *  @param      FTM_FTMn FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  通道号(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @since      v1.0
 *  @note       static声明,作用域仅在MK66_FTM.c
 */
static void FTM_PORT_MUX(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx)
{
  switch(FTM_FTMx)//选择FTM模块号
  {
    case FTM_FTM0://FTM0
                  SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;//FTM0时钟使能
                  switch(FTM_CHx)//选择FTM通道FTM0_CH0~FTM0_CH7
                  {
                    case FTM_CH0:
                                 if(FTM0_CH0_PIN == PTC1)
                                 {
                                   PORT_Init(FTM0_CH0_PIN,ALT4);
                                 }
                                 else if(FTM0_CH0_PIN == PTA3)
                                 {
                                   PORT_Init(FTM0_CH0_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH1:
                                 if(FTM0_CH1_PIN == PTC2)
                                 {
                                   PORT_Init(FTM0_CH1_PIN,ALT4);
                                 }
                                 else if(FTM0_CH1_PIN == PTA4)
                                 {
                                   PORT_Init(FTM0_CH1_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH2:
                                 if(FTM0_CH2_PIN == PTC3)
                                 {
                                   PORT_Init(FTM0_CH2_PIN,ALT4);
                                 }
                                 else if(FTM0_CH2_PIN == PTA5)
                                 {
                                   PORT_Init(FTM0_CH2_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH3:
                                 if(FTM0_CH3_PIN == PTC4)
                                 {
                                   PORT_Init(FTM0_CH3_PIN,ALT4);
                                 }
                                 else if(FTM0_CH3_PIN == PTA6)
                                 {
                                   PORT_Init(FTM0_CH3_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH4:
                                 if(FTM0_CH4_PIN == PTD4)
                                 {
                                   PORT_Init(FTM0_CH4_PIN,ALT4);
                                 }
                                 else if(FTM0_CH4_PIN == PTA7)
                                 {
                                   PORT_Init(FTM0_CH4_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH5:
                                 if(FTM0_CH5_PIN == PTD5)
                                 {
                                   PORT_Init(FTM0_CH5_PIN,ALT4);
                                 }
                                 else if(FTM0_CH5_PIN == PTA0)
                                 {
                                   PORT_Init(FTM0_CH5_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH6:
                                 if(FTM0_CH6_PIN == PTD6)
                                 {
                                   PORT_Init(FTM0_CH6_PIN,ALT4);
                                 }
                                 else if(FTM0_CH6_PIN == PTA1)
                                 {
                                   PORT_Init(FTM0_CH6_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH7:
                                 if(FTM0_CH7_PIN == PTD7)
                                 {
                                   PORT_Init(FTM0_CH7_PIN,ALT4);
                                 }
                                 else if(FTM0_CH7_PIN == PTA2)
                                 {
                                   PORT_Init(FTM0_CH7_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    default:
                                 ASSERT(0);
                                 break;                                 
                  }
                  break;
    case FTM_FTM1://FTM1
                  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;//FTM1时钟使能
                  switch(FTM_CHx)//选择FTM通道FTM1_CH0~FTM1_CH1
                  {
                    case FTM_CH0:
                                 if((FTM1_CH0_PIN == PTA8) || (FTM1_CH0_PIN == PTA12) || (FTM1_CH0_PIN == PTB0))
                                 {
                                   PORT_Init(FTM1_CH0_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH1:
                                 if((FTM1_CH1_PIN == PTA9) || (FTM1_CH1_PIN == PTA13) || (FTM1_CH1_PIN == PTB1))
                                 {
                                   PORT_Init(FTM1_CH1_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    default:
                                 ASSERT(0);
                                 break;
                  }
                  break;
    case FTM_FTM2://FTM2
                  SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;//FTM2时钟使能
                  SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;//FTM2时钟使能
                  switch(FTM_CHx)//选择FTM通道FTM2_CH0~FTM2_CH1
                  {
                    case FTM_CH0:
                                 if((FTM2_CH0_PIN == PTA10) || (FTM2_CH0_PIN == PTB18))
                                 {
                                   PORT_Init(FTM2_CH0_PIN,ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH1:
                                 if((FTM2_CH1_PIN == PTA11) || (FTM2_CH1_PIN == PTB19))
                                 {
                                   PORT_Init(FTM2_CH1_PIN, ALT3);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    default:
                                 ASSERT(0);
                                 break;
                  }
                  break;
    case FTM_FTM3://FTM3
                  SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;//FTM3时钟使能
                  switch(FTM_CHx)//选择FTM通道FTM3_CH0~FTM3_CH7
                  {
                    case FTM_CH0:
                                 if(FTM3_CH0_PIN == PTD0)
                                 {
                                   PORT_Init(FTM3_CH0_PIN,ALT4);
                                 }
                                 else if(FTM3_CH0_PIN == PTE5)
                                 {
                                   PORT_Init(FTM3_CH0_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH1:
                                 if(FTM3_CH1_PIN == PTD1)
                                 {
                                   PORT_Init(FTM3_CH1_PIN,ALT4);
                                 }
                                 else if(FTM3_CH1_PIN == PTE6)
                                 {
                                   PORT_Init(FTM3_CH1_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH2:
                                 if(FTM3_CH2_PIN == PTD2)
                                 {
                                   PORT_Init(FTM3_CH2_PIN,ALT4);
                                 }
                                 else if(FTM3_CH2_PIN == PTE7)
                                 {
                                   PORT_Init(FTM3_CH2_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH3:
                                 if(FTM3_CH3_PIN == PTD3)
                                 {
                                   PORT_Init(FTM3_CH3_PIN,ALT4);
                                 }
                                 else if(FTM3_CH3_PIN == PTE8)
                                 {
                                   PORT_Init(FTM3_CH3_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH4:
                                 if(FTM3_CH4_PIN == PTC8)
                                 {
                                   PORT_Init(FTM3_CH4_PIN,ALT3);
                                 }
                                 else if(FTM3_CH4_PIN == PTE9)
                                 {
                                   PORT_Init(FTM3_CH4_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH5:
                                 if(FTM3_CH5_PIN == PTC9)
                                 {
                                   PORT_Init(FTM3_CH5_PIN,ALT3);
                                 }
                                 else if(FTM3_CH5_PIN == PTE10)
                                 {
                                   PORT_Init(FTM3_CH5_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH6:
                                 if(FTM3_CH6_PIN == PTC10)
                                 {
                                   PORT_Init(FTM3_CH6_PIN,ALT3);
                                 }
                                 else if(FTM3_CH6_PIN == PTE11)
                                 {
                                   PORT_Init(FTM3_CH6_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    case FTM_CH7:
                                 if(FTM3_CH7_PIN == PTC11)
                                 {
                                   PORT_Init(FTM3_CH7_PIN,ALT3);
                                 }
                                 else if(FTM3_CH7_PIN == PTE12)
                                 {
                                   PORT_Init(FTM3_CH7_PIN,ALT6);
                                 }
                                 else
                                 {
                                   ASSERT(0);
                                 }
                                 break;
                    default:
                                 ASSERT(0);
                                 break;                                 
                  }
                  break;
    default:
                  ASSERT(0);
                  break;                  
  }
  
}

/*
 *  @brief      初始化FTM的PWM功能
 *  @param      FTM_FTMn FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  通道号(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @param      uint32   FTM_Freq 频率(单位为Hz)
 *  @param      uint32   FTM_Duty 占空比分子,占空比 = FTM_Duty / FTMn_PRECISON
 *  @since      v1.0
 *  @note       同一个FTM,PWM频率是必须一样的,但占空比可不一样.共4个FTM,即可以输出4个不同频率PWM,电机控制建议用FTM0和FTM3
 *  Sample usage:       FTM_PWM_Init(FTM_FTM0, FTM_CH6,200, 10);    //初始化 FTM0_CH6 为 频率 200Hz 的PWM，占空比为 10/FTM0_PRECISON
 */
void FTM_PWM_Init(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,uint32 FTM_Freq,uint32 FTM_Duty)
{
  uint8  FTM_Ps=0;      //FTM分频因子2^FTM_Ps
  uint16 FTM_Mod=0;     //FTM模数值,FTM脉冲周期
  uint16 FTM_Cv=0;      //FTM脉冲周期高电平持续时间
  uint32 FTM_Clk_Hz=0;  //FTM时钟频率,选择总线时钟,即为Bus_Clock
  
  //FTM断言,FTM1和FTM2只有CH0,CH1;FTM0和FTM3有CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  FTM_PORT_MUX(FTM_FTMx,FTM_CHx);//FTM时钟端口复用
  
  //PWM频率计算公式:PWM_Freq = (MK66_Bus_Clock) / (2^FTM_PS * (MOD - CNTIN + 1))
  //计数初值CNTIN设置为0,频率计算公式可简化为:PWM_Freq = (MK66_Bus_Clock) / (2^FTM_PS * (MOD + 1))
  FTM_Clk_Hz = MK6X_Bus_KHz * 1000;//FTM时钟频率(Hz)
  FTM_Mod = (FTM_Clk_Hz >> 16) / FTM_Freq;//FTM_Mod临时缓存,(MOD+1)先设为最大值(0xffff+0x1=0x10000,即2^16,右移16Bit,计算FTM_PS的值)
  FTM_Ps=0;
  
  while((FTM_Mod >> FTM_Ps) >= 1)//求FTM_Ps最小值,满足分频条件
  {
    FTM_Ps++;
  }
  
  ASSERT(FTM_Ps <= 0x07);//断言,FTM_Ps(0~7),FTM_Ps最大值为0x07,超过0x07,PWM频率设置过低或Bus频率过高
  
  FTM_Mod = (FTM_Clk_Hz >> FTM_Ps) / FTM_Freq;//计算FTM_Mod的值,FTM周期值
  
  //EPWM边沿对齐模式PWM,FTM_Cv / FTM_PRECISON = FTM_Duty / (FTM_Mod + 1)
  
  switch(FTM_FTMx)//选择FTM模块,计算占空比
  {
    case FTM_FTM0:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM0_PRECISON;
                  break;
    case FTM_FTM1:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM1_PRECISON;
                  break;
    case FTM_FTM2:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM2_PRECISON;
                  break;
    case FTM_FTM3:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM3_PRECISON;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  //通道状态控制，根据模式来选择 边沿或电平
  FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~FTM_CnSC_ELSA_MASK;
  FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
  
  FTM_SC_REG(FTMN[FTM_FTMx]) = (0 | FTM_SC_PS(FTM_Ps) | FTM_SC_CLKS(1));//选择总线时钟,时钟分频2^FTM_Ps
  FTM_MOD_REG(FTMN[FTM_FTMx]) = FTM_Mod;//FTM模数值,FTM脉冲周期
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;//FTM定时器初值,设置为0
  FTM_CnV_REG(FTMN[FTM_FTMx],FTM_CHx) = FTM_Cv;//FTM计数值计数器,FTM高电平持续周期
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//计数器计数值清零
  
}

/*
 *  @brief      设置FTM的PWM通道占空比
 *  @param      FTM_FTMn FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  通道号(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @param      uint32   FTM_Duty 占空比分子,占空比 = FTM_Duty / FTMn_PRECISON
 *  @since      v1.0
 *  @note       同一个FTM，PWM频率是必须一样的，但占空比可不一样。共4个FTM，即可以输出4个不同频率PWM
 *  Sample usage:       FTM_PWM_Duty(FTM_FTM0, FTM_CH6, 10);    //设置 FTM0_CH6占空比为 10/FTM0_PRECISON
 */
void FTM_PWM_Duty(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,uint32 FTM_Duty)
{
  uint32 FTM_Cv=0;
  uint32 FTM_Mod=0;
  
  //FTM断言,FTM1和FTM2只有CH0,CH1;FTM0和FTM3有CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  switch(FTM_FTMx)//断言监测FTM占空比是否满足精度要求
  {
    case FTM_FTM0:
                  ASSERT(FTM_Duty <= FTM0_PRECISON);
                  break;
    case FTM_FTM1:
                  ASSERT(FTM_Duty <= FTM1_PRECISON);
                  break;
    case FTM_FTM2:
                  ASSERT(FTM_Duty <= FTM2_PRECISON);
                  break;
    case FTM_FTM3:
                  ASSERT(FTM_Duty <= FTM3_PRECISON);
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  do
  {
    FTM_Mod = FTM_MOD_REG(FTMN[FTM_FTMx]);//读取MOD值
  }while(FTM_Mod == 0);//多读计次MOD值,读到不为0为止
  
  //EPWM边沿对齐模式PWM,FTM_Cv / FTM_PRECISON = FTM_Duty / (FTM_Mod + 1)
  
  switch(FTM_FTMx)//PWM占空比计算
  {
    case FTM_FTM0:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM0_PRECISON;
                  break;
    case FTM_FTM1:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM1_PRECISON;
                  break;
    case FTM_FTM2:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM2_PRECISON;
                  break;
    case FTM_FTM3:
                  FTM_Cv = (FTM_Duty * (FTM_Mod + 1)) / FTM3_PRECISON;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  FTM_CnV_REG(FTMN[FTM_FTMx],FTM_CHx) = FTM_Cv;//设置FTM高电平计数值
  
}

/*
 *  @brief      设置FTM的频率
 *  @param      FTM_FTMn FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  通道号(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @since      v1.0
 *  @note       修改PWM频率后，必须调用 FTM_PWM_Duty 重新配置占空比。同一个模块，PWM频率必须相同。
 *  Sample usage:       FTM_PWM_Freq(FTM_FTM0,200);    //设置 FTM0 的 频率 为 200Hz
 */
void FTM_PWM_Freq(FTM_FTMn FTM_FTMx,uint32 FTM_Freq)
{
  uint8  FTM_Ps=0;      //FTM分频因子2^FTM_Ps
  uint32 FTM_Mod=0;     //FTM模数值,FTM脉冲周期
  uint32 FTM_Clk_Hz=0;  //FTM时钟频率,选择总线时钟,即为Bus_Clock
  
  FTM_Clk_Hz = MK6X_Bus_KHz * 1000;//Bus频率
  FTM_Mod = (FTM_Clk_Hz >> 16) / FTM_Freq;//FTM_Mod临时缓存
  FTM_Ps=0;
  
  while((FTM_Mod >> FTM_Ps) >= 1)//求FTM_Ps最小值
  {
    FTM_Ps++;
  }
  
  ASSERT(FTM_Ps <= 0x07);//断言,FTM_Ps最大值为0x07,超过0x07,PWM频率设置过低或Bus频率过高
  
  FTM_Mod = (FTM_Clk_Hz >> FTM_Ps) / FTM_Freq;//计算FTM_Mod的值
  
  //FTM频率时钟配置
  FTM_SC_REG(FTMN[FTM_FTMx]) = (0 | FTM_SC_PS(FTM_Ps) | FTM_SC_CLKS(1));//选择总线时钟,时钟分频2^FTM_Ps
  FTM_MOD_REG(FTMN[FTM_FTMx]) = FTM_Mod;//FTM周期 FTM_MOD+1
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;//FTM计数初值0
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//FTM计数器清零
  
}

/*
 *  @brief      输入捕捉初始化函数
 *  @param      FTM_FTMn        FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn         FTM_CHx  通道号(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @param      FTM_INPUT_CFG   FTM_CFG  输入捕捉触发条件配置
 *  @param      FTM_PS_n        FTM_PS_x 分频因子
 *  @since      v1.0
 *  @note       同一个FTM，只能干一个活，用于输入捕捉后就不要再用于其他功能，例如PWM。
 *  Sample usage:       FTM_Input_Init(FTM_FTM0, FTM_CH0, FTM_Rising,FTM_PS_2);    //设置 FTM0_CH0上升沿触发输入捕捉，二分频
 */
void FTM_Input_Init(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,FTM_INPUT_CFG FTM_CFG,FTM_PS_n FTM_PS_x)
{
  //FTM断言,FTM1和FTM2只有CH0,CH1;FTM0和FTM3有CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  FTM_PORT_MUX(FTM_FTMx,FTM_CHx);//FTM时钟端口复用
  
  switch(FTM_CFG)//选择输入捕捉触发模式
  {
    case FTM_Rising://上升沿捕捉
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= (FTM_CnSC_ELSA_MASK | FTM_CnSC_CHIE_MASK);//ELSnB:ELSnA=01,上升沿捕捉
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~(FTM_CnSC_ELSB_MASK  | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK);
                               break;
    case FTM_Falling://下降沿捕捉
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= (FTM_CnSC_ELSB_MASK  | FTM_CnSC_CHIE_MASK);//ELSnB:ELSnA=10,下降沿捕捉
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~(FTM_CnSC_ELSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK);
                               break;
    case FTM_Rising_or_Falling://跳变沿捕捉
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= (FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK);
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~(FTM_CnSC_MSB_MASK  | FTM_CnSC_MSA_MASK);//ELSnB:ELSnA=11,跳变沿捕捉
                               break;
    default:
                               ASSERT(0);
                               break;
  }
  
  FTM_SC_REG(FTMN[FTM_FTMx]) = (0 | FTM_SC_CLKS(1) | FTM_SC_PS(FTM_PS_x));//选择Bus时钟,分频系数
  FTM_MODE_REG(FTMN[FTM_FTMx]) |= FTM_MODE_WPDIS_MASK;//禁止写保护
  FTM_COMBINE_REG(FTMN[FTM_FTMx]) = 0;//通道设置不级联
  FTM_MODE_REG(FTMN[FTM_FTMx]) &= ~FTM_MODE_FTMEN_MASK;//FTM使能(开启输入捕捉功能和QUAD正交解码器功能)
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;//计数初值为0
  FTM_STATUS_REG(FTMN[FTM_FTMx]) = 0;//清中断标志
  
}

/*
 *  @brief      输入捕捉获取脉冲函数
 *  @param      FTM_FTMn        FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn         FTM_CHx  通道号(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @return     获取捕捉事件发生时的计数器值 (根据两次捕捉之间的差值可判断周期频率)
 *  @since      v1.0
 *  Sample usage:       uint16 data = FTM_Input_Get(FTM_FTM0, FTM_CH0) ;   // 获取FTM0_CH0输入捕捉事件触发时的计数值
 */
uint16 FTM_Input_Get(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx)
{
  uint16 FTM_Get_Count=0;
  
  //FTM断言,FTM1和FTM2只有CH0,CH1;FTM0和FTM3有CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  FTM_Get_Count = (uint16)FTM_CnV_REG(FTMN[FTM_FTMx],FTM_CHx);//捕获的FTM计数值
  
  return FTM_Get_Count;
  
}

/*
 *  @brief      输入捕捉清计数器值函数
 *  @param      FTM_FTMn        FTM_FTMx 模块号(FTM0,FTM1,FTM2,FTM3)
 *  @return     清计数器计数值
 *  @since      v1.0
 *  Sample usage:       FTM_Input_Clean(FTM_FTM0)
 */
void FTM_Input_Clean(FTM_FTMn FTM_FTMx)
{
  //断言FTM模块号
  ASSERT(FTM_FTMx <= FTM_FTM3);
  
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//FTM计数值清零
}

/*
 *  @brief      初始化FTM的正交解码功能(只有FTM1和FTM2有正交解码器模式)
 *  @param      FTM_FTMn        FTM_FTMx 模块号(FTM1,FTM2)
 *  @since      v1.0
 *  Sample usage:       FTM_QUAD_Init(FTM1);    //初始化FTM1为正交解码模式
 */
void FTM_QUAD_Init(FTM_FTMn FTM_FTMx)
{
  //断言QUAD正交解码只有FTM1和FTM2
  ASSERT((FTM_FTMx == FTM_FTM1) || (FTM_FTMx == FTM_FTM2));
  
  switch(FTM_FTMx)//选择FTM模块初始化QUAD
  {
    case FTM_FTM1:
                  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;//FTM1时钟使能
                  //FTM1_CH0
                  if((FTM1_QDPHA_PIN == PTA8) || (FTM1_QDPHA_PIN == PTB0))
                  {
                    PORT_Init(FTM1_QDPHA_PIN,ALT6);
                  }
                  else if(FTM1_QDPHA_PIN == PTA12)
                  {
                    PORT_Init(FTM1_QDPHA_PIN,ALT7);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  //FTM1_CH1
                  if((FTM1_QDPHB_PIN == PTA9) || (FTM1_QDPHB_PIN == PTB1))
                  {
                    PORT_Init(FTM1_QDPHB_PIN,ALT6);
                  }
                  else if(FTM1_QDPHB_PIN == PTA13)
                  {
                    PORT_Init(FTM1_QDPHB_PIN,ALT7);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case FTM_FTM2:
                  SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;//FTM2时钟使能
                  SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
                  //FTM2_CH0
                  if((FTM2_QDPHA_PIN == PTA10) || (FTM2_QDPHA_PIN == PTB18))
                  {
                    PORT_Init(FTM2_QDPHA_PIN,ALT6);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  //FTM2_CH1
                  if((FTM2_QDPHB_PIN == PTA11) || (FTM2_QDPHB_PIN == PTB19))
                  {
                    PORT_Init(FTM2_QDPHB_PIN,ALT6);
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  FTM_MODE_REG(FTMN[FTM_FTMx]) |= (0 | FTM_MODE_WPDIS_MASK);//禁止写保护
  
  //FTM_QUAD正交解码模式,直接计数模式
  FTM_QDCTRL_REG(FTMN[FTM_FTMx]) |= (0 | FTM_QDCTRL_QUADMODE_MASK);
  //FTM计数初值设置为0
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;
  //FTM计数周期终值设为0xffff
  FTM_MOD_REG(FTMN[FTM_FTMx]) |= FTM_MOD_MOD_MASK;
  //FTM_QUAD正交解码模式使能
  FTM_QDCTRL_REG(FTMN[FTM_FTMx]) |= (0 | FTM_QDCTRL_QUADEN_MASK);
  //FTM使能
  FTM_MODE_REG(FTMN[FTM_FTMx]) |= FTM_MODE_FTMEN_MASK;
  //FTM计数清零
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;
  
}

/*
 *  @brief      获取FTM 正交解码的脉冲数
 *  @param      FTM_FTMn        FTM_FTMx 模块号(FTM1,FTM2)
 *  @since      v1.0
 *  Sample usage:       int16 FTM_Count = FTM_QUAD_Get(FTM_FTM1);    //获取  FTM1 交解码 的脉冲数
 */
int16 FTM_QUAD_Get(FTM_FTMn FTM_FTMx)
{
  int16 FTM_QUAD_Count=0;
  
  //断言QUAD正交解码只有FTM1和FTM2
  ASSERT((FTM_FTMx == FTM_FTM1) || (FTM_FTMx == FTM_FTM2));
  
  FTM_QUAD_Count = FTM_CNT_REG(FTMN[FTM_FTMx]);//QUAD正交解码获取计数器值
  
  return FTM_QUAD_Count;
}

/*
 *  @brief      清除FTM正交解码的脉冲数
 *  @param      FTM_FTMn        FTM_FTMx 模块号(FTM1,FTM2)
 *  @since      v1.0
 *  Sample usage:       FTM_QUAD_Clean(FTM_FTM1);    //清除FTM正交解码的脉冲数
 */
void FTM_QUAD_Clean(FTM_FTMn FTM_FTMx)
{
  //断言QUAD正交解码只有FTM1和FTM2
  ASSERT((FTM_FTMx == FTM_FTM1) || (FTM_FTMx == FTM_FTM2));
  
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//QUAD正交解码计数器值清零
}