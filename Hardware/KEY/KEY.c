#include "KEY.h"

// 按键状态(0：按键松开，1：按键短按，2：按键长按)
uint8_t KEY1_State = 0; // 按键1状态
uint8_t KEY2_State = 0; // 按键2状态
uint8_t KEY3_State = 0; // 按键3状态
uint8_t KEY4_State = 0; // 按键4状态

// 经测试，KEY_CNT_longDown的自增并不是1ms/次。大约20倍误差：计数10次时，实际时间流过200ms左右
// 通过串口输出时间比对、Keil5的Debug查看变量数值发现的规律，我也不清楚具体原因，只能先缩短KEY_CNT_longDown的长按判定时间

/**
 * @brief KEY1按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，标志位是KEY1_State
 */

void KEY1_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY1() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY1() == 0)
        {
            while (GPIO_RetState_KEY1() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY1_State = 2;
            }
            else
            {
                KEY1_State = 1;
            }
        }
    }
}

/**
 * @brief KEY2按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，标志位是KEY2_State
 */
void KEY2_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY2() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY2() == 0)
        {
            while (GPIO_RetState_KEY2() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY2_State = 2;
            }
            else
            {
                KEY2_State = 1;
            }
        }
    }
}

/**
 * @brief KEY3按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，标志位是KEY3_State
 */
void KEY3_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY3() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY3() == 0)
        {
            while (GPIO_RetState_KEY3() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY3_State = 2;
            }
            else
            {
                KEY3_State = 1;
            }
        }
    }
}

/**
 * @brief KEY4按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，标志位是KEY4_State
 */
void KEY4_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY4() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY4() == 0)
        {
            while (GPIO_RetState_KEY4() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY4_State = 2;
            }
            else
            {
                KEY4_State = 1;
            }
        }
    }
}

/**
 * @brief 关闭按键事件监测
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 挂起所有按键事件监测的任务
 */
void KEY_KEYScanf_Disable(void)
{
    vTaskSuspend(TASK1_Handler);
    vTaskSuspend(TASK2_Handler);
    vTaskSuspend(TASK3_Handler);
    vTaskSuspend(TASK4_Handler);
}

/**
 * @brief 打开按键事件监测
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 恢复所有按键事件监测的任务
 */
void KEY_KEYScanf_Enable(void)
{
    vTaskResume(TASK1_Handler);
    vTaskResume(TASK2_Handler);
    vTaskResume(TASK3_Handler);
    vTaskResume(TASK4_Handler);
}

/**
 * @brief 按键初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void KEY_InitPro(void)
{
}
