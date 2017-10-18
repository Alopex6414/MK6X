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
 *  @brief      USBģ�� ��ʼ��
 *  @since      v1.0
 */
void USB_Init(void)
{
  //������� 
  Setup_Pkt = (tUSB_Setup *)BufferPointer[bEP0OUT_ODD];
  gu8USB_State = uPOWER;//���Ϊ�ϵ�״̬
  
  //MPU����
  MPU_CESR = 0;
  
  //SIM����
  #ifdef USB_CLOCK_CLKIN
  FLAG_SET(SIM_SCGC5_PORTE_SHIFT, SIM_SCGC5);
  PORTE_PCR26 = (0 | PORT_PCR_MUX(7));//ʹ��PTE26��ΪCLK����
  #endif
  
  //CLK����
  #ifdef USB_CLOCK_PLL
  SIM_SOPT2 |= (0 | SIM_SOPT2_PLLFLLSEL(1));//ѡ��PLL�ο�ʱ��
  #endif
  
  #ifndef USB_CLOCK_CLKIN
  SIM_SOPT2 |= (0 | SIM_SOPT2_USBSRC_MASK);//USBѡ��MCGPLL�ο�ʱ������
  #endif
  
  SIM_CLKDIV2 = ((SIM_CLKDIV2 & ~(SIM_CLKDIV2_USBDIV_MASK | SIM_CLKDIV2_USBFRAC_MASK))//���SIM_CLKDIV2�Ĵ���
                  | SIM_CLKDIV2_USBDIV(USB_CLK_DIV)                    //USB ��Ƶ����
                  | (USB_CLK_FRAC << SIM_CLKDIV2_USBFRAC_SHIFT)        //USB ��Ƶ����
                   //USB clk = PLL �� [ (USBFRAC+1) / (USBDIV+1) ](80MHz)
                );
  
  SIM_SCGC4 |= SIM_SCGC4_USBOTG_MASK;//USBģ��ʱ��ʹ��
 
  //�����ж�����,ʹ��NVIC��USB OTG�ж�����
  Set_Vector_Handler(USB0_VECTORn,USB_ISR);
  enable_irq(USB0_IRQn);
  
  //USBģ������
  USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;      //��λUSBģ��
  while(FLAG_CHK(USB_USBTRC0_USBRESET_SHIFT, USB0_USBTRC0));
  
  //USB����BDT��ַ�Ĵ���
  USB0_BDTPAGE1 = (uint8)((uint32)tBDTtable >> 8); //���õ�ǰ������������BDT
  USB0_BDTPAGE2 = (uint8)((uint32)tBDTtable >> 16);
  USB0_BDTPAGE3 = (uint8)((uint32)tBDTtable >> 24);
  
  //��USB��λ���
  FLAG_SET(USB_ISTAT_USBRST_MASK, USB0_ISTAT);
  
  //ʹ��USB��λ�ж�
  FLAG_SET(USB_INTEN_USBRSTEN_SHIFT, USB0_INTEN);
  
  //ʹ��USB��������
  USB0_USBCTRL = 0x40;
  USB0_USBTRC0 |= 0x40;
  USB0_CTL |= 0x01;
  FLAG_SET(USB_CONTROL_DPPULLUPNONOTG_SHIFT, USB0_CONTROL);
  
}

/*
 *  @brief      USB ���⴮�� ��ʼ��
 *  @since      v1.0
 */
void USB_COM_Init(void)
{
  USB_Init();//USB��ʼ��
  CDC_Init();//CDC��ʼ��
}

/*
 *  @brief      USB �ȴ�ö��
 *  @since      v1.0
 */
void USB_Enum_Wait(void)
{
  while(gu8USB_State != uENUMERATED);//�ȴ�USB�豸��ö��
}

/*
 *  @brief      USB ���⴮�� ����
 *  @param      uint8_t         *Rx_Buf         ���ݽ��ջ�����
 *  @return     ���յ��ĳ���
 *  @since      v1.0
 */
uint8 USB_COM_Rx(uint8_t *Rx_Buf)
{
  uint8 Len = 0;
  uint8 Temp = 0;
  uint8 *pu8EPBuffer;
  
  //����н��ܵ�����
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
 *  @brief      USB ���⴮�� ����
 *  @param      uint8   *Tx_Buf         ���ݷ��ͻ�����
 *  @param      uint8   Len             ��Ҫ���͵����ݳ���
 *  @since      v1.0
 */
void USB_COM_Tx(uint8 *Tx_Buf,uint8 Len)
{
  EP_IN_Transfer(EP_IN, Tx_Buf, Len);
}
