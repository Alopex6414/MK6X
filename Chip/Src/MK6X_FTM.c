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
**FTM��ַָ��
*/
FTM_MemMapPtr FTMN[FTM_FTM_MAX]=
{
  FTM0_BASE_PTR,//FTM0��ַָ��
  FTM1_BASE_PTR,//FTM1��ַָ��
  FTM2_BASE_PTR,//FTM2��ַָ��
  FTM3_BASE_PTR,//FTM3��ַָ��
};

/*
 *  @brief      ��ʼ��FTM�Ķ˿�(PORT����ΪFTM)
 *  @param      FTM_FTMn FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  ͨ����(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @since      v1.0
 *  @note       static����,���������MK66_FTM.c
 */
static void FTM_PORT_MUX(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx)
{
  switch(FTM_FTMx)//ѡ��FTMģ���
  {
    case FTM_FTM0://FTM0
                  SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;//FTM0ʱ��ʹ��
                  switch(FTM_CHx)//ѡ��FTMͨ��FTM0_CH0~FTM0_CH7
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
                  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;//FTM1ʱ��ʹ��
                  switch(FTM_CHx)//ѡ��FTMͨ��FTM1_CH0~FTM1_CH1
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
                  SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;//FTM2ʱ��ʹ��
                  SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;//FTM2ʱ��ʹ��
                  switch(FTM_CHx)//ѡ��FTMͨ��FTM2_CH0~FTM2_CH1
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
                  SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;//FTM3ʱ��ʹ��
                  switch(FTM_CHx)//ѡ��FTMͨ��FTM3_CH0~FTM3_CH7
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
 *  @brief      ��ʼ��FTM��PWM����
 *  @param      FTM_FTMn FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  ͨ����(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @param      uint32   FTM_Freq Ƶ��(��λΪHz)
 *  @param      uint32   FTM_Duty ռ�ձȷ���,ռ�ձ� = FTM_Duty / FTMn_PRECISON
 *  @since      v1.0
 *  @note       ͬһ��FTM,PWMƵ���Ǳ���һ����,��ռ�ձȿɲ�һ��.��4��FTM,���������4����ͬƵ��PWM,������ƽ�����FTM0��FTM3
 *  Sample usage:       FTM_PWM_Init(FTM_FTM0, FTM_CH6,200, 10);    //��ʼ�� FTM0_CH6 Ϊ Ƶ�� 200Hz ��PWM��ռ�ձ�Ϊ 10/FTM0_PRECISON
 */
void FTM_PWM_Init(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,uint32 FTM_Freq,uint32 FTM_Duty)
{
  uint8  FTM_Ps=0;      //FTM��Ƶ����2^FTM_Ps
  uint16 FTM_Mod=0;     //FTMģ��ֵ,FTM��������
  uint16 FTM_Cv=0;      //FTM�������ڸߵ�ƽ����ʱ��
  uint32 FTM_Clk_Hz=0;  //FTMʱ��Ƶ��,ѡ������ʱ��,��ΪBus_Clock
  
  //FTM����,FTM1��FTM2ֻ��CH0,CH1;FTM0��FTM3��CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  FTM_PORT_MUX(FTM_FTMx,FTM_CHx);//FTMʱ�Ӷ˿ڸ���
  
  //PWMƵ�ʼ��㹫ʽ:PWM_Freq = (MK66_Bus_Clock) / (2^FTM_PS * (MOD - CNTIN + 1))
  //������ֵCNTIN����Ϊ0,Ƶ�ʼ��㹫ʽ�ɼ�Ϊ:PWM_Freq = (MK66_Bus_Clock) / (2^FTM_PS * (MOD + 1))
  FTM_Clk_Hz = MK6X_Bus_KHz * 1000;//FTMʱ��Ƶ��(Hz)
  FTM_Mod = (FTM_Clk_Hz >> 16) / FTM_Freq;//FTM_Mod��ʱ����,(MOD+1)����Ϊ���ֵ(0xffff+0x1=0x10000,��2^16,����16Bit,����FTM_PS��ֵ)
  FTM_Ps=0;
  
  while((FTM_Mod >> FTM_Ps) >= 1)//��FTM_Ps��Сֵ,�����Ƶ����
  {
    FTM_Ps++;
  }
  
  ASSERT(FTM_Ps <= 0x07);//����,FTM_Ps(0~7),FTM_Ps���ֵΪ0x07,����0x07,PWMƵ�����ù��ͻ�BusƵ�ʹ���
  
  FTM_Mod = (FTM_Clk_Hz >> FTM_Ps) / FTM_Freq;//����FTM_Mod��ֵ,FTM����ֵ
  
  //EPWM���ض���ģʽPWM,FTM_Cv / FTM_PRECISON = FTM_Duty / (FTM_Mod + 1)
  
  switch(FTM_FTMx)//ѡ��FTMģ��,����ռ�ձ�
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
  
  //ͨ��״̬���ƣ�����ģʽ��ѡ�� ���ػ��ƽ
  FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~FTM_CnSC_ELSA_MASK;
  FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
  
  FTM_SC_REG(FTMN[FTM_FTMx]) = (0 | FTM_SC_PS(FTM_Ps) | FTM_SC_CLKS(1));//ѡ������ʱ��,ʱ�ӷ�Ƶ2^FTM_Ps
  FTM_MOD_REG(FTMN[FTM_FTMx]) = FTM_Mod;//FTMģ��ֵ,FTM��������
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;//FTM��ʱ����ֵ,����Ϊ0
  FTM_CnV_REG(FTMN[FTM_FTMx],FTM_CHx) = FTM_Cv;//FTM����ֵ������,FTM�ߵ�ƽ��������
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//����������ֵ����
  
}

/*
 *  @brief      ����FTM��PWMͨ��ռ�ձ�
 *  @param      FTM_FTMn FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  ͨ����(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @param      uint32   FTM_Duty ռ�ձȷ���,ռ�ձ� = FTM_Duty / FTMn_PRECISON
 *  @since      v1.0
 *  @note       ͬһ��FTM��PWMƵ���Ǳ���һ���ģ���ռ�ձȿɲ�һ������4��FTM�����������4����ͬƵ��PWM
 *  Sample usage:       FTM_PWM_Duty(FTM_FTM0, FTM_CH6, 10);    //���� FTM0_CH6ռ�ձ�Ϊ 10/FTM0_PRECISON
 */
void FTM_PWM_Duty(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,uint32 FTM_Duty)
{
  uint32 FTM_Cv=0;
  uint32 FTM_Mod=0;
  
  //FTM����,FTM1��FTM2ֻ��CH0,CH1;FTM0��FTM3��CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  switch(FTM_FTMx)//���Լ��FTMռ�ձ��Ƿ����㾫��Ҫ��
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
    FTM_Mod = FTM_MOD_REG(FTMN[FTM_FTMx]);//��ȡMODֵ
  }while(FTM_Mod == 0);//����ƴ�MODֵ,������Ϊ0Ϊֹ
  
  //EPWM���ض���ģʽPWM,FTM_Cv / FTM_PRECISON = FTM_Duty / (FTM_Mod + 1)
  
  switch(FTM_FTMx)//PWMռ�ձȼ���
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
  
  FTM_CnV_REG(FTMN[FTM_FTMx],FTM_CHx) = FTM_Cv;//����FTM�ߵ�ƽ����ֵ
  
}

/*
 *  @brief      ����FTM��Ƶ��
 *  @param      FTM_FTMn FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn  FTM_CHx  ͨ����(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @since      v1.0
 *  @note       �޸�PWMƵ�ʺ󣬱������ FTM_PWM_Duty ��������ռ�ձȡ�ͬһ��ģ�飬PWMƵ�ʱ�����ͬ��
 *  Sample usage:       FTM_PWM_Freq(FTM_FTM0,200);    //���� FTM0 �� Ƶ�� Ϊ 200Hz
 */
void FTM_PWM_Freq(FTM_FTMn FTM_FTMx,uint32 FTM_Freq)
{
  uint8  FTM_Ps=0;      //FTM��Ƶ����2^FTM_Ps
  uint32 FTM_Mod=0;     //FTMģ��ֵ,FTM��������
  uint32 FTM_Clk_Hz=0;  //FTMʱ��Ƶ��,ѡ������ʱ��,��ΪBus_Clock
  
  FTM_Clk_Hz = MK6X_Bus_KHz * 1000;//BusƵ��
  FTM_Mod = (FTM_Clk_Hz >> 16) / FTM_Freq;//FTM_Mod��ʱ����
  FTM_Ps=0;
  
  while((FTM_Mod >> FTM_Ps) >= 1)//��FTM_Ps��Сֵ
  {
    FTM_Ps++;
  }
  
  ASSERT(FTM_Ps <= 0x07);//����,FTM_Ps���ֵΪ0x07,����0x07,PWMƵ�����ù��ͻ�BusƵ�ʹ���
  
  FTM_Mod = (FTM_Clk_Hz >> FTM_Ps) / FTM_Freq;//����FTM_Mod��ֵ
  
  //FTMƵ��ʱ������
  FTM_SC_REG(FTMN[FTM_FTMx]) = (0 | FTM_SC_PS(FTM_Ps) | FTM_SC_CLKS(1));//ѡ������ʱ��,ʱ�ӷ�Ƶ2^FTM_Ps
  FTM_MOD_REG(FTMN[FTM_FTMx]) = FTM_Mod;//FTM���� FTM_MOD+1
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;//FTM������ֵ0
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//FTM����������
  
}

/*
 *  @brief      ���벶׽��ʼ������
 *  @param      FTM_FTMn        FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn         FTM_CHx  ͨ����(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @param      FTM_INPUT_CFG   FTM_CFG  ���벶׽������������
 *  @param      FTM_PS_n        FTM_PS_x ��Ƶ����
 *  @since      v1.0
 *  @note       ͬһ��FTM��ֻ�ܸ�һ����������벶׽��Ͳ�Ҫ�������������ܣ�����PWM��
 *  Sample usage:       FTM_Input_Init(FTM_FTM0, FTM_CH0, FTM_Rising,FTM_PS_2);    //���� FTM0_CH0�����ش������벶׽������Ƶ
 */
void FTM_Input_Init(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx,FTM_INPUT_CFG FTM_CFG,FTM_PS_n FTM_PS_x)
{
  //FTM����,FTM1��FTM2ֻ��CH0,CH1;FTM0��FTM3��CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  FTM_PORT_MUX(FTM_FTMx,FTM_CHx);//FTMʱ�Ӷ˿ڸ���
  
  switch(FTM_CFG)//ѡ�����벶׽����ģʽ
  {
    case FTM_Rising://�����ز�׽
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= (FTM_CnSC_ELSA_MASK | FTM_CnSC_CHIE_MASK);//ELSnB:ELSnA=01,�����ز�׽
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~(FTM_CnSC_ELSB_MASK  | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK);
                               break;
    case FTM_Falling://�½��ز�׽
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= (FTM_CnSC_ELSB_MASK  | FTM_CnSC_CHIE_MASK);//ELSnB:ELSnA=10,�½��ز�׽
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~(FTM_CnSC_ELSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK);
                               break;
    case FTM_Rising_or_Falling://�����ز�׽
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) |= (FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK);
                               FTM_CnSC_REG(FTMN[FTM_FTMx],FTM_CHx) &= ~(FTM_CnSC_MSB_MASK  | FTM_CnSC_MSA_MASK);//ELSnB:ELSnA=11,�����ز�׽
                               break;
    default:
                               ASSERT(0);
                               break;
  }
  
  FTM_SC_REG(FTMN[FTM_FTMx]) = (0 | FTM_SC_CLKS(1) | FTM_SC_PS(FTM_PS_x));//ѡ��Busʱ��,��Ƶϵ��
  FTM_MODE_REG(FTMN[FTM_FTMx]) |= FTM_MODE_WPDIS_MASK;//��ֹд����
  FTM_COMBINE_REG(FTMN[FTM_FTMx]) = 0;//ͨ�����ò�����
  FTM_MODE_REG(FTMN[FTM_FTMx]) &= ~FTM_MODE_FTMEN_MASK;//FTMʹ��(�������벶׽���ܺ�QUAD��������������)
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;//������ֵΪ0
  FTM_STATUS_REG(FTMN[FTM_FTMx]) = 0;//���жϱ�־
  
}

/*
 *  @brief      ���벶׽��ȡ���庯��
 *  @param      FTM_FTMn        FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @param      FTM_CHn         FTM_CHx  ͨ����(FTM0&FTM3:CH0~CH7,FTM1&FTM2:CH0~CH1)
 *  @return     ��ȡ��׽�¼�����ʱ�ļ�����ֵ (�������β�׽֮��Ĳ�ֵ���ж�����Ƶ��)
 *  @since      v1.0
 *  Sample usage:       uint16 data = FTM_Input_Get(FTM_FTM0, FTM_CH0) ;   // ��ȡFTM0_CH0���벶׽�¼�����ʱ�ļ���ֵ
 */
uint16 FTM_Input_Get(FTM_FTMn FTM_FTMx,FTM_CHn FTM_CHx)
{
  uint16 FTM_Get_Count=0;
  
  //FTM����,FTM1��FTM2ֻ��CH0,CH1;FTM0��FTM3��CH0-CH7
  ASSERT(((FTM_FTMx == FTM_FTM0 || FTM_FTMx == FTM_FTM3) && (FTM_CHx <= FTM_CH7))
         || ((FTM_FTMx == FTM_FTM1 || FTM_FTMx == FTM_FTM2) && (FTM_CHx <= FTM_CH1)));
  
  FTM_Get_Count = (uint16)FTM_CnV_REG(FTMN[FTM_FTMx],FTM_CHx);//�����FTM����ֵ
  
  return FTM_Get_Count;
  
}

/*
 *  @brief      ���벶׽�������ֵ����
 *  @param      FTM_FTMn        FTM_FTMx ģ���(FTM0,FTM1,FTM2,FTM3)
 *  @return     �����������ֵ
 *  @since      v1.0
 *  Sample usage:       FTM_Input_Clean(FTM_FTM0)
 */
void FTM_Input_Clean(FTM_FTMn FTM_FTMx)
{
  //����FTMģ���
  ASSERT(FTM_FTMx <= FTM_FTM3);
  
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//FTM����ֵ����
}

/*
 *  @brief      ��ʼ��FTM���������빦��(ֻ��FTM1��FTM2������������ģʽ)
 *  @param      FTM_FTMn        FTM_FTMx ģ���(FTM1,FTM2)
 *  @since      v1.0
 *  Sample usage:       FTM_QUAD_Init(FTM1);    //��ʼ��FTM1Ϊ��������ģʽ
 */
void FTM_QUAD_Init(FTM_FTMn FTM_FTMx)
{
  //����QUAD��������ֻ��FTM1��FTM2
  ASSERT((FTM_FTMx == FTM_FTM1) || (FTM_FTMx == FTM_FTM2));
  
  switch(FTM_FTMx)//ѡ��FTMģ���ʼ��QUAD
  {
    case FTM_FTM1:
                  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;//FTM1ʱ��ʹ��
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
                  SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;//FTM2ʱ��ʹ��
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
  
  FTM_MODE_REG(FTMN[FTM_FTMx]) |= (0 | FTM_MODE_WPDIS_MASK);//��ֹд����
  
  //FTM_QUAD��������ģʽ,ֱ�Ӽ���ģʽ
  FTM_QDCTRL_REG(FTMN[FTM_FTMx]) |= (0 | FTM_QDCTRL_QUADMODE_MASK);
  //FTM������ֵ����Ϊ0
  FTM_CNTIN_REG(FTMN[FTM_FTMx]) = 0;
  //FTM����������ֵ��Ϊ0xffff
  FTM_MOD_REG(FTMN[FTM_FTMx]) |= FTM_MOD_MOD_MASK;
  //FTM_QUAD��������ģʽʹ��
  FTM_QDCTRL_REG(FTMN[FTM_FTMx]) |= (0 | FTM_QDCTRL_QUADEN_MASK);
  //FTMʹ��
  FTM_MODE_REG(FTMN[FTM_FTMx]) |= FTM_MODE_FTMEN_MASK;
  //FTM��������
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;
  
}

/*
 *  @brief      ��ȡFTM ���������������
 *  @param      FTM_FTMn        FTM_FTMx ģ���(FTM1,FTM2)
 *  @since      v1.0
 *  Sample usage:       int16 FTM_Count = FTM_QUAD_Get(FTM_FTM1);    //��ȡ  FTM1 ������ ��������
 */
int16 FTM_QUAD_Get(FTM_FTMn FTM_FTMx)
{
  int16 FTM_QUAD_Count=0;
  
  //����QUAD��������ֻ��FTM1��FTM2
  ASSERT((FTM_FTMx == FTM_FTM1) || (FTM_FTMx == FTM_FTM2));
  
  FTM_QUAD_Count = FTM_CNT_REG(FTMN[FTM_FTMx]);//QUAD���������ȡ������ֵ
  
  return FTM_QUAD_Count;
}

/*
 *  @brief      ���FTM���������������
 *  @param      FTM_FTMn        FTM_FTMx ģ���(FTM1,FTM2)
 *  @since      v1.0
 *  Sample usage:       FTM_QUAD_Clean(FTM_FTM1);    //���FTM���������������
 */
void FTM_QUAD_Clean(FTM_FTMn FTM_FTMx)
{
  //����QUAD��������ֻ��FTM1��FTM2
  ASSERT((FTM_FTMx == FTM_FTM1) || (FTM_FTMx == FTM_FTM2));
  
  FTM_CNT_REG(FTMN[FTM_FTMx]) = 0;//QUAD�������������ֵ����
}