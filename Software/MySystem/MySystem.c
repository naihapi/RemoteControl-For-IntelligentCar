#include "MySystem.h"

/**
 * @brief 系统配置初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_InitPro(void)
{
}

/**
 * @brief OLED深浅模式配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_DarkColor(void)
{
    switch (State_OLEDMode)
    {
    case 0:
        // 深色模式
        OLED_WriteCommand(0xA6);
        break;

    case 1:
        // 浅色模式
        OLED_WriteCommand(0xA7);
        break;
    }
}

/**
 * @brief OLED亮度配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_Brightness(void)
{
    switch (Value_OLED_NowBrightness)
    {
    case 1:
        // 亮度暗
        OLED_WriteCommand(0x81);
        OLED_WriteCommand(0x01);
        break;

    case 2:
        // 亮度中等
        OLED_WriteCommand(0x81);
        OLED_WriteCommand(0x32);
        break;

    case 3:
        // 亮度高
        OLED_WriteCommand(0x81);
        OLED_WriteCommand(0xFF);
        break;
    }
}

/**
 * @brief OLED左右方向配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_DirectionLR(void)
{
    switch (State_OLEDDirection_LR)
    {
    case 0:
        // 正常
        OLED_WriteCommand(0xA1);
        break;

    case 1:
        // 反置
        OLED_WriteCommand(0xA0);
        break;
    }
}

/**
 * @brief OLED上下方向配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_DirectionTB(void)
{
    switch (State_OLEDDirection_TB)
    {
    case 0:
        // 正常
        OLED_WriteCommand(0xC8);
        break;

    case 1:
        // 反置
        OLED_WriteCommand(0xC0);
        break;
    }
}

/**
 * @brief OLED配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 在OLED.c文件的Update函数内调用
 */
void MySystem_OLED_Function(void)
{
    MySystem_OLED_DarkColor();
    MySystem_OLED_Brightness();
    MySystem_OLED_DirectionLR();
    MySystem_OLED_DirectionTB();
}

/**
 * @brief 获取RTOS的剩余堆空间
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数需要全速运行
 */
void MySystem_GetFreeHeap(void)
{
    Value_FreeHeap = xPortGetFreeHeapSize();
}
