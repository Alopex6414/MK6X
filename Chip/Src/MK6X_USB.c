/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_USB.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      USB模块 初始化
 *  @since      v1.0
 */
void USB_Init(void)
{
  //软件设置 
  Setup_Pkt = (tUSB_Setup *)BufferPointer[bEP0OUT_ODD];
  gu8USB_State = uPOWER;//标记为上电状态
  
  //MPU配置
  MPU_CESR = 0;
  
  //SIM配置
  #ifdef USB_CLOCK_CLKIN
  FLAG_SET(SIM_SCGC5_PORTE_SHIFT, SIM_SCGC5);
  PORTE_PCR26 = (0 | PORT_PCR_MUX(7));//使能PTE26作为CLK输入
  #endif
  
  //CLK设置
  #ifdef USB_CLOCK_PLL
  SIM_SOPT2 |= (0 | SIM_SOPT2_PLLFLLSEL(1));//选择PLL参考时钟
  #endif
  
  #ifndef USB_CLOCK_CLKIN
  SIM_SOPT2 |= (0 | SIM_SOPT2_USBSRC_MASK);//USB选择MCGPLL参考时钟输入
  #endif
  
  SIM_CLKDIV2 = ((SIM_CLKDIV2 & ~(SIM_CLKDIV2_USBDIV_MASK | SIM_CLKDIV2_USBFRAC_MASK))//清空SIM_CLKDIV2寄存器
                  | SIM_CLKDIV2_USBDIV(USB_CLK_DIV)                    //USB 分频因子
                  | (USB_CLK_FRAC << SIM_CLKDIV2_USBFRAC_SHIFT)        //USB 倍频因子
                   //USB clk = PLL × [ (USBFRAC+1) / (USBDIV+1) ](80MHz)
                );
  
  SIM_SCGC4 |= SIM_SCGC4_USBOTG_MASK;//USB模块时钟使能
 
  //设置中断向量,使能NVIC中USB OTG中断向量
  Set_Vector_Handler(USB0_VECTORn,USB_ISR);
  enable_irq(USB0_IRQn);
  
  //USB模块配置
  USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;      //复位USB模块
  while(FLAG_CHK(USB_USBTRC0_USBRESET_SHIFT, USB0_USBTRC0));
  
  //USB设置BDT基址寄存器
  USB0_BDTPAGE1 = (uint8)((uint32)tBDTtable >> 8); //配置当前缓冲描述符表BDT
  USB0_BDTPAGE2 = (uint8)((uint32)tBDTtable >> 16);
  USB0_BDTPAGE3 = (uint8)((uint32)tBDTtable >> 24);
  
  //清USB复位标记
  FLAG_SET(USB_ISTAT_USBRST_MASK, USB0_ISTAT);
  
  //使能USB复位中断
  FLAG_SET(USB_INTEN_USBRSTEN_SHIFT, USB0_INTEN);
  
  //使能USB唤醒上拉
  USB0_USBCTRL = 0x40;
  USB0_USBTRC0 |= 0x40;
  USB0_CTL |= 0x01;
  FLAG_SET(USB_CONTROL_DPPULLUPNONOTG_SHIFT, USB0_CONTROL);
  
}

/*
 *  @brief      USB 虚拟串口 初始化
 *  @since      v1.0
 */
void USB_COM_Init(void)
{
  USB_Init();//USB初始化
  CDC_Init();//CDC初始化
}

/*
 *  @brief      USB 等待枚举
 *  @since      v1.0
 */
void USB_Enum_Wait(void)
{
  while(gu8USB_State != uENUMERATED);//等待USB设备被枚举
}

/*
 *  @brief      USB 虚拟串口 接收
 *  @param      uint8_t         *Rx_Buf         数据接收缓冲区
 *  @return     接收到的长度
 *  @since      v1.0
 */
uint8 USB_COM_Rx(uint8_t *Rx_Buf)
{
  uint8 Len = 0;
  uint8 Temp = 0;
  uint8 *pu8EPBuffer;
  
  //如果有接受到数据
  if(FLAG_CHK(EP_OUT, gu8USB_Flags))
  {
    Len = USB_EP_OUT_SizeCheck(EP_OUT);
    Temp = Len;
    pu8EPBuffer = gu8EP3_OUT_ODD_Buffer;
    
    while(Len--)
    {
      *Rx_Buf++ = *pu8EPBuffer++;
    }
    
    usbEP_Reset(EP_OUT);
    usbSIE_CONTROL(EP_OUT);
    FLAG_CLR(EP_OUT, gu8USB_Flags);
    
  }
  
  return Temp;
}

/*
 *  @brief      USB 虚拟串口 发送
 *  @param      uint8   *Tx_Buf         数据发送缓冲区
 *  @param      uint8   Len             需要发送的数据长度
 *  @since      v1.0
 */
void USB_COM_Tx(uint8 *Tx_Buf,uint8 Len)
{
  EP_IN_Transfer(EP_IN, Tx_Buf, Len);
}
