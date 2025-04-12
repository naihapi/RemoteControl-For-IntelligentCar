#include "CC2530.h"

/**
 * @brief 发送CMD后检查关键字
 *
 * @param string 发送的cmd指令
 * @param cmd 检查的关键字
 *
 * @retval 1 比较成功
 * @retval 0 比较失败
 *
 * @note 重试10次，间隔50毫秒，总耗时500毫秒
 * @note 参照<智能台灯>的ESP01S写法
 */
uint8_t CC2530_Command(uint8_t *string, uint8_t *cmd)
{
    // 空值判断
    if (cmd == NULL || string == NULL)
    {
        return 0;
    }

    uint8_t Retry = 10; // 10次重试后超时

    USART_SendString_Wireless(string);
    while (Retry--)
    {
        // 接收完成
        if (USART1_RecFlag == 1)
        {
            // 比对成功
            if (strstr((const char *)USART1_RecBuffer, (const char *)cmd) != NULL)
            {
				USART1_RecFlag=0;
                return 1;
            }
        }

        // 延时50ms后，进行下一次接收标志位判断
        vTaskDelay(50);
    }

    // 超时，比对失败
    return 0;
}

/**
 * @brief SE-发送CMD后检查关键字
 *
 * @param string 发送的cmd指令
 * @param cmd 检查的关键字
 *
 * @retval 1 比较成功
 * @retval 0 比较失败
 *
 * @note 不重试，仅判断一次
 * @note 参照<智能台灯>的ESP01S写法
 */
uint8_t CC2530_CommandSE(uint8_t *string, uint8_t *cmd)
{
    // 空值判断
    if (cmd == NULL || string == NULL)
    {
        return 0;
    }

    uint8_t Retry = 1; // 10次重试后超时

    USART_SendString_Wireless(string);
    while (Retry--)
    {
        // 接收完成
        if (USART1_RecFlag == 1)
        {
            // 比对成功
            if (strstr((const char *)USART1_RecBuffer, (const char *)cmd) != NULL)
            {
                return 1;
            }
        }
    }

    // 超时，比对失败
    return 0;
}

/**
 * @brief PRO-发送CMD后检查关键字
 *
 * @param string 发送的cmd指令
 * @param cmd 检查的关键字
 *
 * @retval 1 比较成功
 * @retval 0 比较失败
 *
 * @note 升级版的命令查询函数，在原版基础上重试5次
 * @note 参照<智能台灯>的ESP01S写法
 */
uint8_t CC2530_CommandPRO(uint8_t *string, uint8_t *cmd)
{
    uint8_t Retry = 5; // 重试5次

    while (Retry)
    {
        USART1_Clear_RecBuffer();
        if (CC2530_Command(string, cmd) == 1)
        {
            // 比对成功
            return 1;
        }

        // 延时10ms后，进行下一次发送判断
        vTaskDelay(10);

        Retry--;
    }

    // 比对失败
    return 0;
}

/**
 * @brief 无线串口初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void CC2530_InitPro(void)
{
}
