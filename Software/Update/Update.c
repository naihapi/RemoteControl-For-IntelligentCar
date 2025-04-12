#include "Update.h"

uint8_t Update_String[] = "Update#"; // 上传体前缀格式

/*---上传体格式说明---*/

// 开关型：#1，视图型：#2，滑块型：#3

// 开关型上传格式：Update#LEDFront#1#1
// 视图型上传格式：Update#LEDFront#2#99
// 滑块型上传格式：Update#LEDFront#3#now#max#mini#

// 开关型返回检查：<成功 "OK"><失败 "Fail">
// 视图型返回检查：<成功 "OK"><失败 "Fail">
// 滑块型返回检查：<成功 "OK"><失败 "Fail">

/*---上传体格式说明---*/

/**
 * @brief 复制粘贴缓冲区并在末尾加字符串
 *
 * @param buf 复制体
 * @param newbuf 粘贴体
 * @param addbuf 末尾添加的字符串
 *
 * @retval 1 状态为打开
 * @retval 0 状态为关闭/获取失败
 *
 * @note 复制一个缓冲区的内容，粘贴到另一个缓冲区，并在末尾添加字符串
 * @note 如果复制体是空的，就跳过粘贴过程
 */
void Update_ChangeRequest(uint8_t *buf, uint8_t *newbuf, uint8_t *addbuf)
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
 * @brief 开关型组件数据上传
 *
 * @param name 硬件名称
 * @param state 状态
 *
 * @retval 1 数据上传成功
 * @retval 0 数据上传失败
 *
 * @note 开关型上传体格式：POST#LEDFront#1
 * @note 检查返回体格式：OK/Fail
 */
uint8_t Update_SwitchModule(uint8_t *name, uint8_t *state)
{
    // 检查字符串、上传字符串、类型和状态字符串、标志位
    uint8_t CheckString[8] = "OK", UpdateString[64] = {0}, TypeStateString[8] = {0}, Flag = 0;

    // 类型、状态组合：'#1'+'#1/#0'
    sprintf((char *)TypeStateString, "#1#%d", *state);

    // 加入：上传前缀名
    Update_ChangeRequest(Update_String, UpdateString, name);   //'Update#'+LEDFront
    Update_ChangeRequest(NULL, UpdateString, TypeStateString); // LEDFront+'#1#1/#0'

    // 发送上传,等待回复
    Flag = CC2530_CommandPRO(UpdateString, CheckString);

    if (Flag == 1)
    {
        // 上传成功
        return 1;
    }

    // 上传失败
    return 0;
}

/**
 * @brief 滑块型组件数据上传
 *
 * @param name 硬件名称
 * @param now 当前值
 * @param max 最大值
 * @param mini 最小值
 *
 * @retval 1 数据上传成功
 * @retval 0 数据上传失败
 *
 * @note 组件型上传体格式：POST#LEDFront#3#now#max#mini#
 * @note 检查返回体格式：OK/Fail
 */
uint8_t Update_SliderModule(uint8_t *name, int *now, int *max, int *mini)
{
    // 检查字符串、上传字符串、类型和数值字符串、标志位
    uint8_t CheckString[8] = "OK", UpdateString[64] = {0}, TypeValueString[32] = {0}, Flag = 0;

    // 类型、数值组合：'#3'+'#now#max#mini#'
    sprintf((char *)TypeValueString, "#3#%d#%d#%d#", *now, *max, *mini);

    // 加入：上传前缀名
    Update_ChangeRequest(Update_String, UpdateString, name);   //'Update#'+LEDFront
    Update_ChangeRequest(NULL, UpdateString, TypeValueString); // LEDFront+'#3#now#max#mini#'

    // 发送上传，等待回复
    Flag = CC2530_CommandPRO(UpdateString, CheckString);

    if (Flag == 1)
    {
        // 上传成功
        return 1;
    }

    // 上传失败
    return 0;
}

/**
 * @brief 通用的上传处理
 *
 * @param name 硬件名称
 * @param length 上传个数
 * @param arr 上传数据包(传入指针数组)
 * @param check 是否检查返回内容(传入NULL不检查)
 *
 * @retval 1 数据上传成功
 * @retval 0 数据上传失败
 * @retval 2 不检查数据请求
 *
 * @note 此函数不存储返回内容
 */
uint8_t Update_Currency(uint8_t *name, uint8_t length, uint8_t **arr, uint8_t *check)
{
    uint8_t retval = 0, result = 0;

    // 检查请求字符串
    uint8_t UpdateString[64] = {0};

    // 加入：请求前缀名、分割符号#
    Update_ChangeRequest(Update_String, UpdateString, name); //'Update#'+name
    Update_ChangeRequest(NULL, UpdateString, "#4");           // Update#name+'#4'

    // 合并请求内容
    for (uint8_t i = 0; i < length-1; i++)
    {
        Update_ChangeRequest(arr[i], UpdateString, "#");
    }
	Update_ChangeRequest(arr[length-1], UpdateString, "");

    // 发送请求
    if (check == NULL)
    {
        result = CC2530_CommandSE(UpdateString, "");
    }
    else
    {
        result = CC2530_CommandPRO(UpdateString, check);
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
 * @brief 数据上传初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Update_InitPro(void)
{
}
