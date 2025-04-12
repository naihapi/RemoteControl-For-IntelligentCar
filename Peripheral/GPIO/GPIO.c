#include "GPIO.h"

/**
 * @brief LED关闭
 *
 * @param 无
 *
 * @retval 无
 *
 * @note LED-PB13
 */
void GPIO_LED_OFF(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_13);
}

/**
 * @brief LED打开
 *
 * @param 无
 *
 * @retval 无
 *
 * @note LED-PB13
 */
void GPIO_LED_ON(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_13);
}

/**
 * @brief LED初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note LED-PB13
 */
void GPIO_LED_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 初始状态LED
    GPIO_LED_OFF();
}

/**
 * @brief IIC2初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void GPIO_IIC2_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief 按键初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note PC14-KEY1 PC15-KEY2 PA0-KEY3 PA1-KEY4
//  * @note 中断优先级8，受RTOS管控
 */
void GPIO_KEY_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_INITSTRUCTURE;
    // EXTI_InitTypeDef EXTI_InitStructure;
    // NVIC_InitTypeDef NVIC_InitStructure;

    // 引脚初始化：KEY1 KEY2 KEY3 KEY4
    GPIO_INITSTRUCTURE.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_INITSTRUCTURE.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INITSTRUCTURE.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_INITSTRUCTURE);

    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1); // KEY1中断线
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2); // KEY2中断线
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3); // KEY3中断线
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4); // KEY4中断线

    // // KEY1外部中断
    // EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    // EXTI_Init(&EXTI_InitStructure);

    // // KEY2外部中断
    // EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    // EXTI_Init(&EXTI_InitStructure);

    // // KEY3外部中断
    // EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    // EXTI_Init(&EXTI_InitStructure);

    // // KEY4外部中断
    // EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    // EXTI_Init(&EXTI_InitStructure);

    // // KEY1嵌套向量
    // NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    // NVIC_Init(&NVIC_InitStructure);

    // // KEY2嵌套向量
    // NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    // NVIC_Init(&NVIC_InitStructure);

    // // KEY3嵌套向量
    // NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    // NVIC_Init(&NVIC_InitStructure);

    // // KEY4嵌套向量
    // NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    // NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief 串口1初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 已接入Zigbee无线串口
 * @note 用作遥控器的数据传输
 */
void GPIO_USART1_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    // 引脚TX配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 引脚RX配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief 串口3初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 已接入USB-C有线串口
 * @note 可用Type-C数据线与电脑连接，用作Debug
 */
void GPIO_USART3_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    // 引脚TX配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 引脚RX配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief 外部中断服务函数1
 *
 * @param 无
 *
 * @retval 无
 *
 * @note KEY1
 */
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        TIM2_Delay_ms(5);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == RESET)
        {
        }

        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

/**
 * @brief 外部中断服务函数2
 *
 * @param 无
 *
 * @retval 无
 *
 * @note KEY2
 */
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) == SET)
    {
        TIM2_Delay_ms(5);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == RESET)
        {
        }
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

/**
 * @brief 外部中断服务函数3
 *
 * @param 无
 *
 * @retval 无
 *
 * @note KEY3
 */
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3) == SET)
    {
        TIM2_Delay_ms(5);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == RESET)
        {
        }
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

/**
 * @brief 外部中断服务函数4
 *
 * @param 无
 *
 * @retval 无
 *
 * @note KEY4
 */
void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line4) == SET)
    {
        TIM2_Delay_ms(5);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == RESET)
        {
        }
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

/**
 * @brief 获取KEY1引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY1
 */
uint8_t GPIO_RetState_KEY1(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
}

/**
 * @brief 获取KEY2引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY2
 */
uint8_t GPIO_RetState_KEY2(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
}

/**
 * @brief 获取KEY3引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY3
 */
uint8_t GPIO_RetState_KEY3(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
}

/**
 * @brief 获取KEY4引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY4
 */
uint8_t GPIO_RetState_KEY4(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
}

/**
 * @brief GPIO引脚初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note IO引脚初始化汇总函数
 */
void GPIO_InitPro(void)
{
    GPIO_LED_Init();    // 初始化LED
    GPIO_IIC2_Init();   // 初始化IIC2
    GPIO_KEY_Init();    // 初始化KEY
    GPIO_USART1_Init(); // 初始化USART1
    GPIO_USART3_Init(); // 初始化USART3
}
