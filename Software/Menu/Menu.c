#include "Menu.h"

/*---菜单项名称(标题、请求体)---*/
uint8_t Name_LEDFront[] = "LEDFront";         // 前车灯
uint8_t Name_LEDRear[] = "LEDRear";           // 后车灯
uint8_t Name_UltraSound[] = "UltraSound";     // 超声波
uint8_t Name_CruiseSpeed[] = "CruiSpeed";     // 定速巡航最大速度
uint8_t Name_CruiseState[] = "CruiState";     // 定速巡航状态
uint8_t Name_OLEDMode[] = "Display";          // 系统-OLED显示模式
uint8_t Name_OLEDBrightness[] = "Brightness"; // 系统-OLED亮度
uint8_t Name_OLEDDirection_LR[] = "Dir-LR";   // 系统-OLED左右方向
uint8_t Name_OLEDDirection_TB[] = "Dir-TB";   // 系统-OLED上下方向
uint8_t Name_FreeHeap[] = "FreeHeap";         // 剩余堆空间
uint8_t Name_Manual[] = "Manual";             // 手动控制
/*---菜单项名称(标题、请求体)---*/

/*---状态(开关组件)---*/
uint8_t State_LedFront = 0;         // 前车灯（0：关闭，1：开启）
uint8_t State_LEDRear = 0;          // 后车灯（0：关闭，1：开启）
uint8_t State_UltraSound = 0;       // 超声波（0：关闭，1：开启）
uint8_t State_CruiseState = 0;      // 定速巡航（0：静止，1：执行）
uint8_t State_OLEDMode = 0;         // 系统-OLED显示模式（0：深色系，1：浅色系）
uint8_t State_OLEDDirection_LR = 0; // 系统-OLED显示左右方向（0：正常，1：左右反置）
uint8_t State_OLEDDirection_TB = 0; // 系统-OLED显示上下方向（0：正常，1：上下反置）
/*---状态(开关组件)---*/

/*---数值(视图组件|滑块组件)---*/
int Value_UltraSound_Distance = 0; // 超声波距离
int Value_Cruise_NowSpeed = 0;     // 选择的速度
int Value_Cruise_MaxSpeed = 0;     // 可选的最大速度
int Value_Cruise_MiniSpeed = 0;    // 可选的最小速度
int Value_OLED_NowBrightness = 2;  // 系统-OLED当前亮度
int Value_OLED_MaxBrightness = 3;  // 系统-OLED可调节的最大亮度
int Value_OLED_MiniBrightness = 1; // 系统-OLED可调节的最小亮度
int Value_FreeHeap = 0;            // 系统-剩余堆空间
/*---数值(视图组件|滑块组件)---*/

/*---单位(滑块组件)---*/
uint8_t Unit_Cruise_Speed[] = "cm/s";        // 定速画圆速度单位
uint8_t Unit_OLED_BrightnessGear[] = "Gear"; // 系统-OLED亮度档位
/*---单位(滑块组件)---*/

/*---描述(视图组件)---*/
uint8_t Description_UltraSound[] = "cm"; // 超声波距离
uint8_t Description_FreeHeap[] = "Byte"; // 系统-剩余堆字节
/*---描述(视图组件)---*/

/*---主页项标题---*/
uint8_t Menu_Title_System[] = {"System"}; // 系统
uint8_t Menu_Title_Light[] = {"LIGHT"};   // 灯光
uint8_t Menu_Title_Sensor[] = {"SENSOR"}; // 传感器
uint8_t Menu_Title_Cruise[] = {"CRUISE"}; // 定速巡航
uint8_t Menu_Title_Circle[] = {"CIRCLE"}; // 定速画圆
uint8_t Menu_Title_Normal[] = {"NORMAL"}; // 普通
/*---主页项标题---*/

/*---最大项---*/
int8_t Menu_MaxItem_Home = 0;   // 主页-最大值
int8_t Menu_MaxItem_Light = 0;  // 控制菜单-最大值
int8_t Menu_MaxItem_Sensor = 0; // 视图菜单-最大值
int8_t Menu_MaxItem_Cruise = 0; // 定速巡航菜单-最大值
int8_t Menu_MaxItem_System = 0; // 系统菜单-最大值
int8_t Menu_MaxItem_Normal = 0; // 普通菜单-最大值
/*---最大项---*/

/*---链表头---*/
MenuHome *Menu_Head_Home;   // 主页
MenuItem *Menu_Head_Light;  // 控制菜单
MenuItem *Menu_Head_Sensor; // 视图菜单
MenuItem *Menu_Head_Cruise; // 定速巡航菜单
MenuItem *Menu_Head_System; // 系统菜单
MenuItem *Menu_Head_Circle; // 定速画圆菜单
MenuItem *Menu_Head_Normal; // 普通菜单
/*---链表头---*/

/**
 * @brief 创建1个主页项
 *
 * @param icon 图标
 * @param title 标题
 * @param menu 菜单链表头
 * @param maxitem 菜单最大个数
 *
 * @retval 返回主页项
 * @retval 创建失败返回NULL
 *
 * @note 分配内存以创建主页项
 * @note 由于创建链表头时无数据传入，因此不检查函数参数
 */
MenuHome *Menu_CreateHomeItem(const uint8_t *icon, uint8_t *title, MenuItem *menu, int8_t *maxitem)
{
    // 为<主页结构体>分配内存
    MenuHome *Item = (MenuHome *)malloc(sizeof(MenuHome));
    if (Item == NULL)
        return NULL;

    Item->Icon = icon;       // 图标
    Item->Title = title;     // 标题
    Item->Menu = menu;       // 菜单
    Item->MaxItem = maxitem; // 最大项

    // Menu_MaxItem_Home += 1;

    return Item;
}

/**
 * @brief 创建1个菜单项
 *
 * @param icon 图标
 * @param title 标题
 * @param type 菜单类型：ItemType_xxx
 * @param pointer 具体组件：Menu_xxxModule
 * @param datahandle 数据处理标志位：DataHandle_xxx
 * @param name 硬件名称
 *
 * @retval 返回1个菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>的<标题Title>和<名称name>取决于<函数参数name>
 */
MenuItem *Menu_CreateItem(const uint8_t *icon, uint8_t type, void *function, void *pointer, uint8_t datahandle, uint8_t *name)
{
    // 为<菜单结构体>分配内存
    MenuItem *Item = (MenuItem *)malloc(sizeof(MenuItem));
    if (Item == NULL)
        return NULL;

    Item->Icon = icon;             // 图标
    Item->Title = name;            // 标题取决于硬件名称
    Item->ItemType = type;         // 组件类型
    Item->Function = function;     // 函数
    Item->ItemPointer = pointer;   // 组件数据
    Item->DataHandle = datahandle; // 数据处理
    Item->Name = name;             // 名称

    return Item;
}

/**
 * @brief 创建1个开关型组件
 *
 * @param state 开关状态
 *
 * @retval 返回1个开关组件
 * @retval 创建失败返回NULL
 *
 * @note 无
 */
Menu_SwitchModule *Mneu_CreateSwitchModule(uint8_t *state)
{
    // 为<开关型组件结构体>分配内存
    Menu_SwitchModule *SwitchData = (Menu_SwitchModule *)malloc(sizeof(Menu_SwitchModule));
    if (SwitchData == NULL)
        return NULL;

    SwitchData->State = state; // 开关状态

    return SwitchData;
}

/**
 * @brief 创建1个视图型组件
 *
 * @param description 描述信息
 * @param value 数值
 * @param realtime 实时活动标志位：ViewModule_DataRealTime_xxx
 *
 * @retval 返回1个视图组件
 * @retval 创建失败返回NULL
 *
 * @note 无
 */
Menu_ViewModule *Menu_CreateViewModule(uint8_t *description, int *value, uint8_t realtime)
{
    // 为<视图型组件结构体>分配内存
    Menu_ViewModule *ViewData = (Menu_ViewModule *)malloc(sizeof(Menu_ViewModule));
    if (ViewData == NULL)
        return NULL;

    ViewData->Description = description; // 信息描述
    ViewData->Value = value;             // 数据值
    ViewData->Data_RealTime = realtime;  // 实时活动

    return ViewData;
}

/**
 * @brief 创建1个滑块型组件
 *
 * @param nowvalue 描述信息
 * @param maxvalue 最大值
 * @param minivalue 最小值
 * @param setting 调整限幅值(SliderModule_xxxSetting)
 * @param unit 单位
 *
 * @retval 返回1个滑块组件
 * @retval 创建失败返回NULL
 *
 * @note 无
 */
Menu_SliderModule *Menu_CreateSliderModule(int *nowvalue, int *maxvalue, int *minivalue, uint8_t setting, uint8_t *unit)
{
    // 为<滑块型组件结构体>分配内存
    Menu_SliderModule *SliderData = (Menu_SliderModule *)malloc(sizeof(Menu_SliderModule));
    if (SliderData == NULL)
        return NULL;

    SliderData->NowValue = nowvalue;   // 当前值
    SliderData->MaxValue = maxvalue;   // 最大值
    SliderData->MiniValue = minivalue; // 最小值
    SliderData->Setting = setting;     // 限幅设置
    SliderData->Unit = unit;

    return SliderData;
}

/**
 * @brief 创建1个开关型菜单项
 *
 * @param icon 图标
 * @param name 硬件名称
 * @param state 状态(1或0)
 * @param datahandle 数据处理标志位：DataHandle_xxx
 *
 * @retval 返回1个开关型菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>和<开关型组件结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateSwitchItem(const uint8_t *icon, uint8_t *name, uint8_t *state, uint8_t datahandle)
{
    // 创建<开关型组件结构体>
    Menu_SwitchModule *SwitchData = Mneu_CreateSwitchModule(state);
    if (SwitchData == NULL)
        return NULL;

    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_Switch, NULL, SwitchData, datahandle, name);
    if (SwitchData == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 创建1个视图型菜单项
 *
 * @param icon 图标
 * @param name 硬件名称
 * @param description 描述符
 * @param value 数值
 * @param datahandle 数据处理标志位：DataHandle_xxx
 * @param realtime 实时活动标志位：ViewModule_DataRealTime_xxx
 *
 * @retval 返回1个视图型菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>和<视图型组件结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateViewItem(const uint8_t *icon, uint8_t *name, uint8_t *description, int *value, uint8_t datahandle, uint8_t realtime)
{
    // 创建<视图型组件结构体>
    Menu_ViewModule *ViewData = Menu_CreateViewModule(description, value, realtime);
    if (ViewData == NULL)
        return NULL;

    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_View, NULL, ViewData, datahandle, name);
    if (Item == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 创建1个滑块型菜单项
 *
 * @param icon 图标
 * @param name 硬件名称
 * @param nowvalue 当前值
 * @param maxvalue 最大值
 * @param minivalue 最小值
 * @param unit 单位
 * @param setting 调整限幅值(SliderModule_xxxSetting)
 * @param datahandle 数据处理标志位：DataHandle_xxx
 *
 * @retval 返回1个视图型菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>和<视图型组件结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateSliderItem(const uint8_t *icon, uint8_t *name, int *nowvalue, int *maxvalue, int *minivalue, uint8_t *unit, uint8_t setting, uint8_t datahandle)
{
    // 创建<滑块型组件结构体>
    Menu_SliderModule *SliderData = Menu_CreateSliderModule(nowvalue, maxvalue, minivalue, setting, unit);
    if (SliderData == NULL)
        return NULL;

    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_Slider, NULL, SliderData, datahandle, name);
    if (Item == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 创建1个自定义型菜单项
 *
 * @param icon 图标
 * @param name 名称
 * @param function 函数
 *
 * @retval 返回1个自定义型菜单项
 * @retval 创建失败返回NULL
 *
 * @note function参数为函数地址，函数返回值为void
 * @note <菜单结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateCustomItem(const uint8_t *icon, uint8_t *name, void *function)
{
    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_Custom, function, NULL, Datahandle_None, name);
    if (Item == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 获取指定的主页项
 *
 * @param Head 主页链表头
 * @param item 选择的项(从1开始)
 *
 * @retval 返回指定项
 * @retval 获取失败返回NULL
 *
 * @note 已跳过头节点
 */
MenuHome *Menu_RetHomeItem(MenuHome *Head, uint8_t item)
{
    if (Head == NULL || item <= 0)
        return NULL;

    uint8_t count = 1;              // 查询主页项计数
    MenuHome *current = Head->Next; // 跳过头节点

    // 遍历链表
    while (current != NULL)
    {
        if (item == count)
        {
            return current;
        }

        count++;                 // 计数自增，直到与item相等
        current = current->Next; // 查询下一项
    }
    return 0;
}

/**
 * @brief 获取指定的菜单项
 *
 * @param Head 菜单链表头
 * @param item 选择的项(从1开始)
 *
 * @retval 返回指定项
 * @retval 获取失败返回NULL
 *
 * @note 已跳过头节点
 */
MenuItem *Menu_RetMenuItem(MenuItem *Head, uint8_t item)
{
    if (Head == NULL || item <= 0)
        return NULL;

    uint8_t count = 1;              // 查询菜单项计数
    MenuItem *current = Head->Next; // 跳过头节点

    // 遍历链表
    while (current != NULL)
    {
        if (item == count)
        {
            return current;
        }

        count++;                 // 计数自增，直到与item相等
        current = current->Next; // 查询下一项
    }

    return NULL;
}

/**
 * @brief 获取主页最大项
 *
 * @param head 主页链表头
 *
 * @retval 返回菜单个数
 *
 * @note 无
 */
int8_t Menu_GetHomeMaxItem(MenuHome *head)
{
    int8_t maxitem = 0;
    MenuHome *current = head->Next; // 从头节点的下一个节点开始计数

    while (current != NULL)
    {
        maxitem += 1;
        current = current->Next;
    }

    return maxitem;
}

/**
 * @brief 获取菜单最大项
 *
 * @param head 菜单链表头
 *
 * @retval 返回菜单个数
 *
 * @note 无
 */
int8_t Menu_GetMenuMaxItem(MenuItem *head)
{
    int8_t maxitem = 0;
    MenuItem *current = head->Next; // 从头节点的下一个节点开始计数

    while (current != NULL)
    {
        maxitem += 1;
        current = current->Next;
    }

    return maxitem;
}

/**
 * @brief 获取主页最后一项
 *
 * @param head 主页链表头
 *
 * @retval 返回主页项
 *
 * @note 无
 */
MenuHome *Menu_GetHomeEndItem(MenuHome *head)
{
    MenuHome *current = head;

    while (current->Next != NULL)
    {
        current = current->Next;
    }

    return current;
}

/**
 * @brief 获取菜单最后一项
 *
 * @param head 菜单链表头
 *
 * @retval 返回菜单项
 *
 * @note 无
 */
MenuItem *Menu_GetMenuEndItem(MenuItem *head)
{
    MenuItem *current = head;

    while (current->Next != NULL)
    {
        current = current->Next;
    }

    return current;
}

/**
 * @brief 菜单项互指
 *
 * @param nowitem 当前项
 * @param lastitem 上一项
 * @param nextitem 下一项
 *
 * @retval 无
 *
 * @note 小记：双指针是指向指针的指针
 * @note 利用双指针，改变单指针所指向的地方
 * @note 互指：上一项的Next指向下一项，下一项的Last指向上一项
 */
void Menu_ItemEachOther(MenuItem **nowitem, MenuItem *lastitem, MenuItem *nextitem)
{
    (*nowitem)->Next = nextitem;
    (*nowitem)->Last = lastitem;
}

/**
 * @brief 主页项包含到主页头
 *
 * @param head 主页链表头
 * @param item 主页项
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_Include_HomeItem(MenuHome *head, MenuHome *item)
{
    MenuHome *current = Menu_GetHomeEndItem(head);

    current->Next = item;
    item->Last = current;
    item->Next = NULL;
}

/**
 * @brief 菜单项包含到菜单头
 *
 * @param head 菜单链表头
 * @param item 菜单项
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_Include_MenuItem(MenuItem *head, MenuItem *item)
{
    MenuItem *current = Menu_GetMenuEndItem(head);

    current->Next = item;
    item->Last = current;
    item->Next = NULL;
}

/**
 * @brief 创建一个主页头
 *
 * @param 无
 *
 * @retval 返回主页头
 *
 * @note 无
 */
MenuHome *Menu_CreateHomeHead(void)
{
    MenuHome *Head = Menu_CreateHomeItem(NULL, NULL, NULL, NULL);
    return Head;
}

/**
 * @brief 创建一个菜单头
 *
 * @param title 菜单标题
 *
 * @retval 返回菜单头
 *
 * @note 无
 */
MenuItem *Menu_CreateMenuHead(uint8_t *title)
{
    MenuItem *Head = Menu_CreateItem(NULL, NULL, NULL, NULL, NULL, title);
    return Head;
}

/**
 * @brief 创建主页
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateHome(void)
{
    // 创建主页头
    Menu_Head_Home = Menu_CreateHomeHead();

    // 创建项
    MenuHome *system = Menu_CreateHomeItem(OLEDData_Icon_Home_System, Menu_Title_System, Menu_Head_System, &Menu_MaxItem_System);
    MenuHome *normal = Menu_CreateHomeItem(OLEDData_Icon_Home_Normal, Menu_Title_Normal, Menu_Head_Normal, &Menu_MaxItem_Normal);
    MenuHome *light = Menu_CreateHomeItem(OLEDData_Icon_Home_Light, Menu_Title_Light, Menu_Head_Light, &Menu_MaxItem_Light);
    MenuHome *sensor = Menu_CreateHomeItem(OLEDData_Icon_Home_Sensor, Menu_Title_Sensor, Menu_Head_Sensor, &Menu_MaxItem_Sensor);
    MenuHome *cruise = Menu_CreateHomeItem(OLEDData_Icon_Home_Cruise, Menu_Title_Cruise, Menu_Head_Cruise, &Menu_MaxItem_Cruise);

    // 菜单头包含
    Menu_Include_HomeItem(Menu_Head_Home, system);
    Menu_Include_HomeItem(Menu_Head_Home, normal);
    Menu_Include_HomeItem(Menu_Head_Home, light);
    Menu_Include_HomeItem(Menu_Head_Home, sensor);
    Menu_Include_HomeItem(Menu_Head_Home, cruise);
}

/**
 * @brief 创建“灯光”菜单
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateLight(void)
{
    // 创建菜单头
    Menu_Head_Light = Menu_CreateMenuHead(Menu_Title_Light);

    // 创建项
    MenuItem *ledfront = Menu_CreateSwitchItem(OLEDData_Icon_LEDfront, Name_LEDFront, &State_LedFront, DataHandle_UpdateANDRequest);
    MenuItem *ledrear = Menu_CreateSwitchItem(OLEDData_Icon_LEDbottom, Name_LEDRear, &State_LEDRear, DataHandle_UpdateANDRequest);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_Light, ledfront);
    Menu_Include_MenuItem(Menu_Head_Light, ledrear);
}

/**
 * @brief 创建“传感器”菜单
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateSensor(void)
{
    // 创建菜单头
    Menu_Head_Sensor = Menu_CreateMenuHead(Menu_Title_Sensor);

    // 创建项
    MenuItem *ultra = Menu_CreateViewItem(OLEDData_Icon_UltraSound, Name_UltraSound, Description_UltraSound, &Value_UltraSound_Distance, DataHandle_OnlyRequest, ViewModule_DataRealTime_ON);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_Sensor, ultra);
}

/**
 * @brief 创建“定速巡航”菜单
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateCruise(void)
{
    // 创建菜单头
    Menu_Head_Cruise = Menu_CreateMenuHead(Menu_Title_Cruise);

    // 创建项
    MenuItem *speed = Menu_CreateSliderItem(OLEDData_Icon_Speed, Name_CruiseSpeed, &Value_Cruise_NowSpeed, &Value_Cruise_MaxSpeed, &Value_Cruise_MiniSpeed, Unit_Cruise_Speed, SliderModule_NotSetting, DataHandle_UpdateANDRequest); // 创建“速度”项
    MenuItem *ultra = Menu_CreateSwitchItem(OLEDData_Icon_UltraSound, Name_UltraSound, &State_UltraSound, DataHandle_UpdateANDRequest);                                                                                               // 创建“超声波”项
    MenuItem *cruise = Menu_CreateSwitchItem(OLEDData_Icon_Cruise, Name_CruiseState, &State_CruiseState, DataHandle_UpdateANDRequest);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_Cruise, speed);
    Menu_Include_MenuItem(Menu_Head_Cruise, ultra);
    Menu_Include_MenuItem(Menu_Head_Cruise, cruise);
}

/**
 * @brief 创建“系统设置”菜单
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateSystem(void)
{
    // 创建菜单头
    Menu_Head_System = Menu_CreateMenuHead(Menu_Title_System);

    // 创建项
    MenuItem *mode = Menu_CreateSwitchItem(OLEDData_Icon_Display, Name_OLEDMode, &State_OLEDMode, SliderModule_NotSetting);
    MenuItem *brightness = Menu_CreateSliderItem(OLEDData_Icon_Brightness, Name_OLEDBrightness, &Value_OLED_NowBrightness, &Value_OLED_MaxBrightness, &Value_OLED_MiniBrightness, Unit_OLED_BrightnessGear, SliderModule_NotSetting, Datahandle_None);
    MenuItem *dirlr = Menu_CreateSwitchItem(OLEDData_Icon_DirLR, Name_OLEDDirection_LR, &State_OLEDDirection_LR, Datahandle_None);
    MenuItem *dirtb = Menu_CreateSwitchItem(OLEDData_Icon_DirTB, Name_OLEDDirection_TB, &State_OLEDDirection_TB, Datahandle_None);
    MenuItem *heap = Menu_CreateViewItem(OLEDData_Icon_FreeHeap, Name_FreeHeap, Description_FreeHeap, &Value_FreeHeap, Datahandle_None, ViewModule_DataRealTime_OFF);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_System, mode);
    Menu_Include_MenuItem(Menu_Head_System, brightness);
    Menu_Include_MenuItem(Menu_Head_System, dirlr);
    Menu_Include_MenuItem(Menu_Head_System, dirtb);
    Menu_Include_MenuItem(Menu_Head_System, heap);
}

/**
 * @brief 创建“普通”菜单
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateNormal(void)
{
    // 创建菜单头
    Menu_Head_Normal = Menu_CreateMenuHead(Menu_Title_Normal);

    // 创建项
    MenuItem *manual = Menu_CreateCustomItem(OLEDData_Icon_Manual, Name_Manual, Manual_CustomFunction);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_Normal, manual);
}

/**
 * @brief 计算菜单最大项
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_MaxItem_Init(void)
{
    Menu_MaxItem_Light = Menu_GetMenuMaxItem(Menu_Head_Light);
    Menu_MaxItem_Sensor = Menu_GetMenuMaxItem(Menu_Head_Sensor);
    Menu_MaxItem_Cruise = Menu_GetMenuMaxItem(Menu_Head_Cruise);
    Menu_MaxItem_System = Menu_GetMenuMaxItem(Menu_Head_System);
    Menu_MaxItem_Home = Menu_GetHomeMaxItem(Menu_Head_Home);
    Menu_MaxItem_Normal = Menu_GetMenuMaxItem(Menu_Head_Normal);
}

/**
 * @brief 菜单创建初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_CreateItem_Init(void)
{
    Menu_CreateLight();  // 创建“灯光”菜单
    Menu_CreateSensor(); // 创建“传感器”菜单
    Menu_CreateCruise(); // 创建“定速巡航”菜单
    Menu_CreateSystem(); // 创建“系统”菜单
    Menu_CreateNormal(); // 创建“普通”菜单

    Menu_CreateHome(); // 创建主页
}

/**
 * @brief 菜单初始化汇总
 *
 * @param 无
 * @param 无
 *
 * @retval 无
 *
 * @note 小记：单指针是直接指到实际变量的地址，而不是下一个指针
 * @note 包括创建主页链表、各种菜单...
 * @note 应当先创建菜单，否则创建主页函数时，menu参数无法关联到菜单链表
 * @note 此函数应当在主函数调用，如果在任务内初始化会导致栈空间不足
 */
void Menu_InitPro(void)
{
    Menu_CreateItem_Init();
    Menu_MaxItem_Init();
}
