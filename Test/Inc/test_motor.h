/**
 * @file    test_motor.h
 * @brief   电机驱动测试头文件
 * @details 提供一个简单的裸机测试代码，用于验证电机的正反转与调速功能。
 */

#ifndef __TEST_MOTOR_H__
#define __TEST_MOTOR_H__

/* 包含标准类型 */
#include "stdint.h"

/* -------------------- 接口函数声明 -------------------- */

/**
 * @brief  电机裸机测试函数
 * @note   该函数包含死循环，用于在 main 函数的主循环中或者直接在调度器启动前测试
 */
void Test_Motor_Routine(void);

#endif /* __TEST_MOTOR_H__ */