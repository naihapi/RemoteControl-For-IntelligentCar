#include "USART.h"

uint8_t USART1_RecBuffer[1024];      // 串口1接收缓冲区-无线串口
uint8_t USART1_Intrrupt_CNT = 0;     // 串口1接收1帧计数（中断函数内使用）
uint8_t USART1_Intrrupt_LastCNT = 0; // 串口1接收1帧计数（记录上一次的值，当前与上次进行对比，相等即接收完成）
uint8_t USART1_RecFlag = 0;          // 串口1接收标志（0=没有数据 2=正在接收数据 1=接收完成）

uint8_t USART3_RecBuffer[1024];      // 串口3接收缓冲区-电脑
uint8_t USART3_Intrrupt_CNT = 0;     // 串口3接收1帧计数（中断函数内使用）
uint8_t USART3_Intrrupt_LastCNT = 0; // 串口3接收1帧计数（记录上一次的值，当前与上次进行对比，相等即接收完成）
uint8_t USART3_RecFlag = 0;          // 串口3接收标志（0=没有数据 2=正在接收数据 1=接收完成）

/**
 * @brief 串口1缓冲区清空
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void USART1_Clear_RecBuffer(void)
{
    memset(USART1_RecBuffer, 0, sizeof(USART1_RecBuffer));
}

/**
 * @brief 串口3缓冲区清空
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 可用Type-C数据线与电脑连接
 */
void USART3_Clear_RecBuffer(void)
{
    memset(USART3_RecBuffer, 0, sizeof(USART3_RecBuffer));
}

/**
 * @brief 串口1初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 1字符中断1次
 * @note 可用Type-C数据线与电脑连接
 */
void USART1_Init(void)
{
    // 清空接收缓冲区
    USART1_Clear_RecBuffer();

    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // USART初始化
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    // 串口1使能字节中断位
    USART_ClearFlag(USART1, USART_FLAG_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 使能串口1中断
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief 串口3初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 1字符中断1次
 * @note 可用Type-C数据线与电脑连接
 */
void USART3_Init(void)
{
    // 清空接收缓冲区
    USART3_Clear_RecBuffer();

    // 开启时钟和结构体定义
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // USART初始化
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStructure);

    // 串口3使能字节中断位
    USART_ClearFlag(USART3, USART_FLAG_RXNE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    // 使能串口3中断
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART3, ENABLE);
}

/**
 * @brief 串口1发送字符
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 仅发送1字符
 * @note 可用Type-C数据线与电脑连接
 */
void USART1_SendByte(uint16_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }
}

/**
 * @brief 串口3发送字符
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 仅发送1字符
 * @note 可用Type-C数据线与电脑连接
 */
void USART3_SendByte(uint16_t Byte)
{
    USART_SendData(USART3, Byte);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    {
    }
}

/**
 * @brief 串口1发送字符串
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 发送字符串
 * @note 可用Type-C数据线与电脑连接
 */
void USART1_SendString(uint8_t *String)
{
    for (uint16_t i = 0; String[i] != '\0'; i++)
    {
        USART1_SendByte((uint8_t)String[i]);
    }
}

/**
 * @brief 串口1发送数字
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 发送数字
 * @note 可用Type-C数据线与电脑连接
 */
void USART1_SendNumber(int32_t Number)
{
    uint8_t Buffer[16];

    snprintf((char *)Buffer, sizeof(Buffer), "%d", Number);
    USART1_SendString(Buffer);
}

/**
 * @brief 串口3发送字符串
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 发送字符串
 * @note 可用Type-C数据线与电脑连接
 */
void USART3_SendString(uint8_t *String)
{
    for (uint16_t i = 0; String[i] != '\0'; i++)
    {
        USART3_SendByte((uint8_t)String[i]);
    }
}

/**
 * @brief 串口3发送数字
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 发送数字
 * @note 可用Type-C数据线与电脑连接
 */
void USART3_SendNumber(int32_t Number)
{
    uint8_t Buffer[16];

    snprintf((char *)Buffer, sizeof(Buffer), "%d", Number);
    USART3_SendString(Buffer);
}

/**
 * @brief 使用串口1接收状态判断
 *
 * @param 无
 *
 * @retval 标志位置位
 * @retval 0 没有收到数据
 * @retval 1 数据接收完成
 * @retval 2 数据接收中
 *
 * @note 不能快速执行函数
 * @note 如果判断太快，会导致<接收完成标志位>提前置位
 * @note 建议500ms判断一次
 */
void USART1_RecState(void)
{
    if (USART1_Intrrupt_CNT == 0)
    {
        // 没有收到数据
        USART1_RecFlag = 0;
    }
    else if (USART1_Intrrupt_CNT != USART1_Intrrupt_LastCNT)
    {
        // 正在接收数据
        USART1_Intrrupt_LastCNT = USART1_Intrrupt_CNT;
        USART1_RecFlag = 2;
    }
    else if (USART1_Intrrupt_CNT == USART1_Intrrupt_LastCNT)
    {
        // 数据接收完成
        USART1_Intrrupt_CNT = 0;
        USART1_RecFlag = 1;
    }
}

/**
 * @brief 向无线串口发送字符串
 *
 * @param String 字符串
 *
 * @retval 无
 *
 * @note 串口1发送字符串
 * @note 向<CC2530无线串口>发送字符串
 */
void USART_SendString_Wireless(uint8_t *String)
{
    USART1_SendString(String);
}

/**
 * @brief 向无线串口发送数字
 *
 * @param Number 数字
 *
 * @retval 无
 *
 * @note 串口1发送数字
 * @note 向<CC2530无线串口>发送数字
 */
void USART_SendNumber_Wireless(int32_t Number)
{
    USART1_SendNumber(Number);
}

/**
 * @brief 向电脑发送字符串
 *
 * @param String 字符串
 *
 * @retval 无
 *
 * @note 串口3发送字符串
 * @note 向<USB-C>发送字符串
 */
void USART_SendString_Computer(uint8_t *String)
{
    USART3_SendString(String);
}

/**
 * @brief 向电脑发送数字
 *
 * @param Number 数字
 *
 * @retval 无
 *
 * @note 串口3发送数字
 * @note 向<USB-C>发送数字
 */
void USART_SendNumber_Computer(int32_t Number)
{
    USART3_SendNumber(Number);
}

/**
 * @brief 使用串口3接收状态判断
 *
 * @param 无
 *
 * @retval 标志位置位
 * @retval 0 没有收到数据
 * @retval 1 数据接收完成
 * @retval 2 数据接收中
 *
 * @note 不能快速执行函数
 * @note 如果判断太快，会导致<接收完成标志位>提前置位
 * @note 建议500ms判断一次
 */
void USART3_RecState(void)
{
    if (USART3_Intrrupt_CNT == 0)
    {
        // 没有收到数据
        USART3_RecFlag = 0;
    }
    else if (USART3_Intrrupt_CNT != USART3_Intrrupt_LastCNT)
    {
        // 正在接收数据
        USART3_Intrrupt_LastCNT = USART3_Intrrupt_CNT;
        USART3_RecFlag = 2;
    }
    else if (USART3_Intrrupt_CNT == USART3_Intrrupt_LastCNT)
    {
        // 数据接收完成
        USART3_Intrrupt_CNT = 0;
        USART3_RecFlag = 1;
    }
}

void USART_InitPro(void)
{
    USART1_Init();
    USART3_Init();

    USART_SendString_Computer("A\nComputer: Remote Control By Naihapi\n");
    USART_SendString_Wireless("A\nWireless: Remote Control By Naihapi\n");
}

/**
 * @brief 串口1中断服务函数
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 使用字节中断进行数据接收
 */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        // 接收缓冲区溢出时，从头开始覆盖原有数据
        if (USART1_Intrrupt_CNT >= sizeof(USART1_RecBuffer))
        {
            USART1_Intrrupt_CNT = 0;
        }

        // 获取1个字节，然后自增
        USART1_RecBuffer[USART1_Intrrupt_CNT] = USART1->DR;
        USART1_Intrrupt_CNT++;

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

/**
 * @brief 串口3中断服务函数
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 使用字节中断进行数据接收
 */
void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        // 接收缓冲区溢出时，从头开始覆盖原有数据
        if (USART3_Intrrupt_CNT >= sizeof(USART3_RecBuffer))
        {
            USART3_Intrrupt_CNT = 0;
        }

        // 获取1个字节，然后自增
        USART3_RecBuffer[USART3_Intrrupt_CNT] = USART3->DR;
        USART3_Intrrupt_CNT++;

        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}
