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
**DMA通道计数初始化计数值
*/
uint32 DMA_Count_Array[32]={0};

/*
 *  @brief      DMA GPIO输入初始化
 *  @param      void    *SADDR  PTX模块地址
 *  @param      uint8   BYTEs   8Bit数据
 *  @since      v1.0
 *  Sample usage:       DMA_GPIO_Input_Init()
 */
static void DMA_GPIO_Input_Init(void *SADDR,uint8 BYTEs)
{
  uint8 n;
  uint8 tmp;
  uint8 ptxn;
  uint8 ptx0=((((uint32)SADDR) & 0x1C0) / 0x40 ) * 32;//转换为PTA0,PTB0,PTC0,PTD0,PTE0
  
  n = (((uint32)SADDR - ((uint32)(&(((Dtype*)(&(PTA_BASE_PTR->PDIR)))->B[0])))) & 0x3f) * 8;//最小管脚号
  ptxn = ptx0 + n;
  tmp = ptxn + (BYTEs * 8) - 1;//最大管脚号
  
  while(ptxn <= tmp)
  {
    GPIO_Init((PTXn)ptxn,GPI,0);
    PORT_Init((PTXn)ptxn,ALT1 | PULLDOWN);
    ptxn++;
  }
  
}

/*
 *  @brief      DMA初始化，由IO口请求传输输入端口的数据到内存
 *  @param      DMA_CHn         通道号(DMA_CH0~DMA_CH31)
 *  @param      SADDR           源地址( (void * )&PTx_Bn_IN 或 (void * )&PTx_Wn_IN 或 (void * )&PTx_IN  )
 *  @param      DADDR           目的地址
 *  @param      PTxn            触发端口
 *  @param      DMA_BYTEn       每次DMA传输字节数
 *  @param      count           一个主循环传输字节数
 *  @param      cfg             DMA传输配置，从DMA_cfg里选择
 *  @since      v5.0
 *  @note       DMA PTXn触发源默认上升沿触发传输，若需修改，则初始化后调用 port_init 配置DMA 触发方式
                初始化后，需要调用 DMA_EN 来实现
 *  Sample usage:   uint8 buff[10];
                    DMA_PORTX_To_Buff_Init(DMA_CH0, PTB_B0_IN, buff, PTA7, DMA_BYTE1, 10, DADDR_RECOVER);
                    //DMA初始化，源地址：PTB_B0_IN，目的地址：buff,PTA7触发(默认上升沿)，每次传输1字节，共传输 10次 ，传输结束后恢复地址

                    port_init(PTA7,ALT1 | DMA_FALLING);             //默认触发源是上升沿，此处改为 下降沿触发

                    DMA_EN(DMA_CH0);                //需要使能 DMA 后才能传输数据
 */
void DMA_PORTX_To_Buff_Init(DMA_CHn DMA_CHx,void *SADDR,void *DADDR,PTXn PTXx,DMA_BYTEn DMA_BYTEx,uint32 Count,DMA_CFG CFG)
{
  uint8 BYTEs=0;
  
  //DMA传输字节数
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
  
  if(Count > 0x7FFF)//DMA计数最大值32767
  {
    Count = 0x7FFF;
  }
  
  //DMA寄存器配置
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;//DMA模块时钟使能
  
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;//DMA多路复用时钟使能
  
  DMA_SADDR(DMA_CHx) = (uint32)SADDR;   //设置DMA传输源地址
  DMA_DADDR(DMA_CHx) = (uint32)DADDR;   //设置DMA传输目的地址
  DMA_SOFF(DMA_CHx) = 0;                //源地址偏移0x00
  DMA_DOFF(DMA_CHx) = BYTEs;            //传输完成后目的地址加BYTEs
  DMA_ATTR(DMA_CHx) = (0
                       | DMA_ATTR_SMOD(0)               //源地址模数禁止
                       | DMA_ATTR_SSIZE(BYTEs)          //源数据位宽
                       | DMA_ATTR_DMOD(0)               //目标地址模数禁止
                       | DMA_ATTR_DSIZE(BYTEs)          //目标数据位宽
                       );
  
  DMA_CITER_ELINKNO(DMA_CHx)  = DMA_CITER_ELINKNO_CITER(Count);//当前主循环次数
  DMA_BITER_ELINKNO(DMA_CHx)  = DMA_BITER_ELINKNO_BITER(Count);//起始主循环次数
  DMA_CR &= ~DMA_CR_EMLM_MASK;//禁止
  
  DMA_NBYTES_MLNO(DMA_CHx) = DMA_NBYTES_MLNO_NBYTES(DMA_BYTEx);
  
  DMA_SLAST(DMA_CHx) = 0;
  DMA_DLAST_SGA(DMA_CHx) = (uint32)((CFG & DADDR_KEEPON) == 0 ? (-Count) : 0);
  
  DMA_CSR(DMA_CHx) = (0
                      | DMA_CSR_BWC(3)               //带宽控制,每读一次，eDMA 引擎停止 8 个周期（0不停止；1保留；2停止4周期；3停止8周期）
                      | DMA_CSR_DREQ_MASK            //主循环结束后停止硬件请求
                      | DMA_CSR_INTMAJOR_MASK        //主循环结束后产生中断
                      );
  
  DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,DMA_CHx) = (0
                                               | DMAMUX_CHCFG_ENBL_MASK                         //DMA通道使能
                                               | DMAMUX_CHCFG_SOURCE(PORT_PTX(PTXx)+DMA_PORTA)  //DMA通道触发源(DMA_PORTA~DMA_PORTE)
                                               );
  
  PORT_Init(PTXx,ALT1 | DMA_RISING);    //PORT端口初始化PTXx,DMA上升沿
  DMA_GPIO_Input_Init(SADDR,BYTEs);     //GPIO设置初始化
  
  DMA_DIS(DMA_CHx);             //DMA通道使能
  DMA_IRQ_CLEAN(DMA_CHx);       //DMAIRQ中断使能
  
}

/*
 *  @brief      DMA 脉冲计数初始化
 *  @param      DMA_CHn DMA_CHx DMA通道号(DMA_CH0~DMA_CH31)
 *  @param      PTXn    PTXx    PTX触发DMA传输端口
 *  @param      uint32  DMA_Count DMA计数脉冲满值(0~32767)
 *  @param      DMA_CFG  DMA_Cfg DMA触发方式配置
 *  @since      v1.0
 *  Sample usage:       DMA_Count_Init(DMA_CH0,PTA19,32767,DMA_RISING)
 */
void DMA_Count_Init(DMA_CHn DMA_CHx,PTXn PTXx,uint32 DMA_Count,PORT_CFG DMA_cfg)
{
  uint8 DMA_Byten=DMA_BYTE1;//8Bit传输
  uint8 BYTEs=1;
  
  if(DMA_Count > 0x7FFF)//DMA计数最大值32767
  {
    DMA_Count = 0x7FFF;
  }
  
  DMA_Count_Array[DMA_CHx] = DMA_Count;//DMA通道计数初值
  
  //DMA寄存器配置
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;//DMA模块时钟使能
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;//DMA多路复用时钟使能
  
  DMA_SADDR(DMA_CHx) = (uint32)DMA_COUNTSADDR;          //设置DMA传输源地址
  DMA_DADDR(DMA_CHx) = (uint32)DMA_COUNTDADDR;          //设置DMA传输目的地址
  DMA_SOFF(DMA_CHx) = 0;                                //源地址偏移0
  DMA_DOFF(DMA_CHx) = 0;                                //目的地址偏移0
  DMA_ATTR(DMA_CHx) = (0
                       | DMA_ATTR_SMOD(0)               //源地址模址禁止
                       | DMA_ATTR_SSIZE(DMA_Byten)      //源数据位宽,8Bit
                       | DMA_ATTR_DMOD(0)               //目标地址模址禁止
                       | DMA_ATTR_DSIZE(DMA_Byten)      //目标数据位宽,8Bit
                       );
  
  DMA_CITER_ELINKNO(DMA_CHx) = DMA_CITER_ELINKNO_CITER(DMA_Count);//当前主循环次数
  DMA_BITER_ELINKNO(DMA_CHx) = DMA_BITER_ELINKNO_BITER(DMA_Count);//起始主循环次数
  DMA_CR &= ~DMA_CR_EMLM_MASK;//禁止传输
  
  DMA_NBYTES_MLNO(DMA_CHx) = DMA_NBYTES_MLNO_NBYTES(BYTEs);//DMA传输字节数
  
  DMA_SLAST(DMA_CHx) = -DMA_Count;      //恢复源地址
  DMA_DLAST_SGA(DMA_CHx) = -DMA_Count;  //恢复目的地址
  
  DMA_CSR(DMA_CHx) = (0
                      | DMA_CSR_DREQ_MASK       //主循环结束后停止硬件请求
                      | DMA_CSR_INTMAJOR_MASK   //主循环结束后产生中断
                      );
  
  //DMA触发源配置(正常模式)
  DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,DMA_CHx) = (0
                                               | DMAMUX_CHCFG_ENBL_MASK                         //DMA通道使能
                                               | DMAMUX_CHCFG_SOURCE(PORT_PTX(PTXx)+DMA_PORTA)  //DMA通道触发源(DMA_PORTA~DMA_PORTE)
                                               );
  
  GPIO_Init(PTXx,GPI,0);//PTXx设置为输入
  PORT_Init(PTXx,ALT1 | PULLDOWN | DMA_cfg);//DMA上升沿触发
  
  DMA_EN(DMA_CHx);      //DMA通道使能
  DMA_IRQ_EN(DMA_CHx);  //DMAIRQ中断使能
  
}

/*
 *  @brief      DMA 获取脉冲计数值
 *  @param      DMA_CHn DMA_CHx DMA通道号(DMA_CH0~DMA_CH31)
 *  @since      v1.0
 *  Sample usage:       DMA_Temp = DMA_Count_Get(DMA_CH0)
 */
uint32 DMA_Count_Get(DMA_CHn DMA_CHx)
{
  uint32 DMA_Temp=0;
  
  DMA_Temp = DMA_Count_Array[DMA_CHx] - DMA_CITER_ELINKNO(DMA_CHx);//读取当前DMA脉冲计数值
  
  return DMA_Temp;
}

/*
 *  @brief      DMA 脉冲计数清零
 *  @param      DMA_CHn DMA_CHx DMA通道号(DMA_CH0~DMA_CH31)
 *  @since      v1.0
 *  Sample usage:       DMA_Count_Reset(DMA_CH0)
 */
void DMA_Count_Reset(DMA_CHn DMA_CHx)
{
  DMA_IRQ_CLEAN(DMA_CHx);//清DMA中断标志位
  DMA_CITER_ELINKNO(DMA_CHx) = DMA_Count_Array[DMA_CHx];//DMA计数值复位
}