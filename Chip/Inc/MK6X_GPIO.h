/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_GPIO.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_GPIO_H__
#define __MK6X_GPIO_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**枚举定义GPIO管脚方向(输入,输出)
*/
typedef enum
{
  GPI,          //GPIO Input(GPIO输入)
  GPO,          //GPIO Output(GPIO输出)
}GPIO_CFG;

#define HIGH    1u
#define LOW     0u

#define GPIOX_BASE(PTxn)    GPIOX[PORT_PTX(PTxn)]       //GPIO模块的基址指针

/*
**GPIO端口设置宏
*/
#define GPIO_SET(PTxn,x)        GPIO_SET_##x(PTxn)      //x是输出电平,只能为0或1,0:低电平,1:高电平
#define GPIO_DDRX(PTxn,x)       GPIO_DDRX_##x(PTxn)     //x是管脚方向,只能为0或1,0:输入,1:输出
#define GPIO_TURN(PTxn)         GPIO_PTOR_REG(GPIOX_BASE(PTxn)) |= (1 << PORT_PTn(PTxn))
#define GPIO_GET(PTxn)          ((GPIO_PDIR_REG(GPIOX_BASE(PTxn)) >> PORT_PTn(PTxn)) & 0x01)

#define GPIO_SET_1(PTxn)        GPIO_PDOR_REG(GPIOX_BASE(PTxn)) |= (1 << PORT_PTn(PTxn))
#define GPIO_SET_0(PTxn)        GPIO_PDOR_REG(GPIOX_BASE(PTxn)) &= ~(1 << PORT_PTn(PTxn))

#define GPIO_DDRX_1(PTxn)       GPIO_PDDR_REG(GPIOX_BASE(PTxn)) |= (1 << PORT_PTn(PTxn))
#define GPIO_DDRX_0(PTxn)       GPIO_PDDR_REG(GPIOX_BASE(PTxn)) &= ~(1 << PORT_PTn(PTxn))

/*
**variate declaration
*/
extern GPIO_MemMapPtr GPIOX[PORT_PTX_MAX];

/*
**function declaration
*/
extern void GPIO_Init(PTXn PTXx,GPIO_CFG CFG,uint8 DATA);
extern void GPIO_DDR(PTXn PTXx,GPIO_CFG CFG);
extern void GPIO_Set(PTXn PTXx,uint8 DATA);
extern void GPIO_Turn(PTXn PTXx);
extern uint8 GPIO_Get(PTXn PTXx);

#endif