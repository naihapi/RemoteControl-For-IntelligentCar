#include "POST.h"

uint8_t POST_String[] = "POST#"; // 请求体前缀格式

/*---请求体格式说明---*/

// 开关型：#1，视图型：#2，滑块型：#3

// 开关型请求：POST#LEDFront#1
// 视图型请求：POST#LEDFront#2
// 滑块型请求：POST#LEDFront#3

// 开关型返回检查：POST#LEDFront#1#
// 视图型返回检查：POST#LEDFront#2#
// 滑块型返回检查：POST#LEDFront#3#

// 开关型数据：<打开 POST#LEDFront#1#1><关闭 POST#LEDFront#1#0>
// 视图型数据：<打开 POST#LEDFront#2#1><关闭 POST#LEDFront#2#0>
// 滑块型数据：<当前#最大#最小 POST#LEDFront#3#now#max#mini#>

/*---请求体格式说明---*/

/**
 * @brief 复制粘贴缓冲区并在末尾加字符串
 *
 * @param buf 复制体
 * @param newbuf 粘贴体
 * @param addbuf 末尾添加的字符串
 *
 * @retval 无
 *
 * @note 复制一个缓冲区的内容，粘贴到另一个缓冲区，并在末尾添加字符串
 * @note 如果复制体是空的，就跳过粘贴过程
 */
void POST_ChangeRequest(uint8_t *buf, uint8_t *newbuf, uint8_t *addbuf)
{
    if (buf == NULL || buf == "")
    {
        strcat((char *)newbuf, (const char *)addbuf);
    }
    else
    {
        strcat((char *)newbuf, (const char *)buf);
        strcat((char *)newbuf, (const char *)addbuf);
    }
}

/**
 * @brief 开关型组件读取状态
 *
 * @param result 需要提取状态的字符串
 *
 * @retval 1 状态为打开
 * @retval 0 状态为关闭/获取失败
 *
 * @note result参数只能接收两种结果：POST#xxx#1#0或POST#xxx#1#1
 */
uint8_t POST_SwitchModule_GetState(uint8_t *result)
{
    uint8_t State = 0, *p = result;

    p = (uint8_t *)strchr((const char *)result, '#'); // 查找请求体中<第一个#>的位置
    if (p == NULL)
    {
        // 获取失败
        return 0;
    }
    p++; // 跳过<第一个#>的位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第二个#>的位置
    if (p == NULL)
    {
        // 获取失败
        return 0;
    }
    p++; // 跳过<第二个#>的位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第三个#>的位置
    if (p == NULL)
    {
        // 获取失败
        return 0;
    }
    p++; // 跳过<第三个#>的位置

    State = *p; // 更新状态

    State = atoi((const char *)p);

    return State;
}

/**
 * @brief 开关型组件数据请求
 *
 * @param name 硬件名称
 * @param state 状态
 *
 * @retval 1 数据请求成功
 * @retval 0 数据请求失败
 *
 * @note 开关型请求体格式：POST#LEDFront#1
 * @note 检查返回体格式：POST#LEDFront#1#
 * @note 返回结果：POST#LEDFront#1#1或POST#LEDFront#1#0
 */
uint8_t POST_SwitchModule(uint8_t *name, uint8_t *state)
{
    // 检查字符串和请求字符串
    uint8_t CheckString[32] = {0}, RequestString[32] = {0};

    // 加入：请求前缀名、组件后缀标识
    POST_ChangeRequest(POST_String, RequestString, name); //'POST#'+LEDFront
    POST_ChangeRequest(NULL, RequestString, "#1");        // LEDFront+'#1'

    // 检查返回体：POST#LEDFront#1+'#'
    POST_ChangeRequest(RequestString, CheckString, "#");

    // 发送请求
    if (CC2530_CommandPRO(RequestString, CheckString) == 1)
    {
        *state = POST_SwitchModule_GetState(USART1_RecBuffer);

        // 处理成功
        return 1;
    }
    else
    {
        // 处理失败
        return 0;
    }
}

/**
 * @brief 视图型组件读取数值
 *
 * @param result 需要提取状态的字符串
 *
 * @retval 数值
 *
 * @note result参数：POST#xxx##2#value
 */
int POST_ViewModule_GetValue(uint8_t *result)
{
    uint8_t *p = result;
    int value = 0;

    p = (uint8_t *)strchr((const char *)result, '#'); // 查找请求体中<第一个#>的位置
    if (p == NULL)
    {
        // 获取失败
        return 0;
    }
    p++; // 跳过<第一个#>的位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第二个#>的位置
    if (p == NULL)
    {
        // 获取失败
        return 0;
    }
    p++; // 跳过<第二个#>的位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第三个#>的位置
    if (p == NULL)
    {
        // 获取失败
        return 0;
    }
    p++; // 跳过<第三个#>的位置

    value = atoi((const char *)p);

    return value;
}

/**
 * @brief 视图型组件数据请求
 *
 * @param name 硬件名称
 * @param value 数值
 *
 * @retval 1 数据请求成功
 * @retval 0 数据请求失败
 *
 * @note 视图型请求体格式：POST#LEDFront#2
 * @note 检查返回体格式：POST#LEDFront#2#
 * @note 返回结果：POST#LEDFront#2#1或POST#LEDFront#2#0
 */
uint8_t POST_ViewModule(uint8_t *name, int *value)
{
    // 检查字符串和请求字符串
    uint8_t CheckString[32] = {0}, RequestString[32] = {0};

    // 加入：请求前缀名、组件后缀标识
    POST_ChangeRequest(POST_String, RequestString, name); //'POST#'+LEDFront
    POST_ChangeRequest(NULL, RequestString, "#2");        // LEDFront+'#2'

    // 检查返回体：POST#LEDFront#2+'#'
    POST_ChangeRequest(RequestString, CheckString, "#");

    // 发送请求
    if (CC2530_CommandPRO(RequestString, CheckString) == 1)
    {
        *value = POST_ViewModule_GetValue(USART1_RecBuffer);

        // 处理成功
        return 1;
    }
    else
    {
        // 处理失败
        return 0;
    }
}

/**
 * @brief 滑块型组件提取数据
 *
 * @param result 需要提取数据的字符串
 * @param nowvalue 当前值
 * @param maxvalue 最大值
 * @param minivalue 最小值
 *
 * @retval 1 提取成功
 * @retval 0 提取失败
 *
 * @note result参数：POST#xxx#3#now#max#mini#
 */
uint8_t POST_SliderModule_GetData(uint8_t *result, int *nowvalue, int *maxvalue, int *minivalue)
{
    uint8_t *p = result, *start = NULL, *end = NULL, buffer[64];
    size_t length;

    /*-------------------------------跳过无用的'#'字符-------------------------------*/
    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第一个#>的位置
    if (p == NULL)
        return 0;
    p++; // 跳过<第一个#>的位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第二个#>的位置
    if (p == NULL)
        return 0;
    p++; // 跳过<第二个#>的位置
    /*-------------------------------跳过无用的'#'字符-------------------------------*/

    /*-------------------------------提取当前值now-------------------------------*/
    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第三个#>的位置
    if (p == NULL)
        return 0;

    p++;       // 跳过<第三个#>的位置
    start = p; // 记录<now>的起始位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第四个#>的位置
    if (p == NULL)
        return 0;

    end = p; // 记录<第四个#>的位置

    length = end - start; // 获取<now>和<第四个#>之间的长度
    if (length >= sizeof(buffer))
        return 0;

    // 复制<now>和<第四个#>之间的内容到缓冲区中，并添加结束符
    strncpy((char *)buffer, (const char *)start, length);
    buffer[length] = '\0';

    *nowvalue = atoi((const char *)buffer); // 提取
    /*-------------------------------提取当前值now-------------------------------*/

    memset(buffer, 0, sizeof(buffer)); // 清空缓冲区

    /*-------------------------------提取最大值max-------------------------------*/
    p++;       // 跳过<第四个#>的位置
    start = p; // 记录<max>的起始位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第五个#>的位置
    if (p == NULL)
        return 0;

    end = p; // 记录<第五个#>的位置

    length = end - start; // 获取<max>和<第五个#>之间的长度
    if (length >= sizeof(buffer))
        return 0;

    // 复制<max>和<第五个#>之间的内容到缓冲区中，并添加结束符
    strncpy((char *)buffer, (const char *)start, length);
    buffer[length] = '\0';

    *maxvalue = atoi((const char *)buffer); // 提取
    /*-------------------------------提取最大值max-------------------------------*/

    /*-------------------------------提取最小值mini-------------------------------*/
    p++;       // 跳过<第五个#>的位置
    start = p; // 记录<mini>的起始位置

    p = (uint8_t *)strchr((const char *)p, '#'); // 查找请求体中<第六个#>的位置
    if (p == NULL)
        return 0;

    end = p; // 记录<第六个#>的位置

    length = end - start; // 获取<mini>和<第六个#>之间的长度
    if (length >= sizeof(buffer))
        return 0;

    // 复制<mini>和<第六个#>之间的内容到缓冲区中，并添加结束符
    strncpy((char *)buffer, (const char *)start, length);
    buffer[length] = '\0';

    *minivalue = atoi((const char *)buffer); // 提取
    /*-------------------------------提取最小值mini-------------------------------*/

    // 获取成功
    return 1;
}

/**
 * @brief 滑块型组件数据请求
 *
 * @param name 硬件名称
 * @param nowvalue 当前值
 * @param maxvalue 最大值
 * @param minivalue 最小值
 *
 * @retval 1 数据请求成功
 * @retval 0 数据请求失败
 *
 * @note 滑块型请求体格式：POST#LEDFront#3
 * @note 检查返回体格式：POST#LEDFront#3#
 * @note 返回结果：POST#LEDFront#3#now#max#min#
 */
uint8_t POST_SliderModule(uint8_t *name, int *nowvalue, int *maxvalue, int *minivalue)
{
    // 检查字符串和请求字符串
    uint8_t CheckString[32] = {0}, RequestString[32] = {0};

    // 加入：请求前缀名、组件后缀标识
    POST_ChangeRequest(POST_String, RequestString, name); //'POST#'+LEDFront
    POST_ChangeRequest(NULL, RequestString, "#3");        // LEDFront+'#3'

    // 检查返回体：POST#LEDFront#3+'#'
    POST_ChangeRequest(RequestString, CheckString, "#");

    // 发送请求
    if (CC2530_CommandPRO(RequestString, CheckString) == 1)
    {
        if (POST_SliderModule_GetData(USART1_RecBuffer, nowvalue, maxvalue, minivalue) == 1)
        {
            // 处理成功
            return 1;
        }
        else
        {
            // 处理失败
            return 0;
        }
    }
    else
    {
        // 处理失败
        return 0;
    }
}

/**
 * @brief 通用的请求处理
 *
 * @param name 硬件名称
 * @param length 请求个数
 * @param arr 请求数据包(传入指针数组)
 * @param check 是否检查返回内容(传入NULL不检查)
 *
 * @retval 1 数据请求成功
 * @retval 0 数据请求失败
 * @retval 2 不检查数据请求
 *
 * @note 此函数不存储返回内容
 */
uint8_t POST_Currency(uint8_t *name, uint8_t length, uint8_t **arr, uint8_t *check)
{
    uint8_t retval = 0, result = 0;

    // 检查请求字符串
    uint8_t RequestString[64] = {0};

    // 加入：请求前缀名、分割符号#
    POST_ChangeRequest(POST_String, RequestString, name); //'POST#'+name
    POST_ChangeRequest(NULL, RequestString, "#4");         // POST#name+'#4'

    // 合并请求内容
    for (uint8_t i = 0; i < length-1; i++)
    {
        POST_ChangeRequest(arr[i], RequestString, "#");
    }
	POST_ChangeRequest(arr[length-1], RequestString, "");

    // 发送请求
    if (check == NULL)
    {
        result = CC2530_CommandSE(RequestString, "");
    }
    else
    {
        result = CC2530_CommandPRO(RequestString, check);
    }

    if (result == 1)
    {
        // 比对成功
        retval = 1;
    }
    else
    {
        // 比对失败
        retval = 0;
    }

    if (check == NULL)
    {
        // 无需比对
        retval = 2;
    }

    return retval;
}

/**
 * @brief 数据请求初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void POST_InitPro(void)
{
}
