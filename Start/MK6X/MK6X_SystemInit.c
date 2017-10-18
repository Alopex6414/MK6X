/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_SystemInit.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam"

/*
**ϵͳƵ��
*/
uint16  MK6X_Core_MHz=0;
uint32  MK6X_Core_KHz=0;
uint32  MK6X_Bus_KHz=0;

/*
 *  @brief      �����ж������� �� ��Ҫ�����ݵ� RAM��
 *  @since      v1.0
 */
void Common_StartUp(void)
{
    /* Declare a counter we'll use in all of the copy loops */
    uint32 n;

    /* Declare pointers for various data sections. These pointers
     * are initialized using values pulled in from the linker file
     */
    uint8 *data_ram, * data_rom, * data_rom_end;
    uint8 *bss_start, * bss_end;
    

    /*  VECTOR_TABLE �� VECTOR_RAM �ĵ�ַ��  linker �ļ����� ��*.icf�� */
    extern uint32 __VECTOR_TABLE[];
    extern uint32 __VECTOR_RAM[];
    
    /*�ж���������ָ��*/
    uint32 *VECTOR_TABLE_P = &__VECTOR_TABLE[0];
    uint32 *VECTOR_RAM_P = &__VECTOR_RAM[0];

    /* ����ROM����ж�������RAM�� */
    if (__VECTOR_RAM != __VECTOR_TABLE)             //�������RAM����������Ҫ�����ж�������
    {
        for (n=0; n<0x410; n++)         //�������
            *VECTOR_RAM_P++ = *VECTOR_TABLE_P++;
    }
    /* ָ���µ��ж��������ַΪ __VECTOR_RAM */
    write_vtor((uint32)__VECTOR_RAM);
    //write_vtor((uint32)__VECTOR_TABLE);

    /* ���Ѹ���ֵ�ı�����ROM�︴�����ݵ�RAM�� */
    data_ram = __section_begin(".data");            //�Ѹ���ֵ�ı����ĵ�ַ��RAM��
    data_rom = __section_begin(".data_init");       //�Ѹ���ֵ�ı��������ݴ����ROM���Ҫ��ֵ��RAM��
    data_rom_end = __section_end(".data_init");
    n = data_rom_end - data_rom;

    /* ���Ƴ�ʼ�����ݵ�RAM�� */
    while (n--)
        *data_ram++ = *data_rom++;

    /* û����ֵ���߳�ֵΪ0�ı�������Ҫ�����RAM������ݣ�ȷ��ֵΪ0 */
    bss_start = __section_begin(".bss");
    bss_end = __section_end(".bss");

    /* ���û����ֵ���߳�ֵΪ0�ı�������ֵ */
    n = bss_end - bss_start;
    while(n--)
        *bss_start++ = 0;

    /* ��ֵ�� __ramfunc �����ĺ����ĵĴ���ε� RAM�����Լӿ���������        */
    uint8 *code_relocate_ram = __section_begin("CodeRelocateRam");
    uint8 *code_relocate = __section_begin("CodeRelocate");
    uint8 *code_relocate_end = __section_end("CodeRelocate");

    /* ��ROM�︴�ƺ������뵽RAM�� */
    n = code_relocate_end - code_relocate;
    while (n--)
        *code_relocate_ram++ = *code_relocate++;
}

/*
 *  @brief      ϵͳ��ʼ��������ϵͳƵ��
 *  @since      v1.0
 *  @note       �˺�����ϵͳ���������ɻ�ຯ�����ã�Ȼ��ִ��main����
 */
void SysInit(void)
{
  MK6X_Core_MHz = PLL_Init(MK6X_CORE_PLL_CLK);
  MK6X_Core_KHz = MK6X_Core_MHz * 1000;
  MK6X_Bus_KHz  = MK6X_Core_KHz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1);  
}

/*
 *  @brief      Kinetis ��������
 *  @since      v1.0
 *  @note       �˺�����ϵͳ���������ɻ�ຯ�����ã�Ȼ��ִ��main����
 */
void Start(void)
{
  #if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));//FPU����֧��
  #endif
  
  WDOG_Disable();//��ֹWDOG
  
  Common_StartUp();//�����ж��������������ݵ�RAM
  
  SysInit();//ϵͳ��ʼ��PLL����
  
  main();//������
  
  while(1);
}