#include "TIM.h"

uint16_t TIM3_CNT = 0;        // 定时器3计数值
uint8_t TIM3_CountFinish = 0; // 定时器3计数完成标志

/**
 * @brief 定时器2初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 用作阻塞式延时，详见Delay.c
 */
void TIM2_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;          // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36000 - 1;       // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = DISABLE; // 溢出x次后才触发更新中断
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, DISABLE);
}

/**
 * @brief 定时器3初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 用作按键点击事件检测
 */
void TIM3_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // PSC=7200 ARR=1000 10ms
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;  // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, DISABLE);
}

/**
 * @brief 定时器3中断服务函数
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 用作按键点击事件检测
 */
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        TIM3_CNT++;

        if (TIM3_CNT >= 250)
        {
            // 计数250毫秒后置位
            TIM3_CountFinish = 1;

            // 重置定时器部分参数
            TIM_Cmd(TIM3, DISABLE);
            TIM_SetCounter(TIM3, 0);
            TIM3_CNT = 0;
        }

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

/**
 * @brief 定时器初始化汇总
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void TIM_InitPro(void)
{
    TIM2_Init();
    TIM3_Init();
}
