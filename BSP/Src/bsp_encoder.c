/**
 * @file    bsp_encoder.c
 * @brief   电机编码器读取板(BSP)源文件
 * @details 依赖于 TIM2 的 Encoder 模式配置 (TI12模式，即双边沿触发)。
 *          读取到的脉冲数是实际光电码盘线数 × 4。
 */

#include "bsp_encoder.h"

/* 引入外部定时器句柄，由 STM32CubeMX 在 tim.c 中生成并初始化 */
extern TIM_HandleTypeDef htim2;

/* -------------------- 接口函数实现 -------------------- */

/**
 * @brief  初始化电机A的编码器
 */
void BSP_Encoder_Init_A(void)
{
    /* 开启定时器2的编码器接口，需同时开启通道1和通道2 */
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    
    /* 初始时将计数器清零 */
    __HAL_TIM_SET_COUNTER(&htim2, 0);
}

/**
 * @brief  获取电机A编码器的计数值增量并清零
 * @return int16_t: 增量值
 */
int16_t BSP_Encoder_GetDelta_A(void)
{
    int16_t count;
    
    /* 获取当前的计数器值。
       因为定时器配置的 Period 是 65535 (16位)，所以直接强制类型转换为有符号的 16 位整数。
       当反转导致计数器从 0 减到 65535 时，(int16_t)65535 会自动转换为 -1，完美处理溢出。 */
    count = (int16_t)__HAL_TIM_GET_COUNTER(&htim2);
    
    /* 读取完成后立即清零，为下一次读取做准备 */
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    
    return count;
}

/**
 * @brief  获取电机A编码器的绝对计数值
 * @return int16_t: 当前计数值
 */
int16_t BSP_Encoder_GetCount_A(void)
{
    return (int16_t)__HAL_TIM_GET_COUNTER(&htim2);
}
