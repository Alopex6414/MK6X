/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_SPI.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**SPI基址指针
*/
SPI_MemMapPtr SPIN[SPI_SPI_MAX]= 
{
  SPI0_BASE_PTR,//SPI0基址指针
  SPI1_BASE_PTR,//SPI1基址指针
  SPI2_BASE_PTR,//SPI2基址指针
};

/*
 *  @brief      SPI初始化,设置模式
 *  @param      SPI_SPIn        SPI_SPIx        SPI模块(SPI0、SPI1、SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        片选管脚编号
 *  @param      SPI_CFG         SPI_cfg         SPI主从机模式选择
 *  @param      uint32          SPI_Baud        SPI波特率
 *  @since      v1.0
 *  Sample usage:       uint32 SPI_Real_Baud = SPI_Init(SPI_SPI0,SPIn_PCS0, MASTER,10*1000*1000);              //初始化SPI,选择CS0,主机模式, 波特率为1M ,返回真实波特率到baud变量
 */
uint32 SPI_Init(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,SPI_CFG SPI_cfg,uint32 SPI_Baud)
{
  uint8 SPI_Br=0;
  uint8 SPI_Pbr=0;
  uint8 SPI_Pcssck=0;
  uint8 SPI_Cssck=0;
  uint8 SPI_Fit_Pcssck=0;
  uint8 SPI_Fit_Cssck=0;
  uint8 SPI_PreScaler[]={2,3,5,7};
  uint32 SPI_Clk=MK6X_Bus_KHz*1000/SPI_Baud;
  uint32 SPI_Scaler[]={2,4,6,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
  uint32 SPI_Tmp=0;
  uint32 SPI_Fit_Clk=0;
  uint32 SPI_Fit_Br=0;
  uint32 SPI_Fit_Pbr=0;
  uint32 SPI_Min_Diff=~0;
  uint32 SPI_Diff=0;
  
  //SPI管脚复用(选择SPI模块)
  switch(SPI_SPIx)
  {
    case SPI_SPI0:
                  SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;//SPI0时钟使能
                  PORT_Init(SPI0_SCK_PIN,ALT2);//初始化SPI_SCK
                  PORT_Init(SPI0_SOUT_PIN,ALT2);//初始化SPI_SOUT
                  PORT_Init(SPI0_SIN_PIN,ALT2);//初始化SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI0_PCS0_PIN,ALT2);//初始化CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI0_PCS1_PIN,ALT2);//初始化CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI0_PCS2_PIN,ALT2);//初始化CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI0_PCS3_PIN,ALT2);//初始化CS3
                  }
                  else if(SPI_PCSx == SPI_PCS4)
                  {
                    PORT_Init(SPI0_PCS4_PIN,ALT2);//初始化CS4
                  }
                  else if(SPI_PCSx == SPI_PCS5)
                  {
                    PORT_Init(SPI0_PCS5_PIN,ALT3);//初始化CS5
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI1:
                  SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;//SPI1时钟使能
                  PORT_Init(SPI1_SCK_PIN,ALT2);//初始化SPI_SCK
                  PORT_Init(SPI1_SOUT_PIN,ALT2);//初始化SPI_SOUT
                  PORT_Init(SPI1_SIN_PIN,ALT2);//初始化SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI1_PCS0_PIN,ALT2);//初始化CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI1_PCS1_PIN,ALT2);//初始化CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI1_PCS2_PIN,ALT2);//初始化CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI1_PCS3_PIN,ALT2);//初始化CS3
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI2:
                  SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;//SPI2时钟使能
                  PORT_Init(SPI2_SCK_PIN,ALT2);//初始化SPI_SCK
                  PORT_Init(SPI2_SOUT_PIN,ALT2);//初始化SPI_SOUT
                  PORT_Init(SPI2_SIN_PIN,ALT2);//初始化SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI2_PCS0_PIN,ALT2);//初始化CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI2_PCS1_PIN,ALT2);//初始化CS1
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
  
  //SPI寄存器配置
  SPI_MCR_REG(SPIN[SPI_SPIx]) = (0
                                 | SPI_MCR_CLR_TXF_MASK //清空 Tx FIFO 计数器
                                 | SPI_MCR_CLR_RXF_MASK //清空 Rx FIFO 计数器
                                 | SPI_MCR_HALT_MASK    //停止SPI传输
                                 );
  
  SPI_SR_REG(SPIN[SPI_SPIx]) = (0
                                | SPI_SR_EOQF_MASK      //发送队列空了,发送完毕
                                | SPI_SR_TFUF_MASK      //传输FIFO下溢标志位,SPI为从机模式,Tx FIFO为空,而外部SPI主机模式启动传输,标志位就会置1,写1清0
                                | SPI_SR_TFFF_MASK      //传输FIFO满标志位.写1或者DMA控制器发现传输FIFO满了就会清0.0表示Tx FIFO满了
                                | SPI_SR_RFOF_MASK      //接收FIFO溢出标志位.
                                | SPI_SR_RFDF_MASK      //接收FIFO损耗标志位,写1或者DMA控制器发现传输FIFO空了就会清0.0表示Rx FIFO空
                                );
  
  if(SPI_cfg == MASTER)//主机模式
  {
    SPI_MCR_REG(SPIN[SPI_SPIx]) = (0
                                   | SPI_MCR_MSTR_MASK          //使能主机模式
                                   | SPI_MCR_PCSIS(SPI_PCSx)    //片选信号高电平,禁用SPI传输
                                   );
    
    //设置传输波特率,分频因子
    for(SPI_Br=0;SPI_Br<16;SPI_Br++)
    {
      for(SPI_Pbr=0;SPI_Pbr<4;SPI_Pbr++)
      {
        SPI_Tmp = SPI_Scaler[SPI_Br] * SPI_PreScaler[SPI_Pbr];
        SPI_Diff = abs(SPI_Tmp - SPI_Clk);
        if(SPI_Min_Diff > SPI_Diff)
        {
          SPI_Min_Diff = SPI_Diff;
          SPI_Fit_Br = SPI_Br;
          SPI_Fit_Pbr = SPI_Pbr;
          
          if(SPI_Min_Diff == 0)
          {
            goto SPI_CLK_EXIT;
          }
        }
      }
    }
    
  SPI_CLK_EXIT:
    SPI_Fit_Clk = MK6X_Bus_KHz * 1000 / (SPI_Scaler[SPI_Fit_Br] * SPI_PreScaler[SPI_Fit_Pbr]);
    SPI_Clk = MK6X_Bus_KHz * 1000 / SPI_Fit_Clk / 2;
    SPI_Min_Diff = ~0;
    SPI_Fit_Cssck = 15;
    SPI_Fit_Pcssck = 3;
    
    for(SPI_Cssck=0;SPI_Cssck<15;SPI_Cssck++)
    {
      SPI_Tmp = 1 << (SPI_Cssck + 1);
      SPI_Pcssck = (SPI_Clk / SPI_Tmp - 1) / 2;
      if(SPI_Pcssck > 3)
      {
        continue;
      }
      SPI_Tmp = SPI_Tmp * (2 * SPI_Pcssck + 1);
      SPI_Diff = abs(SPI_Tmp - SPI_Clk);
      if(SPI_Min_Diff > SPI_Diff)
      {
        SPI_Min_Diff = SPI_Diff;
        SPI_Fit_Cssck = SPI_Cssck;
        SPI_Fit_Pcssck = SPI_Pcssck;
        
        if(SPI_Min_Diff == 0)
        {
          goto SPI_CSSCK_EXIT;
        }
      } 
    }
    
  SPI_CSSCK_EXIT:
    SPI_CTAR_REG(SPIN[SPI_SPIx],0) = (0
                                      | SPI_CTAR_PBR(SPI_Fit_Pbr)       //波特率预分频因
                                      | SPI_CTAR_BR(SPI_Fit_Br)         //波特率分频因子
                                      | SPI_CTAR_PDT(0)                 //传输延迟
                                      | SPI_CTAR_FMSZ(7)                //7Bit传输
                                      | SPI_CTAR_PCSSCK(SPI_Fit_Pcssck) //片选信号预分频延时
                                      | SPI_CTAR_CSSCK(SPI_Fit_Cssck)   //片选信号分频延时
                                      );
    
  }
  else//从机模式
  {
    SPI_CTAR_SLAVE_REG(SPIN[SPI_SPIx],0) = (0
                                            | SPI_CTAR_SLAVE_FMSZ(7)
                                            | SPI_CTAR_SLAVE_CPOL_MASK
                                            | SPI_CTAR_SLAVE_CPHA_MASK
                                            );
  }
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_HALT_MASK;
  
  return SPI_Fit_Clk;
}

/*
 *  @brief      SPI传输公用SPI选择其他片选
 *  @param      SPI_SPIn        SPI_SPIx        SPI模块(SPI0、SPI1、SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        片选管脚编号
 *  @since      v1.0
 *  Sample usage:           SPI_Extra_PCS_Init(SPI_SPI2,SPI_PCS1);//主机模式...
 */
void SPI_Extra_PCS_Init(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx)
{
  //SPI管脚复用(选择SPI模块)
  switch(SPI_SPIx)
  {
    case SPI_SPI0:
                  SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;//SPI0时钟使能
                  PORT_Init(SPI0_SCK_PIN,ALT2);//初始化SPI_SCK
                  PORT_Init(SPI0_SOUT_PIN,ALT2);//初始化SPI_SOUT
                  PORT_Init(SPI0_SIN_PIN,ALT2);//初始化SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI0_PCS0_PIN,ALT2);//初始化CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI0_PCS1_PIN,ALT2);//初始化CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI0_PCS2_PIN,ALT2);//初始化CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI0_PCS3_PIN,ALT2);//初始化CS3
                  }
                  else if(SPI_PCSx == SPI_PCS4)
                  {
                    PORT_Init(SPI0_PCS4_PIN,ALT2);//初始化CS4
                  }
                  else if(SPI_PCSx == SPI_PCS5)
                  {
                    PORT_Init(SPI0_PCS5_PIN,ALT3);//初始化CS5
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI1:
                  SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;//SPI1时钟使能
                  PORT_Init(SPI1_SCK_PIN,ALT2);//初始化SPI_SCK
                  PORT_Init(SPI1_SOUT_PIN,ALT2);//初始化SPI_SOUT
                  PORT_Init(SPI1_SIN_PIN,ALT2);//初始化SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI1_PCS0_PIN,ALT2);//初始化CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI1_PCS1_PIN,ALT2);//初始化CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI1_PCS2_PIN,ALT2);//初始化CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI1_PCS3_PIN,ALT2);//初始化CS3
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI2:
                  SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;//SPI2时钟使能
                  PORT_Init(SPI2_SCK_PIN,ALT2);//初始化SPI_SCK
                  PORT_Init(SPI2_SOUT_PIN,ALT2);//初始化SPI_SOUT
                  PORT_Init(SPI2_SIN_PIN,ALT2);//初始化SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI2_PCS0_PIN,ALT2);//初始化CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI2_PCS1_PIN,ALT2);//初始化CS1
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
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//片选信号高电平,禁用SPI传输
}

/*
 *  @brief      SPI发送接收函数
 *  @param      SPI_SPIn        SPI_SPIx        SPI模块(SPI0、SPI1、SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        片选管脚编号
 *  @param      uint8*          SPI_MO_Data     发送的数据缓冲区地址(不需要接收则传 NULL)
 *  @param      uint8*          SPI_MI_Data     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
 *  @param      uint32          SPI_Len         发送数据长度
 *  @since      v1.0
 *  Sample usage:           SPI_MOSI(SPI0,SPIn_PCS0,buff,buff,2);    //发送buff的内容，并接收到buff里，长度为2字节
 */
void SPI_MOSI(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_Len)
{
  uint32 i=0;
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//选中片选信号
  
  //清除传输标志位
  do
  {
    SPI_SR_REG(SPIN[SPI_SPIx]) |= (0
                                   | SPI_SR_EOQF_MASK      //发送队列空了,发送完毕
                                   | SPI_SR_TFUF_MASK      //传输FIFO下溢标志位,SPI为从机模式,Tx FIFO为空,而外部SPI主机模式启动传输,标志位就会置1,写1清0
                                   | SPI_SR_TFFF_MASK      //传输FIFO满标志位.写1或者DMA控制器发现传输FIFO满了就会清0.0表示Tx FIFO满了
                                   | SPI_SR_RFOF_MASK      //接收FIFO溢出标志位.
                                   | SPI_SR_RFDF_MASK      //接收FIFO损耗标志位,写1或者DMA控制器发现传输FIFO空了就会清0.0表示Rx FIFO空
                                   );
    
    SPI_MCR_REG(SPIN[SPI_SPIx]) |= (0
                                    | SPI_MCR_CLR_TXF_MASK //清空 Tx FIFO 计数器
                                    | SPI_MCR_CLR_RXF_MASK //清空 Rx FIFO 计数器
                                    );
  }while(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK);
  
  if(SPI_MO_Data != NULL)//发送数据不为NULL
  {
    if(SPI_MI_Data != NULL)//接受数据不为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//接受数据为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  else//发送数据为NULL
  {
    if(SPI_MI_Data != NULL)//接受数据不为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//接受数据为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_PCSIS(SPI_PCSx);//释放片选信号
}

/*
 *  @brief      SPI发送接收函数(带发送命令CMD)
 *  @param      SPI_SPIn        SPI_SPIx        SPI模块(SPI0、SPI1、SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        片选管脚编号
 *  @param      uint8*          SPI_MO_CMD      发送的命令缓冲区地址(不需要接收则传 NULL)
 *  @param      uint8*          SPI_MI_CMD      发送命令时接收到的数据的存储地址(不需要接收则传 NULL)
 *  @param      uint8*          SPI_MO_Data     发送的数据缓冲区地址(不需要接收则传 NULL)
 *  @param      uint8*          SPI_MI_Data     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
 *  @param      uint32          SPI_CMD_Len     发送命令长度
 *  @param      uint32          SPI_Len         发送数据长度
 *  @since      v1.0
 *  Sample usage:           SPI_MOSI_CMD(SPI0,SPIn_PCS0,cmd,NULL,buff,buff,1,2);    //发送cmd/buff的内容，不接收cmd发送时的数据，接收buff发送时的数据到buff里，长度分别为1、2字节
 */
void SPI_MOSI_CMD(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,uint8 *SPI_MO_CMD,uint8 *SPI_MI_CMD,uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_CMD_Len,uint32 SPI_Len)
{
  uint32 i=0;
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//选中片选信号
  
  do
  {
    SPI_SR_REG(SPIN[SPI_SPIx]) |= (0
                                   | SPI_SR_EOQF_MASK      //发送队列空了,发送完毕
                                   | SPI_SR_TFUF_MASK      //传输FIFO下溢标志位,SPI为从机模式,Tx FIFO为空,而外部SPI主机模式启动传输,标志位就会置1,写1清0
                                   | SPI_SR_TFFF_MASK      //传输FIFO满标志位.写1或者DMA控制器发现传输FIFO满了就会清0.0表示Tx FIFO满了
                                   | SPI_SR_RFOF_MASK      //接收FIFO溢出标志位.
                                   | SPI_SR_RFDF_MASK      //接收FIFO损耗标志位,写1或者DMA控制器发现传输FIFO空了就会清0.0表示Rx FIFO空
                                   );
    SPI_MCR_REG(SPIN[SPI_SPIx]) |= (0
                                    | SPI_MCR_CLR_TXF_MASK //清空 Tx FIFO 计数器
                                    | SPI_MCR_CLR_RXF_MASK //清空 Rx FIFO 计数器
                                    );
  }while(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK);
  
  if(SPI_MO_CMD != NULL)//发送命令不为NULL
  {
    if(SPI_MI_CMD != NULL)//接受命令不为NULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_CMD[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_CMD[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
    else//接受命令为NULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_CMD[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
  }
  else//发送命令为NULL
  {
    if(SPI_MI_CMD != NULL)//接受命令不为NULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_CMD[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
    else//接受命令为NULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
  }
  
  if(SPI_MO_Data != NULL)//发送数据不为NULL
  {
    if(SPI_MI_Data != NULL)//接受数据不为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//接受数据为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  else//发送数据为NULL
  {
    if(SPI_MI_Data != NULL)//接受数据不为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//接受数据为NULL
    {
      //发送前N-1个数据
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                         | SPI_PUSHR_CONT_MASK      //传输期间保持PCSn信号
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //发送最后一个数据
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //选择CTAR0寄存器
                                       | SPI_PUSHR_EOQ_MASK       //传输SPI最后的数据
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_PCSIS(SPI_PCSx);//释放片选信号
}

/*
 *  @brief      SPI发送8Bit数据
 *  @param      SPI_SPIn        SPI_SPIx        SPI模块(SPI0、SPI1、SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        片选管脚编号
 *  @param      uint8           Data            8Bit数据
 *  @since      v1.0
 *  Sample usage:           SPI_Send(SPI_SPI2,SPI_PCS1,0x00);
 */
void SPI_Send(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,uint8 Data)
{
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//选中片选信号
  
  do
  {
    SPI_SR_REG(SPIN[SPI_SPIx]) |= (0
                                   | SPI_SR_EOQF_MASK      //发送队列空了,发送完毕
                                   | SPI_SR_TFUF_MASK      //传输FIFO下溢标志位,SPI为从机模式,Tx FIFO为空,而外部SPI主机模式启动传输,标志位就会置1,写1清0
                                   | SPI_SR_TFFF_MASK      //传输FIFO满标志位.写1或者DMA控制器发现传输FIFO满了就会清0.0表示Tx FIFO满了
                                   | SPI_SR_RFOF_MASK      //接收FIFO溢出标志位.
                                   | SPI_SR_RFDF_MASK      //接收FIFO损耗标志位,写1或者DMA控制器发现传输FIFO空了就会清0.0表示Rx FIFO空
                                   );
    SPI_MCR_REG(SPIN[SPI_SPIx]) |= (0
                                    | SPI_MCR_CLR_TXF_MASK //清空 Tx FIFO 计数器
                                    | SPI_MCR_CLR_RXF_MASK //清空 Rx FIFO 计数器
                                    );
  }while(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK);
  
  SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                   | SPI_PUSHR_CTAS(0)          //选择CTAR0寄存器
                                   | SPI_PUSHR_EOQ_MASK         //传输SPI最后的数据
                                   | SPI_PUSHR_PCS(SPI_PCSx)    //使能片选CS信号,SPI启用
                                   | SPI_PUSHR_TXDATA(Data)     //发送8Bit数据
                                   );
  
  while((SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_TCF_MASK) != SPI_SR_TCF_MASK);//等待SPI传输完成
  
  SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_TCF_MASK;//清除TCF传输完成标志
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_PCSIS(SPI_PCSx);//释放片选信号
}