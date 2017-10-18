/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PDB.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      PDB��ʼ��
 *  @since      v1.0
 *  Sample usage:       PDB_Init();//��ʼ�� PDB0
 */
void PDB_Init(void)
{
  SIM_SCGC6 |= SIM_SCGC6_PDB_MASK;//PDBģ��ʱ��ʹ��
  
  //PDB״̬���ƼĴ���
  PDB_SC_REG(PDB0_BASE_PTR) = (0
                               | PDB_SC_CONT_MASK       //PDB����ģʽ
                               | PDB_SC_TRGSEL(15)      //PDB�������
                               | PDB_SC_PDBEN_MASK      //PDBģ��ʹ��
                               );
  
}