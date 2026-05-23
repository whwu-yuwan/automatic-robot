/**
 * @file    task_manager.h
 * @brief   FreeRTOS 任务统一管理头文件
 * @details 提供任务句柄的外部声明以及任务创建的统一接口
 */

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

/* 包含 FreeRTOS 核心头文件 */
#include "FreeRTOS.h"
#include "task.h"

/* 如果有其他需要包含的头文件可以加在这里 */

/* -------------------- 任务句柄声明 -------------------- */
/**
 * @brief 默认任务的句柄，用于管理、控制该任务（如挂起、恢复、删除）
 */
extern TaskHandle_t DefaultTaskHandle;

/* TODO: 在此处添加更多任务句柄的外部声明 */


/* -------------------- 接口函数声明 -------------------- */
/**
 * @brief 统一创建和初始化所有系统任务
 */
void TaskManager_Init(void);

#endif /* __TASK_MANAGER_H__ */
