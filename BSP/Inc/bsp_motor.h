/**
 * @file    bsp_motor.h
 * @brief   电机驱动板(BSP)头文件
 * @details 负责电机控制的底层接口封装。
 *          根据硬件配置，电机A的控制信号由 PE9(TIM1_CH1) 和 PE11(TIM1_CH2) 输出PWM波形。
 */

#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

/* 包含标准类型和HAL库头文件 */
#include "stdint.h"
#include "main.h"

/* 
 * 电机最大速度限制 
 * 根据实际配置的定时器 ARR (Auto-Reload Register) 值进行修改。
 * 在 tim.c 中 TIM1 的 Period (ARR) 配置为 99，因此最大值为 100。
 */
#define MOTOR_MAX_SPEED 4200

/* 
 * 电机衰减模式选择
 * 1: 慢衰减模式 (Slow Decay) - 推荐用于低噪音、低转速抖动的场景
 * 0: 快衰减模式 (Fast Decay) - 适用于需要快速响应、急刹车的场景
 */
#define MOTOR_SLOW_DECAY_MODE 1

/* -------------------- 接口函数声明 -------------------- */

/**
 * @brief  电机底层硬件初始化
 * @note   主要用于开启定时器的PWM输出通道
 */
void BSP_Motor_Init(void);

/**
 * @brief  设置电机A的运行速度与方向
 * @param  speed: 目标速度。
 *                正数表示正转 (0 ~ MOTOR_MAX_SPEED)
 *                负数表示反转 (0 ~ -MOTOR_MAX_SPEED)
 *                0表示停止
 */
void BSP_Motor_SetSpeed_A(int16_t speed);

/**
 * @brief  停止电机A
 * @note   快速将双通道PWM设置为0，使电机自由滑行或制动（取决于具体驱动芯片）
 */
void BSP_Motor_Stop_A(void);

#endif /* __BSP_MOTOR_H__ */
