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
**SPI��ַָ��
*/
SPI_MemMapPtr SPIN[SPI_SPI_MAX]= 
{
  SPI0_BASE_PTR,//SPI0��ַָ��
  SPI1_BASE_PTR,//SPI1��ַָ��
  SPI2_BASE_PTR,//SPI2��ַָ��
};

/*
 *  @brief      SPI��ʼ��,����ģʽ
 *  @param      SPI_SPIn        SPI_SPIx        SPIģ��(SPI0��SPI1��SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        Ƭѡ�ܽű��
 *  @param      SPI_CFG         SPI_cfg         SPI���ӻ�ģʽѡ��
 *  @param      uint32          SPI_Baud        SPI������
 *  @since      v1.0
 *  Sample usage:       uint32 SPI_Real_Baud = SPI_Init(SPI_SPI0,SPIn_PCS0, MASTER,10*1000*1000);              //��ʼ��SPI,ѡ��CS0,����ģʽ, ������Ϊ1M ,������ʵ�����ʵ�baud����
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
  
  //SPI�ܽŸ���(ѡ��SPIģ��)
  switch(SPI_SPIx)
  {
    case SPI_SPI0:
                  SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;//SPI0ʱ��ʹ��
                  PORT_Init(SPI0_SCK_PIN,ALT2);//��ʼ��SPI_SCK
                  PORT_Init(SPI0_SOUT_PIN,ALT2);//��ʼ��SPI_SOUT
                  PORT_Init(SPI0_SIN_PIN,ALT2);//��ʼ��SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI0_PCS0_PIN,ALT2);//��ʼ��CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI0_PCS1_PIN,ALT2);//��ʼ��CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI0_PCS2_PIN,ALT2);//��ʼ��CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI0_PCS3_PIN,ALT2);//��ʼ��CS3
                  }
                  else if(SPI_PCSx == SPI_PCS4)
                  {
                    PORT_Init(SPI0_PCS4_PIN,ALT2);//��ʼ��CS4
                  }
                  else if(SPI_PCSx == SPI_PCS5)
                  {
                    PORT_Init(SPI0_PCS5_PIN,ALT3);//��ʼ��CS5
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI1:
                  SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;//SPI1ʱ��ʹ��
                  PORT_Init(SPI1_SCK_PIN,ALT2);//��ʼ��SPI_SCK
                  PORT_Init(SPI1_SOUT_PIN,ALT2);//��ʼ��SPI_SOUT
                  PORT_Init(SPI1_SIN_PIN,ALT2);//��ʼ��SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI1_PCS0_PIN,ALT2);//��ʼ��CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI1_PCS1_PIN,ALT2);//��ʼ��CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI1_PCS2_PIN,ALT2);//��ʼ��CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI1_PCS3_PIN,ALT2);//��ʼ��CS3
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI2:
                  SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;//SPI2ʱ��ʹ��
                  PORT_Init(SPI2_SCK_PIN,ALT2);//��ʼ��SPI_SCK
                  PORT_Init(SPI2_SOUT_PIN,ALT2);//��ʼ��SPI_SOUT
                  PORT_Init(SPI2_SIN_PIN,ALT2);//��ʼ��SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI2_PCS0_PIN,ALT2);//��ʼ��CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI2_PCS1_PIN,ALT2);//��ʼ��CS1
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
  
  //SPI�Ĵ�������
  SPI_MCR_REG(SPIN[SPI_SPIx]) = (0
                                 | SPI_MCR_CLR_TXF_MASK //��� Tx FIFO ������
                                 | SPI_MCR_CLR_RXF_MASK //��� Rx FIFO ������
                                 | SPI_MCR_HALT_MASK    //ֹͣSPI����
                                 );
  
  SPI_SR_REG(SPIN[SPI_SPIx]) = (0
                                | SPI_SR_EOQF_MASK      //���Ͷ��п���,�������
                                | SPI_SR_TFUF_MASK      //����FIFO�����־λ,SPIΪ�ӻ�ģʽ,Tx FIFOΪ��,���ⲿSPI����ģʽ��������,��־λ�ͻ���1,д1��0
                                | SPI_SR_TFFF_MASK      //����FIFO����־λ.д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾTx FIFO����
                                | SPI_SR_RFOF_MASK      //����FIFO�����־λ.
                                | SPI_SR_RFDF_MASK      //����FIFO��ı�־λ,д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾRx FIFO��
                                );
  
  if(SPI_cfg == MASTER)//����ģʽ
  {
    SPI_MCR_REG(SPIN[SPI_SPIx]) = (0
                                   | SPI_MCR_MSTR_MASK          //ʹ������ģʽ
                                   | SPI_MCR_PCSIS(SPI_PCSx)    //Ƭѡ�źŸߵ�ƽ,����SPI����
                                   );
    
    //���ô��䲨����,��Ƶ����
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
                                      | SPI_CTAR_PBR(SPI_Fit_Pbr)       //������Ԥ��Ƶ��
                                      | SPI_CTAR_BR(SPI_Fit_Br)         //�����ʷ�Ƶ����
                                      | SPI_CTAR_PDT(0)                 //�����ӳ�
                                      | SPI_CTAR_FMSZ(7)                //7Bit����
                                      | SPI_CTAR_PCSSCK(SPI_Fit_Pcssck) //Ƭѡ�ź�Ԥ��Ƶ��ʱ
                                      | SPI_CTAR_CSSCK(SPI_Fit_Cssck)   //Ƭѡ�źŷ�Ƶ��ʱ
                                      );
    
  }
  else//�ӻ�ģʽ
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
 *  @brief      SPI���乫��SPIѡ������Ƭѡ
 *  @param      SPI_SPIn        SPI_SPIx        SPIģ��(SPI0��SPI1��SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        Ƭѡ�ܽű��
 *  @since      v1.0
 *  Sample usage:           SPI_Extra_PCS_Init(SPI_SPI2,SPI_PCS1);//����ģʽ...
 */
void SPI_Extra_PCS_Init(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx)
{
  //SPI�ܽŸ���(ѡ��SPIģ��)
  switch(SPI_SPIx)
  {
    case SPI_SPI0:
                  SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;//SPI0ʱ��ʹ��
                  PORT_Init(SPI0_SCK_PIN,ALT2);//��ʼ��SPI_SCK
                  PORT_Init(SPI0_SOUT_PIN,ALT2);//��ʼ��SPI_SOUT
                  PORT_Init(SPI0_SIN_PIN,ALT2);//��ʼ��SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI0_PCS0_PIN,ALT2);//��ʼ��CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI0_PCS1_PIN,ALT2);//��ʼ��CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI0_PCS2_PIN,ALT2);//��ʼ��CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI0_PCS3_PIN,ALT2);//��ʼ��CS3
                  }
                  else if(SPI_PCSx == SPI_PCS4)
                  {
                    PORT_Init(SPI0_PCS4_PIN,ALT2);//��ʼ��CS4
                  }
                  else if(SPI_PCSx == SPI_PCS5)
                  {
                    PORT_Init(SPI0_PCS5_PIN,ALT3);//��ʼ��CS5
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI1:
                  SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;//SPI1ʱ��ʹ��
                  PORT_Init(SPI1_SCK_PIN,ALT2);//��ʼ��SPI_SCK
                  PORT_Init(SPI1_SOUT_PIN,ALT2);//��ʼ��SPI_SOUT
                  PORT_Init(SPI1_SIN_PIN,ALT2);//��ʼ��SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI1_PCS0_PIN,ALT2);//��ʼ��CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI1_PCS1_PIN,ALT2);//��ʼ��CS1
                  }
                  else if(SPI_PCSx == SPI_PCS2)
                  {
                    PORT_Init(SPI1_PCS2_PIN,ALT2);//��ʼ��CS2
                  }
                  else if(SPI_PCSx == SPI_PCS3)
                  {
                    PORT_Init(SPI1_PCS3_PIN,ALT2);//��ʼ��CS3
                  }
                  else
                  {
                    ASSERT(0);
                  }
                  break;
    case SPI_SPI2:
                  SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;//SPI2ʱ��ʹ��
                  PORT_Init(SPI2_SCK_PIN,ALT2);//��ʼ��SPI_SCK
                  PORT_Init(SPI2_SOUT_PIN,ALT2);//��ʼ��SPI_SOUT
                  PORT_Init(SPI2_SIN_PIN,ALT2);//��ʼ��SPI_SIN
                  if(SPI_PCSx == SPI_PCS0)
                  {
                    PORT_Init(SPI2_PCS0_PIN,ALT2);//��ʼ��CS0
                  }
                  else if(SPI_PCSx == SPI_PCS1)
                  {
                    PORT_Init(SPI2_PCS1_PIN,ALT2);//��ʼ��CS1
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
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//Ƭѡ�źŸߵ�ƽ,����SPI����
}

/*
 *  @brief      SPI���ͽ��պ���
 *  @param      SPI_SPIn        SPI_SPIx        SPIģ��(SPI0��SPI1��SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        Ƭѡ�ܽű��
 *  @param      uint8*          SPI_MO_Data     ���͵����ݻ�������ַ(����Ҫ������ NULL)
 *  @param      uint8*          SPI_MI_Data     ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
 *  @param      uint32          SPI_Len         �������ݳ���
 *  @since      v1.0
 *  Sample usage:           SPI_MOSI(SPI0,SPIn_PCS0,buff,buff,2);    //����buff�����ݣ������յ�buff�����Ϊ2�ֽ�
 */
void SPI_MOSI(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_Len)
{
  uint32 i=0;
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//ѡ��Ƭѡ�ź�
  
  //��������־λ
  do
  {
    SPI_SR_REG(SPIN[SPI_SPIx]) |= (0
                                   | SPI_SR_EOQF_MASK      //���Ͷ��п���,�������
                                   | SPI_SR_TFUF_MASK      //����FIFO�����־λ,SPIΪ�ӻ�ģʽ,Tx FIFOΪ��,���ⲿSPI����ģʽ��������,��־λ�ͻ���1,д1��0
                                   | SPI_SR_TFFF_MASK      //����FIFO����־λ.д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾTx FIFO����
                                   | SPI_SR_RFOF_MASK      //����FIFO�����־λ.
                                   | SPI_SR_RFDF_MASK      //����FIFO��ı�־λ,д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾRx FIFO��
                                   );
    
    SPI_MCR_REG(SPIN[SPI_SPIx]) |= (0
                                    | SPI_MCR_CLR_TXF_MASK //��� Tx FIFO ������
                                    | SPI_MCR_CLR_RXF_MASK //��� Rx FIFO ������
                                    );
  }while(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK);
  
  if(SPI_MO_Data != NULL)//�������ݲ�ΪNULL
  {
    if(SPI_MI_Data != NULL)//�������ݲ�ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//��������ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  else//��������ΪNULL
  {
    if(SPI_MI_Data != NULL)//�������ݲ�ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//��������ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_PCSIS(SPI_PCSx);//�ͷ�Ƭѡ�ź�
}

/*
 *  @brief      SPI���ͽ��պ���(����������CMD)
 *  @param      SPI_SPIn        SPI_SPIx        SPIģ��(SPI0��SPI1��SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        Ƭѡ�ܽű��
 *  @param      uint8*          SPI_MO_CMD      ���͵����������ַ(����Ҫ������ NULL)
 *  @param      uint8*          SPI_MI_CMD      ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
 *  @param      uint8*          SPI_MO_Data     ���͵����ݻ�������ַ(����Ҫ������ NULL)
 *  @param      uint8*          SPI_MI_Data     ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
 *  @param      uint32          SPI_CMD_Len     ���������
 *  @param      uint32          SPI_Len         �������ݳ���
 *  @since      v1.0
 *  Sample usage:           SPI_MOSI_CMD(SPI0,SPIn_PCS0,cmd,NULL,buff,buff,1,2);    //����cmd/buff�����ݣ�������cmd����ʱ�����ݣ�����buff����ʱ�����ݵ�buff����ȷֱ�Ϊ1��2�ֽ�
 */
void SPI_MOSI_CMD(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,uint8 *SPI_MO_CMD,uint8 *SPI_MI_CMD,uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_CMD_Len,uint32 SPI_Len)
{
  uint32 i=0;
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//ѡ��Ƭѡ�ź�
  
  do
  {
    SPI_SR_REG(SPIN[SPI_SPIx]) |= (0
                                   | SPI_SR_EOQF_MASK      //���Ͷ��п���,�������
                                   | SPI_SR_TFUF_MASK      //����FIFO�����־λ,SPIΪ�ӻ�ģʽ,Tx FIFOΪ��,���ⲿSPI����ģʽ��������,��־λ�ͻ���1,д1��0
                                   | SPI_SR_TFFF_MASK      //����FIFO����־λ.д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾTx FIFO����
                                   | SPI_SR_RFOF_MASK      //����FIFO�����־λ.
                                   | SPI_SR_RFDF_MASK      //����FIFO��ı�־λ,д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾRx FIFO��
                                   );
    SPI_MCR_REG(SPIN[SPI_SPIx]) |= (0
                                    | SPI_MCR_CLR_TXF_MASK //��� Tx FIFO ������
                                    | SPI_MCR_CLR_RXF_MASK //��� Rx FIFO ������
                                    );
  }while(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK);
  
  if(SPI_MO_CMD != NULL)//�������ΪNULL
  {
    if(SPI_MI_CMD != NULL)//�������ΪNULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_CMD[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_CMD[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
    else//��������ΪNULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_CMD[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
  }
  else//��������ΪNULL
  {
    if(SPI_MI_CMD != NULL)//�������ΪNULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_CMD[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
    else//��������ΪNULL
    {
      for(i=0;i<SPI_CMD_Len;i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
    }
  }
  
  if(SPI_MO_Data != NULL)//�������ݲ�ΪNULL
  {
    if(SPI_MI_Data != NULL)//�������ݲ�ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//��������ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(SPI_MO_Data[i])
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  else//��������ΪNULL
  {
    if(SPI_MI_Data != NULL)//�������ݲ�ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_MI_Data[i] = (uint8)SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
    else//��������ΪNULL
    {
      //����ǰN-1������
      for(i=0;i<(SPI_Len-1);i++)
      {
        SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                         | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                         | SPI_PUSHR_CONT_MASK      //�����ڼ䱣��PCSn�ź�
                                         | SPI_PUSHR_PCS(SPI_PCSx)
                                         | SPI_PUSHR_TXDATA(NULL)
                                         );
        while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
        
        SPI_POPR_REG(SPIN[SPI_SPIx]);
        
        SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
      }
      
      //�������һ������
      SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                       | SPI_PUSHR_CTAS(0)        //ѡ��CTAR0�Ĵ���
                                       | SPI_PUSHR_EOQ_MASK       //����SPI��������
                                       | SPI_PUSHR_PCS(SPI_PCSx)
                                       | SPI_PUSHR_TXDATA(NULL)
                                       );
      SPI_EOQF_WAIT(SPI_SPIx);
      
      while(!(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK));
      
      SPI_POPR_REG(SPIN[SPI_SPIx]);
        
      SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_RFDF_MASK;
    }
  }
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_PCSIS(SPI_PCSx);//�ͷ�Ƭѡ�ź�
}

/*
 *  @brief      SPI����8Bit����
 *  @param      SPI_SPIn        SPI_SPIx        SPIģ��(SPI0��SPI1��SPI2)
 *  @param      SPI_PCSn        SPI_PCSx        Ƭѡ�ܽű��
 *  @param      uint8           Data            8Bit����
 *  @since      v1.0
 *  Sample usage:           SPI_Send(SPI_SPI2,SPI_PCS1,0x00);
 */
void SPI_Send(SPI_SPIn SPI_SPIx,SPI_PCSn SPI_PCSx,uint8 Data)
{
  SPI_MCR_REG(SPIN[SPI_SPIx]) |= SPI_MCR_PCSIS(SPI_PCSx);//ѡ��Ƭѡ�ź�
  
  do
  {
    SPI_SR_REG(SPIN[SPI_SPIx]) |= (0
                                   | SPI_SR_EOQF_MASK      //���Ͷ��п���,�������
                                   | SPI_SR_TFUF_MASK      //����FIFO�����־λ,SPIΪ�ӻ�ģʽ,Tx FIFOΪ��,���ⲿSPI����ģʽ��������,��־λ�ͻ���1,д1��0
                                   | SPI_SR_TFFF_MASK      //����FIFO����־λ.д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾTx FIFO����
                                   | SPI_SR_RFOF_MASK      //����FIFO�����־λ.
                                   | SPI_SR_RFDF_MASK      //����FIFO��ı�־λ,д1����DMA���������ִ���FIFO���˾ͻ���0.0��ʾRx FIFO��
                                   );
    SPI_MCR_REG(SPIN[SPI_SPIx]) |= (0
                                    | SPI_MCR_CLR_TXF_MASK //��� Tx FIFO ������
                                    | SPI_MCR_CLR_RXF_MASK //��� Rx FIFO ������
                                    );
  }while(SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_RFDF_MASK);
  
  SPI_PUSHR_REG(SPIN[SPI_SPIx]) = (0
                                   | SPI_PUSHR_CTAS(0)          //ѡ��CTAR0�Ĵ���
                                   | SPI_PUSHR_EOQ_MASK         //����SPI��������
                                   | SPI_PUSHR_PCS(SPI_PCSx)    //ʹ��ƬѡCS�ź�,SPI����
                                   | SPI_PUSHR_TXDATA(Data)     //����8Bit����
                                   );
  
  while((SPI_SR_REG(SPIN[SPI_SPIx]) & SPI_SR_TCF_MASK) != SPI_SR_TCF_MASK);//�ȴ�SPI�������
  
  SPI_SR_REG(SPIN[SPI_SPIx]) |= SPI_SR_TCF_MASK;//���TCF������ɱ�־
  
  SPI_MCR_REG(SPIN[SPI_SPIx]) &= ~SPI_MCR_PCSIS(SPI_PCSx);//�ͷ�Ƭѡ�ź�
}