#include "Build.h"

uint8_t Build_CNT_HomeItem = 1;     // 主页项计数
uint8_t Build_CNT_MenuItem = 1;     // 菜单项计数
uint8_t Build_CNT_SliderModule = 1; // 滑块组件计数(1~3,1：当前值，2：最大值，3：最小值)
uint8_t Build_NowPage = 1;          // 当前所处页(1：主页，2：菜单页，3：请求页，4：组件页，5：上传页，6：自定义页)
MenuHome *Build_NowHomeItem;        // 当前所处主页项
MenuItem *Build_NowMenuItem;        // 当前所处菜单项

/**
 * @brief 计数目标限幅
 *
 * @param target 目标值
 * @param now 当前值
 *
 * @retval 限幅后的值
 *
 * @note 返回的最小值为1
 */
uint8_t Build_Limit(uint8_t target, uint8_t now)
{
    if (now > target)
    {
        // 如果now大于target，则限制为target
        return target;
    }
    else if (now <= 0)
    {
        // 如果now小于等于0，则限制为1
        return 1;
    }
    else
    {
        // 如果now在范围内，则保持原值
        return now;
    }
}

/**
 * @brief 页面切换
 *
 * @param datahandle_flag 数据处理标志位(SliderModule_xxxSetting)
 * @param nowpage 当前页(Build_NowPage)
 *
 * @retval 无
 *
 * @note 根据数据处理标志位进行页面切换，指定菜单页的下一页，或组件页的上一页
 * @note 菜单页->请求页/组件页
 * @note 组件页->上传页/菜单页
 */
void Build_PageSwitching(uint8_t datahandle_flag, uint8_t *nowpage)
{
    // 组件类型为自定义型
    if (Build_NowMenuItem->ItemType == ItemType_Custom)
    {
        *nowpage = 6;
        return;
    }

    if (*nowpage == 2)
    {
        switch (datahandle_flag)
        {
        case Datahandle_None:
        {
            // 不处理，进入组件页
            *nowpage = 4;
        }
        break;

        case DataHandle_OnlyRequest:
        {
            // 无论是仅请求、还是上传请求都需要，都进入请求页
            *nowpage = 3;
        }
        break;

        case DataHandle_UpdateANDRequest:
        {
            // 无论是仅请求、还是上传请求都需要，都进入请求页
            *nowpage = 3;
        }
        break;
        }
    }
    else if (*nowpage == 4)
    {
        // 选择组件页的上一页（上传页或菜单页）
        switch (datahandle_flag)
        {
        case Datahandle_None:
        {
            // 不处理，返回菜单页
            *nowpage = 2;
        }
        break;

        case DataHandle_OnlyUpdate:
        {
            // 无论是仅上传、还是上传请求都需要，都进入上传页
            *nowpage = 5;
        }
        break;

        case DataHandle_UpdateANDRequest:
        {
            // 无论是仅上传、还是上传请求都需要，都进入上传页
            *nowpage = 5;
        }
        break;
        }
    }

    // 根据标志位，判断是否需要处理数据
}

/**
 * @brief 主页按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 主页的按键控制逻辑汇总
 */
void Build_HomeControl_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY1_State == 1) // KEY1短按事件
    {
        Build_NowPage = 2; // 切换到菜单页

        Build_NowMenuItem = Menu_RetMenuItem(Build_NowHomeItem->Menu, Build_CNT_MenuItem); // 更新当前菜单项

        KEY1_State = 0; // 清除状态
    }
    if (KEY3_State == 1) // KEY3短按事件
    {
        Build_CNT_HomeItem--;                                                    // 主页项减少1
        Build_CNT_HomeItem = Build_Limit(Menu_MaxItem_Home, Build_CNT_HomeItem); // 限幅

        Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, Build_CNT_HomeItem); // 更新当前主页项

        KEY3_State = 0; // 清除状态
    }
    if (KEY4_State == 1) // KEY4短按事件
    {
        Build_CNT_HomeItem++;                                                    // 主页项增加1
        Build_CNT_HomeItem = Build_Limit(Menu_MaxItem_Home, Build_CNT_HomeItem); // 限幅

        Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, Build_CNT_HomeItem); // 更新当前主页项

        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY1_State == 2 || KEY2_State == 2 || KEY3_State == 2 || KEY4_State == 2) // KEY1、KEY2、KEY3、KEY4长按事件
    {
        KEY1_State = 0; // 清除状态
        KEY2_State = 0; // 清除状态
        KEY3_State = 0; // 清除状态
        KEY4_State = 0; // 清除状态
    }
    if (KEY2_State == 1) // KEY2短按事件
    {
        KEY2_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 主页控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_HomeControl(void)
{
    // 主页按键控制
    Build_HomeControl_KEYevent();

    // 主页渲染
    UI_Display_Home(Build_CNT_HomeItem, Menu_Head_Home);
}

/**
 * @brief 菜单按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 菜单的按键控制逻辑汇总
 */
void Build_MenuControl_KEYevent(void)
{
    int8_t *maxitem = Build_NowHomeItem->MaxItem; // 获取最大项

    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY1_State == 1) // KEY1短按事件
    {
        Build_PageSwitching(Build_NowMenuItem->DataHandle, &Build_NowPage);

        KEY1_State = 0; // 清除状态
    }
    if (KEY2_State == 1) // KEY2短按事件
    {
        Build_NowPage = 1; // 切换到主页

        Build_CNT_MenuItem = 1; // 菜单项计数初始化

        KEY2_State = 0; // 清除状态
    }
    if (KEY3_State == 1) // KEY3短按事件
    {
        Build_CNT_MenuItem--;                                           // 主页项减少1
        Build_CNT_MenuItem = Build_Limit(*maxitem, Build_CNT_MenuItem); // 限幅

        Build_NowMenuItem = Menu_RetMenuItem(Build_NowHomeItem->Menu, Build_CNT_MenuItem); // 更新当前菜单项

        KEY3_State = 0; // 清除状态
    }
    if (KEY4_State == 1) // KEY4短按事件
    {
        Build_CNT_MenuItem++;                                           // 主页项增加1
        Build_CNT_MenuItem = Build_Limit(*maxitem, Build_CNT_MenuItem); // 限幅

        Build_NowMenuItem = Menu_RetMenuItem(Build_NowHomeItem->Menu, Build_CNT_MenuItem); // 更新当前菜单项

        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY1_State == 2) // KEY1短按事件
    {
        KEY1_State = 0; // 清除状态
    }
    if (KEY2_State == 2) // KEY2短按事件
    {
        KEY2_State = 0; // 清除状态
    }
    if (KEY3_State == 2) // KEY3短按事件
    {
        KEY3_State = 0; // 清除状态
    }
    if (KEY4_State == 2) // KEY4短按事件
    {
        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 菜单控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_MenuControl(void)
{
    // 菜单按键控制
    Build_MenuControl_KEYevent();

    // 获取当前主页项和最大项
    MenuItem *current = Build_NowHomeItem->Menu;
    int8_t *maxitem = Build_NowHomeItem->MaxItem;

    // 菜单渲染
    UI_Display_Menu(Build_CNT_MenuItem, current, *maxitem);
}

/**
 * @brief 开关组件请求数据
 *
 * @param 无
 *
 * @retval 1 获取成功
 * @retval 0 获取失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_RequestControl_SwitchModule(void)
{
    uint8_t Result = 0; // 请求结果

    Menu_SwitchModule *switchmodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的开关组件
    uint8_t *state = switchmodule->State;                             // 获取开关组件的当前状态

    Result = POST_SwitchModule(Build_NowMenuItem->Name, state); // 发送请求

    if (Result == 1)
    {
        // 获取成功
        return 1;
    }

    // 获取失败
    return 0;
}

/**
 * @brief 视图组件请求数据
 *
 * @param 无
 *
 * @retval 1 获取成功
 * @retval 0 获取失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_RequestControl_ViewModule(void)
{
    uint8_t Result = 0; // 请求结果

    Menu_ViewModule *viewmodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的视图组件
    int *value = viewmodule->Value;                               // 获取视图组件的数值

    Result = POST_ViewModule(Build_NowMenuItem->Name, value); // 发送请求

    if (Result == 1)
    {
        // 获取成功
        return 1;
    }

    // 获取失败
    return 0;
}

/**
 * @brief 滑块组件请求数据
 *
 * @param 无
 *
 * @retval 1 获取成功
 * @retval 0 获取失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_RequestControl_SliderModule(void)
{
    uint8_t Result = 0; // 请求结果

    Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的滑块组件
    int *nowvalue = slidermodule->NowValue;                           // 获取当前值
    int *maxvalue = slidermodule->MaxValue;                           // 获取最大值
    int *minivalue = slidermodule->MiniValue;                         // 获取最小值

    Result = POST_SliderModule(Build_NowMenuItem->Name, nowvalue, maxvalue, minivalue);

    if (Result == 1)
    {
        // 获取成功
        return 1;
    }

    // 获取失败
    return 0;
}

/**
 * @brief 发出请求
 *
 * @param 无
 *
 * @retval 1 获取成功
 * @retval 0 获取失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_RequestControl_Requesting(void)
{
    uint8_t Result = 0;                           // 请求结果
    uint8_t module = Build_NowMenuItem->ItemType; // 获取当前组件

    switch (module)
    {
    case ItemType_Switch:
        Result = Build_RequestControl_SwitchModule();
        break;

    case ItemType_View:
        Result = Build_RequestControl_ViewModule();
        break;

    case ItemType_Slider:
        Result = Build_RequestControl_SliderModule();
        break;
    }

    return Result;
}

/**
 * @brief 请求/上传按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 请求页/上传页共用的按键控制逻辑汇总
 * @note 需要为此函数独立分配一个任务
 * @note 请求/上传过程中，恢复此任务；请求完成后，挂起此任务
 */
void Build_RequestUpdateControl_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY1_State == 1 || KEY2_State == 1 || KEY3_State == 1 || KEY4_State == 1) // KEY1、KEY2、KEY3、KEY4短按事件
    {
        KEY1_State = 0; // 清除状态
        KEY2_State = 0; // 清除状态
        KEY3_State = 0; // 清除状态
        KEY4_State = 0; // 清除状态
    }

    if (KEY1_State == 2 || KEY2_State == 2 || KEY3_State == 2 || KEY4_State == 2) // KEY1、KEY2、KEY3、KEY4长按事件
    {
        KEY1_State = 0; // 清除状态
        KEY2_State = 0; // 清除状态
        KEY3_State = 0; // 清除状态
        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 请求控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 从菜单进入此页时，调用请求控制
 */
void Build_RequestControl(void)
{
    uint8_t result = 0; // 请求结果

    UI_Display_Requesting(); // 渲染请求等待界面

    vTaskResume(TASK5_Handler);  // 恢复OLED刷新任务
    vTaskResume(TASK15_Handler); // 请求时按键控制

    result = Build_RequestControl_Requesting(); // 开始请求，等待请求结果

    if (result == 0) // 请求失败
    {
        UI_Display_RequestFail();   // 渲染请求失败界面
        vTaskResume(TASK5_Handler); // 恢复OLED刷新任务

        // 等待3秒，挂起请求按键控制任务，切换到菜单页
        vTaskDelay(3000);
        vTaskSuspend(TASK15_Handler);
        Build_NowPage = 2;
    }
    else if (result == 1) // 请求成功
    {
        UI_Display_RequestSuccess(); // 渲染请求成功界面
        vTaskResume(TASK5_Handler);  // 恢复OLED刷新任务

        // 等待3秒，挂起请求按键控制任务，切换到组件页
        vTaskDelay(3000);
        vTaskSuspend(TASK15_Handler);
        Build_NowPage = 4;
    }
}

/**
 * @brief 开关组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 开关组件可以切换状态，退出组件需要进入上传页
 */
void Build_ModuleControl_Switch_KEYevent(void)
{
    Menu_SwitchModule *switchmodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的开关组件
    uint8_t *state = switchmodule->State;                             // 获取开关组件的当前状态

    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY2_State == 1) // KEY2短按事件
    {
        Build_PageSwitching(Build_NowMenuItem->DataHandle, &Build_NowPage);

        KEY2_State = 0; // 清除状态
    }
    if (KEY3_State == 2) // KEY3长按事件
    {
        *state = 1; // 打开

        KEY3_State = 0; // 清除状态
    }
    if (KEY4_State == 2) // KEY4长按事件
    {
        *state = 0; // 关闭

        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY1_State == 1) // KEY1短按事件
    {
        KEY1_State = 0; // 清除状态
    }
    if (KEY1_State == 2) // KEY1长按事件
    {
        KEY1_State = 0; // 清除状态
    }
    if (KEY2_State == 2) // KEY2长按事件
    {
        KEY2_State = 0; // 清除状态
    }
    if (KEY3_State == 1) // KEY3短按事件
    {
        KEY3_State = 0; // 清除状态
    }
    if (KEY4_State == 1) // KEY4短按事件
    {
        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 视图组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 视图组件只用于查看数据，不需要进入上传页
 */
void Build_ModuleControl_View_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY2_State == 1) // KEY2短按事件
    {
        Build_NowPage = 2; // 切换到菜单页

        KEY2_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY1_State == 1 || KEY3_State == 1 || KEY4_State == 1) // KEY1、KEY3、KEY4短按事件
    {
        KEY1_State = 0; // 清除状态
        KEY3_State = 0; // 清除状态
        KEY4_State = 0; // 清除状态
    }

    if (KEY1_State == 2 || KEY2_State == 2 || KEY3_State == 2 || KEY4_State == 2) // KEY1、KEY2、KEY3、KEY4长按事件
    {
        KEY1_State = 0; // 清除状态
        KEY2_State = 0; // 清除状态
        KEY3_State = 0; // 清除状态
        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 滑块组件按键3事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 按键3的短按事件
 */
void Build_ModuleControl_Slider_KEYevent_KEY3(void)
{
    Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer;
    int *now = slidermodule->NowValue;
    int *max = slidermodule->MaxValue;
    int *mini = slidermodule->MiniValue;

    switch (Build_CNT_SliderModule)
    {
    case 1:
    {
        *now -= 1; // 增加数值

        if (*now < *mini) // 限幅
        {
            *now += 1;
        }
    }
    break;

    case 2:
    {
        *max -= 1; // 减少数值

        if (*max < *now) // 限幅
        {
            *max += 1;
        }
    }
    break;

    case 3:
    {
        *mini -= 1;
    }
    break;
    }
}

/**
 * @brief 滑块组件按键4事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 按键4的短按事件
 */
void Build_ModuleControl_Slider_KEYevent_KEY4(void)
{
    Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer;
    int *now = slidermodule->NowValue;
    int *max = slidermodule->MaxValue;
    int *mini = slidermodule->MiniValue;

    switch (Build_CNT_SliderModule)
    {
    case 1:
    {
        *now += 1; // 增加数值

        // 限幅
        if (*now > *max)
        {
            *now -= 1;
        }
    }
    break;

    case 2:
    {
        *max += 1; // 增加数值
    }
    break;

    case 3:
    {
        *mini += 1; // 增加数值

        if (*mini > *now)
        {
            *mini -= 1;
        }
    }
    break;
    }
}

/**
 * @brief 滑块组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_ModuleControl_Slider_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY2_State == 1) // KEY2短按事件
    {
        Build_PageSwitching(Build_NowMenuItem->DataHandle, &Build_NowPage);

        KEY2_State = 0; // 清除状态
    }
    if (KEY3_State == 1) // KEY3短按事件
    {
        Build_ModuleControl_Slider_KEYevent_KEY3();

        KEY3_State = 3; // 清除状态
    }
    if (KEY4_State == 1) // KEY4短按事件
    {
        Build_ModuleControl_Slider_KEYevent_KEY4();

        KEY4_State = 0; // 清除状态
    }
    if (KEY3_State == 2) // KEY3长按事件
    {
        // 获取当前主页标题，判断当前菜单是否为系统菜单(系统菜单无需滑块长按事件)
        // 例如：屏幕显示亮度调节时，不可增加最大亮度
        uint8_t *str = Build_NowHomeItem->Title;
        if (strstr((const char *)str, (const char *)Menu_Title_System) != NULL)
        {
        }
        else
        {
            Build_CNT_SliderModule--;                                        // 更新选中项
            Build_CNT_SliderModule = Build_Limit(3, Build_CNT_SliderModule); // 限幅
        }

        KEY3_State = 0; // 清除状态
    }
    if (KEY4_State == 2) // KEY4长按事件
    {
        // 获取当前菜单项标题，判断当前菜单是否为系统菜单(系统菜单无需滑块长按事件)
        uint8_t *str = Build_NowHomeItem->Title;
        if (strstr((const char *)str, (const char *)Menu_Title_System) != NULL)
        {
        }
        else
        {
            Build_CNT_SliderModule++;                                        // 更新选中项
            Build_CNT_SliderModule = Build_Limit(3, Build_CNT_SliderModule); // 限幅
        }

        KEY4_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY1_State == 1) // KEY1短按事件
    {
        KEY1_State = 0; // 清除状态
    }

    if (KEY1_State == 2 || KEY2_State == 2) // KEY1、KEY2长按事件
    {
        KEY1_State = 0; // 清除状态
        KEY2_State = 0; // 清除状态
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 组件的按键控制逻辑汇总
 * @note 每个组件对应的按键事件都不一样，需要各写一个函数
 */
void Build_ModuleControl_KEYevent(void)
{
    uint8_t moduletype = Build_NowMenuItem->ItemType; // 获取当前组件类型

    switch (moduletype)
    {
    case ItemType_Switch:
        Build_ModuleControl_Switch_KEYevent();
        break;
    case ItemType_View:
        Build_ModuleControl_View_KEYevent();
        break;
    case ItemType_Slider:
        Build_ModuleControl_Slider_KEYevent();
        break;
    }
}

/**
 * @brief 组件控制选择性显示
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 组件控制的选择其一组件显示，取决于当前组件类型
 * @note 如果创建菜单项时，打开了实时活动，此时会：请求1次数据/500ms（仅支持视图型组件）
 */
void Build_ModuleControl_SelectDisplay(void)
{
    uint8_t module = Build_NowMenuItem->ItemType; // 获取当前菜单的组件类型

    switch (module)
    {
    case ItemType_Switch:
    {
        Menu_SwitchModule *switchmodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象指向当前菜单
        uint8_t *state = switchmodule->State;                             // 状态

        UI_Display_SwitchModule(Build_NowMenuItem->Title, state); // 渲染开关组件
    }
    break;

    case ItemType_View:
    {
        Menu_ViewModule *viewmodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象指向当前菜单
        int value = *viewmodule->Value;                               // 数值

        UI_Display_ViewModule(Build_NowMenuItem->Title, viewmodule->Description, &value); // 渲染视图组件
    }
    break;

    case ItemType_Slider:
    {
        Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象指向当前菜单
        int nowvalue = *slidermodule->NowValue;                           // 当前值
        int maxvalue = *slidermodule->MaxValue;                           // 最大值
        int minivalue = *slidermodule->MiniValue;                         // 最小值
        uint8_t *unit = slidermodule->Unit;

        UI_Display_SliderModule(Build_NowMenuItem->Title, &nowvalue, &maxvalue, &minivalue, unit, Build_CNT_SliderModule); // 渲染滑块组件
    }
    break;
    }
}

/**
 * @brief 组件实时活动数据更新
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 仅支持视图型组件
 */
void Build_ModuleControl_RealTime_Handle(void)
{
    // 确保当前处于组件页
    if (Build_NowPage != 4)
    {
        return;
    }

    // 仅视图型组件支持实时更新
    if (Build_NowMenuItem->ItemType != ItemType_View)
    {
        return;
    }

    Menu_ViewModule *viewmodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象是视图型组件
    uint8_t realtime_state = viewmodule->Data_RealTime;           // 获取实时活动状态

    // 判断是否开启实时活动
    if (realtime_state == ViewModule_DataRealTime_OFF)
    {
        return;
    }
    else
    {
        Build_RequestControl_ViewModule(); // 视图组件请求数据
        vTaskDelay(1000);                  // 等待1000ms
    }
}

/**
 * @brief 组件控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_ModuleControl(void)
{
    // 组件按键控制
    Build_ModuleControl_KEYevent();

    // 组件渲染
    Build_ModuleControl_SelectDisplay();
}

/**
 * @brief 开关组件上传数据
 *
 * @param 无
 *
 * @retval 1 上传成功
 * @retval 0 上传失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_UpdateControl_SwitchModule(void)
{
    uint8_t Result = 0; // 上传结果

    uint8_t *name = Build_NowMenuItem->Name;                          // 获取菜单项的名称
    Menu_SwitchModule *switchmodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的开关组件
    uint8_t *state = switchmodule->State;                             // 获取开关组件的当前状态

    Result = Update_SwitchModule(name, state); // 发起上传

    if (Result == 1)
    {
        // 获取成功
        return 1;
    }

    // 获取失败
    return 0;
}

/**
 * @brief 滑块组件上传数据
 *
 * @param 无
 *
 * @retval 1 上传成功
 * @retval 0 上传失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_UpdateControl_SliderModule(void)
{
    uint8_t Result = 0; // 上传结果

    uint8_t *name = Build_NowMenuItem->Name;                          // 获取菜单项的名称
    Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的滑块组件
    int *now = slidermodule->NowValue;                                // 获取组件的当前值
    int *max = slidermodule->MaxValue;                                // 获取组件的最大值
    int *mini = slidermodule->MiniValue;                              // 获取组件的最小值

    Result = Update_SliderModule(name, now, max, mini); // 发起上传

    if (Result == 1)
    {
        // 获取成功
        return 1;
    }

    // 获取失败
    return 0;
}

/**
 * @brief 发起上传
 *
 * @param 无
 *
 * @retval 1 获取成功
 * @retval 0 获取失败
 *
 * @note 汇总关联：实际存储的变量、请求函数、菜单链表
 */
uint8_t Build_UpdateControl_Uploading(void)
{
    uint8_t Result = 0;
    uint8_t module = Build_NowMenuItem->ItemType;

    switch (module)
    {
    case ItemType_Switch:
        Result = Build_UpdateControl_SwitchModule();
        break;

    case ItemType_View:
        // 视图组件无需上传数据
        break;

    case ItemType_Slider:
        Result = Build_UpdateControl_SliderModule();
        break;
    }

    if (Result == 1)
    {
        // 获取成功
        return 1;
    }

    // 获取失败
    return 0;
}

/**
 * @brief 上传控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_UpdateControl(void)
{
    uint8_t result = 0; // 上传结果

    UI_Display_Uploading(); // 渲染上传等待界面

    vTaskResume(TASK5_Handler);  // 恢复OLED刷新任务
    vTaskResume(TASK15_Handler); // 上传时按键控制

    result = Build_UpdateControl_Uploading(); // 开始上传，等待上传结果

    if (result == 0) // 上传失败
    {
        UI_Display_UpdateFail();    // 渲染上传失败界面
        vTaskResume(TASK5_Handler); // 恢复OLED刷新任务
    }
    else if (result == 1) // 上传成功
    {
        UI_Display_UpdateSuccess(); // 渲染上传成功界面
        vTaskResume(TASK5_Handler); // 恢复OLED刷新任务
    }

    // 等待3秒，挂起上传按键控制任务，切换到菜单页
    vTaskDelay(3000);
    vTaskSuspend(TASK15_Handler);
    Build_NowPage = 2;
}

/**
 * @brief 自定义页面控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 进入此页方法：菜单页面触发KEY1单击事件，且类型为ItemType_Custom
 * @note 详情：Build_PageSwitching()、Build_MenuControl_KEYevent()
 */
void Build_CustomControl(void)
{
    // 创建一个类型为<函数>的变量，并执行它
    void (*func)() = (void (*)())Build_NowMenuItem->Function;
    func();
}

/**
 * @brief 菜单构建控制汇总
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 在主页单独加了是否为"手动控制"的判断
 * @note 在菜单页单独加了是否为"系统设置"的判断
 */
void Build_ControlPro(void)
{
    if (Build_NowPage == 6)
    {
        // 当前页：自定义页
        Build_CustomControl();
    }

    if (Build_NowPage == 2)
    {
        // 当前页：菜单页
        Build_MenuControl();
    }

    if (Build_NowPage == 1)
    {
        // 当前页：主页
        Build_HomeControl();
    }

    if (Build_NowPage == 3)
    {
        // 当前页：请求页
        Build_RequestControl();
    }

    if (Build_NowPage == 4)
    {
        // 当前页：组件页
        Build_ModuleControl();
    }

    if (Build_NowPage == 5)
    {
        // 当前页：上传页
        Build_UpdateControl();
    }
}

/**
 * @brief 菜单构建初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_InitPro(void)
{
    // 选定默认主页项
    Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, 1);
}
