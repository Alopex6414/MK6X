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
**系统频率
*/
uint16  MK6X_Core_MHz=0;
uint32  MK6X_Core_KHz=0;
uint32  MK6X_Bus_KHz=0;

/*
 *  @brief      复制中断向量表 和 必要的数据到 RAM里
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
    

    /*  VECTOR_TABLE 和 VECTOR_RAM 的地址从  linker 文件里获得 （*.icf） */
    extern uint32 __VECTOR_TABLE[];
    extern uint32 __VECTOR_RAM[];
    
    /*中断向量表复制指针*/
    uint32 *VECTOR_TABLE_P = &__VECTOR_TABLE[0];
    uint32 *VECTOR_RAM_P = &__VECTOR_RAM[0];

    /* 复制ROM里的中断向量表到RAM里 */
    if (__VECTOR_RAM != __VECTOR_TABLE)             //如果不是RAM启动，则需要复制中断向量表
    {
        for (n=0; n<0x410; n++)         //逐个复制
            *VECTOR_RAM_P++ = *VECTOR_TABLE_P++;
    }
    /* 指定新的中断向量表地址为 __VECTOR_RAM */
    write_vtor((uint32)__VECTOR_RAM);
    //write_vtor((uint32)__VECTOR_TABLE);

    /* 把已赋初值的变量从ROM里复制数据到RAM里 */
    data_ram = __section_begin(".data");            //已赋初值的变量的地址在RAM里
    data_rom = __section_begin(".data_init");       //已赋初值的变量的数据存放在ROM里，需要赋值到RAM里
    data_rom_end = __section_end(".data_init");
    n = data_rom_end - data_rom;

    /* 复制初始化数据到RAM里 */
    while (n--)
        *data_ram++ = *data_rom++;

    /* 没赋初值或者初值为0的变量，需要清除其RAM里的数据，确保值为0 */
    bss_start = __section_begin(".bss");
    bss_end = __section_end(".bss");

    /* 清除没赋初值或者初值为0的变量数据值 */
    n = bss_end - bss_start;
    while(n--)
        *bss_start++ = 0;

    /* 赋值用 __ramfunc 声明的函数的的代码段到 RAM，可以加快代码的运行        */
    uint8 *code_relocate_ram = __section_begin("CodeRelocateRam");
    uint8 *code_relocate = __section_begin("CodeRelocate");
    uint8 *code_relocate_end = __section_end("CodeRelocate");

    /* 从ROM里复制函数代码到RAM里 */
    n = code_relocate_end - code_relocate;
    while (n--)
        *code_relocate_ram++ = *code_relocate++;
}

/*
 *  @brief      系统初始化，设置系统频率
 *  @since      v1.0
 *  @note       此函数是系统启动初期由汇编函数调用，然后执行main函数
 */
void SysInit(void)
{
  MK6X_Core_MHz = PLL_Init(MK6X_CORE_PLL_CLK);
  MK6X_Core_KHz = MK6X_Core_MHz * 1000;
  MK6X_Bus_KHz  = MK6X_Core_KHz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1);  
}

/*
 *  @brief      Kinetis 启动函数
 *  @since      v1.0
 *  @note       此函数是系统启动初期由汇编函数调用，然后执行main函数
 */
void Start(void)
{
  #if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));//FPU浮点支持
  #endif
  
  WDOG_Disable();//禁止WDOG
  
  Common_StartUp();//复制中断向量表和相关数据到RAM
  
  SysInit();//系统初始化PLL设置
  
  main();//主函数
  
  while(1);
}