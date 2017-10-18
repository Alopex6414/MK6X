/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FLASH.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      Flash����
 *  @return     ����ִ�н��(1�ɹ���0ʧ��)
 *  @since      v1.0
 */
__RAMFUNC uint8 Flash_CMD(void)
{
  FTFE_FSTAT = (0
                | FTFE_FSTAT_CCIF_MASK        //ָ����ɱ�־(д1��0)
                | FTFE_FSTAT_RDCOLERR_MASK    //����ͻ�����־(д1��0)
                | FTFE_FSTAT_ACCERR_MASK      //���ʴ����־λ(д1��0)
                | FTFE_FSTAT_FPVIOL_MASK      //�Ƿ����ʱ�����־λ(д1��0)
                );
  while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)); //�ȴ��������
  
  if(FTFE_FSTAT & (FTFE_FSTAT_ACCERR_MASK | FTFE_FSTAT_RDCOLERR_MASK | FTFE_FSTAT_FPVIOL_MASK | FTFE_FSTAT_MGSTAT0_MASK))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*
 *  @brief      ��ʼ��flash
 *  @since      v1.0
 */
__RAMFUNC void Flash_Init(void)
{
  // ���FlashԤ��ȡ������
  #if defined(MK66F18)
  FMC_PFB01CR |= FMC_PFB01CR_S_B_INV_MASK;
  #elif defined(MK64F12)
  FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
  #endif
  
  while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));
  
  FTFE_FSTAT = (0
                | FTFE_FSTAT_CCIF_MASK        //ָ����ɱ�־(д1��0)
                | FTFE_FSTAT_RDCOLERR_MASK    //����ͻ�����־(д1��0)
                | FTFE_FSTAT_ACCERR_MASK      //���ʴ����־λ(д1��0)
                | FTFE_FSTAT_FPVIOL_MASK      //�Ƿ����ʱ�����־λ(д1��0)
                );
  DELAY_MS(10);
}

/*
 *  @brief      ����ָ��flash����
 *  @param      sector_num    ������(MK66FN2M0ʵ��ʹ��0~511,MK66FX1M0ʵ��ʹ��0~255)
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v1.0
 *  Sample usage:       Flash_Erase_Sector(512-1);        //��������512-1
 */
__RAMFUNC uint8 Flash_Erase_Sector(uint16 sector_num)
{
  uint32 addr = sector_num * FLASH_SECTOR_SIZE;
  
  //���ò�������
  FCMD = ERSSCR;

  //����Ŀ���ַ
  FADDR2 = ((Dtype *)&addr)->B[2];
  FADDR1 = ((Dtype *)&addr)->B[1];
  FADDR0 = ((Dtype *)&addr)->B[0];
  
  if(Flash_CMD() == 0)//Flash_CMD�����Ƿ����
  {
    return 0;
  }
  
  if(sector_num == 0)//�����Ų�ҪΪ0
  {
    return Flash_Write(sector_num,0x000408,0xFFFFFFFFFFFFFFFF);
  }
  
  return 1;
}

/*
 *  @brief      д�볤�ֽ����ݵ� flashָ����ַ
 *  @param      sector_num      ������(MK66FN2M0ʵ��ʹ��0~511,MK66FX1M0ʵ��ʹ��0~255)
 *  @param      offset          д�������ڲ�ƫ�Ƶ�ַ(0~4095 �� 8�ı���)
 *  @param      data            ��Ҫд�������
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v1.0
 *  Sample usage:       Flash_Write(511,0,0xAABBCCDDEEFF0011);        //����127,ƫ�Ƶ�ַΪ0,д������:0xFFFFFFFE
 */
__RAMFUNC uint8 Flash_Write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data)
{
  uint32 addr = sector_num * FLASH_SECTOR_SIZE + offset;
  uint32 tmpdata;
  
  //ƫ�Ƶ�ַ����FLASH_ALIGN_ADDR�ı�����ƫ�Ƶ�ַ����������Сִ��ʧ��
  if(offset % FLASH_ALIGN_ADDR != 0 || offset > FLASH_SECTOR_SIZE)
  {
    return 0;
  }
  
  //����Ŀ���ַ
  FADDR2 = ((Dtype *)&addr)->B[2];
  FADDR1 = ((Dtype *)&addr)->B[1];
  FADDR0 = ((Dtype *)&addr)->B[0];
  
  //���õ�32λ����
  tmpdata = (uint32)data;
  FDATA0 = ((Dtype *)&tmpdata)->B[3];                    // ����д������
  FDATA1 = ((Dtype *)&tmpdata)->B[2];
  FDATA2 = ((Dtype *)&tmpdata)->B[1];
  FDATA3 = ((Dtype *)&tmpdata)->B[0];
  
  FCMD = PGM8;
  
  tmpdata = (uint32)(data>>32);

  FDATA4 = ((Dtype *)&tmpdata)->B[3];                 // ����д������
  FDATA5 = ((Dtype *)&tmpdata)->B[2];
  FDATA6 = ((Dtype *)&tmpdata)->B[1];
  FDATA7 = ((Dtype *)&tmpdata)->B[0];
  
  if(Flash_CMD() == 0)
  {
    return 0;
  }
  
  return 1;
}

/*
 *  @brief      д�����ݻ������� flashָ����ַ
 *  @param      sector_num      ������(MK66FN2M0ʵ��ʹ��0~511,MK66FX1M0ʵ��ʹ��0~255)
 *  @param      offset          д�������ڲ�ƫ�Ƶ�ַ(0~4095 �� 8�ı���)
 *  @param      buf             ��Ҫд������ݻ������׵�ַ
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v1.0
 *  Sample usage:           uint32 buff[10];
                            Flash_Write_Buff(127,0,sizeof(buff),buff);        //����127,ƫ�Ƶ�ַΪ0,д������Դ��ַ:buff,��Ŀsizeof(buff)
 */
__RAMFUNC uint8 Flash_Write_Buff(uint16 sector_num, uint16 offset, uint16 cnt, uint8 *buf)
{
  uint32  size;
  uint32  addr;
  uint32  data;
  
  //ƫ�Ƶ�ַ����FLASH_ALIGN_ADDR�ı�����ƫ�Ƶ�ַ����������Сִ��ʧ��
  if(offset % FLASH_ALIGN_ADDR != 0 || offset > FLASH_SECTOR_SIZE)
  {
    return 0;
  }
  
  addr = sector_num * FLASH_SECTOR_SIZE + offset;
  
  FCMD = PGM8;
  
  for(size = 0; size < cnt; size += FLASH_ALIGN_ADDR)
  {
    //����Ŀ���ַ
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];
    
    //���õ�32λ����
    data =  *(uint32 *)buf;
    
    FDATA0 = ((Dtype *)&data)->B[3];                    // ����д������
    FDATA1 = ((Dtype *)&data)->B[2];
    FDATA2 = ((Dtype *)&data)->B[1];
    FDATA3 = ((Dtype *)&data)->B[0];
    
    //���ø�32λ����
    data = *(uint32 *)(buf+4);

    FDATA4 = ((Dtype *)&data)->B[3];                    // ����д������
    FDATA5 = ((Dtype *)&data)->B[2];
    FDATA6 = ((Dtype *)&data)->B[1];
    FDATA7 = ((Dtype *)&data)->B[0];
    
    if(Flash_CMD() == 0)
    {
      return 0;
    }
    
    addr += FLASH_ALIGN_ADDR;
    buf += FLASH_ALIGN_ADDR;
  }
  
  return 1;
}