#ifndef _Menu_H
#define _Menu_H

// 标准库
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// MCU型号
#include "stm32f10x.h"

// 外设
#include "Flash.h"

// 外置硬件
#include "OLED.h"

// 软件
#include "POST.h"
#include "Manual.h"

// 宏定义
#define ItemType_Switch 1             // 菜单项类型-开关型
#define ItemType_Slider 2             // 菜单项类型-滑块型
#define ItemType_View 3               // 菜单项类型-视图型
#define ItemType_Custom 4             // 菜单项类型-自定义型
#define Datahandle_None 0             // 数据处理方式-无
#define DataHandle_OnlyRequest 1      // 数据处理方式-仅请求
#define DataHandle_OnlyUpdate 2       // 数据处理方式-仅上传
#define DataHandle_UpdateANDRequest 3 // 数据处理方式-请求和上传都需要
#define SliderModule_YesSetting 1     // 滑块型组件-允许跳转最大、最小值的设置
#define SliderModule_NotSetting 0     // 滑块型组件-不允许跳转最大、最小值的设置
#define ViewModule_DataRealTime_ON 1  // 视图型组件-打开数据实时更新
#define ViewModule_DataRealTime_OFF 0 // 视图型组件-关闭数据实时更新

// 菜单（1个菜单项所包含的信息）
typedef struct MenuItem
{
    const uint8_t *Icon;   // 图标路径
    uint8_t *Title;        // 菜单项标题
    uint8_t ItemType;      // 菜单项类型(ItemType_xxx)
    void *Function;        // 指向一个函数
    void *ItemPointer;     // 具体组件数据(Menu_xxxModule)
    uint8_t DataHandle;    // 是否需要数据处理(DataHandle_xxx)
    uint8_t *Name;         // 外置硬件的名称
    struct MenuItem *Last; // 指向上一个菜单项
    struct MenuItem *Next; // 指向下一个菜单项
} MenuItem;

// 主页（1个主页项所包含的信息）
typedef struct MenuHome
{
    const uint8_t *Icon;   // 图标路径
    uint8_t *Title;        // 主页标题
    struct MenuItem *Menu; // 主页选定的菜单
    int8_t *MaxItem;       // 主页选定的菜单项最大个数
    struct MenuHome *Last; // 指向上一个主页项的指针
    struct MenuHome *Next; // 指向下一个主页项的指针
} MenuHome;

// 开关型组件（1个开关型组件项所包含的信息）
typedef struct Menu_SwitchModule
{
    uint8_t *State; // 指向开关状态的指针
} Menu_SwitchModule;

// 视图型组件（1个视图型组件所包含的信息）
typedef struct Menu_ViewModule
{
    uint8_t *Description;  // 描述信息
    int *Value;            // 数值
    uint8_t Data_RealTime; // 实时活动(ViewModule_DataRealTime_xxx)
} Menu_ViewModule;

// 滑块型组件（1个滑块型组件所包含的信息）
typedef struct Menu_SliderModule
{
    int *NowValue;   // 指向当前值
    int *MaxValue;   // 指向最大值
    int *MiniValue;  // 指向最小值
    uint8_t Setting; // 是否可以调整最大、最小值(SliderModule_xxxSetting)
    uint8_t *Unit;   // 单位
} Menu_SliderModule;

// 变量
extern int8_t Menu_MaxItem_Home;
extern int8_t Menu_MaxItem_Light;
extern int8_t Menu_MaxItem_Sensor;
extern int8_t Menu_MaxItem_Cruise;
extern MenuHome *Menu_Head_Home;
extern MenuItem *Menu_Head_Light;
extern MenuItem *Menu_Head_Sensor;
extern MenuItem *Menu_Head_Cruise;
extern MenuItem *Menu_Head_Circle;
extern uint8_t Menu_Title_System[];
extern uint8_t State_OLEDDirection_LR;
extern uint8_t State_OLEDDirection_TB;
extern uint8_t State_Reset;
extern int Value_OLED_NowBrightness;
extern int Value_OLED_MaxBrightness;
extern int Value_OLED_MiniBrightness;
extern int Value_FreeHeap;

// API
void Menu_InitPro(void);
MenuHome *Menu_RetHomeItem(MenuHome *Head, uint8_t item);
MenuItem *Menu_RetMenuItem(MenuItem *Head, uint8_t item);

#endif
