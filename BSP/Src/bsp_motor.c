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
 * @note   快衰减逻辑 (PWM + 低电平)：
 *         正转：CH1 输出 0，CH2 输出 PWM
 *         反转：CH1 输出 PWM，CH2 输出 0
 *         慢衰减逻辑 (PWM + 高电平，反相占空比)：
 *         正转：CH1 输出 100% 高电平，CH2 输出 (100%-PWM)
 *         反转：CH1 输出 (100%-PWM)，CH2 输出 100% 高电平
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

#if MOTOR_SLOW_DECAY_MODE
    /* -------------------- 慢衰减模式 (Slow Decay) -------------------- */
    /* 在慢衰减模式下，不输出 PWM 的那一端保持高电平(满占空比)。
       输出 PWM 的一端需要反相占空比，即：设定的速度越大，低电平时间越长。 */
    if (speed > 0)
    {
        // 正转：CH1 满占空比(常高)，CH2 输出反相占空比
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MOTOR_MAX_SPEED);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MOTOR_MAX_SPEED - speed);
    }
    else if (speed < 0)
    {
        // 反转：CH1 输出反相占空比，CH2 满占空比(常高)
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MOTOR_MAX_SPEED - (-speed));
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MOTOR_MAX_SPEED);
    }
    else
    {
        // 停止：双端均高电平，电机短路刹车制动
        BSP_Motor_Stop_A();
    }
#else
    /* -------------------- 快衰减模式 (Fast Decay) -------------------- */
    /* 在快衰减模式下，不输出 PWM 的那一端保持低电平(0)。 */
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
        // 停止逻辑：双端低电平，电机自由滑行
        BSP_Motor_Stop_A();
    }
#endif
}

/**
 * @brief  停止电机A
 * @note   快衰减下双 0 为滑行；慢衰减下双满占空比为刹车
 */
void BSP_Motor_Stop_A(void)
{
#if MOTOR_SLOW_DECAY_MODE
    /* 慢衰减停止：双高电平，电机短路产生制动力矩（刹车） */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MOTOR_MAX_SPEED);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MOTOR_MAX_SPEED);
#else
    /* 快衰减停止：双低电平，电机失去驱动力自由滑行 */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
#endif
}
