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
**����Ƶ��OSC(50MHz)
*/
#define EXTAL_IN_MHz            50

/*
**PLL���໷Ƶ�����ú�
*/
#if defined(MK66F18)//MK66F18 PLLʱ������
#define MK6X_CORE_PLL_CLK       PLL230          //�ں�PLLƵ��(PLL220-PLL230�Ƚ��ȶ�,����PLL220)

#define MK6X_CORE_CLK           230             //�ں�ʱ��Ƶ��
#define MK6X_BUS_CLK            115             //����ʱ��Ƶ��
#define MK6X_FLEX_CLK            35             //FLEXʱ��Ƶ��
#define MK6X_FLASH_CLK           30             //FLASHʱ��Ƶ��
#elif defined(MK64F12)//MK64F12 PLLʱ������
#define MK6X_CORE_PLL_CLK       PLL100          //�ں�PLLƵ��(PLL150-PLL180�Ƚ��ȶ�,����PLL150)

#define MK6X_CORE_CLK           100             //�ں�ʱ��Ƶ��
#define MK6X_BUS_CLK             50             //����ʱ��Ƶ��
#define MK6X_FLEX_CLK            25             //FLEXʱ��Ƶ��
#define MK6X_FLASH_CLK           25             //FLASHʱ��Ƶ��
#endif
/*
**SIM��Ƶ��������
*/
#define MK6X_CORE_DIV   0
#define MK6X_BUS_DIV    1
#define MK6X_FLEX_DIV   7
#define MK6X_FLASH_DIV  7

/*
**DWT��ʱ
*/
#define DELAY_MS(ms)    DWT_Delay_ms(ms)
#define DELAY_US(us)    DWT_Delay_us(us)

/*
**ѡ���Ƿ����������Ϣ���������ע������ĺ궨��
*/
#define DEBUG_PRINT

/*
**���ö��Ժ���ʵ�ֺ���
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
**���õ����������
*/
#if( defined(DEBUG) && defined(DEBUG_PRINT))
#define DEBUG_PRINTF(FORMAT,...)        do{printf(FORMAT,##__VA_ARGS__);}while(0)	/*�����ӡ������Ϣʱ���뽫������ע�͵�*/
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