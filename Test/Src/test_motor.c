/**
 * @file    test_motor.c
 * @brief   电机驱动测试源文件
 * @details 循环执行正转、反转、停止，便于用示波器或实际电机验证 PWM 输出。
 */

#include "test_motor.h"
#include "bsp_motor.h"
#include "main.h" /* 包含 HAL 库，用于 HAL_Delay */

/* -------------------- 测试函数实现 -------------------- */

/**
 * @brief  电机裸机测试的具体实现
 * @note   使用 HAL_Delay 进行延时，不会发生任务调度
 */
void Test_Motor_Routine(void)
{
    /* 测试主循环 */
    while (1)
    {
        /* 1. 正转，50% 速度，持续 2 秒 */
        BSP_Motor_SetSpeed_A(MOTOR_MAX_SPEED / 2);
        HAL_Delay(2000);

        /* 2. 停止，持续 1 秒 */
        BSP_Motor_Stop_A();
        HAL_Delay(1000);

        /* 3. 反转，50% 速度，持续 2 秒 */
        BSP_Motor_SetSpeed_A(-(MOTOR_MAX_SPEED / 2));
        HAL_Delay(2000);

        /* 4. 停止，持续 1 秒 */
        BSP_Motor_Stop_A();
        HAL_Delay(1000);
        
        /* 5. 正转，100% 满速，持续 2 秒 */
        BSP_Motor_SetSpeed_A(MOTOR_MAX_SPEED);
        HAL_Delay(2000);
        
        /* 6. 停止，持续 2 秒 */
        BSP_Motor_Stop_A();
        HAL_Delay(2000);
    }
}