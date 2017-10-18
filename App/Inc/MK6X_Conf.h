/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_Conf.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_CONF_H__
#define __MK6X_CONF_H__

#include "Common.h"

/*
**晶振频率OSC(50MHz)
*/
#define EXTAL_IN_MHz            50

/*
**PLL锁相环频率设置宏
*/
#if defined(MK66F18)//MK66F18 PLL时钟设置
#define MK6X_CORE_PLL_CLK       PLL230          //内核PLL频率(PLL220-PLL230比较稳定,建议PLL220)

#define MK6X_CORE_CLK           230             //内核时钟频率
#define MK6X_BUS_CLK            115             //总线时钟频率
#define MK6X_FLEX_CLK            35             //FLEX时钟频率
#define MK6X_FLASH_CLK           30             //FLASH时钟频率
#elif defined(MK64F12)//MK64F12 PLL时钟设置
#define MK6X_CORE_PLL_CLK       PLL100          //内核PLL频率(PLL150-PLL180比较稳定,建议PLL150)

#define MK6X_CORE_CLK           100             //内核时钟频率
#define MK6X_BUS_CLK             50             //总线时钟频率
#define MK6X_FLEX_CLK            25             //FLEX时钟频率
#define MK6X_FLASH_CLK           25             //FLASH时钟频率
#endif
/*
**SIM分频因子设置
*/
#define MK6X_CORE_DIV   0
#define MK6X_BUS_DIV    1
#define MK6X_FLEX_DIV   7
#define MK6X_FLASH_DIV  7

/*
**DWT延时
*/
#define DELAY_MS(ms)    DWT_Delay_ms(ms)
#define DELAY_US(us)    DWT_Delay_us(us)

/*
**选择是否输出调试信息，不输出则注释下面的宏定义
*/
#define DEBUG_PRINT

/*
**配置断言和其实现函数
*/
void assert_failed(char *, int);

#if defined( DEBUG )
#define ASSERT(expr) \
    if (!(expr)) \
        assert_failed(__FILE__, __LINE__)
#else
#define ASSERT(expr)
#endif
          
/*
**配置调试输出函数
*/
#if( defined(DEBUG) && defined(DEBUG_PRINT))
#define DEBUG_PRINTF(FORMAT,...)        do{printf(FORMAT,##__VA_ARGS__);}while(0)	/*无需打印调试信息时，请将宏内容注释掉*/
#else
#define DEBUG_PRINTF(FORMAT,...)
#endif

/*
**variate declaration
*/
extern uint8 Vector_Str[][15];

/*
**function declaration
*/
extern void default_isr(void);


#endif