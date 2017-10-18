/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DMA.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**DMAͨ��������ʼ������ֵ
*/
uint32 DMA_Count_Array[32]={0};

/*
 *  @brief      DMA GPIO�����ʼ��
 *  @param      void    *SADDR  PTXģ���ַ
 *  @param      uint8   BYTEs   8Bit����
 *  @since      v1.0
 *  Sample usage:       DMA_GPIO_Input_Init()
 */
static void DMA_GPIO_Input_Init(void *SADDR,uint8 BYTEs)
{
  uint8 n;
  uint8 tmp;
  uint8 ptxn;
  uint8 ptx0=((((uint32)SADDR) & 0x1C0) / 0x40 ) * 32;//ת��ΪPTA0,PTB0,PTC0,PTD0,PTE0
  
  n = (((uint32)SADDR - ((uint32)(&(((Dtype*)(&(PTA_BASE_PTR->PDIR)))->B[0])))) & 0x3f) * 8;//��С�ܽź�
  ptxn = ptx0 + n;
  tmp = ptxn + (BYTEs * 8) - 1;//���ܽź�
  
  while(ptxn <= tmp)
  {
    GPIO_Init((PTXn)ptxn,GPI,0);
    PORT_Init((PTXn)ptxn,ALT1 | PULLDOWN);
    ptxn++;
  }
  
}

/*
 *  @brief      DMA��ʼ������IO������������˿ڵ����ݵ��ڴ�
 *  @param      DMA_CHn         ͨ����(DMA_CH0~DMA_CH31)
 *  @param      SADDR           Դ��ַ( (void * )&PTx_Bn_IN �� (void * )&PTx_Wn_IN �� (void * )&PTx_IN  )
 *  @param      DADDR           Ŀ�ĵ�ַ
 *  @param      PTxn            �����˿�
 *  @param      DMA_BYTEn       ÿ��DMA�����ֽ���
 *  @param      count           һ����ѭ�������ֽ���
 *  @param      cfg             DMA�������ã���DMA_cfg��ѡ��
 *  @since      v5.0
 *  @note       DMA PTXn����ԴĬ�������ش������䣬�����޸ģ����ʼ������� port_init ����DMA ������ʽ
                ��ʼ������Ҫ���� DMA_EN ��ʵ��
 *  Sample usage:   uint8 buff[10];
                    DMA_PORTX_To_Buff_Init(DMA_CH0, PTB_B0_IN, buff, PTA7, DMA_BYTE1, 10, DADDR_RECOVER);
                    //DMA��ʼ����Դ��ַ��PTB_B0_IN��Ŀ�ĵ�ַ��buff,PTA7����(Ĭ��������)��ÿ�δ���1�ֽڣ������� 10�� �����������ָ���ַ

                    port_init(PTA7,ALT1 | DMA_FALLING);             //Ĭ�ϴ���Դ�������أ��˴���Ϊ �½��ش���

                    DMA_EN(DMA_CH0);                //��Ҫʹ�� DMA ����ܴ�������
 */
void DMA_PORTX_To_Buff_Init(DMA_CHn DMA_CHx,void *SADDR,void *DADDR,PTXn PTXx,DMA_BYTEn DMA_BYTEx,uint32 Count,DMA_CFG CFG)
{
  uint8 BYTEs=0;
  
  //DMA�����ֽ���
  if(DMA_BYTEx == DMA_BYTE1)
  {
    BYTEs = 1;
  }
  else if(DMA_BYTEx == DMA_BYTE2)
  {
    BYTEs = 2;
  }
  else if(DMA_BYTEx == DMA_BYTE4)
  {
    BYTEs = 4;
  }
  else
  {
    BYTEs = 16;
  }
  
  ASSERT(((DMA_BYTEx == DMA_BYTE1) && (SADDR >= &(((Dtype*)(&(PTA_BASE_PTR->PDIR)))->B[0]) && SADDR <= &(((Dtype*)(&(PTE_BASE_PTR->PDIR)))->B[3])))
         ||((DMA_BYTEx == DMA_BYTE2) && (SADDR >= &(((Dtype*)(&(PTA_BASE_PTR->PDIR)))->B[0]) && SADDR <= &(((Dtype*)(&(PTE_BASE_PTR->PDIR)))->W[1])) && (((uint32)SADDR & 0x03) != 0x03))
           ||((DMA_BYTEx == DMA_BYTE4) && (SADDR >= &(((Dtype*)(&(PTA_BASE_PTR->PDIR)))->B[0]) && SADDR <= &(((Dtype*)(&(PTE_BASE_PTR->PDIR)))->B[0])) && (((uint32)SADDR & 0x03) == 0x00)));
  
  if(Count > 0x7FFF)//DMA�������ֵ32767
  {
    Count = 0x7FFF;
  }
  
  //DMA�Ĵ�������
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;//DMAģ��ʱ��ʹ��
  
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;//DMA��·����ʱ��ʹ��
  
  DMA_SADDR(DMA_CHx) = (uint32)SADDR;   //����DMA����Դ��ַ
  DMA_DADDR(DMA_CHx) = (uint32)DADDR;   //����DMA����Ŀ�ĵ�ַ
  DMA_SOFF(DMA_CHx) = 0;                //Դ��ַƫ��0x00
  DMA_DOFF(DMA_CHx) = BYTEs;            //������ɺ�Ŀ�ĵ�ַ��BYTEs
  DMA_ATTR(DMA_CHx) = (0
                       | DMA_ATTR_SMOD(0)               //Դ��ַģ����ֹ
                       | DMA_ATTR_SSIZE(BYTEs)          //Դ����λ��
                       | DMA_ATTR_DMOD(0)               //Ŀ���ַģ����ֹ
                       | DMA_ATTR_DSIZE(BYTEs)          //Ŀ������λ��
                       );
  
  DMA_CITER_ELINKNO(DMA_CHx)  = DMA_CITER_ELINKNO_CITER(Count);//��ǰ��ѭ������
  DMA_BITER_ELINKNO(DMA_CHx)  = DMA_BITER_ELINKNO_BITER(Count);//��ʼ��ѭ������
  DMA_CR &= ~DMA_CR_EMLM_MASK;//��ֹ
  
  DMA_NBYTES_MLNO(DMA_CHx) = DMA_NBYTES_MLNO_NBYTES(DMA_BYTEx);
  
  DMA_SLAST(DMA_CHx) = 0;
  DMA_DLAST_SGA(DMA_CHx) = (uint32)((CFG & DADDR_KEEPON) == 0 ? (-Count) : 0);
  
  DMA_CSR(DMA_CHx) = (0
                      | DMA_CSR_BWC(3)               //�������,ÿ��һ�Σ�eDMA ����ֹͣ 8 �����ڣ�0��ֹͣ��1������2ֹͣ4���ڣ�3ֹͣ8���ڣ�
                      | DMA_CSR_DREQ_MASK            //��ѭ��������ֹͣӲ������
                      | DMA_CSR_INTMAJOR_MASK        //��ѭ������������ж�
                      );
  
  DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,DMA_CHx) = (0
                                               | DMAMUX_CHCFG_ENBL_MASK                         //DMAͨ��ʹ��
                                               | DMAMUX_CHCFG_SOURCE(PORT_PTX(PTXx)+DMA_PORTA)  //DMAͨ������Դ(DMA_PORTA~DMA_PORTE)
                                               );
  
  PORT_Init(PTXx,ALT1 | DMA_RISING);    //PORT�˿ڳ�ʼ��PTXx,DMA������
  DMA_GPIO_Input_Init(SADDR,BYTEs);     //GPIO���ó�ʼ��
  
  DMA_DIS(DMA_CHx);             //DMAͨ��ʹ��
  DMA_IRQ_CLEAN(DMA_CHx);       //DMAIRQ�ж�ʹ��
  
}

/*
 *  @brief      DMA ���������ʼ��
 *  @param      DMA_CHn DMA_CHx DMAͨ����(DMA_CH0~DMA_CH31)
 *  @param      PTXn    PTXx    PTX����DMA����˿�
 *  @param      uint32  DMA_Count DMA����������ֵ(0~32767)
 *  @param      DMA_CFG  DMA_Cfg DMA������ʽ����
 *  @since      v1.0
 *  Sample usage:       DMA_Count_Init(DMA_CH0,PTA19,32767,DMA_RISING)
 */
void DMA_Count_Init(DMA_CHn DMA_CHx,PTXn PTXx,uint32 DMA_Count,PORT_CFG DMA_cfg)
{
  uint8 DMA_Byten=DMA_BYTE1;//8Bit����
  uint8 BYTEs=1;
  
  if(DMA_Count > 0x7FFF)//DMA�������ֵ32767
  {
    DMA_Count = 0x7FFF;
  }
  
  DMA_Count_Array[DMA_CHx] = DMA_Count;//DMAͨ��������ֵ
  
  //DMA�Ĵ�������
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;//DMAģ��ʱ��ʹ��
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;//DMA��·����ʱ��ʹ��
  
  DMA_SADDR(DMA_CHx) = (uint32)DMA_COUNTSADDR;          //����DMA����Դ��ַ
  DMA_DADDR(DMA_CHx) = (uint32)DMA_COUNTDADDR;          //����DMA����Ŀ�ĵ�ַ
  DMA_SOFF(DMA_CHx) = 0;                                //Դ��ַƫ��0
  DMA_DOFF(DMA_CHx) = 0;                                //Ŀ�ĵ�ַƫ��0
  DMA_ATTR(DMA_CHx) = (0
                       | DMA_ATTR_SMOD(0)               //Դ��ַģַ��ֹ
                       | DMA_ATTR_SSIZE(DMA_Byten)      //Դ����λ��,8Bit
                       | DMA_ATTR_DMOD(0)               //Ŀ���ַģַ��ֹ
                       | DMA_ATTR_DSIZE(DMA_Byten)      //Ŀ������λ��,8Bit
                       );
  
  DMA_CITER_ELINKNO(DMA_CHx) = DMA_CITER_ELINKNO_CITER(DMA_Count);//��ǰ��ѭ������
  DMA_BITER_ELINKNO(DMA_CHx) = DMA_BITER_ELINKNO_BITER(DMA_Count);//��ʼ��ѭ������
  DMA_CR &= ~DMA_CR_EMLM_MASK;//��ֹ����
  
  DMA_NBYTES_MLNO(DMA_CHx) = DMA_NBYTES_MLNO_NBYTES(BYTEs);//DMA�����ֽ���
  
  DMA_SLAST(DMA_CHx) = -DMA_Count;      //�ָ�Դ��ַ
  DMA_DLAST_SGA(DMA_CHx) = -DMA_Count;  //�ָ�Ŀ�ĵ�ַ
  
  DMA_CSR(DMA_CHx) = (0
                      | DMA_CSR_DREQ_MASK       //��ѭ��������ֹͣӲ������
                      | DMA_CSR_INTMAJOR_MASK   //��ѭ������������ж�
                      );
  
  //DMA����Դ����(����ģʽ)
  DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,DMA_CHx) = (0
                                               | DMAMUX_CHCFG_ENBL_MASK                         //DMAͨ��ʹ��
                                               | DMAMUX_CHCFG_SOURCE(PORT_PTX(PTXx)+DMA_PORTA)  //DMAͨ������Դ(DMA_PORTA~DMA_PORTE)
                                               );
  
  GPIO_Init(PTXx,GPI,0);//PTXx����Ϊ����
  PORT_Init(PTXx,ALT1 | PULLDOWN | DMA_cfg);//DMA�����ش���
  
  DMA_EN(DMA_CHx);      //DMAͨ��ʹ��
  DMA_IRQ_EN(DMA_CHx);  //DMAIRQ�ж�ʹ��
  
}

/*
 *  @brief      DMA ��ȡ�������ֵ
 *  @param      DMA_CHn DMA_CHx DMAͨ����(DMA_CH0~DMA_CH31)
 *  @since      v1.0
 *  Sample usage:       DMA_Temp = DMA_Count_Get(DMA_CH0)
 */
uint32 DMA_Count_Get(DMA_CHn DMA_CHx)
{
  uint32 DMA_Temp=0;
  
  DMA_Temp = DMA_Count_Array[DMA_CHx] - DMA_CITER_ELINKNO(DMA_CHx);//��ȡ��ǰDMA�������ֵ
  
  return DMA_Temp;
}

/*
 *  @brief      DMA �����������
 *  @param      DMA_CHn DMA_CHx DMAͨ����(DMA_CH0~DMA_CH31)
 *  @since      v1.0
 *  Sample usage:       DMA_Count_Reset(DMA_CH0)
 */
void DMA_Count_Reset(DMA_CHn DMA_CHx)
{
  DMA_IRQ_CLEAN(DMA_CHx);//��DMA�жϱ�־λ
  DMA_CITER_ELINKNO(DMA_CHx) = DMA_Count_Array[DMA_CHx];//DMA����ֵ��λ
}