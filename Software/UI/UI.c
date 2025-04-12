#include "UI.h"

/**
 * @brief 计数整型长度
 *
 * @param 整型参数传入
 *
 * @retval 数据长度
 *
 * @note 无
 */
int digitLength(int num)
{
    if (num == 0)
    {
        return 1; // 特殊情况，0的长度为1
    }
    return (int)floor(log10(abs(num))) + 1;
}

/**
 * @brief 主页显示
 *
 * @param select 当前选中的项
 * @param head 主页的链表头
 *
 * @retval 无
 *
 * @note 展示内容：描述此主页的标题、主页的图标、图标框、当前页和总计页
 * @note 主页最大项取决于Menu_MaxItem_Home
 */
void UI_Display_Home(uint8_t selected, struct MenuHome *head)
{
    MenuHome *current;

    // 选择项超过最大项时，退出函数
    if (selected > Menu_MaxItem_Home)
        return;

    // 清空屏幕
    OLED_Clear();

    // 返回单个主页项
    current = Menu_RetHomeItem(head, selected);

    // 显示标题、图标、图标框
    OLED_ShowString(1, 0, (char *)current->Title, OLED_8X16);
    OLED_ShowImage(1, 20, 80, 40, current->Icon);
    OLED_DrawRectangle(1, 20, 80, 40, OLED_UNFILLED);

    // 主页项和总主页项显示
    OLED_ShowNum(97, 10, selected, 2, OLED_8X16);
    OLED_ShowString(100, 28, (char *)"/", OLED_6X8);
    OLED_ShowNum(97, 36, Menu_MaxItem_Home, 2, OLED_8X16);
}

/**
 * @brief 菜单显示
 *
 * @param selected 被选中的项(从1开始)
 * @param head 菜单链表头
 * @param maxitem 当前菜单最大的项
 *
 * @retval 无
 *
 * @note 展示内容：描述此菜单的标题、当前页码、菜单项的图标、图标框、菜单项的描述字符、当前选中或未选中的菜单项
 * @note 一次只展示两个菜单项，详见语雀（智能车->功能实现->定义划分和结构体定义V2.0）
 */
void UI_Display_Menu(uint8_t selected, struct MenuItem *head, uint8_t maxitem)
{
    MenuItem *current;

    // 清空屏幕
    OLED_Clear();

    // 渲染常规项目
    OLED_ShowString(1, 0, (char *)head->Title, OLED_8X16); // 标题
    OLED_ShowString(96, 0, (char *)"-", OLED_6X8);         // 分割线
    OLED_ShowString(120, 0, (char *)"-", OLED_6X8);        // 分割线
    OLED_ShowNum(104, 0, selected, 2, OLED_8X16);          // 当前项
    OLED_DrawRectangle(110, 22, 12, 12, OLED_UNFILLED);    // 选择框1
    OLED_DrawRectangle(110, 43, 12, 12, OLED_UNFILLED);    // 选择框2

    if (selected == maxitem && selected % 2 == 1)
    {
        // 被选中项为最大且是奇数
        current = Menu_RetMenuItem(head, selected); // 获取菜单项

        OLED_ShowImage(1, 18, 20, 20, current->Icon);     // 渲染菜单图标
        OLED_DrawRectangle(1, 18, 20, 20, OLED_UNFILLED); // 图标框

        OLED_ShowString(23, 20, (char *)current->Title, OLED_8X16); // 渲染标题

        OLED_DrawRectangle(110, 22, 12, 12, OLED_FILLED);   // 选择框1
        OLED_ClearArea(110, 43, 12, 12);                    // 清除选择框2
        OLED_ShowString(48, 45, (char *)"-End-", OLED_6X8); // 提示符
    }
    else if (selected % 2 == 0)
    {
        // 被选中项为偶数
        current = Menu_RetMenuItem(head, selected); // 获取菜单项

        OLED_ShowImage(1, 40, 20, 20, current->Icon);     // 渲染菜单图标
        OLED_DrawRectangle(1, 40, 20, 20, OLED_UNFILLED); // 图标框

        OLED_ShowString(23, 42, (char *)current->Title, OLED_8X16); // 渲染标题

        current = current->Last; // 偏移到上1项

        OLED_DrawRectangle(110, 43, 12, 12, OLED_FILLED); // 选择框2

        OLED_ShowImage(1, 18, 20, 20, current->Icon);     // 渲染菜单图标
        OLED_DrawRectangle(1, 18, 20, 20, OLED_UNFILLED); // 图标框

        OLED_ShowString(23, 20, (char *)current->Title, OLED_8X16); // 渲染标题
    }
    else if (selected % 2 == 1)
    {
        // 被选中项为奇数
        current = Menu_RetMenuItem(head, selected); // 获取菜单项

        OLED_ShowImage(1, 18, 20, 20, current->Icon);     // 渲染菜单图标
        OLED_DrawRectangle(1, 18, 20, 20, OLED_UNFILLED); // 图标框

        OLED_ShowString(23, 20, (char *)current->Title, OLED_8X16); // 渲染标题
        OLED_DrawRectangle(110, 22, 12, 12, OLED_FILLED);           // 选择框1

        current = current->Next; // 偏移到下1项

        OLED_ShowImage(1, 40, 20, 20, current->Icon);     // 渲染菜单图标
        OLED_DrawRectangle(1, 40, 20, 20, OLED_UNFILLED); // 图标框

        OLED_ShowString(23, 42, (char *)current->Title, OLED_8X16); // 渲染标题
    }
}

/**
 * @brief 视图界面
 *
 * @param Title 窗口标题
 * @param Description 描述字符
 * @param Value 描述数值
 *
 * @retval 无
 *
 * @note 展示内容：描述此组件的标题、描述字符、描述数值、数值
 * @note 详见语雀（智能车->功能实现->定义划分和结构体定义V2.0）
 */
void UI_Display_ViewModule(uint8_t *Title, uint8_t *Description, int *Value)
{
    // 清空屏幕
    OLED_Clear();

    OLED_DrawRectangle(2, 2, 125, 61, OLED_UNFILLED); // 绘制窗口边框
    OLED_ShowString(15, 0, (char *)Title, OLED_6X8);  // 标题

    OLED_ShowString(10, 17, (char *)"description:", OLED_6X8); // 提示符
    OLED_ShowString(10, 38, (char *)"value:", OLED_6X8);       // 提示符

    OLED_ShowString(83, 17, (char *)Description, OLED_6X8); // 描述
    OLED_ShowSignedNum(55, 32, *Value, 5, OLED_8X16);       // 数值
}

/**
 * @brief 滑块界面
 *
 * @param Title 窗口标题
 * @param NowValue 当前值
 * @param MaxValue 最大值
 * @param MiniValue 最小值
 * @param Unit 单位
 * @param Selected 选中项(1：now，2：max，3：mini)
 *
 * @retval 无
 *
 * @note 展示内容：描述此组件的标题、最大值、最小值、当前值、滑块、提示箭头
 * @note 提示条绘制算法：始终从0开始，max-mini=真实长度，now-mini=真实进度
 * @note 负数比较难写，就先不写了
 */
void UI_Display_SliderModule(uint8_t *Title, int *NowValue, int *MaxValue, int *MiniValue, uint8_t *Unit, uint8_t Selected)
{
    uint8_t Y = 0;                      // y轴坐标
    int real = *MaxValue - *MiniValue;  // 提示条真实长度
    int value = *NowValue - *MiniValue; // 提示条真实进度
    uint8_t width = (float)value / (float)real * 110.0;

    // 清空屏幕
    OLED_Clear();

    OLED_DrawRectangle(2, 2, 125, 61, OLED_UNFILLED); // 绘制窗口边框
    OLED_ShowString(15, 0, (char *)Title, OLED_6X8);  // 标题
    OLED_ShowString(15, 56, (char *)Unit, OLED_6X8);  // 单位

    // 如果有负数，不绘制提示条
    if (*NowValue < 0 || *MaxValue < 0 || *MiniValue < 0)
    {
        Y = 18;
    }
    else
    {
        Y = 10;

        OLED_DrawRectangle(10, 42, 110, 10, OLED_UNFILLED); // 提示条边框
        OLED_DrawRectangle(10, 42, width, 10, OLED_FILLED); // 提示条填充(110为提示条全长)
    }

    OLED_ShowString(45, Y, (char *)"now:", OLED_6X8);       // 提示符
    OLED_ShowString(45, Y + 10, (char *)"max:", OLED_6X8);  // 提示符
    OLED_ShowString(45, Y + 20, (char *)"mini:", OLED_6X8); // 提示符

    OLED_ShowSignedNum(75, Y, *NowValue, digitLength(*NowValue), OLED_6X8);        // 最小值
    OLED_ShowSignedNum(75, Y + 10, *MaxValue, digitLength(*MaxValue), OLED_6X8);   // 最大值
    OLED_ShowSignedNum(75, Y + 20, *MiniValue, digitLength(*MiniValue), OLED_6X8); // 最小值

    switch (Selected)
    {
    case 1: // 箭头在当前值
        OLED_ShowString(30, Y, "->", OLED_6X8);
        break;

    case 2: // 箭头在最大值
        OLED_ShowString(30, Y + 10, "->", OLED_6X8);
        break;

    case 3: // 箭头在最小值
        OLED_ShowString(30, Y + 20, "->", OLED_6X8);
        break;
    }
}

/**
 * @brief 开关界面
 *
 * @param Title 窗口标题
 * @param State 开关状态(1或0)
 *
 * @retval 无
 *
 * @note 展示内容：描述此组件的标题、打开或关闭的提示方块
 */
void UI_Display_SwitchModule(uint8_t *Title, uint8_t *State)
{
    // 清空屏幕
    OLED_Clear();

    OLED_DrawRectangle(2, 2, 125, 61, OLED_UNFILLED); // 绘制窗口边框
    OLED_ShowString(15, 0, (char *)Title, OLED_6X8);  // 标题

    if (*State == 1)
    {
        OLED_DrawRectangle(15, 15, 30, 40, OLED_UNFILLED); // 绘制开关框
        OLED_ShowString(23, 25, (char *)"ON", OLED_8X16);  // 提示符
    }
    else if (*State == 0)
    {
        OLED_DrawRectangle(44, 15, 70, 40, OLED_UNFILLED); // 绘制开关框
        OLED_ShowString(67, 25, (char *)"OFF", OLED_8X16); // 提示符
    }
}

/**
 * @brief 数据请求等待界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 展示内容：提示符、图标
 * @note 提示符：请求数据...
 * @note 向车体请求数据时，会显示此界面以表示等待，直到收到数据为止
 */
void UI_Display_Requesting(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_Request);    // 图标
    OLED_ShowString(10, 50, "Requesting Data...", OLED_6X8); // 提示符
}

/**
 * @brief 数据请求成功界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 展示内容：提示符、图标
 * @note 提示符：数据请求成功！
 */
void UI_Display_RequestSuccess(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_RequestSuccess); // 图标
    OLED_ShowString(15, 50, "Request Success!", OLED_6X8);       // 提示符
}

/**
 * @brief 数据请求失败界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 展示内容：提示符、图标
 * @note 提示符：请求失败了！
 */
void UI_Display_RequestFail(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_RequestFail); // 图标
    OLED_ShowString(20, 50, "Request Failed!", OLED_6X8);     // 提示符
}

/**
 * @brief 数据更新等待界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 图标沿用：数据请求等待图标
 * @note 展示内容：提示符、图标
 * @note 提示符：上传数据...
 */
void UI_Display_Uploading(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_Request);   // 图标
    OLED_ShowString(15, 50, "Uploading Data...", OLED_6X8); // 提示符
}

/**
 * @brief 数据更新成功界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 图标沿用：数据请求成功图标
 * @note 展示内容：提示符、图标
 * @note 提示符：上传成功！
 */
void UI_Display_UpdateSuccess(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_RequestSuccess); // 图标
    OLED_ShowString(15, 50, "Update Success!", OLED_6X8);        // 提示符
}

/**
 * @brief 数据更新失败界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 图标沿用：数据请求失败图标
 * @note 展示内容：提示符、图标
 * @note 提示符：上传失败了！
 */
void UI_Display_UpdateFail(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_RequestFail); // 图标
    OLED_ShowString(20, 50, "Update Failed!", OLED_6X8);      // 提示符
}

/**
 * @brief 手动控制的角标绘制
 *
 * @param left 左旋转标志位
 * @param right 右旋转标志位
 * @param front 向前标志位
 * @param rear 后退标志位
 *
 * @retval 无
 *
 * @note 无
 */
void UI_Display_ManualControl_Cornor(uint8_t left, uint8_t right, uint8_t front, uint8_t rear)
{
    // 方向角标-左
    switch (left)
    {
    case 0:
    {
        OLED_ClearArea(2, 56, 6, 6);
    }
    break;

    case 1:
    {
        OLED_ShowImage(1, 56, 6, 6, OLEDData_ManualCorner);
    }
    break;
    }

    // 方向角标-右
    switch (right)
    {
    case 0:
    {
        OLED_ClearArea(33, 56, 6, 6);
    }
    break;

    case 1:
    {
        OLED_ShowImage(32, 56, 6, 6, OLEDData_ManualCorner);
    }
    break;
    }

    // 方向角标-前
    switch (front)
    {
    case 0:
    {
        OLED_ClearArea(66, 56, 6, 6);
    }
    break;

    case 1:
    {
        OLED_ShowImage(65, 56, 6, 6, OLEDData_ManualCorner);
    }
    break;
    }

    // 方向角标-后
    switch (rear)
    {
    case 0:
    {
        OLED_ClearArea(98, 56, 6, 6);
    }
    break;

    case 1:
    {
        OLED_ShowImage(97, 56, 6, 6, OLEDData_ManualCorner);
    }
    break;
    }
}

/**
 * @brief 手动控制界面
 *
 * @param left 左旋转标志位
 * @param right 右旋转标志位
 * @param front 向前标志位
 * @param rear 后退标志位
 *
 * @retval 无
 *
 * @note 无
 */
void UI_Display_ManualControl(uint8_t left, uint8_t right, uint8_t front, uint8_t rear)
{
    // 清空屏幕
    OLED_Clear();

    // 字符框
    OLED_DrawRectangle(1, 1, 126, 20, OLED_UNFILLED);

    // 提示符
    OLED_ShowString(20, 7, "Manual Control", OLED_6X8);

    // 方向框
    OLED_DrawRectangle(1, 22, 30, 41, OLED_UNFILLED);
    OLED_DrawRectangle(32, 22, 32, 41, OLED_UNFILLED);
    OLED_DrawRectangle(65, 22, 31, 41, OLED_UNFILLED);
    OLED_DrawRectangle(97, 22, 30, 41, OLED_UNFILLED);

    // 箭头
    OLED_ShowImage(6, 33, 20, 20, OLEDData_ManualLeft);
    OLED_ShowImage(38, 33, 20, 20, OLEDData_ManualRitght);
    OLED_ShowImage(70, 33, 20, 20, OLEDData_ManualFront);
    OLED_ShowImage(102, 33, 20, 20, OLEDData_ManualRear);

    // 方向角标
    UI_Display_ManualControl_Cornor(left, right, front, rear);
}

/**
 * @brief 退出的提示界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此为通用界面，可以放置在需要的界面
 */
void UI_Display_ExitTips(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Exit);     // 图标
    OLED_ShowString(33, 50, "Aborting...", OLED_6X8); // 提示符
}

/**
 * @brief 进入的提示界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此为通用界面，可以放置在需要的界面
 */
void UI_Display_TipsInto(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Into);       // 图标
    OLED_ShowString(25, 50, "Be Opening...", OLED_6X8); // 提示符
}

/**
 * @brief 失败的提示界面
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此为通用界面，可以放置在需要的界面
 */
void UI_Display_TipsFail(void)
{
    // 清空屏幕
    OLED_Clear();

    OLED_ShowImage(45, 3, 40, 40, OLEDData_Icon_RequestFail); // 图标
    OLED_ShowString(43, 50, "Failed!", OLED_6X8);             // 提示符
}

/**
 * @brief UI设计初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 开机界面
 */
void UI_InitPro(void)
{
    OLED_ShowImage(46, 5, 35, 35, OLEDData_Icon_Welcome);
    OLED_ShowString(23, 45, "Remote Control", OLED_6X8);
    OLED_ShowString(30, 45 + 9, "-By naihapi-", OLED_6X8);

    vTaskResume(TASK5_Handler);
    vTaskDelay(1000);
}
