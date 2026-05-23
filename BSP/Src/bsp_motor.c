/**
 * @file    bsp_motor.c
 * @brief   电机驱动板(BSP)源文件
 * @details 负责电机控制的具体硬件操作，通过修改 TIM1 的 CH1 和 CH2 的比较值(CCR)来改变 PWM 占空比，
 *          从而控制电机的转速和方向。
 */

#include "bsp_motor.h"

/* 引入外部定时器句柄。由于你已经使用CubeMX等工具配置好了初始化，
 * htim1 通常会在 tim.h 中声明并初始化。 */
extern TIM_HandleTypeDef htim1;

/* -------------------- 接口函数实现 -------------------- */

/**
 * @brief  电机底层硬件初始化
 * @note   由于引脚和定时器的基础配置已在 main 中完成，
 *         这里只需要启动对应通道的 PWM 输出即可。
 */
void BSP_Motor_Init(void)
{
    /* 开启定时器1的通道1 (PE9) 的 PWM 输出 */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    
    /* 开启定时器1的通道2 (PE11) 的 PWM 输出 */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    
    /* 默认初始化后让电机处于停止状态 */
    BSP_Motor_Stop_A();
}

/**
 * @brief  设置电机A的运行速度与方向
 * @param  speed: 目标速度。范围为 -MOTOR_MAX_SPEED 到 MOTOR_MAX_SPEED。
 * @note   常见的双PWM引脚控制逻辑：
 *         正转：CH1 输出 0，CH2 输出 PWM
 *         反转：CH1 输出 PWM，CH2 输出 0
 *         停止：CH1 和 CH2 均输出 0
 */
void BSP_Motor_SetSpeed_A(int16_t speed)
{
    /* 限制输入速度幅值，防止超出定时器 ARR 导致溢出异常 */
    if (speed > MOTOR_MAX_SPEED)
    {
        speed = MOTOR_MAX_SPEED;
    }
    else if (speed < -MOTOR_MAX_SPEED)
    {
        speed = -MOTOR_MAX_SPEED;
    }

    /* 根据速度的正负号判断方向，并分别设置两个通道的占空比 */
    if (speed > 0)
    {
        // 正转逻辑：CH1 输出低电平(0)，CH2 输出占空比
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
    }
    else if (speed < 0)
    {
        // 反转逻辑：CH1 输出占空比 (注意speed是负数，需要取反)，CH2 输出低电平(0)
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -speed);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    }
    else
    {
        // 停止逻辑
        BSP_Motor_Stop_A();
    }
}

/**
 * @brief  停止电机A
 * @note   将两路 PWM 比较值都设为 0，停止电机输出
 */
void BSP_Motor_Stop_A(void)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
}
