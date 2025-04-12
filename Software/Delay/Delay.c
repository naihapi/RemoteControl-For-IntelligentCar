#include "Delay.h"

/**
 * @brief 定时器2毫秒级延时
 *
 * @param 毫秒数值
 *
 * @retval 无
 *
 * @note 使用TIM2计数延时
 */
void TIM2_Delay_ms(uint16_t xms)
{
    // 如果计数值大于65535，则不执行
    if (xms >= 65535)
    {
        return;
    }
    else
    {
        TIM_Cmd(TIM2, ENABLE);

        while (TIM_GetCounter(TIM2) < xms)
        {
        }

        TIM_Cmd(TIM2, DISABLE);
        TIM_SetCounter(TIM2, 0);
    }
}

/**
 * @brief 定时器2秒级延时
 *
 * @param 秒数值
 *
 * @retval 无
 *
 * @note 使用TIM2计数延时
 */
void TIM2_Delay_s(uint16_t xs)
{
    TIM2_Delay_ms(xs * 1000);
}
