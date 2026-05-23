/**
 * @file    task_manager.c
 * @brief   FreeRTOS 任务统一管理源文件
 * @details 负责系统中所有 FreeRTOS 任务的创建与初始化
 */

#include "task_manager.h"

/* -------------------- 任务参数定义 -------------------- */

/* 默认任务的优先级与堆栈大小 */
#define DEFAULT_TASK_PRIO       ( tskIDLE_PRIORITY + 1 )  // 优先级（数值越大优先级越高）
#define DEFAULT_TASK_STK_SIZE   128                       // 堆栈大小（单位：字，32位系统中为4字节）

/* TODO: 在此处定义其他任务的优先级与堆栈大小 */


/* -------------------- 任务句柄定义 -------------------- */

TaskHandle_t DefaultTaskHandle = NULL;  // 默认任务句柄定义

/* TODO: 在此处定义其他任务的句柄 */


/* -------------------- 任务函数声明 -------------------- */

/**
 * @brief 默认任务函数
 * @param pvParameters 传递给任务的参数
 */
static void DefaultTask(void *pvParameters);

/* TODO: 在此处声明其他任务的执行函数 */


/* -------------------- 接口函数实现 -------------------- */

/**
 * @brief  初始化任务管理器，统一创建所有的 FreeRTOS 任务
 * @note   调用此函数后，必须在主函数中调用 vTaskStartScheduler() 才能启动调度器
 */
void TaskManager_Init(void)
{
    BaseType_t xReturn = pdPASS;

    /* 1. 创建默认任务 */
    xReturn = xTaskCreate((TaskFunction_t )DefaultTask,             // 任务函数指针
                          (const char*    )"DefaultTask",           // 任务名称（用于调试）
                          (uint16_t       )DEFAULT_TASK_STK_SIZE,   // 任务堆栈大小
                          (void*          )NULL,                    // 传递给任务函数的参数
                          (UBaseType_t    )DEFAULT_TASK_PRIO,       // 任务优先级
                          (TaskHandle_t*  )&DefaultTaskHandle);     // 用于保存任务句柄

    if (xReturn == pdPASS) {
        /* 任务创建成功，可在此添加调试打印信息 */
    }

    /* TODO: 2. 在此处依次创建其他系统任务 */
    // xTaskCreate(...);
    
}

/* -------------------- 任务函数实现 -------------------- */

/**
 * @brief  默认任务的具体实现
 * @param  pvParameters: 传递给任务的参数
 */
static void DefaultTask(void *pvParameters)
{
    /* 任务初始化代码，这里只执行一次 */
    // 例如：初始化特定的传感器、外设等

    /* 任务主循环，必须是死循环，或者在结束时调用 vTaskDelete(NULL) */
    while (1)
    {
        /* 任务主体代码 */
        
        // 示例：每隔 1000 毫秒执行一次（使用系统节拍转换宏）
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* TODO: 在此处实现其他任务的具体逻辑 */
