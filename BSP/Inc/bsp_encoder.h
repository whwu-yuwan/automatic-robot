/**
 * @file    bsp_encoder.h
 * @brief   电机编码器读取板(BSP)头文件
 * @details 负责从硬件定时器(TIM2)中读取电机A的编码器脉冲数据。
 *          硬件连接：TIM2_CH1(PA15), TIM2_CH2(PB3)
 */

#ifndef __BSP_ENCODER_H__
#define __BSP_ENCODER_H__

#include "stdint.h"
#include "main.h"

/* -------------------- 接口函数声明 -------------------- */

/**
 * @brief  初始化电机A的编码器
 * @note   主要用于启动 TIM2 的 Encoder 模式
 */
void BSP_Encoder_Init_A(void);

/**
 * @brief  获取电机A编码器的计数值增量
 * @return int16_t: 两次调用之间编码器的计数值增量（带方向，正数为正转，负数为反转）
 * @note   调用后会自动将定时器的计数值清零，以防止溢出，并方便下一次直接读取增量。
 *         适用于周期性（例如 10ms）调用的 PID 闭环控制中。
 */
int16_t BSP_Encoder_GetDelta_A(void);

/**
 * @brief  获取电机A编码器的绝对计数值（不清零）
 * @return int16_t: 当前定时器计数值
 */
int16_t BSP_Encoder_GetCount_A(void);

#endif /* __BSP_ENCODER_H__ */

