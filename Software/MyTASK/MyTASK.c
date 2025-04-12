#include "MyTASK.h"

TaskHandle_t TASK1_Handler;
TaskHandle_t TASK2_Handler;
TaskHandle_t TASK3_Handler;
TaskHandle_t TASK4_Handler;
TaskHandle_t TASK5_Handler;
TaskHandle_t TASK6_Handler;
TaskHandle_t TASK7_Handler;
TaskHandle_t TASK8_Handler;
TaskHandle_t TASK9_Handler;
TaskHandle_t TASK10_Handler;
TaskHandle_t TASK11_Handler;
TaskHandle_t TASK12_Handler;
TaskHandle_t TASK13_Handler;
TaskHandle_t TASK14_Handler;
TaskHandle_t TASK15_Handler;
TaskHandle_t TASK_START_Handler;

/**
 * @brief 任务1
 *
 * @note KEY1按键扫描
 */
void TASK1(void *pvParameters)
{
    while (1)
    {
        KEY1_Scanf();
    }
}

/**
 * @brief 任务2
 *
 * @note KEY2按键扫描
 */
void TASK2(void *pvParameters)
{
    while (1)
    {
        KEY2_Scanf();
    }
}

/**
 * @brief 任务3
 *
 * @note KEY3按键扫描
 */
void TASK3(void *pvParameters)
{
    while (1)
    {
        KEY3_Scanf();
    }
}

/**
 * @brief 任务4
 *
 * @note KEY4按键扫描
 */
void TASK4(void *pvParameters)
{
    while (1)
    {
        KEY4_Scanf();
    }
}

/**
 * @brief 任务5
 *
 * @note 默认挂起状态
 * @note OLED屏幕刷新
 */
void TASK5(void *pvParameters)
{
    OLED_Init();
    while (1)
    {
        OLED_Update();
        vTaskSuspend(NULL);
    }
}

/**
 * @brief 任务6
 *
 * @note 页面构建控制
 */
void TASK6(void *pvParameters)
{
    UI_InitPro();
    while (1)
    {
        Build_ControlPro();
        vTaskResume(TASK5_Handler);
    }
}

/**
 * @brief 任务7
 *
 * @note 串口接收控制
 */
void TASK7(void *pvParameters)
{
    while (1)
    {
        USART1_RecState();
        USART3_RecState();
        vTaskDelay(100);
    }
}

/**
 * @brief 任务8
 *
 * @note 无
 */
void TASK8(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务9
 *
 * @note 无
 */
void TASK9(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务10
 *
 * @note 无
 */
void TASK10(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务11
 *
 * @note 无
 */
void TASK11(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务12
 *
 * @note 无
 */
void TASK12(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务13
 *
 * @note 组件页的实时数据采集
 * @note 手动控制页数据上传
 */
void TASK13(void *pvParameters)
{
    while (1)
    {
        Build_ModuleControl_RealTime_Handle();
        Manual_TurnState_UpdateToCar();
    }
}

/**
 * @brief 任务14
 *
 * @note FLASH数据保存和堆内存获取
 * @note 采集数据间隔5s
 */
void TASK14(void *pvParameters)
{
    while (1)
    {
        MySystem_GetFreeHeap(); // 获取空闲堆内存
        Flash_SavaData();       // 保存数据
        vTaskDelay(5000);       // 间隔5s
    }
}

/**
 * @brief 任务15
 *
 * @note 默认挂起状态
 * @note 处于上传界面、请求界面时，按键事件的处理
 */
void TASK15(void *pvParameters)
{
    vTaskSuspend(NULL);
    while (1)
    {
        Build_RequestUpdateControl_KEYevent();
    }
}

/**
 * @brief 打开任务
 *
 * @param pvParameters 系统传递数据
 *
 * @retval 无
 *
 * @note 打开其它的所有任务
 */
void Task_Start(void *pvParameters)
{
    taskENTER_CRITICAL(); // 进入临界区(中断关闭)

    xTaskCreate((TaskFunction_t)TASK1,
                (char *)"TASK1",
                (configSTACK_DEPTH_TYPE)TASK1_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_PRIORITY,
                (TaskHandle_t *)&TASK1_Handler);

    xTaskCreate((TaskFunction_t)TASK2,
                (char *)"TASK2",
                (configSTACK_DEPTH_TYPE)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_PRIORITY,
                (TaskHandle_t *)&TASK2_Handler);

    xTaskCreate((TaskFunction_t)TASK3,
                (char *)"TASK3",
                (configSTACK_DEPTH_TYPE)TASK3_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK3_PRIORITY,
                (TaskHandle_t *)&TASK3_Handler);

    xTaskCreate((TaskFunction_t)TASK4,
                (char *)"TASK4",
                (configSTACK_DEPTH_TYPE)TASK4_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK4_PRIORITY,
                (TaskHandle_t *)&TASK4_Handler);

    xTaskCreate((TaskFunction_t)TASK5,
                (char *)"TASK5",
                (configSTACK_DEPTH_TYPE)TASK5_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK5_PRIORITY,
                (TaskHandle_t *)&TASK5_Handler);

    xTaskCreate((TaskFunction_t)TASK6,
                (char *)"TASK6",
                (configSTACK_DEPTH_TYPE)TASK6_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK6_PRIORITY,
                (TaskHandle_t *)&TASK6_Handler);

    xTaskCreate((TaskFunction_t)TASK7,
                (char *)"TASK7",
                (configSTACK_DEPTH_TYPE)TASK7_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK7_PRIORITY,
                (TaskHandle_t *)&TASK7_Handler);

    xTaskCreate((TaskFunction_t)TASK8,
                (char *)"TASK8",
                (configSTACK_DEPTH_TYPE)TASK8_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK8_PRIORITY,
                (TaskHandle_t *)&TASK8_Handler);

    xTaskCreate((TaskFunction_t)TASK9,
                (char *)"TASK9",
                (configSTACK_DEPTH_TYPE)TASK9_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK9_PRIORITY,
                (TaskHandle_t *)&TASK9_Handler);

    xTaskCreate((TaskFunction_t)TASK10,
                (char *)"TASK10",
                (configSTACK_DEPTH_TYPE)TASK10_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK10_PRIORITY,
                (TaskHandle_t *)&TASK10_Handler);

    xTaskCreate((TaskFunction_t)TASK11,
                (char *)"TASK11",
                (configSTACK_DEPTH_TYPE)TASK11_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK11_PRIORITY,
                (TaskHandle_t *)&TASK11_Handler);

    xTaskCreate((TaskFunction_t)TASK12,
                (char *)"TASK12",
                (configSTACK_DEPTH_TYPE)TASK12_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK12_PRIORITY,
                (TaskHandle_t *)&TASK12_Handler);

    xTaskCreate((TaskFunction_t)TASK13,
                (char *)"TASK13",
                (configSTACK_DEPTH_TYPE)TASK13_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK13_PRIORITY,
                (TaskHandle_t *)&TASK13_Handler);

    xTaskCreate((TaskFunction_t)TASK14,
                (char *)"TASK14",
                (configSTACK_DEPTH_TYPE)TASK14_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK14_PRIORITY,
                (TaskHandle_t *)&TASK14_Handler);

    xTaskCreate((TaskFunction_t)TASK15,
                (char *)"TASK15",
                (configSTACK_DEPTH_TYPE)TASK15_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK15_PRIORITY,
                (TaskHandle_t *)&TASK15_Handler);

    vTaskDelete(NULL);   // 删除任务
    taskEXIT_CRITICAL(); // 退出临界区(中断打开)
}

/**
 * @brief 任务初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 调用后，将开始RTOS任务调度
 */
void TASK_InitPro(void)
{
    /*中断优先级分组(全抢占优先级模式)*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    xTaskCreate((TaskFunction_t)Task_Start,                    // 函数名称
                (char *)"Task_Start",                          // 任务名称
                (configSTACK_DEPTH_TYPE)TASK_START_STACK_SIZE, // 栈空间
                (void *)NULL,                                  // 传给任务的参数
                (UBaseType_t)TASK_START_PRIORITY,              // 优先级
                (TaskHandle_t *)&TASK_START_Handler);          // 任务句柄

    vTaskStartScheduler(); // 启动任务调度器
}

/*
-奶哈啤的遥控器日志(以往的日志，留下来放在这里吧~)-
2024-12-6项目暂停，目前可以切换主页，“控制”菜单可以自由切换
2024-12-10项目继续，可以从主页进入菜单、菜单进入组件，目前仅开放控制组件
2024-12-11优化了屎山代码，可以自由进入退出部分菜单,目前仅开放控制组件
2024-12-12在临界区调用了延时,速度更快了...？另外加入了串口发送
2024-12-13加入JSON，但是解析出问题，待优化
2024-12-14休息，没写
2024-12-15本地解析车辆json数据
2024-12-16感冒休息,喝了茶百道
2024-12-17感冒写了一点,task函数内串口只发送"8H8H"而不是json数据包
2024-12-18在学习阻抗匹配、台灯的最后检查
2024-12-19在做拓展坞，赶在下午已经打板，晚修结束后重新开始这个项目，目前了解到cjson在串口只发送“8H8H”原因是内存管理的问题，预计明天解决
2024-12-20早读前已解决，涉及到钩子
*/
