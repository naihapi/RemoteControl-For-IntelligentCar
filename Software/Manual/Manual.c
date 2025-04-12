#include "Manual.h"

uint8_t Manual_State_Left = 0;        // 左转状态
uint8_t Manual_State_Right = 0;       // 右转状态
uint8_t Manual_State_Front = 0;       // 前进状态
uint8_t Manual_State_Rear = 0;        // 后退状态
uint8_t Manual_Init_Flag = 0;         // 初始化标志位(1：已初始化，0：未初始化)
uint8_t Manual_UpdateToCar_Flag = 0;  // 上传数据标志位(1：允许上传，0：不允许上传)
uint8_t Manual_Name[] = "Manual";     // 手动控制名称
uint8_t Manual_State_ON[] = "#ON";     // 状态打开关键字
uint8_t Manual_State_OFF[] = "#OFF";   // 状态关闭关键字
uint8_t Manual_CheckSuccess[] = "OK"; // 比对成功关键字

/**
 * @brief 连接到车体
 *
 * @param 无
 *
 * @retval 1 连接成功，其它返回为失败
 *
 * @note 无
 */
uint8_t Manual_ConnectToCat(void)
{
    // 请求包赋值为"Manual_State_ON"
    uint8_t *DataPack[1] = {Manual_State_ON};
    uint8_t result = 0;

    // 发送请求
    result = POST_Currency(Manual_Name, 1, DataPack, Manual_CheckSuccess);

    return result;
}

/**
 * @brief 断开到车体的连接
 *
 * @param 无
 *
 * @retval 1 断开成功，其它返回为失败
 *
 * @note 无
 */
uint8_t Manual_DisconnectToCat(void)
{
    // 请求包赋值为"Manual_State_OFF"
    uint8_t *DataPack[1] = {Manual_State_OFF};
    uint8_t result = 0;

    // 发送请求
    result = POST_Currency(Manual_Name, 1, DataPack, Manual_CheckSuccess);

    return result;
}

/**
 * @brief 采集转向状态并上传
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Manual_TurnState_UpdateToCar(void)
{
    if (Manual_UpdateToCar_Flag == 0)
        return;

    // 转向状态转为字符串
    uint8_t LeftState_String[3] = {0};
    uint8_t RightState_String[2] = {0};
    uint8_t FrontState_String[2] = {0};
    uint8_t RearState_String[2] = {0};
    sprintf((char *)LeftState_String, "#%d", !Manual_State_Left);
    sprintf((char *)RightState_String, "%d", !Manual_State_Right);
    sprintf((char *)FrontState_String, "%d", !Manual_State_Front);
    sprintf((char *)RearState_String, "%d", !Manual_State_Rear);
    uint8_t *DataPack[4] = {LeftState_String, RightState_String, FrontState_String, RearState_String};

    // 上传数据
    Update_Currency(Manual_Name, 4, DataPack, NULL);

    vTaskDelay(100);
}

/**
 * @brief 获取当前按键状态
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 仅获取按下或未按下
 */
void Manual_KEYevent_GetState_Turn(void)
{
    Manual_State_Left = GPIO_RetState_KEY1();
    Manual_State_Right = GPIO_RetState_KEY2();
    Manual_State_Front = GPIO_RetState_KEY3();
    Manual_State_Rear = GPIO_RetState_KEY4();
}

/**
 * @brief 退出手动控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 四个按键都按下，且按下事件超过100ms，表示退出
 * @note 退出时，将进入一个退出提示页面，并向车体发生退出消息
 */
void Manual_KEYevent_Exit(void)
{
    // 退出手动控制
    if (Manual_State_Left == 0 && Manual_State_Right == 0 && Manual_State_Front == 0 && Manual_State_Rear == 0)
    {
        vTaskDelay(100);
        if (Manual_State_Left == 0 && Manual_State_Right == 0 && Manual_State_Front == 0 && Manual_State_Rear == 0)
        {
            uint8_t result = 0;

            UI_Display_ExitTips();       // 渲染退出提示
            vTaskResume(TASK5_Handler);  // 恢复OLED刷新任务
            Manual_UpdateToCar_Flag = 0; // 关闭上传数据

            vTaskDelay(100); // 等待100ms

            result = Manual_DisconnectToCat(); // 发送断开请求

            if (result == 0)
            {
                UI_Display_TipsFail();      // 渲染错误提示
                vTaskResume(TASK5_Handler); // 恢复OLED刷新任务
                vTaskDelay(1000);           // 等待1000ms

                Manual_UpdateToCar_Flag = 1; // 打开上传数据

                return;
            }

            KEY_KEYScanf_Enable(); // 打开按键事件监测
            Manual_Init_Flag = 0;  // 设为未初始化
            Build_NowPage = 2;     // 切换到菜单页
        }
    }
}

/**
 * @brief 手动控制按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Manual_KEYevent(void)
{
    // 获取转向状态
    Manual_KEYevent_GetState_Turn();

    // 监测退出手动控制的状态
    Manual_KEYevent_Exit();
}

/**
 * @brief 手动控制初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Manual_InitPro(void)
{
    // 初始化（每次进入此页，都需要执行一次）
    if (Manual_Init_Flag == 0)
    {
        uint8_t result = 0;

        KEY_KEYScanf_Disable(); // 关闭按键事件监测

        UI_Display_TipsInto();      // 渲染进入提示
        vTaskResume(TASK5_Handler); // 恢复OLED刷新任务

        vTaskDelay(100); // 等待100ms

        result = Manual_ConnectToCat(); // 发送连接请求

        if (result == 0)
        {
            UI_Display_TipsFail();      // 渲染错误提示
            vTaskResume(TASK5_Handler); // 恢复OLED刷新任务
            vTaskDelay(1000);           // 等待1000ms

            KEY_KEYScanf_Enable(); // 打开按键事件监测
            Build_NowPage = 2;     // 切换到菜单页

            return;
        }

        Manual_Init_Flag = 1;        // 标志位设为已初始化
        Manual_UpdateToCar_Flag = 1; // 打开上传数据
    }
}

/**
 * @brief 手动控制的钩子函数
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数在创建自定义组件时，包含在内
 */
void Manual_CustomFunction(void)
{
    // 初始化
    Manual_InitPro();

    // 按键事件
    Manual_KEYevent();

    // 界面绘制
    UI_Display_ManualControl(!Manual_State_Left, !Manual_State_Right, !Manual_State_Front, !Manual_State_Rear);
}
