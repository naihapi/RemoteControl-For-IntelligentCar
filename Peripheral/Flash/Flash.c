#include "Flash.h"

uint16_t FlashData[Flash_DataLength];

/**
 * @brief flash读1个半字
 *
 * @param Addr 地址
 *
 * @retval 无
 *
 * @note 无
 */
uint16_t Flash_ReadHalfWord(uint32_t Addr)
{
    return *((__IO uint16_t *)(Addr));
}

/**
 * @brief flash写数据
 *
 * @param Addr 地址
 * @param Data 1个半字
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_WriteHalfWord(uint32_t Addr, uint16_t Data)
{
    FLASH_Unlock();
    FLASH_ProgramHalfWord(Addr, Data);
    FLASH_Lock();
}

/**
 * @brief flash页擦除
 *
 * @param PageAddr 页地址
 *
 * @retval 无
 *
 * @note 新开一页时，最后调用一下此函数
 * @note 可以由1写0，覆写数据时不能由0写1;如果需要由0写1，只能整页擦除
 */
void Flash_ErasePage(uint32_t PageAddr)
{
    FLASH_Unlock();
    FLASH_ErasePage(PageAddr);
    FLASH_Lock();
}

/**
 * @brief flash写数组
 *
 * @param Addr 地址
 * @param Data 数据
 * @param Length 数组长度
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_WriteBuffer(uint32_t Addr, uint16_t *Data, uint16_t Length)
{
    for (uint16_t i = 0; i < Length; i++)
    {
        Flash_WriteHalfWord(Addr + i * 2, Data[i]);
    }
}

/**
 * @brief flash读取数组
 *
 * @param Addr 地址
 * @param Buffer 数组
 * @param Length 数组长度
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_ReadBuffer(uint32_t Addr, uint16_t *Buffer, uint16_t Length)
{
    for (uint16_t i = 0; i < Length; i++)
    {
        Buffer[i] = Flash_ReadHalfWord(Addr + i * 2);
    }
}

/**
 * @brief 恢复数据到全局变量
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_RecoverData(void)
{
    Flash_ReadBuffer(Flash_Address_EndPage, FlashData, Flash_DataLength); // 读取数据到Flash数组

    // 读取Flash数组到全局变量
    Value_OLED_NowBrightness = FlashData[0];
    Value_OLED_MaxBrightness = FlashData[1];
    Value_OLED_MiniBrightness = FlashData[2];
    State_OLEDMode = FlashData[3];
    State_OLEDDirection_LR = FlashData[4];
    State_OLEDDirection_TB = FlashData[5];
}

/**
 * @brief 保存数据到Flash
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_SavaData(void)
{
    Flash_ErasePage(Flash_Address_EndPage); // 擦除最后一页

    // 保存数据到Flash数组
    FlashData[0] = Value_OLED_NowBrightness;
    FlashData[1] = Value_OLED_MaxBrightness;
    FlashData[2] = Value_OLED_MiniBrightness;
    FlashData[3] = State_OLEDMode;
    FlashData[4] = State_OLEDDirection_LR;
    FlashData[5] = State_OLEDDirection_TB;

    // 保存数据到Flash
    Flash_WriteBuffer(Flash_Address_EndPage, FlashData, Flash_DataLength);
}

/**
 * @brief flash初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 每次开机时,都初始化数据
 */
void FLash_InitPro(void)
{
    //Flash_SavaData();    // 数据意外丢失时，请解除本行注释并烧写一次！
    Flash_RecoverData(); // 恢复数据
}
