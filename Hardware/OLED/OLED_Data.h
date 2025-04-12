#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*中文字符字节宽度*/
#define OLED_CHN_CHAR_WIDTH 3 // UTF-8编码格式给3，GB2312编码格式给2

/*字模基本单元*/
typedef struct
{
	char Index[OLED_CHN_CHAR_WIDTH + 1]; // 汉字索引
	uint8_t Data[32];					 // 字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t OLED_CF16x16[];

/*图像数据声明*/
extern const uint8_t Diode[];
extern const uint8_t OLEDData_Icon_Welcome[];
extern const uint8_t OLEDData_Icon_LEDfront[];
extern const uint8_t OLEDData_Icon_LEDbottom[];
extern const uint8_t OLEDData_Icon_UltraSound[];
extern const uint8_t OLEDData_Icon_Home_Light[];
extern const uint8_t OLEDData_Icon_Home_Sensor[];
extern const uint8_t OLEDData_Icon_Home_View[];
extern const uint8_t OLEDData_Icon_Home_Cruise[];
extern const uint8_t OLEDData_Icon_Home_Circle[];
extern const uint8_t OLEDData_Icon_Home_System[];
extern const uint8_t OLEDData_Icon_Display[];
extern const uint8_t OLEDData_Icon_Brightness[];
extern const uint8_t OLEDData_Icon_DirLR[];
extern const uint8_t OLEDData_Icon_DirTB[];
extern const uint8_t OLEDData_Icon_Request[];
extern const uint8_t OLEDData_Icon_RequestSuccess[];
extern const uint8_t OLEDData_Icon_RequestFail[];
extern const uint8_t OLEDData_Icon_Speed[];
extern const uint8_t OLEDData_Icon_Cruise[];
extern const uint8_t OLEDData_Icon_FreeHeap[];
extern const uint8_t OLEDData_Icon_Manual[];
extern const uint8_t OLEDData_ManualCorner[];
extern const uint8_t OLEDData_ManualLeft[];
extern const uint8_t OLEDData_ManualRitght[];
extern const uint8_t OLEDData_ManualFront[];
extern const uint8_t OLEDData_ManualRear[];
extern const uint8_t OLEDData_Exit[];
extern const uint8_t OLEDData_Into[];
extern const uint8_t OLEDData_Icon_Home_Normal[];
/*按照上面的格式，在这个位置加入新的图像数据声明*/
//...

#endif

/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
