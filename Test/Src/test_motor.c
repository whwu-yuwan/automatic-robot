/**
 * @file    test_motor.c
 * @brief   电机驱动测试源文件
 * @details 循环执行正转、反转、停止，便于用示波器或实际电机验证 PWM 输出。
 */

#include "test_motor.h"
#include "bsp_motor.h"
#include "bsp_encoder.h"
#include "main.h" /* 包含 HAL 库，用于 HAL_Delay */
#include <stdio.h> /* 用于 printf */

/* -------------------- 内部辅助函数 -------------------- */
/**
 * @brief  延时并定期打印编码器数据
 * @param  ms: 延时总时间（毫秒）
 * @note   每隔 100ms 打印一次编码器的绝对计数值和增量值
 */
static void Delay_And_Print_Encoder(uint32_t ms)
{
    uint32_t count = ms / 100;
    uint32_t remain = ms % 100;

    for (uint32_t i = 0; i < count; i++)
    {
        HAL_Delay(100);
        /* 获取增量（这会清零定时器）*/
        int16_t delta = BSP_Encoder_GetDelta_A();
        printf("Encoder Delta (100ms): %d\r\n", delta);
    }
    
    if (remain > 0)
    {
        HAL_Delay(remain);
    }
}

/* -------------------- 测试函数实现 -------------------- */

/**
 * @brief  电机裸机测试的具体实现
 * @note   使用 HAL_Delay 进行延时，不会发生任务调度，同时打印编码器数据
 */
void Test_Motor_Routine(void)
{
    /* 初始化编码器 */
    BSP_Encoder_Init_A();
    printf("\r\n--- Motor & Encoder Test Start ---\r\n");

    /* 测试主循环 */
    while (1)
    {
        /* 1. 正转，速度 2500，持续 1 秒 */
        printf("\r\n[1] Motor Forward (Speed: 2500)...\r\n");
        BSP_Motor_SetSpeed_A(2500);
        Delay_And_Print_Encoder(1000);

        /* 2. 停止，持续 1 秒 */
        printf("\r\n[2] Motor Stop...\r\n");
        BSP_Motor_Stop_A();
        Delay_And_Print_Encoder(1000);

        /* 3. 反转，速度 -2600，持续 2 秒 */
        printf("\r\n[3] Motor Backward (Speed: -2600)...\r\n");
        BSP_Motor_SetSpeed_A(-2600); // 注意：反转需要负数
        Delay_And_Print_Encoder(2000);

        /* 4. 停止，持续 1 秒 */
        printf("\r\n[4] Motor Stop...\r\n");
        BSP_Motor_Stop_A();
        Delay_And_Print_Encoder(1000);
        
        /* 5. 正转，速度 2700，持续 2 秒 */
        printf("\r\n[5] Motor Forward (Speed: 2700)...\r\n");
        BSP_Motor_SetSpeed_A(2700);
        Delay_And_Print_Encoder(2000);
        
        /* 6. 停止，持续 2 秒 */
        printf("\r\n[6] Motor Stop...\r\n");
        BSP_Motor_Stop_A();
        Delay_And_Print_Encoder(2000);
    }
}
