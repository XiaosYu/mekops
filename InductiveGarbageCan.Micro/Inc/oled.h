#ifndef __OLED_H
#define __OLED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"

void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void);

void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, char *chr,uint8_t size);	 

void OLED_Init(void);

#ifdef __cplusplus
}
#endif

#endif  
