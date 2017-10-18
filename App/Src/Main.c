/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Main.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      main    ������
 *  @note 	������
 *  @since      v1.0
 *  Sample usage:       void main(void)
 */
void main(void)
{ 
  Site_t Site={0,0};
  
  AllInit();//��ʼ��
  
  MAPS_LCDC_BMP_From_SD("0:/Mitsuha.bmp",Site);//����ͼ��
  
  for(;;)
  {
    MAPS_Dock_KEY_Incident();//�����������ڷ���
    MAPS_Dock_Rocker_Key_LCM_Control();//LCM��ʾ
  }
}